/* 
    Name: main.c
    Project: Hadbrake Firmware
    Author: Christoph Honal
 */

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "usbdrv.h"
#include "osccal.h"

/*
    PB3 = analog input (ADC3)
    PB0, PB2 = USB data lines
*/

static uchar reportBuffer[4]; //buffer for HID reports
static uchar idleRate; //in 4 ms units
static uint16_t adc_value = 0; //last value of adv

#pragma region USB Definitions

const PROGMEM char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {
    /* USB report descriptor */
   	0x05, 0x01,     // USAGE_PAGE (Generic Desktop)
	0x09, 0x05,     // USAGE (Game Pad)
	0xa1, 0x01,     // COLLECTION (Application)
	0x09, 0x01,     //   USAGE (Pointer)
	0xa1, 0x00,     //   COLLECTION (Physical)
	0x09, 0x30,     //     USAGE (X)
	0x09, 0x31,     //     USAGE (Y)
	0x15, 0x81,     //   LOGICAL_MINIMUM (-127)
	0x25, 0x7f,     //   LOGICAL_MAXIMUM (127)
	0x75, 0x08,     //   REPORT_SIZE (8)
	0x95, 0x02,     //   REPORT_COUNT (2)
	0x81, 0x02,     //   INPUT (Data,Var,Abs)
	0xc0,           // END_COLLECTION
	0x05, 0x09,     // USAGE_PAGE (Button)
	0x19, 0x01,     //   USAGE_MINIMUM (Button 1)
	0x29, 0x08,     //   USAGE_MAXIMUM (Button 8)
	0x15, 0x00,     //   LOGICAL_MINIMUM (0)
	0x25, 0x01,     //   LOGICAL_MAXIMUM (1)
	0x75, 0x01,     // REPORT_SIZE (1)
	0x95, 0x08,     // REPORT_COUNT (8)
	0x81, 0x02,     // INPUT (Data,Var,Abs)
	0xc0            // END_COLLECTION
};

#pragma endregion

#pragma region Helpers

static void updateReport()
{
    reportBuffer[0] = 0; //testing
    reportBuffer[1] = 0;
    reportBuffer[2] = 0;
    reportBuffer[2] = 0;
}

#pragma endregion

#pragma region ADC

static void adcPoll(void)
{
    ADCSRA |= (1 << ADSC); //start next conversion
    while (ADCSRA & (1<<ADSC) ) { } //wait for conversion
    adc_value = ADCW; //set adc wide value
}

static void adcInit(void)
{
    ADMUX = (1 << MUX1) | (1 << MUX0);  //ref=Vcc, no aref, use ADC3
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //enable adc, not free running, interrupt disable, rate = 1/128
    while (ADCSRA & (1<<ADSC) ) { } //wait for first conversion
    (void) ADCW; //discard first reading
}

#pragma endregion

#pragma region USB

uchar usbFunctionSetup(uchar data[8])
{
    usbRequest_t *rq = (void *)data;
    usbMsgPtr = reportBuffer;
    if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) // class request type
    {
        if (rq->bRequest == USBRQ_HID_GET_REPORT) // wValue: ReportType (highbyte), ReportID (lowbyte)
        {
            // we only have one report type, so don't look at wValue
            updateReport();
            return sizeof(reportBuffer);
        }
        else if (rq->bRequest == USBRQ_HID_GET_IDLE)
        {
            usbMsgPtr = &idleRate;
            return 1;
        }
        else if (rq->bRequest == USBRQ_HID_SET_IDLE) idleRate = rq->wValue.bytes[1];
    }
    else { } // no vendor specific requests implemented
    return 0;
}

void usbEventResetReady(void)
{
    cli(); // Disable interrupts during oscillator calibration since usbMeasureFrameLength() counts CPU cycles.
    calibrateOscillator();
    sei();
    eeprom_write_byte(0, OSCCAL); // store the calibrated value in EEPROM
}

#pragma endregion

int main(void)
{
    uchar i;
    uchar calibrationValue;
    calibrationValue = eeprom_read_byte(0); // calibration value from last time
    if (calibrationValue != 0xff) OSCCAL = calibrationValue;
    usbDeviceDisconnect();
    for (i = 0; i < 20; i++) _delay_ms(15); // 300 ms disconnect
    usbDeviceConnect();
    adcInit();
    usbInit();
    sei();
    for (;;) // main event loop
    { 
        usbPoll();
        if (usbInterruptIsReady()) // we can send another report
        {
            updateReport();
            usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
        }
        adcPoll();
    }
    return 0;
}

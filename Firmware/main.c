/* 
    Name: main.c
    Project: Handbrake Firmware
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
    PB4 = LED
*/

static uchar reportBuffer[3]; //buffer for HID reports
static uchar idleRate; //in 4 ms units

#pragma region ADC

static void adcPoll(void)
{
    ADCSRA |= (1 << ADSC); //start next conversion
    while (ADCSRA & (1<<ADSC)) { } //wait for conversion
    reportBuffer[0] = ADCH; //get adc 8bit value
}

static void adcInit(void)
{
    ADMUX = (1 << MUX1) | (1 << ADLAR) | (1 << MUX0);  //ref=Vcc, no aref, left align, use ADC3
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //enable adc, not free running, interrupt disable, rate = 1/128
    while (ADCSRA & (1<<ADSC)) { } //wait for first conversion
    (void) ADCW; //discard first reading
}

#pragma endregion

#pragma region USB

const PROGMEM char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {
   	0x05, 0x01,         // USAGE_PAGE (Generic Desktop)
	0x09, 0x05,         // USAGE (Game Pad)
	0xa1, 0x01,         // COLLECTION (Application)
	0x09, 0x01,         //   USAGE (Pointer)
	0xa1, 0x00,         //   COLLECTION (Physical)
	0x09, 0x30,         //     USAGE (X)
	0x09, 0x31,         //     USAGE (Y)
	0x15, 0x00,         //   LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,   //   LOGICAL_MAXIMUM (255)
	0x75, 0x08,         //   REPORT_SIZE (8)
	0x95, 0x02,         //   REPORT_COUNT (2)
	0x81, 0x02,         //   INPUT (Data,Var,Abs)
	0xc0,               // END_COLLECTION
	0x05, 0x09,         // USAGE_PAGE (Button)
	0x19, 0x01,         //   USAGE_MINIMUM (Button 1)
	0x29, 0x08,         //   USAGE_MAXIMUM (Button 8)
	0x15, 0x00,         //   LOGICAL_MINIMUM (0)
	0x25, 0x01,         //   LOGICAL_MAXIMUM (1)
	0x75, 0x01,         // REPORT_SIZE (1)
	0x95, 0x08,         // REPORT_COUNT (8)
	0x81, 0x02,         // INPUT (Data,Var,Abs)
	0xc0                // END_COLLECTION
};

uchar usbFunctionSetup(uchar data[8])
{
    usbRequest_t *rq = (void *)data;
    usbMsgPtr = reportBuffer;
    if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) // class request type
    {
        if (rq->bRequest == USBRQ_HID_GET_REPORT) // wValue: ReportType (highbyte), ReportID (lowbyte)
        {
            // we only have one report type, so don't look at wValue
            return sizeof(reportBuffer);
        }
        else if (rq->bRequest == USBRQ_HID_GET_IDLE)
        {
            usbMsgPtr = &idleRate;
            return 1;
        }
        else if (rq->bRequest == USBRQ_HID_SET_IDLE) idleRate = rq->wValue.bytes[1];
    }
    // no vendor specific requests implemented
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
    uchar calibrationValue = eeprom_read_byte(0); // calibration value from last time
    if (calibrationValue != 0xff) OSCCAL = calibrationValue;
    usbDeviceDisconnect();
    uchar i;
    for (i = 0; i < 20; i++) _delay_ms(15); // 300 ms disconnect
    usbDeviceConnect();
    DDRB |= 1 << PB4;
    adcInit();
    usbInit();
    sei();
    PORTB |= 1 << PB4;
    for (;;)
    { 
        adcPoll();
        usbPoll();
        if (usbInterruptIsReady()) usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
    }
    return 0;
}

EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Handbrake Hardware"
Date "2017-11-07"
Rev "1"
Comp "chrz.de"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATTINY85-20PU U1
U 1 1 5A01CE96
P 5200 3700
F 0 "U1" H 4050 4100 50  0000 C CNN
F 1 "ATTINY85-20PU" H 6200 3300 50  0000 C CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 6200 3700 50  0001 C CIN
F 3 "" H 5200 3700 50  0001 C CNN
	1    5200 3700
	1    0    0    -1  
$EndComp
$Comp
L USB_B J1
U 1 1 5A01CFC4
P 5150 2500
F 0 "J1" H 4950 2950 50  0000 L CNN
F 1 "USB_B" H 4950 2850 50  0000 L CNN
F 2 "Connectors:USB_B" H 5300 2450 50  0001 C CNN
F 3 "" H 5300 2450 50  0001 C CNN
	1    5150 2500
	0    -1   1    0   
$EndComp
$Comp
L CP1 C1
U 1 1 5A01D096
P 6700 3700
F 0 "C1" H 6725 3800 50  0000 L CNN
F 1 "10u" H 6725 3600 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D5.0mm_P2.00mm" H 6700 3700 50  0001 C CNN
F 3 "" H 6700 3700 50  0001 C CNN
	1    6700 3700
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5A01D28B
P 3500 3950
F 0 "R1" V 3580 3950 50  0000 C CNN
F 1 "4.7K" V 3500 3950 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3430 3950 50  0001 C CNN
F 3 "" H 3500 3950 50  0001 C CNN
	1    3500 3950
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 5A01D334
P 3600 3450
F 0 "R2" V 3680 3450 50  0000 C CNN
F 1 "68" V 3600 3450 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3530 3450 50  0001 C CNN
F 3 "" H 3600 3450 50  0001 C CNN
	1    3600 3450
	0    -1   -1   0   
$EndComp
$Comp
L R R3
U 1 1 5A01D3B7
P 3500 3650
F 0 "R3" V 3580 3650 50  0000 C CNN
F 1 "68" V 3500 3650 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3430 3650 50  0001 C CNN
F 3 "" H 3500 3650 50  0001 C CNN
	1    3500 3650
	0    -1   -1   0   
$EndComp
$Comp
L R R4
U 1 1 5A01D434
P 4700 3200
F 0 "R4" V 4780 3200 50  0000 C CNN
F 1 "2.2K" V 4700 3200 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4630 3200 50  0001 C CNN
F 3 "" H 4700 3200 50  0001 C CNN
	1    4700 3200
	0    1    1    0   
$EndComp
$Comp
L D_Zener D1
U 1 1 5A01D5EC
P 3700 2600
F 0 "D1" H 3700 2700 50  0000 C CNN
F 1 "3.6" H 3700 2500 50  0000 C CNN
F 2 "Diodes_THT:D_A-405_P7.62mm_Horizontal" H 3700 2600 50  0001 C CNN
F 3 "" H 3700 2600 50  0001 C CNN
	1    3700 2600
	0    -1   -1   0   
$EndComp
$Comp
L D_Zener D2
U 1 1 5A01D649
P 3350 2600
F 0 "D2" H 3350 2700 50  0000 C CNN
F 1 "3.6" H 3350 2500 50  0000 C CNN
F 2 "Diodes_THT:D_A-405_P7.62mm_Horizontal" H 3350 2600 50  0001 C CNN
F 3 "" H 3350 2600 50  0001 C CNN
	1    3350 2600
	0    -1   -1   0   
$EndComp
$Comp
L Conn_01x03_Female J2
U 1 1 5A01D883
P 3750 4800
F 0 "J2" H 3750 5000 50  0000 C CNN
F 1 "Sensor_Female" H 3750 4600 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Angled_1x03_Pitch2.54mm" H 3750 4800 50  0001 C CNN
F 3 "" H 3750 4800 50  0001 C CNN
	1    3750 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	3650 3650 3850 3650
Wire Wire Line
	5550 2500 7300 2500
Wire Wire Line
	7300 2500 7300 3950
Wire Wire Line
	4950 2800 4950 3200
Wire Wire Line
	3350 3050 5250 3050
Wire Wire Line
	5250 3050 5250 2800
Wire Wire Line
	3350 3650 3250 3650
Wire Wire Line
	3250 3650 3250 2950
Wire Wire Line
	3250 2950 5150 2950
Wire Wire Line
	5150 2950 5150 2800
Wire Wire Line
	3850 3950 3650 3950
Wire Wire Line
	3350 3950 3150 3950
Wire Wire Line
	3150 2850 3150 4250
Wire Wire Line
	3150 2850 4950 2850
Connection ~ 4950 2850
Connection ~ 5700 2500
Wire Wire Line
	3850 3750 3750 3750
Wire Wire Line
	3750 3750 3750 4600
Wire Wire Line
	3850 4600 3850 4250
Wire Wire Line
	3650 4600 3650 4250
Wire Wire Line
	3650 4250 3150 4250
Connection ~ 3150 3950
Connection ~ 4950 3200
Connection ~ 3350 3050
Wire Wire Line
	3350 2750 3350 3450
Wire Wire Line
	3700 2950 3700 2750
Connection ~ 3700 2950
Wire Wire Line
	3350 2450 3350 2200
Wire Wire Line
	2950 2200 5700 2200
Wire Wire Line
	5700 2200 5700 2500
Wire Wire Line
	3700 2450 3700 2200
Connection ~ 3700 2200
Wire Wire Line
	4550 3200 4450 3200
Wire Wire Line
	4450 3200 4450 3050
Connection ~ 4450 3050
Wire Wire Line
	3350 3450 3450 3450
Wire Wire Line
	3750 3450 3850 3450
Wire Wire Line
	6550 3450 7050 3450
Wire Wire Line
	7050 3450 7050 3550
Wire Wire Line
	7300 3950 6550 3950
Wire Wire Line
	7050 3950 7050 3850
Wire Wire Line
	6700 3850 6700 4250
Connection ~ 6700 3950
Wire Wire Line
	6700 3200 6700 3550
Connection ~ 6700 3450
Wire Wire Line
	4850 3200 6700 3200
Wire Wire Line
	6700 4250 3850 4250
Connection ~ 7050 3950
NoConn ~ 5550 2400
NoConn ~ 3850 3550
$Comp
L C C2
U 1 1 5A0237DA
P 7050 3700
F 0 "C2" H 7075 3800 50  0000 L CNN
F 1 "0.1u" H 7075 3600 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 7088 3550 50  0001 C CNN
F 3 "" H 7050 3700 50  0001 C CNN
	1    7050 3700
	1    0    0    -1  
$EndComp
$Comp
L LED D3
U 1 1 5A02482B
P 2950 3600
F 0 "D3" H 2950 3700 50  0000 C CNN
F 1 "Red" H 2950 3500 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 2950 3600 50  0001 C CNN
F 3 "" H 2950 3600 50  0001 C CNN
	1    2950 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 3850 2950 3850
Wire Wire Line
	2950 3850 2950 3750
Wire Wire Line
	2950 3450 2950 2200
Connection ~ 3350 2200
$EndSCHEMATC

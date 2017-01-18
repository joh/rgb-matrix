EESchema Schematic File Version 2
LIBS:rgb-matrix-rescue
LIBS:power
LIBS:device
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
LIBS:stm32
LIBS:rgb-matrix
LIBS:rgb-matrix-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 6
Title "USB RGB Matrix"
Date ""
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 1750 2800 0    60   BiDi ~ 0
SPI2_MISO
Text GLabel 1750 2650 0    60   BiDi ~ 0
SPI2_MOSI
Text GLabel 1750 2950 0    60   BiDi ~ 0
SPI2_NSS
Text GLabel 1750 2500 0    60   BiDi ~ 0
SPI2_SCK
Text Label 3800 3850 0    60   ~ 0
DATA
$Comp
L CONN_01X06 P8
U 1 1 581A55CB
P 3600 3800
F 0 "P8" H 3600 4200 50  0000 C CNN
F 1 "PWEST" V 3700 3800 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Angled_1x06" H 3600 3800 50  0001 C CNN
F 3 "" H 3600 3800 50  0000 C CNN
	1    3600 3800
	-1   0    0    1   
$EndComp
Text Label 4350 3500 3    60   ~ 0
MOSI
Text Label 4350 4000 3    60   ~ 0
MISO
$Comp
L GND #PWR036
U 1 1 581A55DB
P 3800 4050
F 0 "#PWR036" H 3800 3800 50  0001 C CNN
F 1 "GND" H 3800 3900 50  0000 C CNN
F 2 "" H 3800 4050 50  0000 C CNN
F 3 "" H 3800 4050 50  0000 C CNN
	1    3800 4050
	-1   0    0    -1  
$EndComp
Text Label 3800 3950 0    60   ~ 0
NSS
Text Label 3800 3750 0    60   ~ 0
SCK
Text Label 1850 2950 0    60   ~ 0
NSS
Text Label 1850 2500 0    60   ~ 0
SCK
Text Label 1850 2800 0    60   ~ 0
MISO
Text Label 1850 2650 0    60   ~ 0
MOSI
Text Label 7150 3850 2    60   ~ 0
DATA
$Comp
L CONN_01X06 P11
U 1 1 581F606F
P 7350 3800
F 0 "P11" H 7350 4200 50  0000 C CNN
F 1 "PEAST" V 7450 3800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x06" H 7350 3800 50  0001 C CNN
F 3 "" H 7350 3800 50  0000 C CNN
	1    7350 3800
	1    0    0    1   
$EndComp
$Comp
L GND #PWR037
U 1 1 581F6077
P 7150 4050
F 0 "#PWR037" H 7150 3800 50  0001 C CNN
F 1 "GND" H 7150 3900 50  0000 C CNN
F 2 "" H 7150 4050 50  0000 C CNN
F 3 "" H 7150 4050 50  0000 C CNN
	1    7150 4050
	1    0    0    -1  
$EndComp
Text Label 7150 3950 2    60   ~ 0
NSS
Text Label 7150 3750 2    60   ~ 0
SCK
Text Label 5450 2150 3    60   ~ 0
DATA
$Comp
L CONN_01X06 P9
U 1 1 581F64E2
P 5400 1950
F 0 "P9" H 5400 2350 50  0000 C CNN
F 1 "PNORTH" V 5500 1950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x06" H 5400 1950 50  0001 C CNN
F 3 "" H 5400 1950 50  0000 C CNN
	1    5400 1950
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR038
U 1 1 581F64EA
P 5650 2150
F 0 "#PWR038" H 5650 1900 50  0001 C CNN
F 1 "GND" H 5650 2000 50  0000 C CNN
F 2 "" H 5650 2150 50  0000 C CNN
F 3 "" H 5650 2150 50  0000 C CNN
	1    5650 2150
	0    -1   -1   0   
$EndComp
Text Label 5550 2150 3    60   ~ 0
NSS
Text Label 5350 2150 3    60   ~ 0
SCK
Text Label 5450 5600 1    60   ~ 0
DATA
$Comp
L CONN_01X06 P10
U 1 1 581F661C
P 5400 5800
F 0 "P10" H 5400 6200 50  0000 C CNN
F 1 "PSOUTH" V 5500 5800 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Angled_1x06" H 5400 5800 50  0001 C CNN
F 3 "" H 5400 5800 50  0000 C CNN
	1    5400 5800
	0    -1   1    0   
$EndComp
$Comp
L GND #PWR039
U 1 1 581F6624
P 5650 5600
F 0 "#PWR039" H 5650 5350 50  0001 C CNN
F 1 "GND" H 5650 5450 50  0000 C CNN
F 2 "" H 5650 5600 50  0000 C CNN
F 3 "" H 5650 5600 50  0000 C CNN
	1    5650 5600
	0    -1   1    0   
$EndComp
Text Label 5550 5600 1    60   ~ 0
NSS
Text Label 5350 5600 1    60   ~ 0
SCK
$Comp
L CONN_01X03 P12
U 1 1 582389C1
P 4600 3850
F 0 "P12" H 4600 4050 50  0000 C CNN
F 1 "WEST" H 4600 3650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 4600 3850 50  0001 C CNN
F 3 "" H 4600 3850 50  0000 C CNN
	1    4600 3850
	1    0    0    -1  
$EndComp
Text Label 5100 5050 0    60   ~ 0
MOSI
Text Label 5600 5050 0    60   ~ 0
MISO
$Comp
L CONN_01X03 P14
U 1 1 58278DD1
P 5450 4800
F 0 "P14" H 5450 5000 50  0000 C CNN
F 1 "SOUTH" H 5450 4600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 5450 4800 50  0001 C CNN
F 3 "" H 5450 4800 50  0000 C CNN
	1    5450 4800
	0    -1   -1   0   
$EndComp
Text Label 6600 3500 3    60   ~ 0
MOSI
Text Label 6600 4000 3    60   ~ 0
MISO
$Comp
L CONN_01X03 P15
U 1 1 58278EAB
P 6350 3850
F 0 "P15" H 6350 4050 50  0000 C CNN
F 1 "EAST" H 6350 3650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 6350 3850 50  0001 C CNN
F 3 "" H 6350 3850 50  0000 C CNN
	1    6350 3850
	-1   0    0    -1  
$EndComp
Text Label 5100 2700 0    60   ~ 0
MOSI
Text Label 5600 2700 0    60   ~ 0
MISO
$Comp
L CONN_01X03 P13
U 1 1 58278F66
P 5450 2950
F 0 "P13" H 5450 3150 50  0000 C CNN
F 1 "NORTH" H 5450 2750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 5450 2950 50  0001 C CNN
F 3 "" H 5450 2950 50  0000 C CNN
	1    5450 2950
	0    -1   1    0   
$EndComp
$Comp
L +5V #PWR040
U 1 1 584F116F
P 3850 3500
F 0 "#PWR040" H 3850 3350 50  0001 C CNN
F 1 "+5V" H 3850 3640 50  0000 C CNN
F 2 "" H 3850 3500 50  0000 C CNN
F 3 "" H 3850 3500 50  0000 C CNN
	1    3850 3500
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR041
U 1 1 584F18CF
P 5100 2200
F 0 "#PWR041" H 5100 2050 50  0001 C CNN
F 1 "+5V" H 5100 2340 50  0000 C CNN
F 2 "" H 5100 2200 50  0000 C CNN
F 3 "" H 5100 2200 50  0000 C CNN
	1    5100 2200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4350 3750 4350 3450
Wire Wire Line
	4350 4250 4350 3950
Wire Wire Line
	3800 3850 4400 3850
Wire Wire Line
	3800 3750 4050 3750
Wire Wire Line
	3800 3950 4050 3950
Wire Wire Line
	2050 2950 1750 2950
Wire Wire Line
	2050 2500 1750 2500
Wire Wire Line
	2050 2800 1750 2800
Wire Wire Line
	2050 2650 1750 2650
Wire Wire Line
	7150 3750 6900 3750
Wire Wire Line
	7150 3950 6900 3950
Wire Wire Line
	7100 3650 7150 3650
Wire Wire Line
	7150 3550 7100 3550
Wire Wire Line
	5350 2150 5350 2400
Wire Wire Line
	5550 2150 5550 2400
Wire Wire Line
	5250 2200 5250 2150
Wire Wire Line
	5150 2150 5150 2200
Wire Wire Line
	5350 5600 5350 5350
Wire Wire Line
	5550 5600 5550 5350
Wire Wire Line
	5250 5550 5250 5600
Wire Wire Line
	5150 5600 5150 5550
Wire Wire Line
	4400 3750 4350 3750
Wire Wire Line
	4350 3950 4400 3950
Wire Wire Line
	5350 5050 5050 5050
Wire Wire Line
	5850 5050 5550 5050
Wire Wire Line
	5450 5600 5450 5000
Wire Wire Line
	5350 5000 5350 5050
Wire Wire Line
	5550 5050 5550 5000
Wire Wire Line
	6600 3750 6600 3450
Wire Wire Line
	6600 4250 6600 3950
Wire Wire Line
	7150 3850 6550 3850
Wire Wire Line
	6550 3750 6600 3750
Wire Wire Line
	6600 3950 6550 3950
Wire Wire Line
	5350 2700 5050 2700
Wire Wire Line
	5850 2700 5550 2700
Wire Wire Line
	5450 2150 5450 2750
Wire Wire Line
	5350 2750 5350 2700
Wire Wire Line
	5550 2700 5550 2750
Wire Wire Line
	3850 3650 3800 3650
Connection ~ 3850 3550
Wire Wire Line
	3850 3550 3800 3550
Wire Wire Line
	3850 3500 3850 3650
Wire Wire Line
	5100 2200 5250 2200
Connection ~ 5150 2200
$Comp
L +5V #PWR042
U 1 1 584F1DB4
P 7100 3500
F 0 "#PWR042" H 7100 3350 50  0001 C CNN
F 1 "+5V" H 7100 3640 50  0000 C CNN
F 2 "" H 7100 3500 50  0000 C CNN
F 3 "" H 7100 3500 50  0000 C CNN
	1    7100 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3500 7100 3650
Connection ~ 7100 3550
$Comp
L +5V #PWR043
U 1 1 584F21C6
P 5100 5550
F 0 "#PWR043" H 5100 5400 50  0001 C CNN
F 1 "+5V" H 5100 5690 50  0000 C CNN
F 2 "" H 5100 5550 50  0000 C CNN
F 3 "" H 5100 5550 50  0000 C CNN
	1    5100 5550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5100 5550 5250 5550
Connection ~ 5150 5550
Text Notes 2200 3600 0    60   ~ 0
2x pin headers = 6A max!
$EndSCHEMATC

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
Sheet 3 6
Title "USB RGB Matrix"
Date ""
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L GND #PWR01
U 1 1 580E2C86
P 3450 2950
F 0 "#PWR01" H 3450 2700 50  0001 C CNN
F 1 "GND" H 3450 2800 50  0000 C CNN
F 2 "" H 3450 2950 50  0000 C CNN
F 3 "" H 3450 2950 50  0000 C CNN
	1    3450 2950
	1    0    0    -1  
$EndComp
Text GLabel 3550 1650 2    60   Output ~ 0
R1
Text GLabel 3550 1750 2    60   Output ~ 0
R2
Text GLabel 3550 1850 2    60   Output ~ 0
R3
Text GLabel 3550 1950 2    60   Output ~ 0
R4
Text GLabel 3550 2050 2    60   Output ~ 0
R5
Text GLabel 3550 2150 2    60   Output ~ 0
R6
Text GLabel 3550 2250 2    60   Output ~ 0
R7
Text GLabel 3550 2350 2    60   Output ~ 0
R8
Text GLabel 2100 1650 0    60   Input ~ 0
PWM_R1
Text GLabel 2100 1750 0    60   Input ~ 0
PWM_R2
Text GLabel 2100 1850 0    60   Input ~ 0
PWM_R3
Text GLabel 2100 1950 0    60   Input ~ 0
PWM_R4
Text GLabel 2100 2050 0    60   Input ~ 0
PWM_R5
Text GLabel 2100 2150 0    60   Input ~ 0
PWM_R6
Text GLabel 2100 2250 0    60   Input ~ 0
PWM_R7
Text GLabel 2100 2350 0    60   Input ~ 0
PWM_R8
$Comp
L GND #PWR02
U 1 1 580E3293
P 3450 4750
F 0 "#PWR02" H 3450 4500 50  0001 C CNN
F 1 "GND" H 3450 4600 50  0000 C CNN
F 2 "" H 3450 4750 50  0000 C CNN
F 3 "" H 3450 4750 50  0000 C CNN
	1    3450 4750
	1    0    0    -1  
$EndComp
Text GLabel 3550 3450 2    60   Output ~ 0
G1
Text GLabel 3550 3550 2    60   Output ~ 0
G2
Text GLabel 3550 3650 2    60   Output ~ 0
G3
Text GLabel 3550 3750 2    60   Output ~ 0
G4
Text GLabel 3550 3850 2    60   Output ~ 0
G5
Text GLabel 3550 3950 2    60   Output ~ 0
G6
Text GLabel 3550 4050 2    60   Output ~ 0
G7
Text GLabel 3550 4150 2    60   Output ~ 0
G8
Text GLabel 2100 3450 0    60   Input ~ 0
PWM_G1
Text GLabel 2100 3550 0    60   Input ~ 0
PWM_G2
Text GLabel 2100 3650 0    60   Input ~ 0
PWM_G3
Text GLabel 2100 3750 0    60   Input ~ 0
PWM_G4
Text GLabel 2100 3850 0    60   Input ~ 0
PWM_G5
Text GLabel 2100 3950 0    60   Input ~ 0
PWM_G6
Text GLabel 2100 4050 0    60   Input ~ 0
PWM_G7
Text GLabel 2100 4150 0    60   Input ~ 0
PWM_G8
$Comp
L GND #PWR03
U 1 1 580E3476
P 3450 6550
F 0 "#PWR03" H 3450 6300 50  0001 C CNN
F 1 "GND" H 3450 6400 50  0000 C CNN
F 2 "" H 3450 6550 50  0000 C CNN
F 3 "" H 3450 6550 50  0000 C CNN
	1    3450 6550
	1    0    0    -1  
$EndComp
Text GLabel 3550 5250 2    60   Output ~ 0
B1
Text GLabel 3550 5350 2    60   Output ~ 0
B2
Text GLabel 3550 5450 2    60   Output ~ 0
B3
Text GLabel 3550 5550 2    60   Output ~ 0
B4
Text GLabel 3550 5650 2    60   Output ~ 0
B5
Text GLabel 3550 5750 2    60   Output ~ 0
B6
Text GLabel 3550 5850 2    60   Output ~ 0
B7
Text GLabel 3550 5950 2    60   Output ~ 0
B8
Text GLabel 2100 5250 0    60   Input ~ 0
PWM_B1
Text GLabel 2100 5350 0    60   Input ~ 0
PWM_B2
Text GLabel 2100 5450 0    60   Input ~ 0
PWM_B3
Text GLabel 2100 5550 0    60   Input ~ 0
PWM_B4
Text GLabel 2100 5650 0    60   Input ~ 0
PWM_B5
Text GLabel 2100 5750 0    60   Input ~ 0
PWM_B6
Text GLabel 2100 5850 0    60   Input ~ 0
PWM_B7
Text GLabel 2100 5950 0    60   Input ~ 0
PWM_B8
$Comp
L 74AC244 U2
U 1 1 580E9E2B
P 2800 4000
F 0 "U2" H 2800 4700 60  0000 C CNN
F 1 "74AC244" H 2800 3350 60  0000 C CNN
F 2 "Housings_SSOP:TSSOP-20_4.4x6.5mm_Pitch0.65mm" H 2700 4700 60  0001 C CNN
F 3 "" H 2700 4700 60  0001 C CNN
	1    2800 4000
	1    0    0    -1  
$EndComp
$Comp
L 74AC244 U1
U 1 1 580E9F31
P 2800 2200
F 0 "U1" H 2800 2900 60  0000 C CNN
F 1 "74AC244" H 2800 1550 60  0000 C CNN
F 2 "Housings_SSOP:TSSOP-20_4.4x6.5mm_Pitch0.65mm" H 2700 2900 60  0001 C CNN
F 3 "" H 2700 2900 60  0001 C CNN
	1    2800 2200
	1    0    0    -1  
$EndComp
$Comp
L 74AC244 U3
U 1 1 580E9FE0
P 2800 5800
F 0 "U3" H 2800 6500 60  0000 C CNN
F 1 "74AC244" H 2800 5150 60  0000 C CNN
F 2 "Housings_SSOP:TSSOP-20_4.4x6.5mm_Pitch0.65mm" H 2700 6500 60  0001 C CNN
F 3 "" H 2700 6500 60  0001 C CNN
	1    2800 5800
	1    0    0    -1  
$EndComp
$Comp
L ULN2803A U4
U 1 1 580EA0CD
P 8150 3700
F 0 "U4" H 8150 4250 60  0000 C CNN
F 1 "ULN2803A" H 8150 3150 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-18W_7.5x11.6mm_Pitch1.27mm" H 8150 4300 60  0001 C CNN
F 3 "" H 8150 4300 60  0001 C CNN
	1    8150 3700
	1    0    0    -1  
$EndComp
Text GLabel 8800 3300 2    60   Output ~ 0
ROW1
Text GLabel 8800 3400 2    60   Output ~ 0
ROW2
Text GLabel 8800 3500 2    60   Output ~ 0
ROW3
Text GLabel 8800 3600 2    60   Output ~ 0
ROW4
Text GLabel 8800 3700 2    60   Output ~ 0
ROW5
Text GLabel 8800 3800 2    60   Output ~ 0
ROW6
Text GLabel 8800 3900 2    60   Output ~ 0
ROW7
Text GLabel 8800 4000 2    60   Output ~ 0
ROW8
NoConn ~ 8650 4100
$Comp
L GND #PWR04
U 1 1 580EA8A7
P 6450 4400
F 0 "#PWR04" H 6450 4150 50  0001 C CNN
F 1 "GND" H 6450 4250 50  0000 C CNN
F 2 "" H 6450 4400 50  0000 C CNN
F 3 "" H 6450 4400 50  0000 C CNN
	1    6450 4400
	1    0    0    -1  
$EndComp
Text GLabel 7550 3300 0    60   Input ~ 0
ON_ROW1
Text GLabel 7550 3400 0    60   Input ~ 0
ON_ROW2
Text GLabel 7550 3500 0    60   Input ~ 0
ON_ROW3
Text GLabel 7550 3600 0    60   Input ~ 0
ON_ROW4
Text GLabel 7550 3700 0    60   Input ~ 0
ON_ROW5
Text GLabel 7550 3800 0    60   Input ~ 0
ON_ROW6
Text GLabel 7550 3900 0    60   Input ~ 0
ON_ROW7
Text GLabel 7550 4000 0    60   Input ~ 0
ON_ROW8
Text GLabel 1050 2600 0    60   Input ~ 0
OE
$Comp
L R R25
U 1 1 58149F91
P 1150 2300
F 0 "R25" V 1230 2300 50  0000 C CNN
F 1 "10k" V 1150 2300 50  0000 C CNN
F 2 "rgb-matrix:R_0805" V 1080 2300 50  0001 C CNN
F 3 "" H 1150 2300 50  0000 C CNN
	1    1150 2300
	1    0    0    -1  
$EndComp
Text GLabel 1850 4400 0    60   Input ~ 0
OE
Text GLabel 1850 6200 0    60   Input ~ 0
OE
$Comp
L +5V #PWR05
U 1 1 58153A1D
P 3800 2600
F 0 "#PWR05" H 3800 2450 50  0001 C CNN
F 1 "+5V" H 3800 2740 50  0000 C CNN
F 2 "" H 3800 2600 50  0000 C CNN
F 3 "" H 3800 2600 50  0000 C CNN
	1    3800 2600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR06
U 1 1 58153A53
P 3800 4400
F 0 "#PWR06" H 3800 4250 50  0001 C CNN
F 1 "+5V" H 3800 4540 50  0000 C CNN
F 2 "" H 3800 4400 50  0000 C CNN
F 3 "" H 3800 4400 50  0000 C CNN
	1    3800 4400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR07
U 1 1 58153D2E
P 3800 6200
F 0 "#PWR07" H 3800 6050 50  0001 C CNN
F 1 "+5V" H 3800 6340 50  0000 C CNN
F 2 "" H 3800 6200 50  0000 C CNN
F 3 "" H 3800 6200 50  0000 C CNN
	1    3800 6200
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR08
U 1 1 5815401A
P 1150 2100
F 0 "#PWR08" H 1150 1950 50  0001 C CNN
F 1 "+3V3" H 1150 2240 50  0000 C CNN
F 2 "" H 1150 2100 50  0000 C CNN
F 3 "" H 1150 2100 50  0000 C CNN
	1    1150 2100
	1    0    0    -1  
$EndComp
$Comp
L C C17
U 1 1 584F6D63
P 3600 4550
F 0 "C17" H 3625 4650 50  0000 L CNN
F 1 "100n" H 3625 4450 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 3638 4400 50  0001 C CNN
F 3 "" H 3600 4550 50  0000 C CNN
	1    3600 4550
	1    0    0    -1  
$EndComp
$Comp
L C C18
U 1 1 584F7F50
P 3600 6350
F 0 "C18" H 3625 6450 50  0000 L CNN
F 1 "100n" H 3625 6250 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 3638 6200 50  0001 C CNN
F 3 "" H 3600 6350 50  0000 C CNN
	1    3600 6350
	1    0    0    -1  
$EndComp
Text Notes 7300 4550 0    60   ~ 0
Common-cathode alternative: TBD62083
$Comp
L +5V #PWR09
U 1 1 5874F556
P 6450 3800
F 0 "#PWR09" H 6450 3650 50  0001 C CNN
F 1 "+5V" H 6450 3940 50  0000 C CNN
F 2 "" H 6450 3800 50  0000 C CNN
F 3 "" H 6450 3800 50  0000 C CNN
	1    6450 3800
	1    0    0    -1  
$EndComp
Text Notes 4800 4400 0    60   ~ 0
For common-anode displays,\nsolder JP1 and\nreplace U4 with TBD62783.\n\nFor common-cathode displays,\nsolder JP2.
$Comp
L C C16
U 1 1 584F7B9B
P 3600 2750
F 0 "C16" H 3625 2850 50  0000 L CNN
F 1 "100n" H 3625 2650 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 3638 2600 50  0001 C CNN
F 3 "" H 3600 2750 50  0000 C CNN
	1    3600 2750
	1    0    0    -1  
$EndComp
$Comp
L C C21
U 1 1 58783112
P 6700 4250
F 0 "C21" H 6725 4350 50  0000 L CNN
F 1 "100n" H 6725 4150 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 6738 4100 50  0001 C CNN
F 3 "" H 6700 4250 50  0000 C CNN
	1    6700 4250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 587832B7
P 6700 4400
F 0 "#PWR010" H 6700 4150 50  0001 C CNN
F 1 "GND" H 6700 4250 50  0000 C CNN
F 2 "" H 6700 4400 50  0000 C CNN
F 3 "" H 6700 4400 50  0000 C CNN
	1    6700 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 2700 3450 2700
Wire Wire Line
	3450 2700 3450 2950
Wire Wire Line
	3550 2350 3400 2350
Wire Wire Line
	3550 1650 3400 1650
Wire Wire Line
	3550 1750 3400 1750
Wire Wire Line
	3550 1850 3400 1850
Wire Wire Line
	3550 1950 3400 1950
Wire Wire Line
	3550 2050 3400 2050
Wire Wire Line
	3550 2150 3400 2150
Wire Wire Line
	3550 2250 3400 2250
Wire Wire Line
	2100 1650 2200 1650
Wire Wire Line
	2100 1750 2200 1750
Wire Wire Line
	2100 1850 2200 1850
Wire Wire Line
	2100 1950 2200 1950
Wire Wire Line
	2100 2050 2200 2050
Wire Wire Line
	2100 2150 2200 2150
Wire Wire Line
	2100 2250 2200 2250
Wire Wire Line
	2100 2350 2200 2350
Wire Wire Line
	3400 4400 3800 4400
Wire Wire Line
	3400 4500 3450 4500
Wire Wire Line
	3450 4500 3450 4750
Wire Wire Line
	1850 4400 2200 4400
Wire Wire Line
	2200 4500 2150 4500
Wire Wire Line
	3550 4150 3400 4150
Wire Wire Line
	3550 3450 3400 3450
Wire Wire Line
	3550 3550 3400 3550
Wire Wire Line
	3550 3650 3400 3650
Wire Wire Line
	3550 3750 3400 3750
Wire Wire Line
	3550 3850 3400 3850
Wire Wire Line
	3550 3950 3400 3950
Wire Wire Line
	3550 4050 3400 4050
Wire Wire Line
	2100 3450 2200 3450
Wire Wire Line
	2100 3550 2200 3550
Wire Wire Line
	2100 3650 2200 3650
Wire Wire Line
	2100 3750 2200 3750
Wire Wire Line
	2100 3850 2200 3850
Wire Wire Line
	2100 3950 2200 3950
Wire Wire Line
	2100 4050 2200 4050
Wire Wire Line
	2100 4150 2200 4150
Wire Wire Line
	3400 6200 3800 6200
Wire Wire Line
	3400 6300 3450 6300
Wire Wire Line
	3450 6300 3450 6550
Wire Wire Line
	1850 6200 2200 6200
Wire Wire Line
	2200 6300 2150 6300
Wire Wire Line
	3550 5950 3400 5950
Wire Wire Line
	3550 5250 3400 5250
Wire Wire Line
	3550 5350 3400 5350
Wire Wire Line
	3550 5450 3400 5450
Wire Wire Line
	3550 5550 3400 5550
Wire Wire Line
	3550 5650 3400 5650
Wire Wire Line
	3550 5750 3400 5750
Wire Wire Line
	3550 5850 3400 5850
Wire Wire Line
	2100 5250 2200 5250
Wire Wire Line
	2100 5350 2200 5350
Wire Wire Line
	2100 5450 2200 5450
Wire Wire Line
	2100 5550 2200 5550
Wire Wire Line
	2100 5650 2200 5650
Wire Wire Line
	2100 5750 2200 5750
Wire Wire Line
	2100 5850 2200 5850
Wire Wire Line
	2100 5950 2200 5950
Wire Wire Line
	8800 4000 8650 4000
Wire Wire Line
	8800 3300 8650 3300
Wire Wire Line
	8800 3400 8650 3400
Wire Wire Line
	8800 3500 8650 3500
Wire Wire Line
	8800 3600 8650 3600
Wire Wire Line
	8800 3700 8650 3700
Wire Wire Line
	8800 3800 8650 3800
Wire Wire Line
	8800 3900 8650 3900
Wire Wire Line
	7550 3300 7650 3300
Wire Wire Line
	7550 3400 7650 3400
Wire Wire Line
	7550 3500 7650 3500
Wire Wire Line
	7550 3600 7650 3600
Wire Wire Line
	7550 3700 7650 3700
Wire Wire Line
	7550 3800 7650 3800
Wire Wire Line
	7550 3900 7650 3900
Wire Wire Line
	7550 4000 7650 4000
Wire Wire Line
	1150 2100 1150 2150
Wire Wire Line
	1150 2450 1150 2600
Wire Wire Line
	2150 4500 2150 4400
Connection ~ 2150 4400
Wire Wire Line
	2150 6300 2150 6200
Connection ~ 2150 6200
Wire Wire Line
	1050 2600 2200 2600
Connection ~ 2150 2600
Wire Wire Line
	2200 2700 2150 2700
Wire Wire Line
	2150 2700 2150 2600
Connection ~ 1150 2600
Wire Wire Line
	3400 2600 3800 2600
Wire Wire Line
	3600 4700 3450 4700
Connection ~ 3450 4700
Connection ~ 3600 4400
Connection ~ 3600 2600
Wire Wire Line
	3450 2900 3600 2900
Connection ~ 3450 2900
Connection ~ 3600 6200
Wire Wire Line
	3450 6500 3600 6500
Connection ~ 3450 6500
Wire Wire Line
	6450 4350 6450 4400
Wire Wire Line
	6450 3800 6450 3850
Wire Wire Line
	6700 4100 6700 4100
Connection ~ 6700 4100
Connection ~ 6450 4100
Wire Wire Line
	6450 4050 6450 4150
Wire Wire Line
	6450 4100 7650 4100
$Comp
L Jumper_NC_Small JP1
U 1 1 58750A6A
P 6450 3950
F 0 "JP1" H 6450 4030 50  0000 C CNN
F 1 "CA" H 6460 3890 50  0000 C CNN
F 2 "rgb-matrix:SMD-solder-bridge-1mm" H 6450 3950 50  0001 C CNN
F 3 "" H 6450 3950 50  0000 C CNN
	1    6450 3950
	0    -1   -1   0   
$EndComp
$Comp
L Jumper_NC_Small JP2
U 1 1 5875096F
P 6450 4250
F 0 "JP2" H 6450 4330 50  0000 C CNN
F 1 "CC" H 6460 4190 50  0000 C CNN
F 2 "rgb-matrix:SMD-solder-bridge-1mm" H 6450 4250 50  0001 C CNN
F 3 "" H 6450 4250 50  0000 C CNN
	1    6450 4250
	0    -1   -1   0   
$EndComp
$EndSCHEMATC

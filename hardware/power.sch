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
Sheet 6 6
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L +5V #PWR044
U 1 1 582B6924
P 1900 4600
F 0 "#PWR044" H 1900 4450 50  0001 C CNN
F 1 "+5V" H 1900 4740 50  0000 C CNN
F 2 "" H 1900 4600 50  0000 C CNN
F 3 "" H 1900 4600 50  0000 C CNN
	1    1900 4600
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR045
U 1 1 582B692A
P 3550 4500
F 0 "#PWR045" H 3550 4350 50  0001 C CNN
F 1 "+3V3" H 3550 4640 50  0000 C CNN
F 2 "" H 3550 4500 50  0000 C CNN
F 3 "" H 3550 4500 50  0000 C CNN
	1    3550 4500
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 582B6930
P 1900 4900
F 0 "C9" H 1925 5000 50  0000 L CNN
F 1 "1uF" H 1925 4800 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 1938 4750 50  0001 C CNN
F 3 "" H 1900 4900 50  0000 C CNN
	1    1900 4900
	-1   0    0    -1  
$EndComp
$Comp
L C C14
U 1 1 582B6937
P 3300 4850
F 0 "C14" H 3325 4950 50  0000 L CNN
F 1 "1uF" H 3325 4750 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 3338 4700 50  0001 C CNN
F 3 "" H 3300 4850 50  0000 C CNN
	1    3300 4850
	1    0    0    -1  
$EndComp
$Comp
L LD3985M33R U6
U 1 1 582B693E
P 2650 4700
F 0 "U6" H 2400 4900 50  0000 C CNN
F 1 "LD3985M33R" H 2850 4900 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5" H 2550 5000 50  0001 C CIN
F 3 "" H 2650 4700 50  0000 C CNN
	1    2650 4700
	1    0    0    -1  
$EndComp
$Comp
L C C12
U 1 1 582B6945
P 2100 5050
F 0 "C12" H 2125 5150 50  0000 L CNN
F 1 "100nF" H 2125 4950 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 2138 4900 50  0001 C CNN
F 3 "" H 2100 5050 50  0000 C CNN
	1    2100 5050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR046
U 1 1 582B694C
P 1900 5250
F 0 "#PWR046" H 1900 5000 50  0001 C CNN
F 1 "GND" H 1900 5100 50  0000 C CNN
F 2 "" H 1900 5250 50  0000 C CNN
F 3 "" H 1900 5250 50  0000 C CNN
	1    1900 5250
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 582B6952
P 3100 5000
F 0 "C13" H 3125 5100 50  0000 L CNN
F 1 "10nF" H 3125 4900 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 3138 4850 50  0001 C CNN
F 3 "" H 3100 5000 50  0000 C CNN
	1    3100 5000
	-1   0    0    -1  
$EndComp
$Comp
L C C15
U 1 1 582B696D
P 3550 5050
F 0 "C15" H 3575 5150 50  0000 L CNN
F 1 "100nF" H 3575 4950 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 3588 4900 50  0001 C CNN
F 3 "" H 3550 5050 50  0000 C CNN
	1    3550 5050
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR047
U 1 1 582B6E1D
P 5500 4750
F 0 "#PWR047" H 5500 4600 50  0001 C CNN
F 1 "VDD" H 5500 4900 50  0000 C CNN
F 2 "" H 5500 4750 50  0000 C CNN
F 3 "" H 5500 4750 50  0000 C CNN
	1    5500 4750
	1    0    0    -1  
$EndComp
$Comp
L BARREL_JACK CON1
U 1 1 582B6E23
P 2000 2350
F 0 "CON1" H 2000 2600 50  0000 C CNN
F 1 "VEXT" H 2000 2150 50  0000 C CNN
F 2 "rgb-matrix:BARREL_JACK" H 2000 2350 50  0001 C CNN
F 3 "" H 2000 2350 50  0000 C CNN
	1    2000 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR048
U 1 1 582B6E2A
P 2300 2550
F 0 "#PWR048" H 2300 2300 50  0001 C CNN
F 1 "GND" H 2300 2400 50  0000 C CNN
F 2 "" H 2300 2550 50  0000 C CNN
F 3 "" H 2300 2550 50  0000 C CNN
	1    2300 2550
	1    0    0    -1  
$EndComp
Text Notes 2500 1400 2    60   ~ 0
Ext power, 9A max
$Comp
L +3V3 #PWR049
U 1 1 582B6E38
P 5250 4750
F 0 "#PWR049" H 5250 4600 50  0001 C CNN
F 1 "+3V3" H 5250 4890 50  0000 C CNN
F 2 "" H 5250 4750 50  0000 C CNN
F 3 "" H 5250 4750 50  0000 C CNN
	1    5250 4750
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P6
U 1 1 582B6E3F
P 1750 1650
F 0 "P6" H 1750 1800 50  0000 C CNN
F 1 "VEXT" V 1850 1650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 1750 1650 50  0001 C CNN
F 3 "" H 1750 1650 50  0000 C CNN
	1    1750 1650
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR050
U 1 1 582B6E46
P 2300 1750
F 0 "#PWR050" H 2300 1500 50  0001 C CNN
F 1 "GND" H 2300 1600 50  0000 C CNN
F 2 "" H 2300 1750 50  0000 C CNN
F 3 "" H 2300 1750 50  0000 C CNN
	1    2300 1750
	1    0    0    -1  
$EndComp
$Comp
L Led_Small D2
U 1 1 582B7639
P 6300 2550
F 0 "D2" H 6250 2675 50  0000 L CNN
F 1 "5V" H 6250 2450 50  0000 L CNN
F 2 "LEDs:LED_1206" V 6300 2550 50  0001 C CNN
F 3 "" V 6300 2550 50  0000 C CNN
	1    6300 2550
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR051
U 1 1 582B7640
P 6450 2550
F 0 "#PWR051" H 6450 2300 50  0001 C CNN
F 1 "GND" H 6450 2400 50  0000 C CNN
F 2 "" H 6450 2550 50  0000 C CNN
F 3 "" H 6450 2550 50  0000 C CNN
	1    6450 2550
	0    -1   1    0   
$EndComp
$Comp
L R R29
U 1 1 582B7646
P 6000 2550
F 0 "R29" V 6080 2550 50  0000 C CNN
F 1 "1k" V 6000 2550 50  0000 C CNN
F 2 "rgb-matrix:R_0805" V 5930 2550 50  0001 C CNN
F 3 "" H 6000 2550 50  0000 C CNN
	1    6000 2550
	0    -1   1    0   
$EndComp
$Comp
L Led_Small D1
U 1 1 582B7663
P 6300 2050
F 0 "D1" H 6250 2175 50  0000 L CNN
F 1 "3.3V" H 6250 1950 50  0000 L CNN
F 2 "LEDs:LED_1206" V 6300 2050 50  0001 C CNN
F 3 "" V 6300 2050 50  0000 C CNN
	1    6300 2050
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR052
U 1 1 582B766A
P 6450 2050
F 0 "#PWR052" H 6450 1800 50  0001 C CNN
F 1 "GND" H 6450 1900 50  0000 C CNN
F 2 "" H 6450 2050 50  0000 C CNN
F 3 "" H 6450 2050 50  0000 C CNN
	1    6450 2050
	0    -1   1    0   
$EndComp
$Comp
L R R28
U 1 1 582B7670
P 6000 2050
F 0 "R28" V 6080 2050 50  0000 C CNN
F 1 "1k" V 6000 2050 50  0000 C CNN
F 2 "rgb-matrix:R_0805" V 5930 2050 50  0001 C CNN
F 3 "" H 6000 2050 50  0000 C CNN
	1    6000 2050
	0    -1   1    0   
$EndComp
$Comp
L +3V3 #PWR053
U 1 1 582B7677
P 5750 2050
F 0 "#PWR053" H 5750 1900 50  0001 C CNN
F 1 "+3V3" H 5750 2190 50  0000 C CNN
F 2 "" H 5750 2050 50  0000 C CNN
F 3 "" H 5750 2050 50  0000 C CNN
	1    5750 2050
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR054
U 1 1 582B7858
P 4450 4900
F 0 "#PWR054" H 4450 4650 50  0001 C CNN
F 1 "GND" H 4450 4750 50  0000 C CNN
F 2 "" H 4450 4900 50  0000 C CNN
F 3 "" H 4450 4900 50  0000 C CNN
	1    4450 4900
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG055
U 1 1 582B785E
P 4450 4800
F 0 "#FLG055" H 4450 4895 50  0001 C CNN
F 1 "PWR_FLAG" H 4450 4980 50  0000 C CNN
F 2 "" H 4450 4800 50  0000 C CNN
F 3 "" H 4450 4800 50  0000 C CNN
	1    4450 4800
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR056
U 1 1 582B7864
P 4850 4750
F 0 "#PWR056" H 4850 4600 50  0001 C CNN
F 1 "+5V" H 4850 4890 50  0000 C CNN
F 2 "" H 4850 4750 50  0000 C CNN
F 3 "" H 4850 4750 50  0000 C CNN
	1    4850 4750
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG057
U 1 1 582B786A
P 4850 4850
F 0 "#FLG057" H 4850 4945 50  0001 C CNN
F 1 "PWR_FLAG" H 4850 5030 50  0000 C CNN
F 2 "" H 4850 4850 50  0000 C CNN
F 3 "" H 4850 4850 50  0000 C CNN
	1    4850 4850
	-1   0    0    1   
$EndComp
Text GLabel 1950 2950 0    60   UnSpc ~ 0
VBUS
Text Notes 2550 3150 2    60   ~ 0
USB power, 3A max
Text Notes 5800 1800 0    60   ~ 0
Power LEDs
Text Label 2500 2250 0    60   ~ 0
VEXT
$Comp
L +5V #PWR058
U 1 1 58729962
P 4650 1900
F 0 "#PWR058" H 4650 1750 50  0001 C CNN
F 1 "+5V" H 4650 2040 50  0000 C CNN
F 2 "" H 4650 1900 50  0000 C CNN
F 3 "" H 4650 1900 50  0000 C CNN
	1    4650 1900
	1    0    0    -1  
$EndComp
Text Label 2500 2950 0    60   ~ 0
VBUS
$Comp
L C C19
U 1 1 5873CE5D
P 2900 2450
F 0 "C19" H 2925 2550 50  0000 L CNN
F 1 "10uF" H 2925 2350 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 2938 2300 50  0001 C CNN
F 3 "" H 2900 2450 50  0000 C CNN
	1    2900 2450
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR059
U 1 1 5873D009
P 2900 2600
F 0 "#PWR059" H 2900 2350 50  0001 C CNN
F 1 "GND" H 2900 2450 50  0000 C CNN
F 2 "" H 2900 2600 50  0000 C CNN
F 3 "" H 2900 2600 50  0000 C CNN
	1    2900 2600
	1    0    0    -1  
$EndComp
$Comp
L C C20
U 1 1 5873D121
P 2900 3150
F 0 "C20" H 2925 3250 50  0000 L CNN
F 1 "10uF" H 2925 3050 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 2938 3000 50  0001 C CNN
F 3 "" H 2900 3150 50  0000 C CNN
	1    2900 3150
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR060
U 1 1 5873D127
P 2900 3300
F 0 "#PWR060" H 2900 3050 50  0001 C CNN
F 1 "GND" H 2900 3150 50  0000 C CNN
F 2 "" H 2900 3300 50  0000 C CNN
F 3 "" H 2900 3300 50  0000 C CNN
	1    2900 3300
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR061
U 1 1 587478CE
P 5750 4750
F 0 "#PWR061" H 5750 4600 50  0001 C CNN
F 1 "VCC" H 5750 4900 50  0000 C CNN
F 2 "" H 5750 4750 50  0000 C CNN
F 3 "" H 5750 4750 50  0000 C CNN
	1    5750 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 2950 3650 2950
Wire Wire Line
	4450 4800 4450 4900
Wire Wire Line
	4850 4750 4850 4850
Wire Wire Line
	5850 2050 5750 2050
Wire Wire Line
	6450 2050 6400 2050
Wire Wire Line
	6200 2050 6150 2050
Wire Wire Line
	6450 2550 6400 2550
Wire Wire Line
	6200 2550 6150 2550
Wire Wire Line
	2300 1700 2300 1750
Wire Wire Line
	1950 1600 2400 1600
Wire Wire Line
	2300 1700 1950 1700
Wire Wire Line
	2300 2250 3650 2250
Connection ~ 2300 2450
Wire Wire Line
	2300 2350 2300 2550
Connection ~ 3550 4650
Wire Wire Line
	3300 4700 3300 4650
Connection ~ 3300 5200
Connection ~ 3300 4650
Connection ~ 3100 5200
Wire Wire Line
	3100 5200 3100 5150
Wire Wire Line
	3100 4850 3100 4800
Connection ~ 2650 5200
Connection ~ 2100 5200
Wire Wire Line
	2650 5200 2650 5000
Connection ~ 1900 5200
Wire Wire Line
	1900 5200 3550 5200
Connection ~ 2100 4800
Connection ~ 1900 4650
Connection ~ 2100 4650
Wire Wire Line
	2100 4650 2100 4900
Wire Wire Line
	2200 4800 2100 4800
Wire Wire Line
	3100 4650 3550 4650
Wire Wire Line
	1900 4650 2200 4650
Wire Wire Line
	1900 4600 1900 4750
Wire Wire Line
	3550 4500 3550 4900
Wire Wire Line
	3300 5200 3300 5000
Wire Wire Line
	1900 5050 1900 5250
Wire Wire Line
	2900 2300 2900 2250
Connection ~ 2900 2250
Wire Wire Line
	2900 3000 2900 2950
Connection ~ 2900 2950
Wire Wire Line
	5750 5000 5750 4750
Wire Wire Line
	5500 4750 5500 5000
Wire Wire Line
	5250 4750 5250 5000
Wire Wire Line
	5250 5000 5750 5000
Connection ~ 5500 5000
$Comp
L Jumper JP3
U 1 1 587FCB06
P 3950 2250
F 0 "JP3" H 3950 2400 50  0000 C CNN
F 1 "Vext" H 3950 2170 50  0000 C CNN
F 2 "rgb-matrix:SMD-solder-bridge-3mm" H 3950 2250 50  0001 C CNN
F 3 "" H 3950 2250 50  0000 C CNN
	1    3950 2250
	1    0    0    -1  
$EndComp
$Comp
L Jumper JP4
U 1 1 587FCBC5
P 3950 2950
F 0 "JP4" H 3950 3100 50  0000 C CNN
F 1 "Vbus" H 3950 2870 50  0000 C CNN
F 2 "rgb-matrix:SMD-solder-bridge-3mm" H 3950 2950 50  0001 C CNN
F 3 "" H 3950 2950 50  0000 C CNN
	1    3950 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2250 4650 2250
Wire Wire Line
	4650 1900 4650 2950
Wire Wire Line
	4650 2950 4250 2950
Connection ~ 4650 2250
Wire Wire Line
	5750 2550 5850 2550
$Comp
L +5V #PWR062
U 1 1 58800ECC
P 5750 2550
F 0 "#PWR062" H 5750 2400 50  0001 C CNN
F 1 "+5V" H 5750 2690 50  0000 C CNN
F 2 "" H 5750 2550 50  0000 C CNN
F 3 "" H 5750 2550 50  0000 C CNN
	1    5750 2550
	0    -1   -1   0   
$EndComp
Connection ~ 2400 2250
Wire Wire Line
	2400 1600 2400 2250
$EndSCHEMATC
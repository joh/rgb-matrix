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
Sheet 4 6
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
L GND #PWR011
U 1 1 580FD53D
P 3800 5950
F 0 "#PWR011" H 3800 5700 50  0001 C CNN
F 1 "GND" H 3800 5800 50  0000 C CNN
F 2 "" H 3800 5950 50  0000 C CNN
F 3 "" H 3800 5950 50  0000 C CNN
	1    3800 5950
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 580FD688
P 4400 900
F 0 "C5" H 4425 1000 50  0000 L CNN
F 1 "100nF" H 4425 800 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 4438 750 50  0001 C CNN
F 3 "" H 4400 900 50  0000 C CNN
	1    4400 900 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 580FFFC5
P 4400 750
F 0 "#PWR012" H 4400 500 50  0001 C CNN
F 1 "GND" H 4400 600 50  0000 C CNN
F 2 "" H 4400 750 50  0000 C CNN
F 3 "" H 4400 750 50  0000 C CNN
	1    4400 750 
	-1   0    0    1   
$EndComp
Text Label 4400 1200 0    60   ~ 0
VDD
$Comp
L C C6
U 1 1 5810026D
P 4700 900
F 0 "C6" H 4725 1000 50  0000 L CNN
F 1 "100nF" H 4725 800 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 4738 750 50  0001 C CNN
F 3 "" H 4700 900 50  0000 C CNN
	1    4700 900 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 58100274
P 4700 750
F 0 "#PWR013" H 4700 500 50  0001 C CNN
F 1 "GND" H 4700 600 50  0000 C CNN
F 2 "" H 4700 750 50  0000 C CNN
F 3 "" H 4700 750 50  0000 C CNN
	1    4700 750 
	-1   0    0    1   
$EndComp
Text Label 4700 1200 0    60   ~ 0
VDD
$Comp
L C C7
U 1 1 581002A2
P 5000 900
F 0 "C7" H 5025 1000 50  0000 L CNN
F 1 "100nF" H 5025 800 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 5038 750 50  0001 C CNN
F 3 "" H 5000 900 50  0000 C CNN
	1    5000 900 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 581002A9
P 5000 750
F 0 "#PWR014" H 5000 500 50  0001 C CNN
F 1 "GND" H 5000 600 50  0000 C CNN
F 2 "" H 5000 750 50  0000 C CNN
F 3 "" H 5000 750 50  0000 C CNN
	1    5000 750 
	-1   0    0    1   
$EndComp
Text Label 5000 1200 0    60   ~ 0
VDD
$Comp
L C C11
U 1 1 5810033F
P 5800 900
F 0 "C11" H 5825 1000 50  0000 L CNN
F 1 "100nF" H 5825 800 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 5838 750 50  0001 C CNN
F 3 "" H 5800 900 50  0000 C CNN
	1    5800 900 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 58100346
P 5800 750
F 0 "#PWR015" H 5800 500 50  0001 C CNN
F 1 "GND" H 5800 600 50  0000 C CNN
F 2 "" H 5800 750 50  0000 C CNN
F 3 "" H 5800 750 50  0000 C CNN
	1    5800 750 
	-1   0    0    1   
$EndComp
Text Label 5800 1200 0    60   ~ 0
VDD
$Comp
L C C2
U 1 1 581004FB
P 1050 2450
F 0 "C2" H 1075 2550 50  0000 L CNN
F 1 "26pF" H 1075 2350 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 1088 2300 50  0001 C CNN
F 3 "" H 1050 2450 50  0000 C CNN
	1    1050 2450
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR016
U 1 1 58100502
P 900 2450
F 0 "#PWR016" H 900 2200 50  0001 C CNN
F 1 "GND" H 900 2300 50  0000 C CNN
F 2 "" H 900 2450 50  0000 C CNN
F 3 "" H 900 2450 50  0000 C CNN
	1    900  2450
	0    1    1    0   
$EndComp
$Comp
L C C4
U 1 1 58100574
P 3650 1100
F 0 "C4" H 3675 1200 50  0000 L CNN
F 1 "1uF" H 3675 1000 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 3688 950 50  0001 C CNN
F 3 "" H 3650 1100 50  0000 C CNN
	1    3650 1100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 5810057A
P 3650 950
F 0 "#PWR017" H 3650 700 50  0001 C CNN
F 1 "GND" H 3650 800 50  0000 C CNN
F 2 "" H 3650 950 50  0000 C CNN
F 3 "" H 3650 950 50  0000 C CNN
	1    3650 950 
	-1   0    0    1   
$EndComp
$Comp
L FILTER FB1
U 1 1 581005C5
P 3150 1250
F 0 "FB1" H 3150 1400 50  0000 C CNN
F 1 "FILTER" H 3150 1150 50  0000 C CNN
F 2 "rgb-matrix:R_0805" H 3150 1250 50  0001 C CNN
F 3 "" H 3150 1250 50  0000 C CNN
	1    3150 1250
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR018
U 1 1 581006D5
P 2750 1150
F 0 "#PWR018" H 2750 1000 50  0001 C CNN
F 1 "VDD" H 2750 1300 50  0000 C CNN
F 2 "" H 2750 1150 50  0000 C CNN
F 3 "" H 2750 1150 50  0000 C CNN
	1    2750 1150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 581008E0
P 4000 5950
F 0 "#PWR019" H 4000 5700 50  0001 C CNN
F 1 "GND" H 4000 5800 50  0000 C CNN
F 2 "" H 4000 5950 50  0000 C CNN
F 3 "" H 4000 5950 50  0000 C CNN
	1    4000 5950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 58100906
P 4200 5950
F 0 "#PWR020" H 4200 5700 50  0001 C CNN
F 1 "GND" H 4200 5800 50  0000 C CNN
F 2 "" H 4200 5950 50  0000 C CNN
F 3 "" H 4200 5950 50  0000 C CNN
	1    4200 5950
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 58100925
P 5100 6100
F 0 "C8" H 5125 6200 50  0000 L CNN
F 1 "2.2uF" H 5125 6000 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 5138 5950 50  0001 C CNN
F 3 "" H 5100 6100 50  0000 C CNN
	1    5100 6100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 58100A18
P 5100 6250
F 0 "#PWR021" H 5100 6000 50  0001 C CNN
F 1 "GND" H 5100 6100 50  0000 C CNN
F 2 "" H 5100 6250 50  0000 C CNN
F 3 "" H 5100 6250 50  0000 C CNN
	1    5100 6250
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 58100A5A
P 5600 6100
F 0 "C10" H 5625 6200 50  0000 L CNN
F 1 "2.2uF" H 5625 6000 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 5638 5950 50  0001 C CNN
F 3 "" H 5600 6100 50  0000 C CNN
	1    5600 6100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR022
U 1 1 58100A9B
P 5600 6250
F 0 "#PWR022" H 5600 6000 50  0001 C CNN
F 1 "GND" H 5600 6100 50  0000 C CNN
F 2 "" H 5600 6250 50  0000 C CNN
F 3 "" H 5600 6250 50  0000 C CNN
	1    5600 6250
	1    0    0    -1  
$EndComp
$Comp
L Crystal X1
U 1 1 58100D3C
P 1200 2750
F 0 "X1" H 1200 2900 50  0000 C CNN
F 1 "8MHz" H 1200 2600 50  0000 C CNN
F 2 "Crystals:Crystal_SMD_5032_2Pads" H 1200 2750 50  0001 C CNN
F 3 "" H 1200 2750 50  0000 C CNN
	1    1200 2750
	0    -1   -1   0   
$EndComp
$Comp
L C C3
U 1 1 581010BD
P 1050 3050
F 0 "C3" H 1075 3150 50  0000 L CNN
F 1 "26pF" H 1075 2950 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 1088 2900 50  0001 C CNN
F 3 "" H 1050 3050 50  0000 C CNN
	1    1050 3050
	0    -1   1    0   
$EndComp
$Comp
L GND #PWR023
U 1 1 581010C3
P 900 3050
F 0 "#PWR023" H 900 2800 50  0001 C CNN
F 1 "GND" H 900 2900 50  0000 C CNN
F 2 "" H 900 3050 50  0000 C CNN
F 3 "" H 900 3050 50  0000 C CNN
	1    900  3050
	0    1    1    0   
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 58101436
P 1200 7150
F 0 "SW1" H 1350 7260 50  0000 C CNN
F 1 "RESET" H 1200 7070 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_SKQG" H 1200 7150 50  0001 C CNN
F 3 "" H 1200 7150 50  0000 C CNN
	1    1200 7150
	0    1    1    0   
$EndComp
$Comp
L R R27
U 1 1 58101A4A
P 1950 7250
F 0 "R27" V 2030 7250 50  0000 C CNN
F 1 "10k" V 1950 7250 50  0000 C CNN
F 2 "rgb-matrix:R_0805" V 1880 7250 50  0001 C CNN
F 3 "" H 1950 7250 50  0000 C CNN
	1    1950 7250
	1    0    0    -1  
$EndComp
Text Label 850  2050 0    60   ~ 0
BOOT0
Text Label 850  2250 0    60   ~ 0
NRST
$Comp
L GND #PWR024
U 1 1 58102147
P 1050 7500
F 0 "#PWR024" H 1050 7250 50  0001 C CNN
F 1 "GND" H 1050 7350 50  0000 C CNN
F 2 "" H 1050 7500 50  0000 C CNN
F 3 "" H 1050 7500 50  0000 C CNN
	1    1050 7500
	-1   0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5810217F
P 900 7150
F 0 "C1" H 925 7250 50  0000 L CNN
F 1 "100nF" H 925 7050 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 938 7000 50  0001 C CNN
F 3 "" H 900 7150 50  0000 C CNN
	1    900  7150
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X06 P3
U 1 1 5810364B
P 10850 3150
F 0 "P3" H 10850 3500 50  0000 C CNN
F 1 "SWD" V 10950 3150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06" H 10850 3150 50  0001 C CNN
F 3 "" H 10850 3150 50  0000 C CNN
	1    10850 3150
	1    0    0    -1  
$EndComp
Text Label 10050 2900 0    60   ~ 0
VDD
Text Label 10050 3000 0    60   ~ 0
JTCK/SWCLK
Text Label 10050 3100 0    60   ~ 0
GND
Text Label 10050 3200 0    60   ~ 0
JTMS/SWDIO
Text Label 10050 3300 0    60   ~ 0
NRST
Text Label 10050 3400 0    60   ~ 0
SWO
Text Label 600  5150 0    60   ~ 0
JTMS/SWDIO
Text Label 600  5250 0    60   ~ 0
JTCK/SWCLK
Text Label 8250 2250 0    60   ~ 0
SWO
Text Label 600  4950 0    60   ~ 0
USB_DM
Text Label 600  5050 0    60   ~ 0
USB_DP
Text Label 8250 2150 0    60   ~ 0
BOOT1
Text Label 1600 7500 0    60   ~ 0
BOOT1
$Comp
L GND #PWR025
U 1 1 5815BDE6
P 1950 7550
F 0 "#PWR025" H 1950 7300 50  0001 C CNN
F 1 "GND" H 1950 7400 50  0000 C CNN
F 2 "" H 1950 7550 50  0000 C CNN
F 3 "" H 1950 7550 50  0000 C CNN
	1    1950 7550
	1    0    0    -1  
$EndComp
Text Label 1600 7050 0    60   ~ 0
BOOT0
$Comp
L VDD #PWR026
U 1 1 5815C70B
P 1950 6300
F 0 "#PWR026" H 1950 6150 50  0001 C CNN
F 1 "VDD" H 1950 6450 50  0000 C CNN
F 2 "" H 1950 6300 50  0000 C CNN
F 3 "" H 1950 6300 50  0000 C CNN
	1    1950 6300
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 5815C808
P 1950 6650
F 0 "SW2" H 2100 6760 50  0000 C CNN
F 1 "BOOT" H 1950 6570 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_SKQG" H 1950 6650 50  0001 C CNN
F 3 "" H 1950 6650 50  0000 C CNN
	1    1950 6650
	0    1    -1   0   
$EndComp
Text Notes 2150 6700 0    60   ~ 0
Enter DFU
$Comp
L R R26
U 1 1 5815F08D
P 1050 6650
F 0 "R26" V 1130 6650 50  0000 C CNN
F 1 "10k" V 1050 6650 50  0000 C CNN
F 2 "rgb-matrix:R_0805" V 980 6650 50  0001 C CNN
F 3 "" H 1050 6650 50  0000 C CNN
	1    1050 6650
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR027
U 1 1 5815F752
P 1050 6450
F 0 "#PWR027" H 1050 6300 50  0001 C CNN
F 1 "VDD" H 1050 6600 50  0000 C CNN
F 2 "" H 1050 6450 50  0000 C CNN
F 3 "" H 1050 6450 50  0000 C CNN
	1    1050 6450
	1    0    0    -1  
$EndComp
Text Label 650  6850 0    60   ~ 0
NRST
Text Notes 750  6200 0    60   ~ 0
RESET Button
$Comp
L STM32F405R U5
U 1 1 580FBDA4
P 4800 3550
F 0 "U5" H 4900 3000 50  0000 C CNN
F 1 "STM32F405R" H 4900 3100 50  0000 C CNN
F 2 "Housings_QFP:TQFP-64_10x10mm_Pitch0.5mm" H 4900 2900 50  0000 C CNN
F 3 "" H 4900 3000 50  0000 C CNN
	1    4800 3550
	1    0    0    -1  
$EndComp
Text GLabel 1200 3850 0    60   Output ~ 0
PWM_B7
Text GLabel 1200 3950 0    60   Output ~ 0
PWM_B8
Text GLabel 1200 4050 0    60   Output ~ 0
PWM_R1
Text GLabel 1200 4150 0    60   Output ~ 0
PWM_R2
Text GLabel 1200 4450 0    60   Output ~ 0
PWM_R3
Text GLabel 1200 4550 0    60   Output ~ 0
PWM_R4
Text GLabel 1200 4650 0    60   Output ~ 0
PWM_G7
Text GLabel 1200 4850 0    60   Output ~ 0
PWM_G8
Text GLabel 8200 1950 2    60   Output ~ 0
PWM_R5
Text GLabel 8200 2050 2    60   Output ~ 0
PWM_R6
Text GLabel 8200 2350 2    60   Output ~ 0
PWM_B1
Text GLabel 8200 2450 2    60   Output ~ 0
PWM_B2
Text GLabel 8200 2550 2    60   Output ~ 0
PWM_B3
Text GLabel 8200 2650 2    60   Output ~ 0
PWM_B4
Text GLabel 8200 2750 2    60   Output ~ 0
PWM_B5
Text GLabel 8200 2850 2    60   Output ~ 0
PWM_B6
Text GLabel 8200 2950 2    60   Output ~ 0
PWM_R7
Text GLabel 8200 3050 2    60   Output ~ 0
PWM_R8
Text GLabel 8200 3350 2    60   Output ~ 0
PWM_G1
Text GLabel 8200 3450 2    60   Output ~ 0
PWM_G2
Text GLabel 8200 4350 2    60   Output ~ 0
PWM_G3
Text GLabel 8200 4450 2    60   Output ~ 0
PWM_G4
Text GLabel 8200 4550 2    60   Output ~ 0
PWM_G5
Text GLabel 8200 4650 2    60   Output ~ 0
PWM_G6
Text GLabel 8200 4250 2    60   Output ~ 0
ON_ROW3
Text GLabel 8200 4150 2    60   Output ~ 0
ON_ROW2
Text GLabel 1200 4350 0    60   Output ~ 0
ON_ROW1
Text GLabel 8200 3850 2    60   Output ~ 0
ON_ROW4
Text GLabel 8200 3750 2    60   Output ~ 0
ON_ROW5
Text GLabel 8200 5250 2    60   Output ~ 0
ON_ROW6
Text GLabel 8200 5150 2    60   Output ~ 0
ON_ROW7
Text GLabel 8200 5050 2    60   Output ~ 0
ON_ROW8
Text GLabel 8200 3150 2    60   BiDi ~ 0
SPI2_NSS
Text GLabel 8200 3250 2    60   BiDi ~ 0
SPI2_SCK
Text GLabel 8200 3950 2    60   BiDi ~ 0
SPI2_MISO
Text GLabel 8200 4050 2    60   BiDi ~ 0
SPI2_MOSI
Text GLabel 1200 4250 0    60   Output ~ 0
OE
Text Label 8700 4750 2    60   ~ 0
SPI3_SCK
Text Label 8700 4850 2    60   ~ 0
SPI3_MISO
Text Label 8700 4950 2    60   ~ 0
SPI3_MOSI
Text Label 1050 5350 2    60   ~ 0
SPI3_NSS
$Comp
L GND #PWR028
U 1 1 581B0CAC
P 10650 4600
F 0 "#PWR028" H 10650 4350 50  0001 C CNN
F 1 "GND" H 10650 4450 50  0000 C CNN
F 2 "" H 10650 4600 50  0000 C CNN
F 3 "" H 10650 4600 50  0000 C CNN
	1    10650 4600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR029
U 1 1 581B0D1D
P 10650 4100
F 0 "#PWR029" H 10650 3950 50  0001 C CNN
F 1 "+5V" H 10650 4240 50  0000 C CNN
F 2 "" H 10650 4100 50  0000 C CNN
F 3 "" H 10650 4100 50  0000 C CNN
	1    10650 4100
	1    0    0    -1  
$EndComp
Text Label 10600 4200 2    60   ~ 0
SPI3_SCK
Text Label 10650 4300 2    60   ~ 0
SPI3_MOSI
Text Label 10650 4400 2    60   ~ 0
SPI3_MISO
Text Label 10600 4500 2    60   ~ 0
SPI3_NSS
Text Label 1200 3450 2    60   ~ 0
UART5_RX
$Comp
L CONN_01X06 P4
U 1 1 581B0B76
P 10850 4350
F 0 "P4" H 10850 4700 50  0000 C CNN
F 1 "SPI3" V 10950 4350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06" H 10850 4350 50  0001 C CNN
F 3 "" H 10850 4350 50  0000 C CNN
	1    10850 4350
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 P5
U 1 1 581C37AC
P 10850 5650
F 0 "P5" H 10850 6000 50  0000 C CNN
F 1 "UART5" V 10950 5650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06" H 10850 5650 50  0001 C CNN
F 3 "" H 10850 5650 50  0000 C CNN
	1    10850 5650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR030
U 1 1 581C3953
P 10650 5400
F 0 "#PWR030" H 10650 5150 50  0001 C CNN
F 1 "GND" H 10650 5250 50  0000 C CNN
F 2 "" H 10650 5400 50  0000 C CNN
F 3 "" H 10650 5400 50  0000 C CNN
	1    10650 5400
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR031
U 1 1 581C3C79
P 10200 5600
F 0 "#PWR031" H 10200 5450 50  0001 C CNN
F 1 "+5V" H 10200 5740 50  0000 C CNN
F 2 "" H 10200 5600 50  0000 C CNN
F 3 "" H 10200 5600 50  0000 C CNN
	1    10200 5600
	1    0    0    -1  
$EndComp
Text Label 9250 4950 2    60   ~ 0
UART5_TX
Text Label 10600 5700 2    60   ~ 0
UART5_TX
Text Label 10600 5800 2    60   ~ 0
UART5_RX
NoConn ~ 10650 5500
NoConn ~ 10650 5900
Text GLabel 1200 4750 0    60   UnSpc ~ 0
VBUS
Text Label 8700 1150 0    60   ~ 0
USB_DM
Text Label 8700 950  0    60   ~ 0
USB_DP
$Comp
L USBUFxxW6 U7
U 1 1 582B9473
P 9600 1050
F 0 "U7" H 9350 1300 60  0000 C CNN
F 1 "USBUF01W6" H 9550 800 60  0000 C CNN
F 2 "rgb-matrix:SOT323-6L" H 9600 1350 60  0001 C CNN
F 3 "" H 9600 1350 60  0001 C CNN
	1    9600 1050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR032
U 1 1 582B947A
P 8650 1050
F 0 "#PWR032" H 8650 800 50  0001 C CNN
F 1 "GND" H 8650 900 50  0000 C CNN
F 2 "" H 8650 1050 50  0000 C CNN
F 3 "" H 8650 1050 50  0000 C CNN
	1    8650 1050
	0    1    1    0   
$EndComp
$Comp
L USB_OTG P7
U 1 1 582B9480
P 10750 950
AR Path="/582B9480" Ref="P7"  Part="1" 
AR Path="/580FBD10/582B9480" Ref="P7"  Part="1" 
F 0 "P7" V 10450 850 50  0000 C CNN
F 1 "USB_B" H 10700 1150 50  0000 C CNN
F 2 "Connect:USB_Micro-B" V 10700 850 50  0001 C CNN
F 3 "" V 10700 850 50  0000 C CNN
	1    10750 950 
	0    1    1    0   
$EndComp
$Comp
L GND #PWR033
U 1 1 582B9487
P 10450 1400
F 0 "#PWR033" H 10450 1150 50  0001 C CNN
F 1 "GND" H 10450 1250 50  0000 C CNN
F 2 "" H 10450 1400 50  0000 C CNN
F 3 "" H 10450 1400 50  0000 C CNN
	1    10450 1400
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR034
U 1 1 582B948D
P 10100 1050
F 0 "#PWR034" H 10100 900 50  0001 C CNN
F 1 "+3V3" H 10100 1190 50  0000 C CNN
F 2 "" H 10100 1050 50  0000 C CNN
F 3 "" H 10100 1050 50  0000 C CNN
	1    10100 1050
	0    1    1    0   
$EndComp
Text GLabel 10200 750  0    60   UnSpc ~ 0
VBUS
NoConn ~ 10450 1050
$Comp
L C C22
U 1 1 587848A6
P 3900 1100
F 0 "C22" H 3925 1200 50  0000 L CNN
F 1 "100nF" H 3925 1000 50  0000 L CNN
F 2 "rgb-matrix:C_0805" H 3938 950 50  0001 C CNN
F 3 "" H 3900 1100 50  0000 C CNN
	1    3900 1100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR035
U 1 1 58784915
P 3900 950
F 0 "#PWR035" H 3900 700 50  0001 C CNN
F 1 "GND" H 3900 800 50  0000 C CNN
F 2 "" H 3900 950 50  0000 C CNN
F 3 "" H 3900 950 50  0000 C CNN
	1    3900 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	8200 2150 8600 2150
Wire Wire Line
	1200 5050 600  5050
Wire Wire Line
	1200 4950 600  4950
Wire Wire Line
	8200 2250 8600 2250
Wire Wire Line
	1200 5150 600  5150
Wire Wire Line
	1200 5250 600  5250
Wire Wire Line
	10650 3400 10050 3400
Wire Wire Line
	10650 3300 10050 3300
Wire Wire Line
	10650 3200 10050 3200
Wire Wire Line
	10650 3100 10050 3100
Wire Wire Line
	10650 3000 10050 3000
Wire Wire Line
	10650 2900 10050 2900
Wire Wire Line
	1200 2900 1200 3050
Wire Wire Line
	1200 2450 1200 2600
Wire Wire Line
	900  7000 900  6850
Connection ~ 1050 7450
Wire Wire Line
	900  7450 900  7300
Wire Wire Line
	1050 7450 1050 7500
Wire Wire Line
	900  7450 1200 7450
Wire Wire Line
	850  2250 1200 2250
Wire Wire Line
	850  2050 1200 2050
Connection ~ 3650 1250
Wire Wire Line
	3500 1250 3900 1250
Wire Wire Line
	5800 1050 5800 1250
Wire Wire Line
	5000 1050 5000 1250
Wire Wire Line
	4700 1050 4700 1250
Wire Wire Line
	4400 1050 4400 1250
Wire Wire Line
	1600 7050 1950 7050
Wire Wire Line
	1950 6950 1950 7100
Wire Wire Line
	1950 6300 1950 6350
Connection ~ 1950 7050
Wire Wire Line
	1050 6450 1050 6500
Wire Wire Line
	650  6850 1200 6850
Connection ~ 900  6850
Wire Wire Line
	1050 6850 1050 6800
Connection ~ 1050 6850
Wire Wire Line
	1950 7400 1950 7550
Wire Wire Line
	1600 7500 1950 7500
Connection ~ 1950 7500
Wire Wire Line
	2750 1150 2750 1250
Wire Wire Line
	2750 1250 2800 1250
Wire Wire Line
	1200 4450 1200 4450
Wire Wire Line
	1200 4550 1200 4550
Wire Wire Line
	8200 4750 8700 4750
Wire Wire Line
	8200 4850 8700 4850
Wire Wire Line
	8200 4950 9250 4950
Wire Wire Line
	600  5350 1200 5350
Wire Wire Line
	10650 4200 10200 4200
Wire Wire Line
	10200 4300 10650 4300
Wire Wire Line
	10200 4400 10650 4400
Wire Wire Line
	10200 4500 10650 4500
Wire Wire Line
	750  3450 1200 3450
Wire Wire Line
	10650 5700 10200 5700
Wire Wire Line
	10200 5800 10650 5800
Wire Wire Line
	10200 5600 10650 5600
Wire Wire Line
	5800 1200 5300 1200
Wire Wire Line
	5300 1200 5300 1250
Connection ~ 5800 1200
Wire Wire Line
	10200 750  10450 750 
Wire Wire Line
	10100 950  10450 950 
Wire Wire Line
	10350 850  10450 850 
Wire Wire Line
	10350 1150 10350 850 
Wire Wire Line
	10350 1150 10100 1150
Wire Wire Line
	8650 1050 9100 1050
Wire Wire Line
	9100 950  8700 950 
Wire Wire Line
	9100 1150 8700 1150
Wire Wire Line
	10450 1150 10450 1400
Wire Wire Line
	10850 1350 10450 1350
Connection ~ 10450 1350
$EndSCHEMATC

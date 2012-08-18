#
# STM32 Project Makefile
#
TARGET := rgb-matrix

CROSS_COMPILE := arm-none-eabi-
OPTLVL := s # Optimization level, can be [0, 1, 2, 3, s].

# Set up some paths
STMLIB := $(HOME)/code/stm32/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries
CMSIS := $(STMLIB)/CMSIS/CM3
CORE := $(CMSIS)/CoreSupport
DEVICE := $(CMSIS)/DeviceSupport/ST/STM32F10x
STARTUP := $(CMSIS)/DeviceSupport/ST/STM32F10x/startup/gcc_ride7
STD_PERIPH := $(STMLIB)/STM32F10x_StdPeriph_Driver

# Include path
INCLUDE = -I.
INCLUDE += -I$(CORE)
INCLUDE += -I$(DEVICE)
INCLUDE += -I$(STD_PERIPH)/inc

# vpath is used so object files are written to the current directory instead
# of the same directory as their source files
vpath %.c $(STD_PERIPH)/src $(DEVICE) $(CORE)
vpath %.s $(STARTUP)

# Linker script
LINKER_SCRIPT := STM32F100RB_FLASH.ld

# Startup file
ASRC = startup_stm32f10x_md_vl.s

# Project Source Files
SRC = main.c
#SRC += stm32f10x_it.c

# CMSIS
SRC += system_stm32f10x.c
SRC += core_cm3.c

# Standard Peripheral Source Files
SRC += stm32f10x_gpio.c
SRC += stm32f10x_tim.c
SRC += stm32f10x_rcc.c
SRC += misc.c

# Compiler flags
CDEFS = -DSTM32F10X_MD_VL
CDEFS += -DUSE_STDPERIPH_DRIVER

MCUFLAGS = -mcpu=cortex-m3 -mthumb
COMMONFLAGS = -O$(OPTLVL) -g -Wall# -Werror
CFLAGS = $(COMMONFLAGS) $(MCUFLAGS) $(INCLUDE) $(CDEFS)

LDLIBS =
LDFLAGS = $(COMMONFLAGS) -fno-exceptions -ffunction-sections -fdata-sections \
          -nostartfiles -Wl,--gc-sections,-T$(LINKER_SCRIPT)

# Object files
OBJ = $(SRC:%.c=%.o) $(ASRC:%.s=%.o)


# Toolchain setup
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy
AS = $(CROSS_COMPILE)as
AR = $(CROSS_COMPILE)ar
GDB = $(CROSS_COMPILE)gdb

#
# Here be rules
#

all: $(TARGET).bin

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

%.elf: $(OBJ) $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $@ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

upload: $(TARGET).bin
	st-flash write $< 0x8000000

.PHONY: clean

clean:
	rm -f *.o *.elf *.hex *.bin


##
## This file is part of the libopencm3 project.
##
## Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
##
## This library is free software: you can redistribute it and/or modify
## it under the terms of the GNU Lesser General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with this library.  If not, see <http://www.gnu.org/licenses/>.
##

BINARY = main

OBJS = display.o utils.o usb.o spi.o spi-daisy.o trace.o tests.o

OPENCM3_DIR=../../stm32/libopencm3-examples/libopencm3
LDSCRIPT = stm32f4-discovery.ld

# Set to 1 if LED matrix is common anode
DISPLAY_COMMON_ANODE ?= 1

# DEBUG=1 enables SWO debug
DEBUG ?= 1

ifeq ($(DISPLAY_COMMON_ANODE),1)
DEFS += -DDISPLAY_COMMON_ANODE
endif

ifeq ($(DEBUG),1)
DEFS += -DDEBUG -DENABLE_TRACE=1
endif

include libopencm3.target.mk

itm.fifo:
	mkfifo $@

console: itm.fifo
	itmdump -f itm.fifo & \
	$(OOCD) -f interface/$(OOCD_INTERFACE).cfg \
		    -f board/$(OOCD_BOARD).cfg \
		    -c "tpiu config internal itm.fifo uart off 168000000" \
	wait

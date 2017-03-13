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

OBJS = display.o utils.o usb.o spi.o tests.o

OPENCM3_DIR=../libopencm3-examples/libopencm3
LDSCRIPT = stm32f4-discovery.ld

# DEBUG=1 enables semihosting
DEBUG ?= 0

ifeq ($(DEBUG),1)
LDFLAGS += --specs=rdimon.specs
LDLIBS += -lrdimon
DEFS += -DENABLE_SEMIHOSTING=1
endif

include libopencm3.target.mk

console:
	$(OOCD) -f interface/$(OOCD_INTERFACE).cfg \
		    -f board/$(OOCD_BOARD).cfg \
		    -c "init" -c "reset init" \
		    -c "arm semihosting enable" \
		    -c "reset"

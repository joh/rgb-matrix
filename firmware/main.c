/*
 * RGB LED with PWM on STM32!
 */
#include <stdio.h>
#include <string.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencmsis/core_cm3.h>

#include "display.h"
#include "utils.h"
#include "usb.h"
#include "spi.h"
#include "spi-daisy.h"
#include "tests.h"
#include "trace.h"

static void clock_init(void)
{
    rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
}

int main(void)
{
    clock_init();
    systick_init();
    trace_init();
    display_init();
    spi_daisy_init();
    spi_slave_init();
    usb_init();

    printf("Starting main loop...\n");

    while (1) {
        usb_poll();
        spi_poll();
    }

    while (1) {
        __WFI(); /* Wait For Interrupt. */
        test_columns();
        test_rows();
        test_swapbuffers();
        test_brightness();
        test_white();
        test_random();
        test_fade();
        test_patterns();
        test_animation();
    }
}

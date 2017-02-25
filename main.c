/*
 * RGB LED with PWM on STM32!
 */
#include <stdio.h>
#include <string.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/exti.h>

#include <libopencmsis/core_cm3.h>

#include "display.h"
#include "utils.h"
#include "usb.h"
#include "tests.h"

//#define DEBUG

#ifdef DEBUG
extern void initialise_monitor_handles(void);
#endif

static void clock_init(void)
{
    rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
}

int main(void)
{
    clock_init();
    display_init();
    systick_init();
    /*usb_init();*/

#ifdef DEBUG
    setbuf(stdout, NULL);
    initialise_monitor_handles();
#endif

    /*while (1) {*/
        /*usb_poll();*/
    /*}*/

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
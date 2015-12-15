/*
 * RGB LED with PWM on STM32!
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/systick.h>

#include <libopencmsis/core_cm3.h>

/* monotonically increasing number of microseconds from reset
 * overflows every 49 days if you're wondering
 */
volatile uint32_t system_micros;

/* Called when systick fires */
void sys_tick_handler(void)
{
    system_micros++;
}

/* sleep for delay microseconds */
static void usleep(uint32_t delay)
{
    uint32_t wake = system_micros + delay;
    while (wake > system_micros);
}

/* Set up a timer to create 1us ticks. */
static void systick_setup(void)
{
    systick_set_frequency(1000000, 168000000);
    systick_counter_enable();
    systick_interrupt_enable();
}

#if 0
void pulse(__IO uint16_t *CCR)
{
    const uint16_t max = 0xfff;
    const uint16_t delay = 100;

    int i;

    for (i = 0; i < max; i++) {
        *CCR = i;
        delay_us(delay);
    }

    for (i = max; i >= 0; i--) {
        *CCR = i;
        delay_us(delay);
    }
}
#endif

__IO uint16_t red_frame[8][8] = {
    {0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0xffff, 0xffff, 0x0000, 0x0000, 0xffff, 0xffff, 0x0000},
    {0x0000, 0x0fff, 0xffff, 0x0000, 0x0000, 0x0fff, 0xffff, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0fff, 0x0000, 0x0000, 0x0001, 0x0000, 0x0fff, 0x0000},
    {0x0000, 0x0000, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
};


// Diagonal line test
/*
__IO uint16_t red_frame[8][8] = {
    {0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0xffff, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff},
};
*/

uint8_t current_row = 0;
uint16_t row_gpios[] = {GPIO0 , GPIO1 , GPIO2 , GPIO3 , GPIO4 , GPIO5 , GPIO10 , GPIO11};
__IO uint32_t *red[8];
__IO uint32_t *green[8];
__IO uint32_t *blue[8];

/**
  * @brief  This function handles TIM7 global interrupt request.
  * @param  None
  * @retval None
  */
void tim7_isr(void)
{
    uint8_t i;

    if (timer_get_flag(TIM7, TIM_SR_UIF)) {
        /* Clear compare interrupt flag. */
        timer_clear_flag(TIM7, TIM_SR_UIF);

        gpio_clear(GPIOC, row_gpios[current_row]);

        timer_disable_preload(TIM1);
        timer_disable_preload(TIM2);
        timer_disable_preload(TIM3);

        current_row = (current_row + 1) % 8;

        for (i = 0; i < 8; i++) {
            /*if (i == current_row) *red[i] = 0xfff;*/
            /*else *red[i] = 0;*/
            *red[i] = red_frame[current_row][i];
        }

        timer_set_counter(TIM1, 0);
        timer_set_counter(TIM2, 0);
        timer_set_counter(TIM3, 0);

        timer_enable_preload(TIM1);
        timer_enable_preload(TIM2);
        timer_enable_preload(TIM3);

        gpio_set(GPIOC, row_gpios[current_row]);
    }
}

static void clock_setup(void)
{
    rcc_clock_setup_hse_3v3(&hse_8mhz_3v3[CLOCK_3V3_168MHZ]);
}

static void gpio_setup(void)
{
    uint16_t gpios = 0;

    /* Enable GPIO clocks */
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);

    /*
     * Columns
     */

    /* PA8: TIM1 channel 1 */
    gpios = GPIO8;
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOA, GPIO_AF1, gpios);

    /* PB3,10,11: TIM2 channels 2,3,4 */
    gpios = GPIO3 | GPIO10 | GPIO11;
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOB, GPIO_AF1, gpios);

    /* PB4,5,0,1: TIM3 channels 1,2,3,4 */
    gpios = GPIO4 | GPIO5 | GPIO0 | GPIO1;
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOB, GPIO_AF2, gpios);

    /* PB6,7,8,9: TIM4 channels 1,2,3,4 */
    gpios = GPIO6 | GPIO7 | GPIO8 | GPIO9;
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOB, GPIO_AF2, gpios);

    /* PA0-3: TIM5 channels 1,2,3,4 */
    gpios = GPIO0 | GPIO1 | GPIO2 | GPIO3;
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOA, GPIO_AF2, gpios);

    /* PC6-9: TIM8 channels 1,2,3,4 */
    gpios = GPIO6 | GPIO7 | GPIO8 | GPIO9;
    gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOC, GPIO_AF3, gpios);

    /* PB14-15: TIM12 channels 1,2 */
    gpios = GPIO14 | GPIO15;
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOB, GPIO_AF9, gpios);

    /* PA6-7: TIM13 channel 1 + TIM14 channel 2 */
    gpios = GPIO6 | GPIO7;
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOA, GPIO_AF9, gpios);

    /*
     * Rows on PC0-5,10-11
     */
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO10 | GPIO11);
}

static void tim_setup(void)
{
    /* Enable TIM clocks */
    rcc_periph_clock_enable(RCC_TIM1);
    rcc_periph_clock_enable(RCC_TIM2);
    rcc_periph_clock_enable(RCC_TIM3);
    rcc_periph_clock_enable(RCC_TIM4);
    rcc_periph_clock_enable(RCC_TIM5);
    rcc_periph_clock_enable(RCC_TIM7);
    rcc_periph_clock_enable(RCC_TIM8);
    rcc_periph_clock_enable(RCC_TIM12);
    rcc_periph_clock_enable(RCC_TIM13);
    rcc_periph_clock_enable(RCC_TIM14);

    /* Reset TIMs */
    timer_reset(TIM1);
    timer_reset(TIM2);
    timer_reset(TIM3);
    timer_reset(TIM4);
    timer_reset(TIM5);
    timer_reset(TIM7);
    timer_reset(TIM8);
    timer_reset(TIM12);
    timer_reset(TIM13);
    timer_reset(TIM14);

    /* Must be called for advanced timers like this one.  Unclear what this
     * does or why it's necessary but the libopencm3 timer and STM32 docs
     * mention it. */
    timer_enable_break_main_output(TIM1);
    timer_enable_break_main_output(TIM8);

    /* Timer global mode:
     * - No divider
     * - Alignment edge
     * - Direction up
     */
    timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_mode(TIM3, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_mode(TIM4, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_mode(TIM5, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_mode(TIM7, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_mode(TIM8, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_mode(TIM12, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_mode(TIM13, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_mode(TIM14, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    /* Reset prescaler value. */
    timer_set_prescaler(TIM1, 1);   /* 168MHz/2 */
    timer_set_prescaler(TIM2, 0);
    timer_set_prescaler(TIM3, 0);
    timer_set_prescaler(TIM4, 0);
    timer_set_prescaler(TIM5, 0);
    timer_set_prescaler(TIM7, 1);   /* 42MHz */
    timer_set_prescaler(TIM8, 1);   /* 168MHz/2 */
    timer_set_prescaler(TIM12, 0);
    timer_set_prescaler(TIM13, 0);
    timer_set_prescaler(TIM14, 0);

    /* Disable preload. */
    timer_disable_preload(TIM1);
    timer_disable_preload(TIM2);
    timer_disable_preload(TIM3);
    timer_disable_preload(TIM4);
    timer_disable_preload(TIM5);
    timer_disable_preload(TIM7);
    timer_disable_preload(TIM8);
    timer_disable_preload(TIM12);
    timer_disable_preload(TIM13);
    timer_disable_preload(TIM14);

    /* Continous mode. */
    timer_continuous_mode(TIM1);
    timer_continuous_mode(TIM2);
    timer_continuous_mode(TIM3);
    timer_continuous_mode(TIM4);
    timer_continuous_mode(TIM5);
    timer_continuous_mode(TIM7);
    timer_continuous_mode(TIM8);
    timer_continuous_mode(TIM12);
    timer_continuous_mode(TIM13);
    timer_continuous_mode(TIM14);

    /* 16 bit timer (count up to 2^16 - 1) */
    timer_set_period(TIM1, 0xffff);
    timer_set_period(TIM2, 0xffff);
    timer_set_period(TIM3, 0xffff);
    timer_set_period(TIM4, 0xffff);
    timer_set_period(TIM5, 0xffff);
    timer_set_period(TIM7, 43749);      /* 120*8=960 Hz */
    timer_set_period(TIM8, 0xffff);
    timer_set_period(TIM12, 0xffff);
    timer_set_period(TIM13, 0xffff);
    timer_set_period(TIM14, 0xffff);

    /* Enable outputs */
    timer_enable_oc_output(TIM1, TIM_OC1);

    timer_enable_oc_output(TIM2, TIM_OC2);
    timer_enable_oc_output(TIM2, TIM_OC3);
    timer_enable_oc_output(TIM2, TIM_OC4);

    timer_enable_oc_output(TIM3, TIM_OC1);
    timer_enable_oc_output(TIM3, TIM_OC2);
    timer_enable_oc_output(TIM3, TIM_OC3);
    timer_enable_oc_output(TIM3, TIM_OC4);

    timer_enable_oc_output(TIM4, TIM_OC1);
    timer_enable_oc_output(TIM4, TIM_OC2);
    timer_enable_oc_output(TIM4, TIM_OC3);
    timer_enable_oc_output(TIM4, TIM_OC4);

    timer_enable_oc_output(TIM5, TIM_OC1);
    timer_enable_oc_output(TIM5, TIM_OC2);
    timer_enable_oc_output(TIM5, TIM_OC3);
    timer_enable_oc_output(TIM5, TIM_OC4);

    timer_enable_oc_output(TIM8, TIM_OC1);
    timer_enable_oc_output(TIM8, TIM_OC2);
    timer_enable_oc_output(TIM8, TIM_OC3);
    timer_enable_oc_output(TIM8, TIM_OC4);

    timer_enable_oc_output(TIM12, TIM_OC1);
    timer_enable_oc_output(TIM12, TIM_OC2);

    timer_enable_oc_output(TIM13, TIM_OC1);

    timer_enable_oc_output(TIM14, TIM_OC1);

    /* OC Mode PWM1 */
    timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);

    timer_set_oc_mode(TIM2, TIM_OC2, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM2, TIM_OC3, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM2, TIM_OC4, TIM_OCM_PWM1);

    timer_set_oc_mode(TIM3, TIM_OC1, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM3, TIM_OC2, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM3, TIM_OC3, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM3, TIM_OC4, TIM_OCM_PWM1);

    timer_set_oc_mode(TIM4, TIM_OC1, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM4, TIM_OC2, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM4, TIM_OC3, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM4, TIM_OC4, TIM_OCM_PWM1);

    timer_set_oc_mode(TIM5, TIM_OC1, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM5, TIM_OC2, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM5, TIM_OC3, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM5, TIM_OC4, TIM_OCM_PWM1);

    timer_set_oc_mode(TIM8, TIM_OC1, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM8, TIM_OC2, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM8, TIM_OC3, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM8, TIM_OC4, TIM_OCM_PWM1);

    timer_set_oc_mode(TIM12, TIM_OC1, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM12, TIM_OC2, TIM_OCM_PWM1);

    timer_set_oc_mode(TIM13, TIM_OC1, TIM_OCM_PWM1);

    timer_set_oc_mode(TIM14, TIM_OC1, TIM_OCM_PWM1);

    /* OC Polarity low (PNP mosfets) */
    timer_set_oc_polarity_low(TIM1, TIM_OC1);

    timer_set_oc_polarity_low(TIM2, TIM_OC2);
    timer_set_oc_polarity_low(TIM2, TIM_OC3);
    timer_set_oc_polarity_low(TIM2, TIM_OC4);

    timer_set_oc_polarity_low(TIM3, TIM_OC1);
    timer_set_oc_polarity_low(TIM3, TIM_OC2);
    timer_set_oc_polarity_low(TIM3, TIM_OC3);
    timer_set_oc_polarity_low(TIM3, TIM_OC4);

    timer_set_oc_polarity_low(TIM4, TIM_OC1);
    timer_set_oc_polarity_low(TIM4, TIM_OC2);
    timer_set_oc_polarity_low(TIM4, TIM_OC3);
    timer_set_oc_polarity_low(TIM4, TIM_OC4);

    timer_set_oc_polarity_low(TIM5, TIM_OC1);
    timer_set_oc_polarity_low(TIM5, TIM_OC2);
    timer_set_oc_polarity_low(TIM5, TIM_OC3);
    timer_set_oc_polarity_low(TIM5, TIM_OC4);

    timer_set_oc_polarity_low(TIM8, TIM_OC1);
    timer_set_oc_polarity_low(TIM8, TIM_OC2);
    timer_set_oc_polarity_low(TIM8, TIM_OC3);
    timer_set_oc_polarity_low(TIM8, TIM_OC4);

    timer_set_oc_polarity_low(TIM12, TIM_OC1);
    timer_set_oc_polarity_low(TIM12, TIM_OC2);

    timer_set_oc_polarity_low(TIM13, TIM_OC1);

    timer_set_oc_polarity_low(TIM14, TIM_OC1);

    /* OC Value */
    timer_set_oc_value(TIM1, TIM_OC1, 0x7fff);

    timer_set_oc_value(TIM2, TIM_OC2, 0x7fff);
    timer_set_oc_value(TIM2, TIM_OC3, 0x7fff);
    timer_set_oc_value(TIM2, TIM_OC4, 0x7fff);

    timer_set_oc_value(TIM3, TIM_OC1, 0x7fff);
    timer_set_oc_value(TIM3, TIM_OC2, 0x7fff);
    timer_set_oc_value(TIM3, TIM_OC3, 0x7fff);
    timer_set_oc_value(TIM3, TIM_OC4, 0x7fff);

    timer_set_oc_value(TIM4, TIM_OC1, 0x7fff);
    timer_set_oc_value(TIM4, TIM_OC2, 0x7fff);
    timer_set_oc_value(TIM4, TIM_OC3, 0x7fff);
    timer_set_oc_value(TIM4, TIM_OC4, 0x7fff);

    timer_set_oc_value(TIM5, TIM_OC1, 0x7fff);
    timer_set_oc_value(TIM5, TIM_OC2, 0x7fff);
    timer_set_oc_value(TIM5, TIM_OC3, 0x7fff);
    timer_set_oc_value(TIM5, TIM_OC4, 0x7fff);

    timer_set_oc_value(TIM8, TIM_OC1, 0x7fff);
    timer_set_oc_value(TIM8, TIM_OC2, 0x7fff);
    timer_set_oc_value(TIM8, TIM_OC3, 0x7fff);
    timer_set_oc_value(TIM8, TIM_OC4, 0x7fff);

    timer_set_oc_value(TIM12, TIM_OC1, 0x7fff);
    timer_set_oc_value(TIM12, TIM_OC2, 0x7fff);

    timer_set_oc_value(TIM13, TIM_OC1, 0x7fff);

    timer_set_oc_value(TIM14, TIM_OC1, 0x7fff);

    /* OC preload enable */
#if 0
    timer_enable_oc_preload(TIM1, TIM_OC1);

    timer_enable_oc_preload(TIM2, TIM_OC2);
    timer_enable_oc_preload(TIM2, TIM_OC3);
    timer_enable_oc_preload(TIM2, TIM_OC4);

    timer_enable_oc_preload(TIM3, TIM_OC1);
    timer_enable_oc_preload(TIM3, TIM_OC2);
    timer_enable_oc_preload(TIM3, TIM_OC3);
    timer_enable_oc_preload(TIM3, TIM_OC4);

    timer_enable_oc_preload(TIM4, TIM_OC1);
    timer_enable_oc_preload(TIM4, TIM_OC2);
    timer_enable_oc_preload(TIM4, TIM_OC3);
    timer_enable_oc_preload(TIM4, TIM_OC4);

    timer_enable_oc_preload(TIM5, TIM_OC1);
    timer_enable_oc_preload(TIM5, TIM_OC2);
    timer_enable_oc_preload(TIM5, TIM_OC3);
    timer_enable_oc_preload(TIM5, TIM_OC4);

    timer_enable_oc_preload(TIM8, TIM_OC1);
    timer_enable_oc_preload(TIM8, TIM_OC2);
    timer_enable_oc_preload(TIM8, TIM_OC3);
    timer_enable_oc_preload(TIM8, TIM_OC4);

    timer_enable_oc_preload(TIM12, TIM_OC1);
    timer_enable_oc_preload(TIM12, TIM_OC2);

    timer_enable_oc_preload(TIM13, TIM_OC1);

    timer_enable_oc_preload(TIM14, TIM_OC1);
#endif

    /* ARR preload enable */
    timer_enable_preload(TIM1);
    timer_enable_preload(TIM2);
    timer_enable_preload(TIM3);
    timer_enable_preload(TIM4);
    timer_enable_preload(TIM5);
    timer_enable_preload(TIM7);
    timer_enable_preload(TIM8);
    timer_enable_preload(TIM12);
    timer_enable_preload(TIM13);
    timer_enable_preload(TIM14);

    /* Enable interrupt for TIM7 */
    timer_enable_irq(TIM7, TIM_DIER_UIE);
    nvic_enable_irq(NVIC_TIM7_IRQ);

    /* Counter enable */
    timer_enable_counter(TIM1);
    timer_enable_counter(TIM2);
    timer_enable_counter(TIM3);
    timer_enable_counter(TIM4);
    timer_enable_counter(TIM5);
    timer_enable_counter(TIM7);
    timer_enable_counter(TIM8);
    timer_enable_counter(TIM12);
    timer_enable_counter(TIM13);
    timer_enable_counter(TIM14);
}

int main(void)
{
    clock_setup();
    gpio_setup();
    systick_setup();
    tim_setup();

    red[0] = &TIM1_CCR1;
    red[1] = &TIM2_CCR2;
    red[2] = &TIM2_CCR3;
    red[3] = &TIM2_CCR4;
    red[4] = &TIM3_CCR1;
    red[5] = &TIM3_CCR2;
    red[6] = &TIM3_CCR3;
    red[7] = &TIM3_CCR4;

    green[0] = &TIM4_CCR1;
    green[1] = &TIM4_CCR2;
    green[2] = &TIM4_CCR3;
    green[3] = &TIM4_CCR4;
    green[4] = &TIM5_CCR1;
    green[5] = &TIM5_CCR2;
    green[6] = &TIM5_CCR3;
    green[7] = &TIM5_CCR4;

    blue[0] = &TIM8_CCR1;
    blue[1] = &TIM8_CCR2;
    blue[2] = &TIM8_CCR3;
    blue[3] = &TIM8_CCR4;
    blue[4] = &TIM12_CCR1;
    blue[5] = &TIM12_CCR2;
    blue[6] = &TIM13_CCR1;
    blue[7] = &TIM14_CCR1;

    uint32_t i, j;
    uint32_t delay = 1000;
    uint16_t brightness = 0;

    for (i = 0; i < 8; i++) {
        /**red[i] = 0xffff * i / 32;*/
        *red[i] = i*100;
    }

    /*timer_set_oc_value(TIM1, TIM_OC1, 0xffff/2);*/

    while (1) {
        __WFI(); /* Wait For Interrupt. */
        // Brightness test
        //brightness = 0xff;
#if 0
        for (i = 0; i < 8; i++) {
            *red[(i-1)%8] = 0;
            *red[i] = brightness;
            usleep(100000);
        }
        brightness = (brightness + 0xff) % 0xfff;
#endif
#if 0
        brightness = (brightness + 0xff) % 0xffff;
        for (i = 0; i < 8; i++) {
            *red[i] = brightness;
            *green[i] = brightness;
            *blue[i] = brightness;
            /*for (j = 0; j < 8; j++) {*/
                /*red_frame[i][j] = brightness;*/
            /*}*/
        }
        usleep(10000);
#endif
    }
}

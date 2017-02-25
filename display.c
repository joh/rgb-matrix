#include <string.h>

#include <libopencmsis/core_cm3.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include "display.h"

/*
 * Rows
 */
struct gpio {
    uint32_t port;
    uint16_t pin;
};

static struct gpio row_gpios[] = {
    {GPIOA, GPIO5},  // ON_ROW1
    {GPIOC, GPIO4},  // ON_ROW2
    {GPIOC, GPIO5},  // ON_ROW3
    {GPIOC, GPIO1},  // ON_ROW4
    {GPIOC, GPIO0},  // ON_ROW5
    {GPIOC, GPIO15}, // ON_ROW6
    {GPIOC, GPIO14}, // ON_ROW7
    {GPIOC, GPIO13}, // ON_ROW8
};

/*
 * Columns
 */
static __IO uint32_t *red[8] = {
    &TIM5_CCR3,  // R1, PA2
    &TIM5_CCR4,  // R2, PA3
    &TIM13_CCR1, // R3, PA6
    &TIM14_CCR1, // R4, PA7
    &TIM3_CCR3,  // R5, PB0
    &TIM3_CCR4,  // R6, PB1
    &TIM2_CCR3,  // R7, PB10
    &TIM2_CCR4,  // R8, PB11
};

static __IO uint32_t *green[8] = {
    &TIM12_CCR1, // G1, PB14
    &TIM12_CCR2, // G2, PB15
    &TIM8_CCR1,  // G3, PC6
    &TIM8_CCR2,  // G4, PC7
    &TIM8_CCR3,  // G5, PC8
    &TIM8_CCR4,  // G6, PC9
    &TIM1_CCR1,  // G7, PA8
    &TIM1_CCR3,  // G8, PA10
};

static __IO uint32_t *blue[8] = {
    &TIM3_CCR1, // B1, PB4
    &TIM3_CCR2, // B2, PB5
    &TIM4_CCR1, // B3, PB6
    &TIM4_CCR2, // B4, PB7
    &TIM4_CCR3, // B5, PB8
    &TIM4_CCR4, // B6, PB9
    &TIM5_CCR1, // B7, PA0
    &TIM5_CCR2, // B8, PA1
};


static uint8_t current_row = 0;

static DisplayBuf framebuffer[2];
static __IO uint8_t front_buffer = 0;
static __IO uint8_t fb_spin = 0;

/**
  * @brief  This function handles TIM1 global interrupt request.
  * @param  None
  * @retval None
  */
void tim1_up_tim10_isr(void)
{
    uint8_t i;

    if (timer_get_flag(TIM1, TIM_SR_UIF)) {
        /* Clear compare interrupt flag. */
        timer_clear_flag(TIM1, TIM_SR_UIF);

        gpio_clear(row_gpios[current_row].port, row_gpios[current_row].pin);
        current_row = (current_row + 1) % 8;

        if (current_row == 0) {
            gpio_set(GPIOD, GPIO1);
            fb_spin = 1;
        }

        for (i = 0; i < 8; i++) {
            *red[i] = framebuffer[front_buffer][current_row][i].r;
            *green[i] = framebuffer[front_buffer][current_row][i].g;
            *blue[i] = framebuffer[front_buffer][current_row][i].b;
        }

        if (current_row == 7) {
            gpio_clear(GPIOD, GPIO1);
            fb_spin = 0;
        }

        gpio_set(row_gpios[current_row].port, row_gpios[current_row].pin);

        /* Enable TIM1 will start all other slaves */
        timer_enable_counter(TIM1);

        /* ... except TIM13 and TIM14 which aren't synchronized */
        timer_enable_counter(TIM13);
        timer_enable_counter(TIM14);
    }
}

static void display_init_gpio(void)
{
    uint16_t gpios = 0;

    /* Enable GPIO clocks */
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);
    /*rcc_periph_clock_enable(RCC_GPIOD); // debug*/

    /*
     * Columns
     */

    /* PA0,1,2,3: TIM5_CH1,2,3,4 */
    gpios = GPIO0 | GPIO1 | GPIO2 | GPIO3;
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOA, GPIO_AF2, gpios);

    /* PA6,7: TIM13_CH1, TIM14_CH1 */
    gpios = GPIO6 | GPIO7;
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOA, GPIO_AF9, gpios);

    /* PA8,10: TIM1_CH1,3 */
    gpios = GPIO8 | GPIO10;
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOA, GPIO_AF1, gpios);

    /* PB0,1,4,5: TIM3_CH3,4,1,2 */
    gpios = GPIO0 | GPIO1 | GPIO4 | GPIO5;
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOB, GPIO_AF2, gpios);

    /* PB6,7,8,9: TIM4_CH1,2,3,4 */
    gpios = GPIO6 | GPIO7 | GPIO8 | GPIO9;
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOB, GPIO_AF2, gpios);

    /* PB10,11: TIM2_CH3,4 */
    gpios = GPIO10 | GPIO11;
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOB, GPIO_AF1, gpios);

    /* PB14,15: TIM12_CH1,2 */
    gpios = GPIO14 | GPIO15;
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOB, GPIO_AF9, gpios);

    /* PC6,7,8,9: TIM8_CH1,2,3,4 */
    gpios = GPIO6 | GPIO7 | GPIO8 | GPIO9;
    gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOC, GPIO_AF3, gpios);

    /*
     * Rows
     */
    for (int i = 0; i < 8; i++) {
        gpio_mode_setup(row_gpios[i].port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, row_gpios[i].pin);
    }

    // debug
    /*gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,*/
            /*GPIO0 | GPIO1 | GPIO2);*/

    // PA4: OE
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO4);
}

static void display_init_tim(void)
{
    /* Enable TIM clocks */
    rcc_periph_clock_enable(RCC_TIM1);
    rcc_periph_clock_enable(RCC_TIM2);
    rcc_periph_clock_enable(RCC_TIM3);
    rcc_periph_clock_enable(RCC_TIM4);
    rcc_periph_clock_enable(RCC_TIM5);
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
    timer_set_mode(TIM8, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_mode(TIM12, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_mode(TIM13, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_mode(TIM14, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    /* Reset prescaler value. */
    const uint32_t ps = 0;
    timer_set_prescaler(TIM1, 2 * ps + 1);   /* 168MHz */
    timer_set_prescaler(TIM2, ps);
    timer_set_prescaler(TIM3, ps);
    timer_set_prescaler(TIM4, ps);
    timer_set_prescaler(TIM5, ps);
    timer_set_prescaler(TIM8, 2 * ps + 1);   /* 168MHz */
    timer_set_prescaler(TIM12, ps);
    timer_set_prescaler(TIM13, ps);
    timer_set_prescaler(TIM14, ps);

    /* Disable preload. */
    timer_disable_preload(TIM1);
    timer_disable_preload(TIM2);
    timer_disable_preload(TIM3);
    timer_disable_preload(TIM4);
    timer_disable_preload(TIM5);
    timer_disable_preload(TIM8);
    timer_disable_preload(TIM12);
    timer_disable_preload(TIM13);
    timer_disable_preload(TIM14);

    /* Continous mode. */
    timer_one_shot_mode(TIM1);
    timer_one_shot_mode(TIM2);
    timer_one_shot_mode(TIM3);
    timer_one_shot_mode(TIM4);
    timer_one_shot_mode(TIM5);
    timer_one_shot_mode(TIM8);
    timer_one_shot_mode(TIM12);
    timer_one_shot_mode(TIM13);
    timer_one_shot_mode(TIM14);

    /* 16 bit timer (count up to 2^16 - 1) */
    timer_set_period(TIM1, 0xffff);
    timer_set_period(TIM2, 0xffff);
    timer_set_period(TIM3, 0xffff);
    timer_set_period(TIM4, 0xffff);
    timer_set_period(TIM5, 0xffff);
    timer_set_period(TIM8, 0xffff);
    timer_set_period(TIM12, 0xffff);
    timer_set_period(TIM13, 0xffff);
    timer_set_period(TIM14, 0xffff);

    /* Enable outputs */
    timer_enable_oc_output(TIM1, TIM_OC1);
    timer_enable_oc_output(TIM1, TIM_OC3);

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
    timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_PWM1);

    /*timer_set_oc_mode(TIM2, TIM_OC2, TIM_OCM_PWM1);*/
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

    /* OC Polarity high */
    timer_set_oc_polarity_high(TIM1, TIM_OC1);
    timer_set_oc_polarity_high(TIM1, TIM_OC3);

    /*timer_set_oc_polarity_high(TIM2, TIM_OC2);*/
    timer_set_oc_polarity_high(TIM2, TIM_OC3);
    timer_set_oc_polarity_high(TIM2, TIM_OC4);

    timer_set_oc_polarity_high(TIM3, TIM_OC1);
    timer_set_oc_polarity_high(TIM3, TIM_OC2);
    timer_set_oc_polarity_high(TIM3, TIM_OC3);
    timer_set_oc_polarity_high(TIM3, TIM_OC4);

    timer_set_oc_polarity_high(TIM4, TIM_OC1);
    timer_set_oc_polarity_high(TIM4, TIM_OC2);
    timer_set_oc_polarity_high(TIM4, TIM_OC3);
    timer_set_oc_polarity_high(TIM4, TIM_OC4);

    timer_set_oc_polarity_high(TIM5, TIM_OC1);
    timer_set_oc_polarity_high(TIM5, TIM_OC2);
    timer_set_oc_polarity_high(TIM5, TIM_OC3);
    timer_set_oc_polarity_high(TIM5, TIM_OC4);

    timer_set_oc_polarity_high(TIM8, TIM_OC1);
    timer_set_oc_polarity_high(TIM8, TIM_OC2);
    timer_set_oc_polarity_high(TIM8, TIM_OC3);
    timer_set_oc_polarity_high(TIM8, TIM_OC4);

    timer_set_oc_polarity_high(TIM12, TIM_OC1);
    timer_set_oc_polarity_high(TIM12, TIM_OC2);

    timer_set_oc_polarity_high(TIM13, TIM_OC1);

    timer_set_oc_polarity_high(TIM14, TIM_OC1);

    /* OC Value */
    timer_set_oc_value(TIM1, TIM_OC1, 0);
    timer_set_oc_value(TIM1, TIM_OC3, 0);

    /*timer_set_oc_value(TIM2, TIM_OC2, 0);*/
    timer_set_oc_value(TIM2, TIM_OC3, 0);
    timer_set_oc_value(TIM2, TIM_OC4, 0);

    timer_set_oc_value(TIM3, TIM_OC1, 0);
    timer_set_oc_value(TIM3, TIM_OC2, 0);
    timer_set_oc_value(TIM3, TIM_OC3, 0);
    timer_set_oc_value(TIM3, TIM_OC4, 0);

    timer_set_oc_value(TIM4, TIM_OC1, 0);
    timer_set_oc_value(TIM4, TIM_OC2, 0);
    timer_set_oc_value(TIM4, TIM_OC3, 0);
    timer_set_oc_value(TIM4, TIM_OC4, 0);

    timer_set_oc_value(TIM5, TIM_OC1, 0);
    timer_set_oc_value(TIM5, TIM_OC2, 0);
    timer_set_oc_value(TIM5, TIM_OC3, 0);
    timer_set_oc_value(TIM5, TIM_OC4, 0);

    timer_set_oc_value(TIM8, TIM_OC1, 0);
    timer_set_oc_value(TIM8, TIM_OC2, 0);
    timer_set_oc_value(TIM8, TIM_OC3, 0);
    timer_set_oc_value(TIM8, TIM_OC4, 0);

    timer_set_oc_value(TIM12, TIM_OC1, 0);
    timer_set_oc_value(TIM12, TIM_OC2, 0);

    timer_set_oc_value(TIM13, TIM_OC1, 0);

    timer_set_oc_value(TIM14, TIM_OC1, 0);

    /* Enable interrupt for TIM1 */
    timer_enable_irq(TIM1, TIM_DIER_UIE);
    nvic_enable_irq(NVIC_TIM1_UP_TIM10_IRQ);

    /* TIM1 is master */
    timer_set_master_mode(TIM1, TIM_CR2_MMS_ENABLE);

    /* TIM2 is slave of TIM1 */
    timer_slave_set_mode(TIM2, TIM_SMCR_SMS_TM);
    timer_slave_set_trigger(TIM2, TIM_SMCR_TS_ITR0);
    timer_set_master_mode(TIM2, TIM_CR2_MMS_ENABLE);

    /* TIM3 is slave of TIM1 */
    timer_slave_set_mode(TIM3, TIM_SMCR_SMS_TM);
    timer_slave_set_trigger(TIM3, TIM_SMCR_TS_ITR0);

    /* TIM4 is slave of TIM1 */
    timer_slave_set_mode(TIM4, TIM_SMCR_SMS_TM);
    timer_slave_set_trigger(TIM4, TIM_SMCR_TS_ITR0);
    timer_set_master_mode(TIM4, TIM_CR2_MMS_ENABLE);

    /* TIM5 is slave of TIM2 */
    timer_slave_set_mode(TIM5, TIM_SMCR_SMS_TM);
    timer_slave_set_trigger(TIM5, TIM_SMCR_TS_ITR0);

    /* TIM8 is slave of TIM1 */
    timer_slave_set_mode(TIM8, TIM_SMCR_SMS_TM);
    timer_slave_set_trigger(TIM8, TIM_SMCR_TS_ITR0);

    /* TIM12 is slave of TIM4 */
    timer_slave_set_mode(TIM12, TIM_SMCR_SMS_TM);
    timer_slave_set_trigger(TIM12, TIM_SMCR_TS_ITR0);

    /* Enable TIM1 will start all other slaves */
    timer_enable_counter(TIM1);

    /* ... except TIM13 and TIM14 which aren't synchronized */
    timer_enable_counter(TIM13);
    timer_enable_counter(TIM14);
}

static void display_enable()
{
    // Pull OE low to enable column drivers
    gpio_clear(GPIOA, GPIO4);
}

void display_init()
{
    display_init_gpio();
    display_init_tim();
    display_enable();
}

DisplayBuf *display_get_backbuffer(void)
{
    uint8_t back_buffer = (front_buffer + 1) % 2;
    return &framebuffer[back_buffer];
}

void display_swapbuffers(void)
{
    while (fb_spin == 1)
        ;
    gpio_set(GPIOD, GPIO0);
    front_buffer = (front_buffer + 1) % 2;
    fb_spin = 1;
    gpio_clear(GPIOD, GPIO0);
}

void display_clear(DisplayBuf *buf, uint16_t r, uint16_t g, uint16_t b)
{
    unsigned int i, j;

    memset(buf, 0, sizeof(*buf));

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            (*buf)[i][j].r = r;
            (*buf)[i][j].g = g;
            (*buf)[i][j].b = b;
        }
    }
}

void display_set(DisplayBuf *buf, unsigned int x, unsigned int y,
        uint16_t r, uint16_t g, uint16_t b)
{
    (*buf)[y % 8][x % 8].r = r;
    (*buf)[y % 8][x % 8].g = g;
    (*buf)[y % 8][x % 8].b = b;
}

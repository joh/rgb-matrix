#include <string.h>

#include <libopencmsis/core_cm3.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include "display.h"

static uint16_t row_gpios[] = {GPIO0 , GPIO1 , GPIO2 , GPIO3 , GPIO4 , GPIO5 , GPIO10 , GPIO11};
static __IO uint32_t *red[8];
static __IO uint32_t *green[8];
static __IO uint32_t *blue[8];

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

        gpio_clear(GPIOC, row_gpios[current_row]);
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

        gpio_set(GPIOC, row_gpios[current_row]);

        /* Enable TIM1 will start all other slaves */
        timer_enable_counter(TIM1);
    }
}

static void display_init_gpio(void)
{
    uint16_t gpios = 0;

    /* Enable GPIO clocks */
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_GPIOD); // debug
    rcc_periph_clock_enable(RCC_GPIOE);

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

    /* PE5-6: TIM9 channels 1,2 */
    gpios = GPIO5 | GPIO6;
    gpio_mode_setup(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOE, GPIO_AF3, gpios);

    /* PB14-15: TIM12 channels 1,2 */
    gpios = GPIO14 | GPIO15;
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOB, GPIO_AF9, gpios);

    /*
     * Rows on PC0-5,10-11
     */
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO10 | GPIO11);

    // debug
    gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
            GPIO0 | GPIO1 | GPIO2);
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
    rcc_periph_clock_enable(RCC_TIM9);
    rcc_periph_clock_enable(RCC_TIM12);

    /* Reset TIMs */
    timer_reset(TIM1);
    timer_reset(TIM2);
    timer_reset(TIM3);
    timer_reset(TIM4);
    timer_reset(TIM5);
    timer_reset(TIM8);
    timer_reset(TIM9);
    timer_reset(TIM12);

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
    timer_set_mode(TIM9, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_mode(TIM12, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    /* Reset prescaler value. */
    const uint32_t ps = 0;
    timer_set_prescaler(TIM1, 2 * ps + 1);   /* 168MHz */
    timer_set_prescaler(TIM2, ps);
    timer_set_prescaler(TIM3, ps);
    timer_set_prescaler(TIM4, ps);
    timer_set_prescaler(TIM5, ps);
    timer_set_prescaler(TIM8, 2 * ps + 1);   /* 168MHz */
    timer_set_prescaler(TIM9, 2 * ps + 1);   /* 168MHz */
    timer_set_prescaler(TIM12, ps);

    /* Disable preload. */
    timer_disable_preload(TIM1);
    timer_disable_preload(TIM2);
    timer_disable_preload(TIM3);
    timer_disable_preload(TIM4);
    timer_disable_preload(TIM5);
    timer_disable_preload(TIM8);
    timer_disable_preload(TIM9);
    timer_disable_preload(TIM12);

    /* Continous mode. */
    timer_one_shot_mode(TIM1);
    timer_one_shot_mode(TIM2);
    timer_one_shot_mode(TIM3);
    timer_one_shot_mode(TIM4);
    timer_one_shot_mode(TIM5);
    timer_one_shot_mode(TIM8);
    timer_one_shot_mode(TIM9);
    timer_one_shot_mode(TIM12);

    /* 16 bit timer (count up to 2^16 - 1) */
    timer_set_period(TIM1, 0xffff);
    timer_set_period(TIM2, 0xffff);
    timer_set_period(TIM3, 0xffff);
    timer_set_period(TIM4, 0xffff);
    timer_set_period(TIM5, 0xffff);
    timer_set_period(TIM8, 0xffff);
    timer_set_period(TIM9, 0xffff);
    timer_set_period(TIM12, 0xffff);

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

    timer_enable_oc_output(TIM9, TIM_OC1);
    timer_enable_oc_output(TIM9, TIM_OC2);

    timer_enable_oc_output(TIM12, TIM_OC1);
    timer_enable_oc_output(TIM12, TIM_OC2);

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

    timer_set_oc_mode(TIM9, TIM_OC1, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM9, TIM_OC2, TIM_OCM_PWM1);

    timer_set_oc_mode(TIM12, TIM_OC1, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM12, TIM_OC2, TIM_OCM_PWM1);

    /* OC Polarity high */
    timer_set_oc_polarity_high(TIM1, TIM_OC1);

    timer_set_oc_polarity_high(TIM2, TIM_OC2);
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

    timer_set_oc_polarity_high(TIM9, TIM_OC1);
    timer_set_oc_polarity_high(TIM9, TIM_OC2);

    timer_set_oc_polarity_high(TIM12, TIM_OC1);
    timer_set_oc_polarity_high(TIM12, TIM_OC2);

    /* OC Value */
    timer_set_oc_value(TIM1, TIM_OC1, 0);

    timer_set_oc_value(TIM2, TIM_OC2, 0);
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

    timer_set_oc_value(TIM9, TIM_OC1, 0);
    timer_set_oc_value(TIM9, TIM_OC2, 0);

    timer_set_oc_value(TIM12, TIM_OC1, 0);
    timer_set_oc_value(TIM12, TIM_OC2, 0);

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

    /* TIM9 is slave of TIM2 */
    timer_slave_set_mode(TIM9, TIM_SMCR_SMS_TM);
    timer_slave_set_trigger(TIM9, TIM_SMCR_TS_ITR0);

    /* TIM12 is slave of TIM4 */
    timer_slave_set_mode(TIM12, TIM_SMCR_SMS_TM);
    timer_slave_set_trigger(TIM12, TIM_SMCR_TS_ITR0);

    /* Enable TIM1 will start all other slaves */
    timer_enable_counter(TIM1);
}


void display_init()
{
    display_init_gpio();
    display_init_tim();

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
    blue[4] = &TIM9_CCR1;
    blue[5] = &TIM9_CCR2;
    blue[6] = &TIM12_CCR1;
    blue[7] = &TIM12_CCR2;
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

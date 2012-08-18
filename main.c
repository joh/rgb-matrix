/*
 * RGB LED with PWM on STM32!
 */

#include "stm32f10x.h"
#include "hsv.h"

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;

void RCC_Configuration(void);
void GPIO_Configuration(void);

#define STM32_DELAY_US_MULT 8

/**
 * @brief Delay the given number of microseconds.
 *
 * @param us Number of microseconds to delay.
 */
static inline void delay_us(uint32_t us)
{
    us *= STM32_DELAY_US_MULT;

    /* fudge for function call overhead  */
    us--;
    asm volatile("   mov r0, %[us]          \n\t"
                 "1: subs r0, #1            \n\t"
                 "   bhi 1b                 \n\t"
                 :
                 : [us] "r" (us)
                 : "r0");
}


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

int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     

    __IO uint16_t *red[] = {
        &(TIM1->CCR1),
        &(TIM1->CCR2),
        &(TIM1->CCR3),
        &(TIM1->CCR4),
        &(TIM2->CCR2),
        &(TIM2->CCR3),
        &(TIM2->CCR4),
        &(TIM3->CCR1),
    };

    /* System Clocks Configuration */
    RCC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    /* Time base configuration */
    // 16 bit timer (count up to 2^16 - 1)
    TIM_TimeBaseStructure.TIM_Period = 0xffff;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* PWM1 Mode configuration */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_Pulse = 0;

    /* R1 = TIM1_CH1 */
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    /* R2 = TIM1_CH2 */
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);

    /* R3 = TIM1_CH3 */
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);

    /* R4 = TIM1_CH4 */
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);

    /* TIM1 enable counter */
    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);


    /* R5 = TIM2_CH2 */
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);

    /* R6 = TIM2_CH3 */
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);

    /* R7 = TIM2_CH4 */
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);

    /* TIM2 enable counter */
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);


    /* R8 = TIM3_CH1 */
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);

    /* TIM3 enable counter */
    TIM_ARRPreloadConfig(TIM3, ENABLE);
    TIM_Cmd(TIM3, ENABLE);

    uint32_t i;
    uint32_t delay = 1000;
    while (1) {
        // 2x2 square test
        /*
        GPIO_Write(GPIOB, 0);
        *red[0] = 0x8fff;
        *red[1] = 0;
        TIM1->CNT = 0;
        GPIO_Write(GPIOB, 1 << 8);

        delay_us(delay);

        GPIO_Write(GPIOB, 0);
        *red[0] = 0;
        *red[1] = 0x8fff;
        TIM1->CNT = 0;
        GPIO_Write(GPIOB, 2 << 8);

        delay_us(delay);

        continue;
        */

        // Single row test
        /*
        for (i = 0; i < 8; i++) {
            *red[i] = 0xfff;
        }
        GPIO_Write(GPIOB, 1 << 15);
        while(1){}
        */

        // Single column test
        /*
        for (i = 0; i < 8; i++) {
            *red[i] = 0;
        }
        *red[0] = 0xffff;
        while(1){
            for (i = 0; i < 8; i++) {
                GPIO_Write(GPIOB, 1 << (i + 8));
                delay_us(1000);
            }
        }
        */

        // Diagonal line test
        for (i = 0; i < 8; i++) {
            GPIO_Write(GPIOB, 0);
            if (i == 0) {
                *red[7] = 0;
            } else {
                *red[i - 1] = 0;
            }
            *red[i] = 0xffff;
            // Not sure if we need this
            TIM1->CNT = 0;
            TIM2->CNT = 0;
            TIM3->CNT = 0;
            GPIO_Write(GPIOB, 1 << (i + 8));
            delay_us(1000);
        }
    }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
    /* TIM1 clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    /* TIM2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    /* GPIOA and GPIOB clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                           RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
}

/**
  * @brief  Configure the TIM3 Ouput Channels.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOA Configuration: TIM1 channel 1, 2, 3 and 4 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* GPIOA Configuration: TIM2 channel 2, 3 and 4 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* GPIOA Configuration: TIM3 channel 1 and 2 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* GPIOB Configuration (ROWs) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    while (1)
    {}
}

#endif

#include <stdio.h>
#include <libopencmsis/core_cm3.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/syscfg.h>

#include "spi.h"
#include "spi-daisy.h"
#include "display.h"
#include "utils.h"

static volatile uint8_t spi_bytes_rcvd = 0;

/* Write position display backbuffer */
static __IO unsigned int dispbuf_pos = 0;

/* SPI slave */
void spi3_isr(void)
{
    uint8_t *dispbuf = (uint8_t *)display_get_backbuffer();
    uint8_t byte = SPI_DR(SPI3);

    /* Fill framebuffer with received byte */
    dispbuf[dispbuf_pos] = byte;
    dispbuf_pos = (dispbuf_pos + 1) % sizeof(DisplayBuf);

    /* Forward next (oldest) byte in framebuffer to the daisy chain */
    spi_daisy_write(dispbuf[dispbuf_pos]);

    /* Prepare next (oldest) byte in the framebuffer for the next transmission */
    SPI_DR(SPI3) = dispbuf[dispbuf_pos];
}

void spi_slave_init()
{
    uint16_t gpios = 0;

    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_SYSCFG);
    rcc_periph_clock_enable(RCC_SPI3);

    /* PC10,11,12: SPI3_{SCK,MISO,MOSI} */
    gpios = GPIO10 | GPIO11 | GPIO12;
    gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOC, GPIO_AF6, gpios);

    /* PA15: SPI3_NSS */
    gpios = GPIO15;
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, gpios);
    gpio_set_af(GPIOA, GPIO_AF6, gpios);

    /* Configure interrupt on rising edge of SPI3_NSS */
    nvic_enable_irq(NVIC_EXTI15_10_IRQ);
    exti_select_source(EXTI15, GPIOA);
    exti_set_trigger(EXTI15, EXTI_TRIGGER_RISING);
    exti_enable_request(EXTI15);

    /* Configure SPI slave */
    spi_set_dff_8bit(SPI3);
    spi_set_standard_mode(SPI3, 0); // Sets CPOL, CPHA
    spi_send_msb_first(SPI3);
    spi_set_slave_mode(SPI3);

    /* Enable SPI interrupts */
    nvic_enable_irq(NVIC_SPI3_IRQ);
    spi_enable_rx_buffer_not_empty_interrupt(SPI3);

    spi_enable(SPI3);
}

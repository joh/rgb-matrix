#include <stdio.h>
#include <libopencmsis/core_cm3.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/syscfg.h>

#include "spi.h"
#include "display.h"
#include "utils.h"

static volatile uint8_t spi_bytes_rcvd = 0;

/* Write position display backbuffer */
static __IO unsigned int dispbuf_pos = 0;

/* Whether we're master or slave in the daisy chain */
static bool daisy_is_master = false;

/* IRQ on SPI2_NSS/SPI3_NSS rising edge */
void exti15_10_isr(void)
{
    exti_reset_request(EXTI15 | EXTI12);
    /* Signal swapbuffers. The display code will
     * call spi_daisy_swapbuffers() when complete. */
    display_swapbuffers_nowait();
    dispbuf_pos = 0;
}

/* Called right after swapbuffers is done */
void spi_daisy_swapbuffers(void)
{
    if (daisy_is_master)
        return;

    uint8_t *dispbuf = (uint8_t *)display_get_backbuffer();

    /* Slaves in the daisy chain need to prepare the TX buffer so it's ready
     * when the first byte is clocked in to the RX buffer. Fill the TX buffer
     * with the first byte to be overwritten in the framebuffer */
    spi_daisy_write(dispbuf[0]);
}

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

/* Daisy slave */
void spi2_isr(void)
{
    uint8_t *dispbuf = (uint8_t *)display_get_backbuffer();
    uint8_t byte = SPI_DR(SPI2);

    /* Fill framebuffer with received byte */
    dispbuf[dispbuf_pos] = byte;
    dispbuf_pos = (dispbuf_pos + 1) % sizeof(DisplayBuf);

    /* Prepare next (oldest) byte in the framebuffer for the next transmission */
    SPI_DR(SPI2) = dispbuf[dispbuf_pos];
}

void spi_daisy_init_master()
{
    uint16_t gpios = 0;

    spi_disable(SPI2);

    spi_set_master_mode(SPI2);
    spi_set_baudrate_prescaler(SPI2, 7); // TODO: increase once debug phase is over
    spi_enable_ss_output(SPI2);

    /* PB12: SPI2_NSS (controlled by master) */
    gpios = GPIO12;
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, gpios);
    spi_daisy_set_nss_low();

    /* Don't need interrupts in master mode */
    nvic_disable_irq(NVIC_SPI2_IRQ);
    spi_disable_rx_buffer_not_empty_interrupt(SPI2);

    exti_disable_request(EXTI12);

    spi_enable(SPI2);

    daisy_is_master = true;
}

void spi_daisy_init_slave()
{
    uint16_t gpios = 0;

    spi_disable(SPI2);

    spi_set_slave_mode(SPI2);

    nvic_enable_irq(NVIC_SPI2_IRQ);
    spi_enable_rx_buffer_not_empty_interrupt(SPI2);

    /* PB12: SPI2_NSS (NSS input in slave mode) */
    gpios = GPIO12;
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, gpios);
    gpio_set_af(GPIOB, GPIO_AF5, gpios);

    /* Configure interrupt on rising edge of SPI2_NSS */
    nvic_enable_irq(NVIC_EXTI15_10_IRQ);
    exti_select_source(EXTI12, GPIOB);
    exti_set_trigger(EXTI12, EXTI_TRIGGER_RISING);
    exti_enable_request(EXTI12);

    spi_enable(SPI2);

    daisy_is_master = false;
}

void spi_daisy_set_nss_low()
{
    gpio_clear(GPIOB, GPIO12);
}

void spi_daisy_set_nss_high()
{
    /* Wait for any pending transmission to complete */
    while (!(SPI_SR(SPI2) & SPI_SR_TXE));
    while ((SPI_SR(SPI2) & SPI_SR_BSY));
    /* TODO: Sleep needed when testing with the BusPirate spisniffer.
     * Check if needed with daisy chain device at full speed */
    usleep(10);

    gpio_set(GPIOB, GPIO12);
}

void spi_daisy_send(uint16_t data)
{
    spi_send(SPI2, data);
}

/* Non-blocking */
void spi_daisy_write(uint16_t data)
{
    spi_write(SPI2, data);
}

bool spi_daisy_is_master(void)
{
    return daisy_is_master;
}

void spi_daisy_init()
{
    uint16_t gpios = 0;

    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_SYSCFG);
    rcc_periph_clock_enable(RCC_SPI2);

    /* PB13: SPI2_SCK */
    gpios = GPIO13;
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOB, GPIO_AF5, gpios);

    /* PC2,3: SPI2_{MISO,MOSI} */
    gpios = GPIO2 | GPIO3;
    gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, gpios);
    gpio_set_af(GPIOC, GPIO_AF5, gpios);

    /* Common SPI stuff */
    spi_set_standard_mode(SPI2, 0); // Sets CPOL, CPHA
    spi_set_dff_8bit(SPI2);
    spi_send_msb_first(SPI2);

    /* Set slave mode by default */
    spi_daisy_init_slave();
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

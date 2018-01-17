#include <stdio.h>
#include <libopencmsis/core_cm3.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/syscfg.h>

#include "spi-daisy.h"
#include "display.h"
#include "utils.h"

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

    /* SPI2 RX */
    dma_disable_stream(DMA1, DMA_STREAM3);
    dma_set_memory_address(DMA1, DMA_STREAM3, (uint32_t) dispbuf);
    dma_enable_stream(DMA1, DMA_STREAM3);

    /* SPI2 TX */
    dma_disable_stream(DMA1, DMA_STREAM4);
    /* At this point, SPI2_DR will contain the first byte of the front buffer,
     * due to the circular DMA mode wrapping around. This incorrect byte will
     * be transferred first, but eventually past the last buffer in the daisy
     * chain. In order for the DMA number of data items to be correctly
     * aligned, we need to offset the memory address by one. */
    dma_set_memory_address(DMA1, DMA_STREAM4, (uint32_t) (dispbuf+1));
    dma_enable_stream(DMA1, DMA_STREAM4);
}

void spi_daisy_init_master()
{
    uint16_t gpios = 0;

    spi_disable(SPI2);

    spi_set_master_mode(SPI2);

    /* ~1.3MHz SPI clock */
    /* Faster clocks cause overrun errors on the receiving end, i.e. the OVR
     * bit is set in the SPI_SR register */
    spi_set_baudrate_prescaler(SPI2, 1);
    spi_enable_ss_output(SPI2);

    /* PB12: SPI2_NSS (controlled by master) */
    gpios = GPIO12;
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, gpios);

    /* Don't need interrupts in master mode */
    nvic_disable_irq(NVIC_SPI2_IRQ);
    spi_disable_rx_buffer_not_empty_interrupt(SPI2);

    exti_disable_request(EXTI12);

    /* No DMA in master mode */
    spi_disable_rx_dma(SPI2);
    spi_disable_tx_dma(SPI2);
    dma_disable_stream(DMA1, DMA_STREAM3);
    dma_disable_stream(DMA1, DMA_STREAM4);

    /* HACK: SPI_DR has already been written to by DMA initiated by
     * spi_daisy_init_slave, and there's no way to flush the transmit buffer
     * from software. So we hold NSS high while we flush the data, so it is
     * ignored by the slaves. */
    spi_daisy_set_nss_high();

    spi_enable(SPI2);

    spi_daisy_wait();
    spi_daisy_set_nss_low();

    daisy_is_master = true;
}

void spi_daisy_init_slave()
{
    uint16_t gpios = 0;

    spi_disable(SPI2);

    spi_set_slave_mode(SPI2);

    /* PB12: SPI2_NSS (NSS input in slave mode) */
    gpios = GPIO12;
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, gpios);
    gpio_set_af(GPIOB, GPIO_AF5, gpios);

    /* Configure interrupt on rising edge of SPI2_NSS */
    nvic_enable_irq(NVIC_EXTI15_10_IRQ);
    exti_select_source(EXTI12, GPIOB);
    exti_set_trigger(EXTI12, EXTI_TRIGGER_RISING);
    exti_enable_request(EXTI12);

    /* Configure DMA */
    rcc_periph_clock_enable(RCC_DMA1);

    uint8_t *dispbuf = (uint8_t *)display_get_backbuffer();

    /* SPI2 RX */
    dma_stream_reset(DMA1, DMA_STREAM3);
    dma_set_priority(DMA1, DMA_STREAM3, DMA_SxCR_PL_VERY_HIGH);
    dma_set_memory_size(DMA1, DMA_STREAM3, DMA_SxCR_MSIZE_8BIT);
    dma_set_peripheral_size(DMA1, DMA_STREAM3, DMA_SxCR_PSIZE_8BIT);
    dma_enable_memory_increment_mode(DMA1, DMA_STREAM3);
    dma_enable_circular_mode(DMA1, DMA_STREAM3);
    dma_set_transfer_mode(DMA1, DMA_STREAM3,
            DMA_SxCR_DIR_PERIPHERAL_TO_MEM);
    dma_set_peripheral_address(DMA1, DMA_STREAM3, (uint32_t) &SPI2_DR);
    dma_set_memory_address(DMA1, DMA_STREAM3, (uint32_t) dispbuf);
    dma_set_number_of_data(DMA1, DMA_STREAM3, sizeof(DisplayBuf));
    dma_channel_select(DMA1, DMA_STREAM3, DMA_SxCR_CHSEL_0);
    dma_enable_stream(DMA1, DMA_STREAM3);

    spi_enable_rx_dma(SPI2);

    /* SPI2 TX */
    dma_stream_reset(DMA1, DMA_STREAM4);
    dma_set_priority(DMA1, DMA_STREAM4, DMA_SxCR_PL_HIGH);
    dma_set_memory_size(DMA1, DMA_STREAM4, DMA_SxCR_MSIZE_8BIT);
    dma_set_peripheral_size(DMA1, DMA_STREAM4, DMA_SxCR_PSIZE_8BIT);
    dma_enable_memory_increment_mode(DMA1, DMA_STREAM4);
    dma_enable_circular_mode(DMA1, DMA_STREAM4);
    dma_set_transfer_mode(DMA1, DMA_STREAM4,
            DMA_SxCR_DIR_MEM_TO_PERIPHERAL);
    dma_set_peripheral_address(DMA1, DMA_STREAM4, (uint32_t) &SPI2_DR);
    dma_set_memory_address(DMA1, DMA_STREAM4, (uint32_t) dispbuf);
    dma_set_number_of_data(DMA1, DMA_STREAM4, sizeof(DisplayBuf));
    dma_channel_select(DMA1, DMA_STREAM4, DMA_SxCR_CHSEL_0);
    dma_enable_stream(DMA1, DMA_STREAM4);

    spi_enable_tx_dma(SPI2);

    spi_enable(SPI2);

    daisy_is_master = false;
}

void spi_daisy_set_nss_low()
{
    gpio_clear(GPIOB, GPIO12);
}

void spi_daisy_set_nss_high()
{
    gpio_set(GPIOB, GPIO12);
}

void spi_daisy_wait()
{
    /* Wait for any pending transmission to complete */
    while (!(SPI_SR(SPI2) & SPI_SR_TXE));
    while ((SPI_SR(SPI2) & SPI_SR_BSY));
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

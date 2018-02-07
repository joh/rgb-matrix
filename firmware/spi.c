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

/* SPI packet */
struct spi_packet {
    uint8_t cmd;
    uint8_t data[64];
};

/* FIFO of packets */
#define FIFO_SIZE 16
static __IO struct spi_packet spi_fifo[FIFO_SIZE];
static __IO size_t fifo_write_pos = 0;
static __IO size_t fifo_read_pos = 0;


void dma1_stream2_isr(void)
{
    if (dma_get_interrupt_flag(DMA1, DMA_STREAM2, DMA_TCIF)) {
        dma_clear_interrupt_flags(DMA1, DMA_STREAM2, DMA_TCIF);

        fifo_write_pos = (fifo_write_pos + 1) % FIFO_SIZE;

#ifdef DEBUG
        if (fifo_write_pos == fifo_read_pos) {
            printf("OVF %d!\n", fifo_write_pos);
        }
#endif

        dma_set_memory_address(DMA1, DMA_STREAM2, (uint32_t)&spi_fifo[fifo_write_pos]);
        dma_enable_stream(DMA1, DMA_STREAM2);
    }
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

    /* Configure SPI slave */
    spi_set_dff_8bit(SPI3);
    spi_set_standard_mode(SPI3, 0); // Sets CPOL, CPHA
    spi_send_msb_first(SPI3);
    spi_set_slave_mode(SPI3);

    /* Configure DMA */
    rcc_periph_clock_enable(RCC_DMA1);

    /* SPI3 RX */
    dma_stream_reset(DMA1, DMA_STREAM2);
    dma_set_priority(DMA1, DMA_STREAM2, DMA_SxCR_PL_VERY_HIGH);
    dma_set_memory_size(DMA1, DMA_STREAM2, DMA_SxCR_MSIZE_8BIT);
    dma_set_peripheral_size(DMA1, DMA_STREAM2, DMA_SxCR_PSIZE_8BIT);
    dma_enable_memory_increment_mode(DMA1, DMA_STREAM2);
    dma_set_transfer_mode(DMA1, DMA_STREAM2,
            DMA_SxCR_DIR_PERIPHERAL_TO_MEM);
    dma_set_peripheral_address(DMA1, DMA_STREAM2, (uint32_t) &SPI3_DR);
    dma_set_memory_address(DMA1, DMA_STREAM2, (uint32_t)&spi_fifo[0]);
    dma_set_number_of_data(DMA1, DMA_STREAM2, sizeof(spi_fifo[0]));
    dma_channel_select(DMA1, DMA_STREAM2, DMA_SxCR_CHSEL_0);
    dma_enable_stream(DMA1, DMA_STREAM2);

    spi_enable_rx_dma(SPI3);

    /* DMA interrupts */
    nvic_enable_irq(NVIC_DMA1_STREAM2_IRQ);
    dma_enable_transfer_complete_interrupt(DMA1, DMA_STREAM2);

    spi_enable(SPI3);
}

void spi_poll(void)
{
    if (fifo_read_pos == fifo_write_pos)
        // Nothing to do
        return;

    __IO struct spi_packet *pkt = &spi_fifo[fifo_read_pos];

    if (pkt->cmd == SPI_CMD_WRITE) {
        uint8_t *dispbuf = (uint8_t *)display_get_backbuffer();

        for (unsigned int i = 0; i < sizeof(pkt->data); i++) {
            spi_daisy_send(dispbuf[dispbuf_pos]);
            dispbuf[dispbuf_pos] = pkt->data[i];
            dispbuf_pos = (dispbuf_pos + 1) % sizeof(DisplayBuf);
        }
    } else if (pkt->cmd == SPI_CMD_SWAPBUFFERS) {
        spi_daisy_wait();
        spi_daisy_set_nss_high();
        display_swapbuffers();
        dispbuf_pos = 0;
        spi_daisy_set_nss_low();

        /* Vertical refresh rate is 160 hz, so wait for one whole period
         * (6.25ms) to give all daisy chained displays time to swap */
        usleep(6250);
    }

    fifo_read_pos = (fifo_read_pos + 1) % FIFO_SIZE;
}

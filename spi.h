#ifndef SPI_H
#define SPI_H

void spi_daisy_init(void);
void spi_daisy_init_master(void);
void spi_daisy_init_slave(void);
void spi_daisy_set_nss_low(void);
void spi_daisy_set_nss_high(void);
void spi_daisy_send(uint16_t data);
void spi_daisy_write(uint16_t data);
bool spi_daisy_is_master(void);
void spi_daisy_swapbuffers(void);

void spi_slave_init(void);

#endif

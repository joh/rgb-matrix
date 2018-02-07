#ifndef SPI_H
#define SPI_H

#define SPI_CMD_NONE 0x00
#define SPI_CMD_WRITE 0x01
#define SPI_CMD_SWAPBUFFERS 0x02

void spi_slave_init(void);
void spi_poll(void);

#endif

/*
 * platform.h
 *
 *  Created on: Jan 30, 2026
 *      Author: manhhai
 */

#ifndef INC_PLATFORM_H_
#define INC_PLATFORM_H_

#include "main.h"
#include "pubsub.h"

typedef enum
{
	SPI_PORT_1 = 0,
	SPI_PORT_TOTAL,
} spi_port_t;

char platform_init();

// platform_spi.c
char platform_spi_init();
char platform_spi_write_read_dma(spi_port_t port, uint8_t *pTxData, uint8_t *pRxData, uint16_t size);
char platform_spi_write_read_blocking(spi_port_t port, uint8_t *pTxData, uint8_t *pRxData, uint16_t size);
void platform_spi_cs_high (void);
void platform_spi_cs_low (void);

// platform_system.c
void platform_system_init();
void platform_system_delay_ms(uint32_t ms);
uint32_t platform_system_millis();
uint32_t platform_system_micros();

#endif /* INC_PLATFORM_H_ */

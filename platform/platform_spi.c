/*
 * platform_spi.c
 *
 *  Created on: Jan 30, 2026
 *      Author: manhhai
 */

#include "platform.h"

extern SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef *spi_port[SPI_PORT_TOTAL] = {&hspi1};

char platform_spi_init()
{
	return 0;
}

char platform_spi_write_read_dma(spi_port_t port, uint8_t *pTxData, uint8_t *pRxData, uint16_t size)
{
	return HAL_SPI_TransmitReceive_DMA(spi_port[port], pTxData, pRxData, size);
}

char platform_spi_write_read_blocking(spi_port_t port, uint8_t *pTxData, uint8_t *pRxData, uint16_t size)
{
	return HAL_SPI_TransmitReceive(spi_port[port], pTxData, pRxData, size, 10);
}

void platform_spi_cs_high (void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, SET);
}

void platform_spi_cs_low (void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, RESET);
}

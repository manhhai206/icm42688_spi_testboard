/*
 * platform_i2c.c
 *
 *  Created on: Feb 2, 2026
 *      Author: manhhai
 */

#include "platform.h"

extern I2C_HandleTypeDef hi2c3;
I2C_HandleTypeDef *i2c_port[I2C_PORT_TOTAL] = {&hi2c3};

char platform_i2c_init()
{
	return 0;
}

char platform_i2c_mem_write_blocking(i2c_port_t port,uint16_t devAddr, uint16_t memAddr, uint16_t memAddrSize, uint8_t *data, uint16_t size, uint32_t timeout)
{
	return HAL_I2C_Mem_Write(i2c_port[port], devAddr, memAddr, memAddrSize, data, size, timeout);
}

char platform_i2c_mem_read_blocking(i2c_port_t port,uint16_t devAddr, uint16_t memAddr, uint16_t memAddrSize, uint8_t *data, uint16_t size, uint32_t timeout)
{
	return HAL_I2C_Mem_Read(i2c_port[port], devAddr, memAddr, memAddrSize, data, size, timeout);
}

char platform_i2c_mem_read_dma(i2c_port_t port,uint16_t devAddr, uint16_t memAddr, uint16_t memAddrSize, uint8_t *data, uint16_t size)
{
	return HAL_I2C_Mem_Read_DMA(i2c_port[port], devAddr, memAddr, memAddrSize, data, size);
}


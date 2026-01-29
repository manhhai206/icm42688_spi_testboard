/*
 * I2c.c
 *
 *  Created on: Jan 14, 2026
 *      Author: manhhai
 */

#include "../drvs/Inc/i2c_drv.h"

#include "main.h"

/* ============================================
 * Internal Channel Configuration
 * ============================================ */
extern I2C_HandleTypeDef hi2c3;
struct I2c_Handle_s
{
    I2C_HandleTypeDef *hal;  
};
static struct I2c_Handle_s i2c3_handle;
static I2c_ConfigType *I2c_ChannelConfig[I2C_CHANNEL_TOTAL] = { 0 };

/* =========================================================
 * Private Function
 * ========================================================= */
static I2C_Status_t I2c_Register (I2c_ConfigType *ConfigPtr, I2C_DRV_HARDWARE type);
static inline I2c_Handle *
I2c_GetHandle(const I2c_ConfigType *ConfigPtr)
{
    return ConfigPtr->hi2c;
}

/******************************************************************
 * @brief Initialize I2C driver
 * @param[in] ConfigPtr Pointer to I2C configuration array
 ******************************************************************/
I2C_Status_t I2C_Init (I2c_ConfigType *ConfigPtr, I2c_InitConfigType *ConfigPtr_init)
{
	if ((ConfigPtr == NULL) || (ConfigPtr_init == NULL))
	        return I2C_ERROR;

    if (I2c_Register(ConfigPtr, ConfigPtr_init->type) != I2C_OK)
        	return I2C_ERROR;

	ConfigPtr->cb = ConfigPtr_init->cb;
	ConfigPtr->cb_arg = ConfigPtr_init->cb_arg;
	ConfigPtr->mode = ConfigPtr_init->mode;
	return I2C_OK;
}

I2C_Status_t I2C_MemWrite(I2c_ConfigType *ConfigPtr, uint16_t devAddr, uint16_t memAddr, uint16_t memAddrSize,
                          uint8_t *data, uint16_t size, uint32_t timeout)
{
	I2c_Handle *handle = I2c_GetHandle(ConfigPtr);
	switch (ConfigPtr->mode)
	    {
	        case I2C_MODE_POLLING:
	            return (HAL_I2C_Mem_Write(handle->hal, devAddr, memAddr, memAddrSize, data, size, timeout) == HAL_OK)
	                   ? I2C_OK : I2C_ERROR;

	        case I2C_MODE_IT:
	            return (HAL_I2C_Mem_Write_IT(handle->hal, devAddr, memAddr, memAddrSize, data, size) == HAL_OK)
	                   ? I2C_OK : I2C_ERROR;

	        case I2C_MODE_DMA:
	            return (HAL_I2C_Mem_Write_DMA(handle->hal, devAddr, memAddr, memAddrSize, data, size) == HAL_OK)
	                   ? I2C_OK : I2C_ERROR;

	        default:
	            break;
	    }
	    return I2C_ERROR;
}

I2C_Status_t I2C_MemRead(I2c_ConfigType *ConfigPtr, uint16_t devAddr, uint16_t memAddr, uint16_t memAddrSize,
        				uint8_t *data, uint16_t size, uint32_t timeout)
{
	I2c_Handle *handle = I2c_GetHandle(ConfigPtr);
	switch (ConfigPtr->mode)
    {
        case I2C_MODE_POLLING:
            return (HAL_I2C_Mem_Read(handle->hal, devAddr, memAddr, memAddrSize, data, size, timeout) == HAL_OK)
                   ? I2C_OK : I2C_ERROR;

        case I2C_MODE_IT:
            return (HAL_I2C_Mem_Read_IT(handle->hal, devAddr, memAddr, memAddrSize, data, size) == HAL_OK)
                   ? I2C_OK : I2C_ERROR;

        case I2C_MODE_DMA:
            return (HAL_I2C_Mem_Read_DMA(handle->hal, devAddr, memAddr, memAddrSize, data, size) == HAL_OK)
                   ? I2C_OK : I2C_ERROR;

        default:
            break;
    }
    return I2C_ERROR;
}

I2C_Status_t I2C_MasterWrite(I2c_ConfigType *ConfigPtr, uint16_t devAddr, uint8_t *data, uint16_t size, uint32_t timeout)
{
	I2c_Handle *handle = I2c_GetHandle(ConfigPtr);
	switch (ConfigPtr->mode)
    {
        case I2C_MODE_POLLING:
            return (HAL_I2C_Master_Transmit(handle->hal, devAddr, data, size, timeout) == HAL_OK)
                   ? I2C_OK : I2C_ERROR;

        case I2C_MODE_IT:
            return (HAL_I2C_Master_Transmit_IT(handle->hal, devAddr, data, size) == HAL_OK)
                   ? I2C_OK : I2C_ERROR;

        case I2C_MODE_DMA:
            return (HAL_I2C_Master_Transmit_DMA(handle->hal, devAddr, data, size) == HAL_OK)
                   ? I2C_OK : I2C_ERROR;

        default:
            break;
    }
    return I2C_ERROR;
}

I2C_Status_t I2C_MasterRead(I2c_ConfigType *ConfigPtr, uint16_t devAddr, uint8_t *data, uint16_t size, uint32_t timeout)
{
	I2c_Handle *handle = I2c_GetHandle(ConfigPtr);
	switch (ConfigPtr->mode)
    {
        case I2C_MODE_POLLING:
            return (HAL_I2C_Master_Receive(handle->hal, devAddr, data, size, timeout) == HAL_OK)
                   ? I2C_OK : I2C_ERROR;

        case I2C_MODE_IT:
            return (HAL_I2C_Master_Receive_IT(handle->hal, devAddr, data, size) == HAL_OK)
                    ? I2C_OK : I2C_ERROR;

        case I2C_MODE_DMA:
            return (HAL_I2C_Master_Receive_DMA(handle->hal, devAddr, data, size) == HAL_OK)
                   ? I2C_OK : I2C_ERROR;

        default:
            break;
    }
    return I2C_ERROR;
}

/******************************************************************
 * @brief Register I2C channel
 ******************************************************************/
static I2C_Status_t
I2c_Register (I2c_ConfigType *ConfigPtr, I2C_DRV_HARDWARE type)
{
	if (ConfigPtr == NULL)
	        return I2C_ERROR;

    switch (type)
        {
        case I2C_CHANNEL_3:
            if (I2c_ChannelConfig[I2C_CHANNEL_3] == NULL)
                {
            		i2c3_handle.hal = &hi2c3;
            		ConfigPtr->hi2c = &i2c3_handle;
            		I2c_ChannelConfig[I2C_CHANNEL_3] = ConfigPtr;
            		ConfigPtr->type = type;
                    return I2C_OK;
                }
            break;
        default:
        	break;
        }

    return I2C_ERROR;
}


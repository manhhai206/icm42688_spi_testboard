/*
 * spi_drv.c
 *
 *  Created on: Jan 24, 2026
 *      Author: manhhai
 */

#include "../drvs/Inc/spi_drv.h"
#include "../drvs/Inc/gpio_drv.h"
#include "main.h"

/* ============================================
 * Internal Channel Configuration
 * ============================================ */
extern SPI_HandleTypeDef hspi1;

struct Spi_Handle_s
{
	SPI_HandleTypeDef *hal;
};

static struct Spi_Handle_s spi1_handle;

static Spi_ConfigType *Spi_ChannelConfig[SPI_CHANNEL_TOTAL] = { 0 };

/* =========================================================
 * Private Function
 * ========================================================= */
SPI_Status_t Spi_Register (Spi_ConfigType *ConfigPtr, SPI_DRV_HARDWARE type);

static inline Spi_Handle *
Spi_GetHandle(const Spi_ConfigType *ConfigPtr)
{
    return ConfigPtr->hspi;
}

static Spi_ConfigType *
Spi_FindConfigFromHal(SPI_HandleTypeDef *hspi)
{
    for (uint8_t i = 0; i < SPI_CHANNEL_TOTAL; i++)
    {
        if (Spi_ChannelConfig[i] != NULL)
        {
            struct Spi_Handle_s *handle = Spi_GetHandle(Spi_ChannelConfig[i]);

            if (handle->hal == hspi)
            {
                return Spi_ChannelConfig[i];
            }
        }
    }
    return NULL;
}

/******************************************************************
 * @brief Initialize SPI driver
 * @param[in] ConfigPtr Pointer to SPI configuration array
 ******************************************************************/
SPI_Status_t SPI_Init (Spi_ConfigType *ConfigPtr, Spi_InitConfigType *ConfigPtr_init)
{
	if ((ConfigPtr == NULL) || (ConfigPtr_init == NULL))
	        return SPI_ERROR;

    if (Spi_Register(ConfigPtr, ConfigPtr_init->type) != SPI_OK)
        	return SPI_ERROR;

	ConfigPtr->cb = ConfigPtr_init->cb;
	ConfigPtr->cb_arg = ConfigPtr_init->cb_arg;
	ConfigPtr->mode = ConfigPtr_init->mode;
	return SPI_OK;
}

SPI_Status_t SPI_Transmit(Spi_ConfigType *ConfigPtr, uint8_t *pdata, uint16_t size, uint32_t timeout)
{
    if (ConfigPtr == NULL || pdata == NULL)
        return SPI_ERROR;

    Spi_Handle *handle = Spi_GetHandle(ConfigPtr);
    if (handle == NULL || handle->hal == NULL)
        return SPI_ERROR;

    switch (ConfigPtr->mode)
    {
        case SPI_MODE_POLLING:
            return (HAL_SPI_Transmit(handle->hal, pdata, size, timeout) == HAL_OK)
                   ? SPI_OK : SPI_ERROR;

        case SPI_MODE_IT:
            return (HAL_SPI_Transmit_IT(handle->hal, pdata, size) == HAL_OK)
                   ? SPI_OK : SPI_ERROR;

        case SPI_MODE_DMA:
            return (HAL_SPI_Transmit_DMA(handle->hal, pdata, size) == HAL_OK)
                   ? SPI_OK : SPI_ERROR;

        default:
            break;
    }

    return SPI_ERROR;
}

SPI_Status_t SPI_Receive(Spi_ConfigType *ConfigPtr, uint8_t *pdata, uint16_t size, uint32_t timeout)
{
    if (ConfigPtr == NULL || pdata == NULL)
        return SPI_ERROR;

    Spi_Handle *handle = Spi_GetHandle(ConfigPtr);
    if (handle == NULL || handle->hal == NULL)
        return SPI_ERROR;

    switch (ConfigPtr->mode)
    {
        case SPI_MODE_POLLING:
            return (HAL_SPI_Receive(handle->hal, pdata, size, timeout) == HAL_OK)
                   ? SPI_OK : SPI_ERROR;

        case SPI_MODE_IT:
            return (HAL_SPI_Receive_IT(handle->hal, pdata, size) == HAL_OK)
                   ? SPI_OK : SPI_ERROR;

        case SPI_MODE_DMA:
            return (HAL_SPI_Receive_DMA(handle->hal, pdata, size) == HAL_OK)
                   ? SPI_OK : SPI_ERROR;

        default:
            break;
    }

    return SPI_ERROR;
}

SPI_Status_t SPI_TransmitReceive(Spi_ConfigType *ConfigPtr, uint8_t *pTxData, uint8_t *pRxData, uint16_t size, uint32_t timeout)
{
    if (ConfigPtr == NULL || pTxData == NULL || pRxData == NULL)
        return SPI_ERROR;

    Spi_Handle *handle = Spi_GetHandle(ConfigPtr);
    if (handle == NULL || handle->hal == NULL)
        return SPI_ERROR;

    switch (ConfigPtr->mode)
    {
        case SPI_MODE_POLLING:
            return (HAL_SPI_TransmitReceive(handle->hal, pTxData, pRxData, size, timeout) == HAL_OK)
                   ? SPI_OK : SPI_ERROR;

        case SPI_MODE_IT:
            return (HAL_SPI_TransmitReceive_IT(handle->hal, pTxData, pRxData, size) == HAL_OK)
                   ? SPI_OK : SPI_ERROR;

        case SPI_MODE_DMA:
            return (HAL_SPI_TransmitReceive_DMA(handle->hal, pTxData, pRxData, size) == HAL_OK)
                   ? SPI_OK : SPI_ERROR;

        default:
            break;
    }

    return SPI_ERROR;
}

void SPI_CS_High(uint8_t Channel)
{
	GPIO_WriteChannel(Channel, GPIO_HIGH);
}

void SPI_CS_Low(uint8_t Channel)
{
	GPIO_WriteChannel(Channel, GPIO_LOW);
}
/******************************************************************
 * @brief Register SPI channel
 ******************************************************************/
SPI_Status_t
Spi_Register (Spi_ConfigType *ConfigPtr, SPI_DRV_HARDWARE type)
{
	if (ConfigPtr == NULL)
		return SPI_ERROR;

	switch (type)
		{
		case SPI_CHANNEL_1:
			if (Spi_ChannelConfig[SPI_CHANNEL_1] == NULL)
				{
					spi1_handle.hal = &hspi1;
					ConfigPtr->hspi = &spi1_handle;
					Spi_ChannelConfig[SPI_CHANNEL_1] = ConfigPtr;
					ConfigPtr->type = type;
					return SPI_OK;
				}
			break;
		default:
			break;
		}
	return SPI_ERROR;
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	Spi_ConfigType *cfg = Spi_FindConfigFromHal(hspi);

    if ((cfg == NULL) || (cfg->cb == NULL))
        return;

    if ((cfg->mode == SPI_MODE_IT) ||
        (cfg->mode == SPI_MODE_DMA))
        cfg->cb(cfg->cb_arg);

}

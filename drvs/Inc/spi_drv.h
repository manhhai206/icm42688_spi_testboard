/*
 * spi_drv.h
 *
 *  Created on: Jan 24, 2026
 *      Author: manhhai
 */

#ifndef INC_SPI_DRV_H_
#define INC_SPI_DRV_H_

#include <stdint.h>

/*******************************************************************
 * @enum SPI_DRV_HARDWARE
 * @brief SPI hardware channel selection
 *******************************************************************/
typedef enum SPI_DRV_HARDWARE_E
{
	SPI_CHANNEL_1 = 0,		/**< SPI Channel 1 */
	SPI_CHANNEL_2,			/**< SPI Channel 2 */
	SPI_CHANNEL_3,			/**< SPI Channel 3 */
	SPI_CHANNEL_TOTAL,
} SPI_DRV_HARDWARE;

/*******************************************************************
 * @enum SPI_Mode_t
 * @brief SPI operating mode
 *******************************************************************/
typedef enum SPI_DRV_MODE_E
{
	SPI_MODE_POLLING = 0,	/**< Mode POLLING */
	SPI_MODE_IT,			/**< Mode INTERRUPT */
	SPI_MODE_DMA,			/**< Mode DMA */
	SPI_MODE_TOTAL
} SPI_DRV_MODE;

/*******************************************************************
 * @enum SPI_Status_t
 * @brief SPI driver return status
 *******************************************************************/
typedef enum
{
    SPI_OK = 0,  /**< Operation successful */
    SPI_ERROR    /**< Operation failed */
} SPI_Status_t;

/*******************************************************************
 * @struct SPI_Config_t
 * @brief SPI configuration structure
 *******************************************************************/
typedef struct Spi_Handle_s Spi_Handle;

/*********************************************************
 * @typedef spi_irq_handler
 * @brief Use to link the callback function
 *********************************************************/
typedef void (*spi_irq_handler) (void * arg);

/**************************************************************
 * @struct SPI_InitConfigType
 * @brief SPI initial configuration structure
 *************************************************************/
typedef struct
{
	SPI_DRV_HARDWARE type;		/**< SPI channel */
	SPI_DRV_MODE  mode;      	/**< SPI mode */
	spi_irq_handler  cb;		/**< Callback function */
	void *cb_arg;			    /**< Callback argument */
} Spi_InitConfigType;

/**************************************************************
 * @struct Spi_ConfigType
 * @brief SPI runtime configuration structure
 *************************************************************/
typedef struct Spi_ConfigType
{
	Spi_Handle *hspi;		 /**< Hardware handle */
	SPI_DRV_MODE  mode;      /**< SPI mode */
    spi_irq_handler cb;	 	 /**< Callback function */
    void *cb_arg; 			 /**< Callback argument */
    uint8_t type;			 /**< I2C type */
} Spi_ConfigType __attribute__ ((aligned (sizeof (uint32_t))));

/******************************************************************
 * @brief Initialize SPI driver
 * @param ConfigPtr Pointer to I2C configuration array
 * @param ConfigPrt_init Pointer saved previous configuration
 * @return SPI_Status_t SPI_OK or SPI_OK
 ******************************************************************/
SPI_Status_t SPI_Init (Spi_ConfigType *ConfigPtr, Spi_InitConfigType *ConfigPtr_init);

SPI_Status_t SPI_Transmit(Spi_ConfigType *ConfigPtr, uint8_t *pdata, uint16_t size, uint32_t timeout);

SPI_Status_t SPI_Receive(Spi_ConfigType *ConfigPtr, uint8_t *pdata, uint16_t size, uint32_t timeout);

SPI_Status_t SPI_TransmitReceive(Spi_ConfigType *ConfigPtr, uint8_t *pTxData, uint8_t *pRxData, uint16_t size, uint32_t timeout);

void SPI_CS_High(uint8_t Channel);

void SPI_CS_Low(uint8_t Channel);

#endif /* INC_SPI_DRV_H_ */

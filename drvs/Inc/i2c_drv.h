/*
 * i2c.h
 *
 *  Created on: Jan 22, 2026
 *      Author: manhhai
 *  @brief   Generic I2C driver interface
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include <stdint.h>

/*******************************************************************
 * @enum I2C_DRV_HARDWARE
 * @brief I2C hardware channel selection
 *******************************************************************/
typedef enum
{
	I2C_CHANNEL_1 = 0,		/**< I2C Channel 1 */
	I2C_CHANNEL_2,			/**< I2C Channel 2 */
	I2C_CHANNEL_3,			/**< I2C Channel 3 */
	I2C_CHANNEL_TOTAL,
} I2C_DRV_HARDWARE;

/*******************************************************************
 * @enum I2C_Mode_t
 * @brief I2C operating mode
 *******************************************************************/
typedef enum
{
    I2C_MODE_POLLING = 0, /**< Polling mode */
    I2C_MODE_IT,          /**< Interrupt mode */
    I2C_MODE_DMA          /**< DMA mode */
} I2C_DRV_MODE;

/*******************************************************************
 * @enum I2C_Status_t
 * @brief I2C driver return status
 *******************************************************************/
typedef enum
{
    I2C_OK = 0,  /**< Operation successful */
    I2C_ERROR    /**< Operation failed */
} I2C_Status_t;

/*******************************************************************
 * @struct I2C_Config_t
 * @brief I2C configuration structure
 *******************************************************************/
typedef struct I2c_Handle_s I2c_Handle;

/*********************************************************
 * @typedef i2c_irq_handler
 * @brief Use to link the callback function
 *********************************************************/
typedef void (*i2c_irq_handler)(void *arg);

/**************************************************************
 * @struct I2c_InitConfigType
 * @brief I2C initial configuration structure
 *************************************************************/
typedef struct
{
	I2C_DRV_HARDWARE type;		/**< I2C channel */
	I2C_DRV_MODE  mode;      	/**< I2C mode */
	i2c_irq_handler  cb;		/**< Callback function */
	void *cb_arg;			    /**< Callback argument */
} I2c_InitConfigType;

/**************************************************************
 * @struct I2c_ConfigType
 * @brief I2C runtime configuration structure
 *************************************************************/
typedef struct
{
	I2c_Handle *hi2c;		 /**< Hardware handle */
	I2C_DRV_MODE  mode;      	/**< I2C mode */
    i2c_irq_handler cb;	 	 /**< Callback function */
    void *cb_arg; 			 /**< Callback argument */
    uint8_t type;			 /**< I2C type */
} I2c_ConfigType __attribute__ ((aligned (sizeof (uint32_t))));

/******************************************************************
 * @brief Initialize I2C driver
 * @param ConfigPtr Pointer to I2C configuration array
 * @param ConfigPrt_init Pointer saved previous configuration
 * @return I2C_Status_t I2C_OK or I2C_ERROR
 ******************************************************************/
I2C_Status_t I2C_Init (I2c_ConfigType *ConfigPtr, I2c_InitConfigType *ConfigPtr_init);

/******************************************************************
 * @brief Transmit I2C driver
 * @param ConfigPtr Pointer to I2C configuration array
 * @param devAddress Address of device
 * @param pData Pointer to data
 * @param size Size of data
 * @param timeout Timeout
 * @return I2C_Status_t E_OK or E_NOT_OK
 ******************************************************************/
I2C_Status_t I2C_MemWrite(I2c_ConfigType *cfg, uint16_t devAddr, uint16_t memAddr, uint16_t memAddrSize,
                          uint8_t *data, uint16_t size, uint32_t timeout);

/******************************************************************
 * @brief Receive I2C driver
 * @param ConfigPtr Pointer to I2C configuration array
 * @param devAddress Address of device
 * @param pData Pointer to data
 * @param size Size of data
 * @param timeout Timeout
 * @return I2C_Status_t E_OK or E_NOT_OK
 ******************************************************************/
I2C_Status_t I2C_MemRead(I2c_ConfigType *ConfigPtr, uint16_t devAddr, uint16_t memAddr, uint16_t memAddrSize,
        				 uint8_t *data, uint16_t size, uint32_t timeout);

/******************************************************************
 * @brief Write I2C Master driver
 * @param ConfigPtr Pointer to I2C configuration array
 * @param devAddress Address of device
 * @param pData Pointer to data
 * @param size Size of data
 * @param timeout Timeout
 * @return I2C_Status_t E_OK or E_NOT_OK
 ******************************************************************/
I2C_Status_t I2C_MasterWrite(I2c_ConfigType *ConfigPtr, uint16_t devAddress, uint8_t *pData, uint16_t size, uint32_t timeout);

/******************************************************************
 * @brief Read I2C Master driver
 * @param ConfigPtr Pointer to I2C configuration array
 * @param devAddress Address of device
 * @param pData Pointer to data
 * @param size Size of data
 * @param timeout Timeout
 * @return I2C_Status_t E_OK or E_NOT_OK
 ******************************************************************/
I2C_Status_t I2C_MasterRead(I2c_ConfigType *ConfigPtr, uint16_t devAddress, uint8_t *pData, uint16_t size, uint32_t timeout);


#endif /* INC_I2C_H_ */

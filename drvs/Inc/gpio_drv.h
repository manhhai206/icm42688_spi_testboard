/*
 * GPIO_drv.h
 *
 *  Created on: Jan 24, 2026
 *      Author: manhhai
 */

#ifndef INC_GPIO_DRV_H_
#define INC_GPIO_DRV_H_

#include <stdint.h>

/*********************************************************
 * @typedef GPIO_ChannelType
 * @brief Type for GPIO channel identifier
 *********************************************************/
typedef uint8_t GPIO_ChannelType;

/*********************************************************
 * @typedef GPIO_LevelType
 * @brief Type for GPIO_Status_t
 *********************************************************/
typedef uint8_t GPIO_LevelType;

/*******************************************************************
 * @enum GPIO_Status_t
 * @brief GPIO driver return status
 *******************************************************************/
typedef enum
{
    GPIO_LOW = 0,    
    GPIO_HIGH  
} GPIO_Status_t;

/* ============================================
 * Declaration API Function of Driver
 * ============================================ */

/*********************************************************
 * @brief Read the level of a GPIO channel
 * @param ChannelID ID of the GPIO channel
 * @return GPIO_LevelType STD_LOW or STD_HIGH
 *********************************************************/
GPIO_LevelType GPIO_ReadChannel(GPIO_ChannelType ChannelID);

/*********************************************************
 * @brief Write a level to a GPIO channel
 * @param ChannelID ID of the GPIO channel
 * @param Level     Level to be written
 *********************************************************/
void GPIO_WriteChannel(GPIO_ChannelType ChannelID, GPIO_LevelType Level);

#endif /* INC_GPIO_DRV_H_ */

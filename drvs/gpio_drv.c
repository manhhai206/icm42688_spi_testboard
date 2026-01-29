/*
 * gpio_drv.c
 *
 *  Created on: Jan 24, 2026
 *      Author: manhhai
 */

#include "gpio_drv.h"
#include "main.h"

/* ============================================
 * Internal Channel Configuration
 * ============================================ */

/*********************************************************
 * @struct Gpio_ChannelConfigType
 * @brief Mapping between Gpio channel and GPIO port/pin
 *********************************************************/
typedef struct
{
    GPIO_TypeDef *Port;  /**< GPIO port */
    uint16_t      Pin;   /**< GPIO pin  */
} Gpio_ChannelConfigType;

/* ============================================
 * Channel Configuration Table
 * ============================================ */
static const Gpio_ChannelConfigType Gpio_ChannelConfig[] =
{
    { GPIOA, GPIO_PIN_11 },
};

/* Total number of configured Gpio channels */
#define GPIO_NUMBER_OF_CHANNELS   \
    (sizeof(Gpio_ChannelConfig) / sizeof(Gpio_ChannelConfig[0]))

/*********************************************************
 * @brief Read the level of a Gpio channel
 *
 * @param ChannelID ID of the Gpio channel
 * @return Gpio_LevelType STD_LOW or STD_HIGH
 *********************************************************/
GPIO_LevelType GPIO_ReadChannel(GPIO_ChannelType ChannelID)
{
    if (ChannelID >= GPIO_NUMBER_OF_CHANNELS)
    {
        return GPIO_LOW; /* fail-safe */
    }

    GPIO_PinState state = HAL_GPIO_ReadPin(
        Gpio_ChannelConfig[ChannelID].Port,
        Gpio_ChannelConfig[ChannelID].Pin);

    return (state == GPIO_PIN_SET) ? GPIO_HIGH : GPIO_LOW;
}

/*********************************************************
 * @brief Write a level to a Gpio channel
 *
 * @param ChannelID ID of the Gpio channel
 * @param Level     Level to be written (STD_LOW or STD_HIGH)
 *********************************************************/
void GPIO_WriteChannel(GPIO_ChannelType ChannelID, GPIO_LevelType Level)
{
    if (ChannelID >= GPIO_NUMBER_OF_CHANNELS)
    {
        return;
    }

    HAL_GPIO_WritePin(
        Gpio_ChannelConfig[ChannelID].Port,
        Gpio_ChannelConfig[ChannelID].Pin,
        (Level == GPIO_HIGH) ? GPIO_PIN_SET : GPIO_PIN_RESET
    );
}

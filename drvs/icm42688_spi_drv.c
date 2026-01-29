/*
 * icm42688_spi_drv.c
 *
 *  Created on: Jan 28, 2026
 *      Author: manhhai
 */


#include "icm42688_spi_drv.h"
#include "main.h"
#include "spi_drv.h"

/* ============================================================
 * Private APIs
 * ============================================================ */

static uint8_t
ICM42688_ReadWrite(Spi_ConfigType *hspi, uint8_t tx)
{
    uint8_t rx = 0xFF;
    SPI_TransmitReceive(hspi, &tx, &rx, 1, 10);
    return rx;
}

static uint8_t
ICM42688_ReadByte(icm42688_spi_drv_t *dev, uint8_t reg)
{
    uint8_t value;

    SPI_CS_Low(0);
    ICM42688_ReadWrite(dev->hspi, reg | ICM42688_SPI_READ);
    value = ICM42688_ReadWrite(dev->hspi, 0x00);
    SPI_CS_High(0);

    return value;
}

static void
ICM42688_WriteByte(icm42688_spi_drv_t *dev, uint8_t reg, uint8_t value)
{
    SPI_CS_Low(0);
    ICM42688_ReadWrite(dev->hspi, reg & ICM42688_SPI_WRITE);
    ICM42688_ReadWrite(dev->hspi, value);
    SPI_CS_High(0);
}

static void
ICM42688_ReadNBytes(icm42688_spi_drv_t *dev,  uint8_t reg, uint8_t *values, uint8_t length)
{
    SPI_CS_Low(0);
    ICM42688_ReadWrite(dev->hspi, reg | ICM42688_SPI_READ);
//    ICM42688_ReadWrite(dev->hspi, 0x00);
    while (length--)
    {
        *values++ = ICM42688_ReadWrite(dev->hspi, 0x00);
    }

    SPI_CS_High(0);
}

/* ===========================================================
 * Public APIs
 * ============================================================ */
uint8_t icm42688_drv_init_spi(icm42688_spi_drv_t *hand)
{
    if (hand == NULL)
        return SPI_ERROR;

    icm42688_setRegisterBank_spi(hand, BANK_0);
    icm42688_setPowerMode_spi(hand, GYRO_LOWNOISE, ACCEL_LOWNOISE);
    HAL_Delay(10);

    ICM42688_WriteByte(hand, ICM42688_SIGNAL_PATH_RESET, 0x01);
    HAL_Delay(2);

    uint8_t who = icm42688_checkWhoAmI_spi(hand);
    if (who == ICM42688_VALUE_WHOAMI)
    {
    	icm42688_setGyroConfig_spi(hand, GYRO_FS_2000, GYRO_32KHZ);
    	icm42688_setAccelConfig_spi(hand, ICM42688_ACCEL_FS_2G,  ACCEL_32KHZ);

    	icm42688_setGyroAccelConfig0_spi(hand);

    	icm42688_setTMSTConfig_spi(hand);
    	icm42688_setINTConfig_spi(hand);
    	icm42688_setINTSOURCE0_spi(hand);

    	icm42688_setGyroConfigStatic2_spi(hand);
    	return SPI_OK;
    }
    return SPI_ERROR;
}

uint8_t
icm42688_checkWhoAmI_spi(icm42688_spi_drv_t *dev)
{
    return ICM42688_ReadByte(dev, ICM42688_WHO_AM_I);
}

void
icm42688_setRegisterBank_spi(icm42688_spi_drv_t *dev, register_bank_sel_t bank)
{
    ICM42688_WriteByte(dev, ICM42688_REG_BANK_SEL, bank & 0x07);
}

void
icm42688_setPowerMode_spi(icm42688_spi_drv_t *dev,
                          gyro_mode_t gyro_mode,
                          accel_mode_t accel_mode)
{
    uint8_t value = ((gyro_mode & 0x03) << 2) | (accel_mode & 0x03);
    ICM42688_WriteByte(dev, ICM42688_PWR_MGMT0, value);
}

void
icm42688_setGyroConfig_spi(icm42688_spi_drv_t *dev,
                           gyro_fs_sel_t gyro_fs,
                           gyro_odr_t gyro_odr)
{
    uint8_t value = ((gyro_fs & 0x07) << 5) | (gyro_odr & 0x0F);
    ICM42688_WriteByte(dev, ICM42688_GYRO_CONFIG0, value);
}

void
icm42688_setGyroAccelConfig0_spi(icm42688_spi_drv_t *dev)
{
	uint8_t value = 0x00;
    ICM42688_WriteByte(dev, ICM42688_GYRO_ACCEL_CONFIG0, value);
}

void icm42688_setAccelConfig_spi(icm42688_spi_drv_t *dev,
                                accel_fs_sel_t fs,
                                accel_odr_t odr)
{
    uint8_t value = ((fs & 0x07) << 5) | (odr & 0x0F);
    ICM42688_WriteByte(dev, ICM42688_ACCEL_CONFIG0, value);
}

void
icm42688_setFifoConfig_spi(icm42688_spi_drv_t *dev)
{
    ICM42688_WriteByte(dev, ICM42688_FIFO_CONFIG1, 0x00);
}

void
icm42688_setTMSTConfig_spi(icm42688_spi_drv_t *dev)
{
	uint8_t value = 0x01;
    ICM42688_WriteByte(dev, ICM42688_TMST_CONFIG, value);
}

void
icm42688_setINTConfig_spi(icm42688_spi_drv_t *dev)
{
	uint8_t value = 0x18 | 0x03;
    ICM42688_WriteByte(dev, ICM42688_INT_CONFIG, value);
}

void
icm42688_setINTSOURCE0_spi(icm42688_spi_drv_t *dev)
{
	uint8_t value = 0x08;
    ICM42688_WriteByte(dev, ICM42688_INT_SOURCE0, value);
}

void
icm42688_setGyroConfigStatic2_spi(icm42688_spi_drv_t *dev)
{
    icm42688_setRegisterBank_spi(dev, BANK_2);
    ICM42688_WriteByte(dev, ICM42688_GYRO_CONFIG_STATIC2, 0x00);
    icm42688_setRegisterBank_spi(dev, BANK_0);
}

void
icm42688_read_spi(icm42688_spi_drv_t *dev)
{
    uint8_t buf[14];

    icm42688_setRegisterBank_spi(dev, BANK_0);

    ICM42688_ReadNBytes(dev, ICM42688_TEMP_DATA1, buf, 14);

    dev->data.temp = (int16_t)((buf[0] << 8) | buf[1]);

    dev->data.ax = (int16_t)((buf[2] << 8) | buf[3]);
    dev->data.ay = (int16_t)((buf[4] << 8) | buf[5]);
    dev->data.az = (int16_t)((buf[6] << 8) | buf[7]);

    dev->data.gx = (int16_t)((buf[8]  << 8) | buf[9]);
    dev->data.gy = (int16_t)((buf[10] << 8) | buf[11]);
    dev->data.gz = (int16_t)((buf[12] << 8) | buf[13]);
}

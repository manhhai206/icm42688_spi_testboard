/*
 * icm42688_drv.c
 *
 *  Created on: Jan 28, 2026
 *      Author: manhhai
 */

#include <icm42688_i2c_drv.h>
#include  "main.h"
#include "i2c_drv.h"

/* ============================================================
 * Private APIs
 * ============================================================ */
static void
ICM42688_WriteByte(icm42688_i2c_drv_t *dev, uint8_t reg, uint8_t value)
{
    I2C_MemWrite(dev->hi2c, ICM42688_DEFAULT_ADDRESS, reg, 1, &value, 1, 1000);
}

static uint8_t
ICM42688_ReadByte(icm42688_i2c_drv_t *dev, uint8_t reg)
{
    uint8_t val;
    I2C_MemRead(dev->hi2c, ICM42688_DEFAULT_ADDRESS, reg, 1, &val, 1, 1000);
    return val;
}

static void
ICM42688_ReadNBytes(icm42688_i2c_drv_t *dev, uint8_t reg, uint8_t len, uint8_t *buf)
{
    I2C_MemRead(dev->hi2c, ICM42688_DEFAULT_ADDRESS, reg, 1, buf, len, 1000);
}

/** Public Function Declaration
 * -------------------------------------------------------------**/
uint8_t icm42688_drv_init (icm42688_i2c_drv_t *hand)
{
	if (hand == NULL)
		return I2C_ERROR;

	uint8_t who = icm42688_checkWhoAmI(hand);
	if (who == ICM42688_DEFAULT_WHOAMI)
	{
		icm42688_setRegisterBank(hand, BANK_0);
		imc42688_setPowerMode(hand, GYRO_LOWNOISE, ACCEL_LOWNOISE);
		HAL_Delay(2);

		icm42688_setGyroConfig(hand, GYRO_FS_2000, GYRO_32KHZ);
		icm42688_setGyroAccelConfig0(hand);

		icm42688_setTMSTConfig(hand);
		icm42688_setINTConfig(hand);
		icm42688_setINTSOURCE0(hand);

		icm42688_setRegisterBank(hand, BANK_2);
		icm42688_setGyroConfigStatic2(hand);

		icm42688_setRegisterBank(hand, BANK_0);
		return I2C_OK;
	}
	return I2C_ERROR;
}

uint8_t icm42688_checkWhoAmI (icm42688_i2c_drv_t *dev)
{
    return ICM42688_ReadByte(dev, ICM42688_WHO_AM_I);
}

void icm42688_setRegisterBank (icm42688_i2c_drv_t *dev, register_bank_sel_t bank)
{
    uint8_t value;
    value = ICM42688_ReadByte(dev, ICM42688_REG_BANK_SEL);
    value &= ~0x07;
    value |= (bank & 0x07);
    ICM42688_WriteByte(dev, ICM42688_REG_BANK_SEL, value);
}

void imc42688_setPowerMode (icm42688_i2c_drv_t *dev, gyro_mode_t gyro_mode, accel_mode_t accel_mode)
{
	uint8_t value;
	value = ICM42688_ReadByte(dev, ICM42688_PWR_MGMT0);
	value &= ~0x0F;
	value |= (gyro_mode << 2) | accel_mode;
	ICM42688_WriteByte(dev, ICM42688_PWR_MGMT0, value);
}

void icm42688_setGyroConfig (icm42688_i2c_drv_t *dev, gyro_fs_sel_t gyro_fs, gyro_odr_t gyro_odr)
{
	uint8_t value;
	value = ICM42688_ReadByte(dev, ICM42688_GYRO_CONFIG0);
	value &= ~((0x07 << 5) | 0x0F);
	value |= ((gyro_fs & 0x07) << 5) | (gyro_odr & 0x0F);
	ICM42688_WriteByte(dev, ICM42688_GYRO_CONFIG0, value);
}

void icm42688_setGyroAccelConfig0 (icm42688_i2c_drv_t *dev)
{
	uint8_t value = 0x07;
	ICM42688_WriteByte(dev, ICM42688_GYRO_ACCEL_CONFIG0, value);
}

//void icm42688_setFifoConfig (icm42688_i2c_drv_t *dev)
//{
//	uint8_t value = 0x03;
//	ICM42688_WriteByte(dev, ICM42688_FIFO_CONFIG1, value);
//}

void icm42688_setTMSTConfig (icm42688_i2c_drv_t *dev)
{
	uint8_t value = 0x01;
	ICM42688_WriteByte(dev, ICM42688_TMST_CONFIG, value);
}

void icm42688_setINTConfig (icm42688_i2c_drv_t *dev)
{
	uint8_t value = 0x18 | 0x03;
	ICM42688_WriteByte(dev, ICM42688_INT_CONFIG, value);
}

void icm42688_setINTSOURCE0 (icm42688_i2c_drv_t *dev)
{
	uint8_t value = 0x08;
	ICM42688_WriteByte(dev, ICM42688_INT_SOURCE0, value);
}

void icm42688_setGyroConfigStatic2 (icm42688_i2c_drv_t *dev)
{
	uint8_t value =0x00;
	ICM42688_WriteByte(dev, ICM42688_GYRO_CONFIG_STATIC2, value);
}

void icm42688_read(icm42688_i2c_drv_t *dev)
{
    uint8_t buf[14];

    icm42688_setRegisterBank(dev, BANK_0);

    ICM42688_ReadNBytes(dev, ICM42688_TEMP_DATA1, 14, buf);

    dev->data.temp = (int16_t)((buf[0] << 8) | buf[1]);

    dev->data.ax = (int16_t)((buf[2] << 8) | buf[3]);
    dev->data.ay = (int16_t)((buf[4] << 8) | buf[5]);
    dev->data.az = (int16_t)((buf[6] << 8) | buf[7]);

    dev->data.gx = (int16_t)((buf[8]  << 8) | buf[9]);
    dev->data.gy = (int16_t)((buf[10] << 8) | buf[11]);
    dev->data.gz = (int16_t)((buf[12] << 8) | buf[13]);
}





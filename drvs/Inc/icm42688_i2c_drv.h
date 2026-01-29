/*
 * icm42688_drv.h
 *
 *  Created on: Jan 28, 2026
 *      Author: manhhai
 */

#ifndef INC_ICM42688_I2C_DRV_H_
#define INC_ICM42688_I2C_DRV_H_

#include <stdint.h>
#include "../../drvs/Inc/i2c_drv.h"

/** Macro Declaration
 * -------------------------------------------------------------**/
#define ICM42688_ADDRESS 			0x68
#define ICM42688_DEFAULT_ADDRESS	(ICM42688_ADDRESS <<1)
#define ICM42688_DEFAULT_WHOAMI		0x47

typedef enum
{
	ICM42688_INT_CONFIG = 0x14,
	ICM42688_PWR_MGMT0 = 0x4E,
	ICM42688_GYRO_CONFIG0 = 0x4F,
	ICM42688_GYRO_ACCEL_CONFIG0 = 0x52,
	ICM42688_TMST_CONFIG = 0x54,
	ICM42688_FIFO_CONFIG1 = 0x5F,
	ICM42688_INT_SOURCE0 = 0x65,
	ICM42688_REG_BANK_SEL = 0x76,
	ICM42688_WHO_AM_I = 0x75,
} icm42688_register_bank0_address_t;

typedef enum
{
	ICM42688_GYRO_CONFIG_STATIC2 = 0x0B,
} icm42688_register_bank2_address_t;

typedef enum
{
    ICM42688_TEMP_DATA1       = 0x1D,
    ICM42688_TEMP_DATA0       = 0x1E,

    ICM42688_ACCEL_DATA_X1    = 0x1F,
    ICM42688_ACCEL_DATA_X0    = 0x20,
    ICM42688_ACCEL_DATA_Y1    = 0x21,
    ICM42688_ACCEL_DATA_Y0    = 0x22,
    ICM42688_ACCEL_DATA_Z1    = 0x23,
    ICM42688_ACCEL_DATA_Z0    = 0x24,

    ICM42688_GYRO_DATA_X1     = 0x25,
    ICM42688_GYRO_DATA_X0     = 0x26,
    ICM42688_GYRO_DATA_Y1     = 0x27,
    ICM42688_GYRO_DATA_Y0     = 0x28,
    ICM42688_GYRO_DATA_Z1     = 0x29,
    ICM42688_GYRO_DATA_Z0     = 0x2A,
} icm42688_data_reg_t;


typedef enum
{
	BANK_0 = 0,
	BANK_1,
	BANK_2,
	BANK_3,
	BANK_4,
} register_bank_sel_t;

typedef enum
{
	GYRO_OFF = 0,
	GYRO_STANDBY,
	GYRO_LOWNOISE = 3,
} gyro_mode_t;

typedef enum
{
	ACCEL_OFF = 0,
	ACCEL_LOWPOWER = 2,
	ACCEL_LOWNOISE = 3,
} accel_mode_t;

typedef enum
{
	GYRO_FS_2000 = 0,
	GYRO_FS_1000,
	GYRO_FS_500,
	GYRO_FS_250,
	GYRO_FS_125,
	GYRO_FS_62_5,
	GYRO_FS_31_25,
	GYRO_FS_15_625
} gyro_fs_sel_t;

typedef enum
{
	GYRO_32KHZ = 1,
	GYRO_16KHZ,
	GYRO_8KHZ,
	GYRO_4KHZ,
	GYRO_2KHZ,
	GYRO_1KHZ,
	GYRO_200HZ,
	GYRO_100HZ,
	GYRO_50HZ,
	GYRO_25HZ,
	GYRO_12_5HZ,
	GYRO_12_500HZ = 14
} gyro_odr_t;

/** Public Typedef Definition
 * -------------------------------------------------------------**/
typedef struct icm42688_i2c_s
{
	int16_t ax, ay, az;
	int16_t gx, gy, gz;
	int16_t temp;
} icm42688_i2c_t;


typedef struct icm42688_i2c_drv_s
{
	I2c_ConfigType *hi2c;
	icm42688_i2c_t data;
} icm42688_i2c_drv_t;

/** Public Function Declaration
 * -------------------------------------------------------------**/
uint8_t icm42688_drv_init(icm42688_i2c_drv_t *hand);
uint8_t icm42688_checkWhoAmI(icm42688_i2c_drv_t *dev);
void icm42688_setRegisterBank(icm42688_i2c_drv_t *dev, register_bank_sel_t bank);
void imc42688_setPowerMode (icm42688_i2c_drv_t *dev, gyro_mode_t gyro_mode, accel_mode_t accel_mode);
void icm42688_setGyroConfig (icm42688_i2c_drv_t *dev, gyro_fs_sel_t gyro_fs, gyro_odr_t gyro_odr);
void icm42688_setGyroAccelConfig0 (icm42688_i2c_drv_t *dev);
void icm42688_setFifoConfig (icm42688_i2c_drv_t *dev);
void icm42688_setTMSTConfig (icm42688_i2c_drv_t *dev);
void icm42688_setINTConfig (icm42688_i2c_drv_t *dev);
void icm42688_setINTSOURCE0 (icm42688_i2c_drv_t *dev);
void icm42688_setGyroConfigStatic2 (icm42688_i2c_drv_t *dev);
void icm42688_read(icm42688_i2c_drv_t *dev);

#endif /* INC_ICM42688_I2C_DRV_H_ */

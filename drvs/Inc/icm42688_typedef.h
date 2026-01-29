/*
 * icm42688_typedef.h
 *
 *  Created on: Jan 29, 2026
 *      Author: manhhai
 */

#ifndef INC_ICM42688_TYPEDEF_H_
#define INC_ICM42688_TYPEDEF_H_

#include <stdint.h>

/** Macro Declaration
 * -------------------------------------------------------------**/
#define ICM42688_ADDRESS 			0x68
#define ICM42688_DEFAULT_ADDRESS	(ICM42688_ADDRESS <<1)
#define ICM42688_VALUE_WHOAMI		0x47

typedef enum
{
    ICM42688_INT_CONFIG            = 0x14,
	ICM42688_SIGNAL_PATH_RESET	   = 0X4B,
    ICM42688_PWR_MGMT0             = 0x4E,
    ICM42688_GYRO_CONFIG0          = 0x4F,
	ICM42688_ACCEL_CONFIG0         = 0x50,
    ICM42688_GYRO_ACCEL_CONFIG0    = 0x52,
    ICM42688_TMST_CONFIG           = 0x54,
    ICM42688_FIFO_CONFIG1          = 0x5F,
    ICM42688_INT_SOURCE0           = 0x65,
    ICM42688_REG_BANK_SEL          = 0x76,
    ICM42688_WHO_AM_I              = 0x75,
} icm42688_register_bank0_t;

typedef enum
{
    ICM42688_GYRO_CONFIG_STATIC2   = 0x0B,
} icm42688_register_bank2_t;

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

typedef enum
{
    ICM42688_ACCEL_FS_16G = 0,
    ICM42688_ACCEL_FS_8G  = 1,
    ICM42688_ACCEL_FS_4G  = 2,
    ICM42688_ACCEL_FS_2G  = 3
} accel_fs_sel_t;

typedef enum
{
    ACCEL_ODR_OFF    = 0x00,
    ACCEL_32KHZ      = 0x01,
    ACCEL_16KHZ      = 0x02,
    ACCEL_8KHZ       = 0x03,
    ACCEL_4KHZ       = 0x04,
    ACCEL_2KHZ       = 0x05,
    ACCEL_1KHZ       = 0x06,
    ACCEL_200HZ      = 0x07,
    ACCEL_100HZ      = 0x08,
    ACCEL_50HZ       = 0x09,
    ACCEL_25HZ       = 0x0A,
    ACCEL_12_5HZ     = 0x0B
} accel_odr_t;

typedef struct icm42688_s
{
	int16_t ax, ay, az;
	int16_t gx, gy, gz;
	int16_t temp;
} icm42688_t;

#endif /* INC_ICM42688_TYPEDEF_H_ */

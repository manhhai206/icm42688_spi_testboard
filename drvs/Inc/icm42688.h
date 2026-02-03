/*
 * icm42688.h
 *
 *  Created on: Jan 30, 2026
 *      Author: manhhai
 */

#ifndef INC_ICM42688_H_
#define INC_ICM42688_H_

#include <stdint.h>
#include <stdbool.h>
#include "platform.h"
#include "imu.h"

/** Typedef Declaration
 * -------------------------------------------------------------**/
typedef enum
{
    ICM42688_INT_CONFIG              = 0x14,
    ICM42688_SIGNAL_PATH_RESET       = 0x4B,
    ICM42688_PWR_MGMT0               = 0x4E,
    ICM42688_GYRO_CONFIG0            = 0x4F,
    ICM42688_ACCEL_CONFIG0           = 0x50,
    ICM42688_GYRO_ACCEL_CONFIG0      = 0x52,
    ICM42688_TMST_CONFIG             = 0x54,
    ICM42688_FIFO_CONFIG1            = 0x5F,
    ICM42688_INT_SOURCE0             = 0x65,
    ICM42688_WHO_AM_I                = 0x75,
    ICM42688_REG_BANK_SEL            = 0x76,
} icm42688_register_bank0_t;

typedef enum
{
    ICM42688_GYRO_CONFIG_STATIC2     = 0x0B,
} icm42688_register_bank2_t;

typedef enum
{
    ICM42688_TEMP_DATA1              = 0x1D,
    ICM42688_TEMP_DATA0              = 0x1E,
    ICM42688_ACCEL_DATA_X1           = 0x1F,
    ICM42688_ACCEL_DATA_X0           = 0x20,
    ICM42688_ACCEL_DATA_Y1           = 0x21,
    ICM42688_ACCEL_DATA_Y0           = 0x22,
    ICM42688_ACCEL_DATA_Z1           = 0x23,
    ICM42688_ACCEL_DATA_Z0           = 0x24,
    ICM42688_GYRO_DATA_X1            = 0x25,
    ICM42688_GYRO_DATA_X0            = 0x26,
    ICM42688_GYRO_DATA_Y1            = 0x27,
    ICM42688_GYRO_DATA_Y0            = 0x28,
    ICM42688_GYRO_DATA_Z1            = 0x29,
    ICM42688_GYRO_DATA_Z0            = 0x2A,
} icm42688_data_reg_t;

typedef enum
{
    BANK_0 = 0x00,
    BANK_1 = 0x01,
    BANK_2 = 0x02,
    BANK_3 = 0x03,
    BANK_4 = 0x04,
} register_bank_sel_t;

typedef enum
{
    GYRO_OFF = 0x00,
    GYRO_SBY = 0x01,
    GYRO_LNS = 0x03,
} gyro_mode_t;

typedef enum
{
    ACCEL_OFF = 0x00,
    ACCEL_LPR = 0x02,
    ACCEL_LNE = 0x03,
} accel_mode_t;

typedef enum
{
    GYRO_FS_2000   = 0x00,
    GYRO_FS_1000   = 0x01,
    GYRO_FS_500    = 0x02,
    GYRO_FS_250    = 0x03,
    GYRO_FS_125    = 0x04,
    GYRO_FS_62_5   = 0x05,
    GYRO_FS_31_25  = 0x06,
    GYRO_FS_15_625 = 0x07
} gyro_fs_sel_t;

typedef enum
{
    GYRO_32KHZ    = 0x01,
    GYRO_16KHZ    = 0x02,
    GYRO_8KHZ     = 0x03,
    GYRO_4KHZ     = 0x04,
    GYRO_2KHZ     = 0x05,
    GYRO_1KHZ     = 0x06,
    GYRO_200HZ    = 0x07,
    GYRO_100HZ    = 0x08,
    GYRO_50HZ     = 0x09,
    GYRO_25HZ     = 0x0A,
    GYRO_12_5HZ   = 0x0B,
    GYRO_12_500HZ = 0x0E
} gyro_odr_t;

typedef enum
{
    ACCEL_FS_16G = 0x00,
    ACCEL_FS_8G  = 0x01,
    ACCEL_FS_4G  = 0x02,
    ACCEL_FS_2G  = 0x03
} accel_fs_sel_t;

typedef enum
{
    ACCEL_ODR_OFF = 0x00,
    ACCEL_32KHZ   = 0x01,
    ACCEL_16KHZ   = 0x02,
    ACCEL_8KHZ    = 0x03,
    ACCEL_4KHZ    = 0x04,
    ACCEL_2KHZ    = 0x05,
    ACCEL_1KHZ    = 0x06,
    ACCEL_200HZ   = 0x07,
    ACCEL_100HZ   = 0x08,
    ACCEL_50HZ    = 0x09,
    ACCEL_25HZ    = 0x0A,
    ACCEL_12_5HZ  = 0x0B
} accel_odr_t;

/** Public Functions
 * -------------------------------------------------------------**/
int icm42688_create_spi(imu_t *imu, spi_port_t port);
int icm42688_create_i2c(imu_t *imu, i2c_port_t port);
void icm42688_spi_dma_done(spi_port_t port);

#endif /* INC_ICM42688_H_ */

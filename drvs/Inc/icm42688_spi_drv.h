#ifndef INC_ICM42688_SPI_DRV_H_
#define INC_ICM42688_SPI_DRV_H_

#include <stdint.h>
#include "../../drvs/Inc/spi_drv.h"

/** Macro Declaration
 * -------------------------------------------------------------**/
#define ICM42688_DEFAULT_WHOAMI 0x47
#define ICM42688_SPI_READ   0x80
#define ICM42688_SPI_WRITE  0x7F


/* ================= Register address ================= */

typedef enum
{
    ICM42688_SPI_INT_CONFIG            = 0x14,
	ICM42688_SPI_SIGNAL_PATH_RESET	   = 0X4B,
    ICM42688_SPI_PWR_MGMT0             = 0x4E,
    ICM42688_SPI_GYRO_CONFIG0          = 0x4F,
	ICM42688_SPI_ACCEL_CONFIG0         = 0x50,
    ICM42688_SPI_GYRO_ACCEL_CONFIG0    = 0x52,
    ICM42688_SPI_TMST_CONFIG           = 0x54,
    ICM42688_SPI_FIFO_CONFIG1          = 0x5F,
    ICM42688_SPI_INT_SOURCE0           = 0x65,
    ICM42688_SPI_REG_BANK_SEL          = 0x76,
    ICM42688_SPI_WHO_AM_I              = 0x75,
} icm42688_spi_register_bank0_t;

typedef enum
{
    ICM42688_SPI_GYRO_CONFIG_STATIC2   = 0x0B,
} icm42688_spi_register_bank2_t;

typedef enum
{
    ICM42688_SPI_TEMP_DATA1       = 0x1D,
    ICM42688_SPI_TEMP_DATA0       = 0x1E,

    ICM42688_SPI_ACCEL_DATA_X1    = 0x1F,
    ICM42688_SPI_ACCEL_DATA_X0    = 0x20,
    ICM42688_SPI_ACCEL_DATA_Y1    = 0x21,
    ICM42688_SPI_ACCEL_DATA_Y0    = 0x22,
    ICM42688_SPI_ACCEL_DATA_Z1    = 0x23,
    ICM42688_SPI_ACCEL_DATA_Z0    = 0x24,

    ICM42688_SPI_GYRO_DATA_X1     = 0x25,
    ICM42688_SPI_GYRO_DATA_X0     = 0x26,
    ICM42688_SPI_GYRO_DATA_Y1     = 0x27,
    ICM42688_SPI_GYRO_DATA_Y0     = 0x28,
    ICM42688_SPI_GYRO_DATA_Z1     = 0x29,
    ICM42688_SPI_GYRO_DATA_Z0     = 0x2A,
} icm42688_spi_data_reg_t;

/* ================= Config enum ================= */

typedef enum
{
    ICM42688_SPI_BANK_0 = 0,
    ICM42688_SPI_BANK_1,
    ICM42688_SPI_BANK_2,
    ICM42688_SPI_BANK_3,
    ICM42688_SPI_BANK_4,
} icm42688_spi_register_bank_sel_t;

typedef enum
{
    ICM42688_SPI_GYRO_OFF = 0,
    ICM42688_SPI_GYRO_STANDBY,
    ICM42688_SPI_GYRO_LOWNOISE = 3,
} icm42688_spi_gyro_mode_t;

typedef enum
{
    ICM42688_SPI_ACCEL_OFF = 0,
    ICM42688_SPI_ACCEL_LOWPOWER = 2,
    ICM42688_SPI_ACCEL_LOWNOISE = 3,
} icm42688_spi_accel_mode_t;

typedef enum
{
    ICM42688_SPI_GYRO_FS_2000 = 0,
    ICM42688_SPI_GYRO_FS_1000,
    ICM42688_SPI_GYRO_FS_500,
    ICM42688_SPI_GYRO_FS_250,
    ICM42688_SPI_GYRO_FS_125,
    ICM42688_SPI_GYRO_FS_62_5,
    ICM42688_SPI_GYRO_FS_31_25,
    ICM42688_SPI_GYRO_FS_15_625
} icm42688_spi_gyro_fs_sel_t;

typedef enum
{
    ICM42688_SPI_GYRO_32KHZ = 1,
    ICM42688_SPI_GYRO_16KHZ,
    ICM42688_SPI_GYRO_8KHZ,
    ICM42688_SPI_GYRO_4KHZ,
    ICM42688_SPI_GYRO_2KHZ,
    ICM42688_SPI_GYRO_1KHZ,
    ICM42688_SPI_GYRO_200HZ,
    ICM42688_SPI_GYRO_100HZ,
    ICM42688_SPI_GYRO_50HZ,
    ICM42688_SPI_GYRO_25HZ,
    ICM42688_SPI_GYRO_12_5HZ,
    ICM42688_SPI_GYRO_12_500HZ = 14
} icm42688_spi_gyro_odr_t;

typedef enum
{
    ICM42688_SPI_ACCEL_FS_16G = 0x00,
    ICM42688_SPI_ACCEL_FS_8G  = 0x01,
    ICM42688_SPI_ACCEL_FS_4G  = 0x02,
    ICM42688_SPI_ACCEL_FS_2G  = 0x03
} icm42688_spi_accel_fs_sel_t;

typedef enum
{
    ICM42688_SPI_ACCEL_ODR_OFF    = 0x00,
    ICM42688_SPI_ACCEL_32KHZ      = 0x01,
    ICM42688_SPI_ACCEL_16KHZ      = 0x02,
    ICM42688_SPI_ACCEL_8KHZ       = 0x03,
    ICM42688_SPI_ACCEL_4KHZ       = 0x04,
    ICM42688_SPI_ACCEL_2KHZ       = 0x05,
    ICM42688_SPI_ACCEL_1KHZ       = 0x06,
    ICM42688_SPI_ACCEL_200HZ      = 0x07,
    ICM42688_SPI_ACCEL_100HZ      = 0x08,
    ICM42688_SPI_ACCEL_50HZ       = 0x09,
    ICM42688_SPI_ACCEL_25HZ       = 0x0A,
    ICM42688_SPI_ACCEL_12_5HZ     = 0x0B
} icm42688_spi_accel_odr_t;

/* ================= Data ================= */

typedef struct
{
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    int16_t temp;
} icm42688_spi_t;

typedef struct
{
    Spi_ConfigType *hspi;
    icm42688_spi_t data;
} icm42688_spi_drv_t;

/* ================= APIs ================= */

uint8_t icm42688_drv_init_spi(icm42688_spi_drv_t *hand);
uint8_t icm42688_checkWhoAmI_spi(icm42688_spi_drv_t *dev);
void icm42688_setRegisterBank_spi(icm42688_spi_drv_t *dev, icm42688_spi_register_bank_sel_t bank);
void icm42688_setPowerMode_spi(icm42688_spi_drv_t *dev,
                               icm42688_spi_gyro_mode_t gyro_mode,
                               icm42688_spi_accel_mode_t accel_mode);
void icm42688_setGyroConfig_spi(icm42688_spi_drv_t *dev,
                                icm42688_spi_gyro_fs_sel_t gyro_fs,
                                icm42688_spi_gyro_odr_t gyro_odr);
void icm42688_setAccelConfig_spi(icm42688_spi_drv_t *dev,
                                icm42688_spi_accel_fs_sel_t fs,
                                icm42688_spi_accel_odr_t odr);
void icm42688_setGyroAccelConfig0_spi(icm42688_spi_drv_t *dev);
void icm42688_setFifoConfig_spi(icm42688_spi_drv_t *dev);
void icm42688_setTMSTConfig_spi(icm42688_spi_drv_t *dev);
void icm42688_setINTConfig_spi(icm42688_spi_drv_t *dev);
void icm42688_setINTSOURCE0_spi(icm42688_spi_drv_t *dev);
void icm42688_setGyroConfigStatic2_spi(icm42688_spi_drv_t *dev);
void icm42688_read_spi(icm42688_spi_drv_t *dev);

#endif

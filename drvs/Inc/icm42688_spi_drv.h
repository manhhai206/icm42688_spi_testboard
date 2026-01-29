#ifndef INC_ICM42688_SPI_DRV_H_
#define INC_ICM42688_SPI_DRV_H_

#include <stdint.h>
#include "../../drvs/Inc/spi_drv.h"
#include "icm42688_typedef.h"

/** Macro Declaration
 * -------------------------------------------------------------**/
#define ICM42688_SPI_READ   0x80
#define ICM42688_SPI_WRITE  0x7F

typedef struct
{
    Spi_ConfigType *hspi;
    icm42688_t data;
} icm42688_spi_drv_t;

/* ================= APIs ================= */
uint8_t icm42688_drv_init_spi(icm42688_spi_drv_t *hand);
uint8_t icm42688_checkWhoAmI_spi(icm42688_spi_drv_t *dev);
void icm42688_setRegisterBank_spi(icm42688_spi_drv_t *dev, register_bank_sel_t bank);
void icm42688_setPowerMode_spi(icm42688_spi_drv_t *dev,
                               gyro_mode_t gyro_mode,
                               accel_mode_t accel_mode);
void icm42688_setGyroConfig_spi(icm42688_spi_drv_t *dev,
                                gyro_fs_sel_t gyro_fs,
                                gyro_odr_t gyro_odr);
void icm42688_setAccelConfig_spi(icm42688_spi_drv_t *dev,
                                accel_fs_sel_t fs,
                                accel_odr_t odr);
void icm42688_setGyroAccelConfig0_spi(icm42688_spi_drv_t *dev);
void icm42688_setFifoConfig_spi(icm42688_spi_drv_t *dev);
void icm42688_setTMSTConfig_spi(icm42688_spi_drv_t *dev);
void icm42688_setINTConfig_spi(icm42688_spi_drv_t *dev);
void icm42688_setINTSOURCE0_spi(icm42688_spi_drv_t *dev);
void icm42688_setGyroConfigStatic2_spi(icm42688_spi_drv_t *dev);
void icm42688_read_spi(icm42688_spi_drv_t *dev);

#endif

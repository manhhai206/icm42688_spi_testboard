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
#include "icm42688_typedef.h"

typedef struct icm42688_i2c_drv_s
{
	I2c_ConfigType *hi2c;
	icm42688_t data;
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

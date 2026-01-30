/*
 * app.c
 *
 *  Created on: Jan 30, 2026
 *      Author: manhhai
 */

#include "app.h"

icm42688p_t imu2 = {{0},{0},SPI_PORT_1,0,0};

void app_init()
{
	platform_init();
	icm42688p_init(&imu2, ACCEL_FS_2G, GYRO_FS_2000, ACCEL_25HZ, GYRO_32KHZ, ACCEL_LNE, GYRO_LNS, 0);
}

/*
 * icm42688_i2c.c
 *
 *  Created on: Feb 2, 2026
 *      Author: manhhai
 */

#include "icm42688.h"
#include "imu.h"
#include <stdbool.h>
#include <string.h>

/** Macro Declaration
 * -------------------------------------------------------------**/
#define ICM42688_ADDRESS              0x68
#define ICM42688_DEFAULT_ADDRESS      (ICM42688_ADDRESS << 1)
#define ICM42688_VALUE_WHOAMI    0x47

/** Typedef structures Declaration
 * -------------------------------------------------------------**/
typedef struct
{
	i2c_port_t i2c_port;
	uint8_t i2c_buffer[32];
} icm42688_i2c_ctx_t;

// static handler
static icm42688_i2c_ctx_t *i2c_handler = NULL;

/** Private Functions
 * -------------------------------------------------------------**/
static void
icm42688_i2c_writebyte(icm42688_i2c_ctx_t *dev, uint8_t reg, uint8_t value)
{
	platform_i2c_mem_write_blocking(dev->i2c_port, ICM42688_DEFAULT_ADDRESS, reg, 1, &value, 1, 10);
}

static uint8_t
icm42688_i2c_readbyte(icm42688_i2c_ctx_t *dev, uint8_t reg)
{
    uint8_t val;
    platform_i2c_mem_read_blocking(dev->i2c_port, ICM42688_DEFAULT_ADDRESS, reg, 1, &val, 1, 1000);
    return val;
}

static void
icm42688_i2c_readNbyte(icm42688_i2c_ctx_t *dev, uint8_t reg, uint8_t len, uint8_t *buf)
{
	platform_i2c_mem_read_blocking(dev->i2c_port, ICM42688_DEFAULT_ADDRESS, reg, 1, buf, len, 1000);
}

/** Hardware Functions
 * -------------------------------------------------------------**/
static int icm42688_i2c_hw_init(icm42688_i2c_ctx_t *dev)
{
	uint8_t who = icm42688_i2c_readbyte(dev, ICM42688_WHO_AM_I);
	if (who == ICM42688_VALUE_WHOAMI)
	{
		// select bank 0
		dev->i2c_buffer[0] = BANK_0 & 0x07;
		icm42688_i2c_writebyte(dev, ICM42688_REG_BANK_SEL, dev->i2c_buffer[0]);

		// accel config
    	dev->i2c_buffer[0] = (ACCEL_FS_4G << 5) | ACCEL_32KHZ;
    	icm42688_i2c_writebyte(dev, ICM42688_ACCEL_CONFIG0, dev->i2c_buffer[0]);

		// power mode
		dev->i2c_buffer[0] = ((GYRO_LNS & 0x03) << 2) | (ACCEL_LNE & 0x03);
		icm42688_i2c_writebyte(dev, ICM42688_PWR_MGMT0, dev->i2c_buffer[0]);
		platform_system_delay_ms(2);

		// gyro config
		dev->i2c_buffer[0] = (GYRO_FS_2000 << 5) | GYRO_32KHZ;
		icm42688_i2c_writebyte(dev, ICM42688_GYRO_CONFIG0, dev->i2c_buffer[0]);

		// set gyro bandwidth
		dev->i2c_buffer[0] = 0x07;
		icm42688_i2c_writebyte(dev, ICM42688_GYRO_ACCEL_CONFIG0, dev->i2c_buffer[0]);

		// set fifo
		dev->i2c_buffer[0] = 0x03;
		icm42688_i2c_writebyte(dev, ICM42688_FIFO_CONFIG1, dev->i2c_buffer[0]);

		// set tmst
		dev->i2c_buffer[0] = 0x1;
		icm42688_i2c_writebyte(dev, ICM42688_TMST_CONFIG, dev->i2c_buffer[0]);

		// config irq
		dev->i2c_buffer[0] =0x18 | 0x03;
		icm42688_i2c_writebyte(dev, ICM42688_INT_CONFIG, dev->i2c_buffer[0]);

		// config source0
		dev->i2c_buffer[0] = 0x08;
		icm42688_i2c_writebyte(dev, ICM42688_INT_SOURCE0, dev->i2c_buffer[0]);

		dev->i2c_buffer[0] = BANK_2 & 0x07; // select bank 2
		icm42688_i2c_writebyte(dev, ICM42688_REG_BANK_SEL, dev->i2c_buffer[0]);

		dev->i2c_buffer[0] = 0x00;
		icm42688_i2c_writebyte(dev, ICM42688_GYRO_CONFIG_STATIC2, dev->i2c_buffer[0]);

		dev->i2c_buffer[0] = BANK_0 & 0x07; // select bank 0
		icm42688_i2c_writebyte(dev, ICM42688_REG_BANK_SEL, dev->i2c_buffer[0]);
	}

	return 0;
}

static int icm42688p_read_i2c_blocking(icm42688_i2c_ctx_t *dev, float *data)
{
	uint8_t buf[14];
	icm42688_i2c_readNbyte(dev, ICM42688_TEMP_DATA1, 14, buf);

    int16_t temp = (int16_t)((buf[0] << 8) | buf[1]);
    int16_t ax   = (int16_t)((buf[2] << 8) | buf[3]);
    int16_t ay   = (int16_t)((buf[4] << 8) | buf[5]);
    int16_t az   = (int16_t)((buf[6] << 8) | buf[7]);
    int16_t gx   = (int16_t)((buf[8]  << 8) | buf[9]);
    int16_t gy   = (int16_t)((buf[10] << 8) | buf[11]);
    int16_t gz   = (int16_t)((buf[12] << 8) | buf[13]);

	data[0] = ax;
	data[1] = ay;
	data[2] = az;
	data[3] = gx;
	data[4] = gy;
	data[5] = gz;
	data[6] = temp;

	return 1;
}

static int icm42688_i2c_read_dma(icm42688_i2c_ctx_t *dev)
{

	i2c_handler = dev;

	icm42688_i2c_readNbyte(dev, ICM42688_TEMP_DATA1, 14, dev->i2c_buffer);
    return 0;
}

static bool icm42688_parse_i2c_data(icm42688_i2c_ctx_t *dev, float *data)
{

    uint8_t *buf = &dev->i2c_buffer[0];

    data[0] = (int16_t)((buf[2] << 8) | buf[3]);
    data[1] = (int16_t)((buf[4] << 8) | buf[5]);
    data[2] = (int16_t)((buf[6] << 8) | buf[7]);
    data[3] = (int16_t)((buf[8] << 8) | buf[9]);
    data[4] = (int16_t)((buf[10] << 8) | buf[11]);
    data[5] = (int16_t)((buf[12] << 8) | buf[13]);
    data[6] = (int16_t)((buf[0] << 8) | buf[1]);

    return true;
}

/** Factory Layers
 * -------------------------------------------------------------**/
static int icm42688_i2c_init_wrap(imu_t *imu)
{
    return icm42688_i2c_hw_init((icm42688_i2c_ctx_t *)imu->ctx);
}

static int icm42688_i2c_read_wrap(imu_t *imu)
{
	return icm42688_i2c_read_dma((icm42688_i2c_ctx_t *)imu->ctx);
}

static bool icm42688_i2c_parse_wrap(imu_t *imu, float *data)
{
	return icm42688_parse_i2c_data((icm42688_i2c_ctx_t *)imu->ctx, data);
}

static int icm42688_i2c_read_blocking_wrap(imu_t *imu, float *data)
{
	return icm42688p_read_i2c_blocking((icm42688_i2c_ctx_t *)imu->ctx, data);
}

/* =========================================================
 *  OPS Table
 * ========================================================= */
static imu_ops_t icm42688_i2c_ops = {
    .init = icm42688_i2c_init_wrap,
    .read = icm42688_i2c_read_wrap,
    .parse = icm42688_i2c_parse_wrap,
	.read_blocking = icm42688_i2c_read_blocking_wrap,
};

int icm42688_create_i2c(imu_t *imu, i2c_port_t port)
{
    static icm42688_i2c_ctx_t ctx_pool[2];
    static uint8_t idx = 0;

    if (idx >= 2)
        return -1;

    icm42688_i2c_ctx_t *ctx = &ctx_pool[idx++];
    memset(ctx, 0, sizeof(*ctx));
    ctx->i2c_port = port;

    imu->ctx = ctx;
    imu->ops = &icm42688_i2c_ops;

    return 0;
}

/** Callback DMA
 * -------------------------------------------------------------**/

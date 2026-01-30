/*
 * icm42688.c
 *
 *  Created on: Jan 30, 2026
 *      Author: manhhai
 */

#include "icm42688.h"

extern SPI_HandleTypeDef hspi1;

static uint8_t
icm42688_readwrite(spi_port_t port, uint8_t tx)
{
    uint8_t rx = 0xFF;
    platform_spi_write_read_blocking(port, &tx, &rx, 1);
    return rx;
}

static uint8_t
icm426888_readbyte(icm42688p_t *dev, uint8_t reg)
{
    uint8_t value;

    platform_spi_cs_low();
    icm42688_readwrite(dev->spi_port, reg | ICM42688_SPI_READ);
    value = icm42688_readwrite(dev->spi_port, 0x00);
    platform_spi_cs_high();
    return value;
}

static void
icm42688_writebyte(icm42688p_t *dev, uint8_t reg, uint8_t value)
{
    platform_spi_cs_low();
    icm42688_readwrite(dev->spi_port, reg & ICM42688_SPI_WRITE);
    icm42688_readwrite(dev->spi_port, value);
    platform_spi_cs_high();
}

static void
icm42688_readNbytes(icm42688p_t *dev, uint8_t reg, uint8_t *values, uint8_t length)
{
    platform_spi_cs_low();
    icm42688_readwrite(dev->spi_port, reg | ICM42688_SPI_READ);
    while (length--)
    {
        *values++ = icm42688_readwrite(dev->spi_port, 0x00);
    }
    platform_spi_cs_high();
}

void icm42688p_init(icm42688p_t *icm42688p, uint8_t Ascale, uint8_t Gscale,
		uint8_t AODR, uint8_t GODR, uint8_t aMode, uint8_t gMode, bool CLKIN)
{
	uint8_t value = 0x00;

	// select bank 0 first
	icm42688_writebyte(icm42688p, ICM42688_REG_BANK_SEL, BANK_0 & 0X07);

	// mode power : accel lownoise gyro lownoise
	value = ((gMode & 0x03) << 2) | (aMode & 0x03);
	icm42688_writebyte(icm42688p, ICM42688_PWR_MGMT0, value);
    platform_system_delay_ms(10);

    icm42688_writebyte(icm42688p, ICM42688_SIGNAL_PATH_RESET, 0x01);
    platform_system_delay_ms(2);
    uint8_t who = icm426888_readbyte(icm42688p, ICM42688_WHO_AM_I);
    if (who == ICM42688_VALUE_WHOAMI)
    {
    	// accel config
    	if (aMode != 0x00) {
    		value = (Ascale << 5) | AODR;
    		icm42688_writebyte(icm42688p, ICM42688_ACCEL_CONFIG0, value);
    	}
    	// gyro config
    	value = (Gscale << 5) | GODR;
    	icm42688_writebyte(icm42688p, ICM42688_GYRO_CONFIG0, value);
    	// set gyro bandwidth
    	value = 0x07;
    	icm42688_writebyte(icm42688p, ICM42688_GYRO_ACCEL_CONFIG0, value);
    	// set fifo
    	value = 0x03;
    	icm42688_writebyte(icm42688p, ICM42688_FIFO_CONFIG1, value);
    	// set tmst
    	value = 0x01;
    	icm42688_writebyte(icm42688p, ICM42688_TMST_CONFIG, value);
    	// config irq
    	value = 0x18 | 0x03;
    	icm42688_writebyte(icm42688p, ICM42688_INT_CONFIG, value);
    	// config source0
    	value = 0x08;
    	icm42688_writebyte(icm42688p, ICM42688_INT_SOURCE0, value);

    	if (CLKIN) {

    	}
    	// select bank 2
    	icm42688_writebyte(icm42688p, ICM42688_REG_BANK_SEL, BANK_2 & 0X07);
    	icm42688_writebyte(icm42688p, ICM42688_GYRO_CONFIG_STATIC2, 0x00);
    	icm42688_writebyte(icm42688p, ICM42688_REG_BANK_SEL, BANK_0 & 0X07);
    }
}

void icm42688p_read_blocking(icm42688p_t *icm42688p, float *data)
{
	uint8_t buf[14];
	icm42688_readNbytes(icm42688p, ICM42688_TEMP_DATA1, buf, 14);

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
}

void icm42688p_read_dma(icm42688p_t *dev)
{
    if (dev->spi_busy)
        return;

    dev->spi_busy = 1;
    dev->data_ready = 0;

    dev->spi_tx_buffer[0] = ICM42688_TEMP_DATA1 | ICM42688_SPI_READ;
    memset(&dev->spi_tx_buffer[1], 0x00, 14);

    platform_spi_cs_low();
    platform_spi_write_read_dma(dev->spi_port, dev->spi_tx_buffer, dev->spi_rx_buffer, 15 );
}

bool icm42688_parse_data(icm42688p_t *dev, float *data)
{
    if (!dev->data_ready)
        return false;

    uint8_t *buf = &dev->spi_rx_buffer[1];

    int16_t temp = (buf[0] << 8) | buf[1];
    int16_t ax   = (buf[2] << 8) | buf[3];
    int16_t ay   = (buf[4] << 8) | buf[5];
    int16_t az   = (buf[6] << 8) | buf[7];
    int16_t gx   = (buf[8]  << 8) | buf[9];
    int16_t gy   = (buf[10] << 8) | buf[11];
    int16_t gz   = (buf[12] << 8) | buf[13];

    data[0] = ax;
    data[1] = ay;
    data[2] = az;
    data[3] = gx;
    data[4] = gy;
    data[5] = gz;
    data[6] = temp;

    dev->data_ready = 0;
    return true;
}


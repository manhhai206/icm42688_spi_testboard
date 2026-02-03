/*
 * icm42688_spi_ddi.c
 *
 *
 *  Created on: Jan 30, 2026
 *  Author: manhhai
 */

#include "icm42688.h"
#include "imu.h"
#include <string.h>
#include <stdbool.h>

/** Macro Declaration
 * -------------------------------------------------------------**/
#define ICM42688_SPI_READ 0x80
#define ICM42688_SPI_WRITE 0x7F
#define ICM42688_VALUE_WHOAMI 0x47

/** Typedef structures Declaration
 * -------------------------------------------------------------**/
typedef struct
{
    spi_port_t spi_port;
    uint8_t spi_tx_buffer[15];
    uint8_t spi_rx_buffer[15];
    volatile uint8_t spi_busy;
    volatile uint8_t data_ready;
} icm42688_spi_ctx_t;

// static handler
static icm42688_spi_ctx_t *spi_handler = NULL;

/** Private Functions
 * -------------------------------------------------------------**/
static uint8_t
icm42688_readwrite(spi_port_t port, uint8_t tx)
{
    uint8_t rx = 0xFF;
    platform_spi_write_read_blocking(port, &tx, &rx, 1);
    return rx;
}

static uint8_t
icm42688_readbyte(icm42688_spi_ctx_t *dev, uint8_t reg)
{
    uint8_t value;

    platform_spi_cs_low();
    icm42688_readwrite(dev->spi_port, reg | ICM42688_SPI_READ);
    value = icm42688_readwrite(dev->spi_port, 0x00);
    platform_spi_cs_high();

    return value;
}

static void
icm42688_writebyte(icm42688_spi_ctx_t *dev, uint8_t reg, uint8_t value)
{
    platform_spi_cs_low();
    icm42688_readwrite(dev->spi_port, reg & ICM42688_SPI_WRITE);
    icm42688_readwrite(dev->spi_port, value);
    platform_spi_cs_high();
}

__attribute__((unused)) static void
icm42688_readNbytes(icm42688_spi_ctx_t *dev, uint8_t reg, uint8_t *values, uint8_t length)
{
    platform_spi_cs_low();
    icm42688_readwrite(dev->spi_port, reg | ICM42688_SPI_READ);
    while (length--)
        *values++ = icm42688_readwrite(dev->spi_port, 0x00);
    platform_spi_cs_high();
}

/** Hardware Functions
 * -------------------------------------------------------------**/
static int icm42688_spi_hw_init(icm42688_spi_ctx_t *dev)
{
    uint8_t value;

    /* Bank 0 */
    icm42688_writebyte(dev, ICM42688_REG_BANK_SEL, BANK_0 & 0x07);

    /* Power mode */
    value = ((GYRO_LNS & 0x03) << 2) | (ACCEL_LNE & 0x03);
    icm42688_writebyte(dev, ICM42688_PWR_MGMT0, value);
    platform_system_delay_ms(2);

    /* Reset */
    icm42688_writebyte(dev, ICM42688_SIGNAL_PATH_RESET, 0x01);
    platform_system_delay_ms(10);

    /* WHO AM I */
    if (icm42688_readbyte(dev, ICM42688_WHO_AM_I) != ICM42688_VALUE_WHOAMI)
        return -1;

    /* Accel config */
    value = (ACCEL_FS_4G << 5) | ACCEL_32KHZ;
    icm42688_writebyte(dev, ICM42688_ACCEL_CONFIG0, value);

    /* Gyro config */
    value = (GYRO_FS_2000 << 5) | GYRO_32KHZ;
    icm42688_writebyte(dev, ICM42688_GYRO_CONFIG0, value);

    icm42688_writebyte(dev, ICM42688_GYRO_ACCEL_CONFIG0, 0x07);
    icm42688_writebyte(dev, ICM42688_FIFO_CONFIG1, 0x03);
    icm42688_writebyte(dev, ICM42688_TMST_CONFIG, 0x01);

    return 0;
}

static int icm42688_spi_read_dma(icm42688_spi_ctx_t *dev)
{
    if (dev->spi_busy)
        return -1;

    spi_handler = dev;
    dev->spi_busy = 1;
    dev->data_ready = 0;

    dev->spi_tx_buffer[0] = ICM42688_TEMP_DATA1 | ICM42688_SPI_READ;
    memset(&dev->spi_tx_buffer[1], 0x00, 14);

    platform_spi_cs_low();
    platform_spi_write_read_dma(dev->spi_port, dev->spi_tx_buffer, dev->spi_rx_buffer, 15);
    return 0;
}

static bool icm42688_parse_spi_data(icm42688_spi_ctx_t *dev, float *data)
{
    if (!dev->data_ready)
        return false;

    uint8_t *buf = &dev->spi_rx_buffer[1];

    data[0] = (int16_t)((buf[2] << 8) | buf[3]);
    data[1] = (int16_t)((buf[4] << 8) | buf[5]);
    data[2] = (int16_t)((buf[6] << 8) | buf[7]);
    data[3] = (int16_t)((buf[8] << 8) | buf[9]);
    data[4] = (int16_t)((buf[10] << 8) | buf[11]);
    data[5] = (int16_t)((buf[12] << 8) | buf[13]);
    data[6] = (int16_t)((buf[0] << 8) | buf[1]);

    dev->data_ready = 0;
    return true;
}

/** Factory Layers
 * -------------------------------------------------------------**/
static int icm42688_spi_init_wrap(imu_t *imu)
{
    return icm42688_spi_hw_init((icm42688_spi_ctx_t *)imu->ctx);
}

static int icm42688_spi_read_wrap(imu_t *imu)
{
    return icm42688_spi_read_dma((icm42688_spi_ctx_t *)imu->ctx);
}

static bool icm42688_spi_parse_wrap(imu_t *imu, float *data)
{
    return icm42688_parse_spi_data((icm42688_spi_ctx_t *)imu->ctx, data);
}

/* =========================================================
 *  OPS Table
 * ========================================================= */
static imu_ops_t icm42688_spi_ops = {
    .init = icm42688_spi_init_wrap,
    .read = icm42688_spi_read_wrap,
    .parse = icm42688_spi_parse_wrap,
};

int icm42688_create_spi(imu_t *imu, spi_port_t port)
{
    static icm42688_spi_ctx_t ctx_pool[2];
    static uint8_t idx = 0;

    if (idx >= 2)
        return -1;

    icm42688_spi_ctx_t *ctx = &ctx_pool[idx++];
    memset(ctx, 0, sizeof(*ctx));
    ctx->spi_port = port;

    imu->ctx = ctx;
    imu->ops = &icm42688_spi_ops;

    return 0;
}

/** Callback DMA
 * -------------------------------------------------------------**/
void icm42688_spi_dma_done(spi_port_t port)
{
    if (!spi_handler || spi_handler->spi_port != port)
        return;

    platform_spi_cs_high();
    spi_handler->spi_busy = 0;
    spi_handler->data_ready = 1;
    spi_handler = NULL;
}

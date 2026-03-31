#include "MPU6500.h"

/* Buffer */
static uint8_t buffer[14];

/* CS Control */
static inline void CS_LOW(void)
{
    HAL_GPIO_WritePin(MPU6500_CS_PORT, MPU6500_CS_PIN, GPIO_PIN_RESET);
}

static inline void CS_HIGH(void)
{
    HAL_GPIO_WritePin(MPU6500_CS_PORT, MPU6500_CS_PIN, GPIO_PIN_SET);
}

/* Write Register */
static void MPU6500_Write(uint8_t reg, uint8_t data)
{
    uint8_t tx[2];

    tx[0] = reg & 0x7F;
    tx[1] = data;

    CS_LOW();
    HAL_SPI_Transmit(&hspi1, tx, 2, HAL_MAX_DELAY);
    CS_HIGH();
}

/* Read Registers */
static void MPU6500_Read(uint8_t reg, uint8_t *data, uint8_t len)
{
    uint8_t tx[1 + len];
    uint8_t rx[1 + len];

    tx[0] = reg | 0x80;

    for (uint8_t i = 1; i < (1 + len); i++)
        tx[i] = 0x00;

    CS_LOW();
    HAL_SPI_TransmitReceive(&hspi1, tx, rx, len + 1, HAL_MAX_DELAY);
    CS_HIGH();

    for (uint8_t i = 0; i < len; i++)
        data[i] = rx[i + 1];
}

/* Init */
void MPU6500_Init(void)
{
    HAL_Delay(100);

    CS_HIGH();  // VERY IMPORTANT

    /* Reset */
    MPU6500_Write(MPU6500_PWR_MGMT_1, 0x80);
    HAL_Delay(100);

    /* Wake up */
    MPU6500_Write(MPU6500_PWR_MGMT_1, 0x00);
    HAL_Delay(10);

    /* Config */
    MPU6500_Write(MPU6500_GYRO_CONFIG, 0x00);
    MPU6500_Write(MPU6500_ACCEL_CONFIG, 0x00);
}

/* WHO AM I */
uint8_t MPU6500_WhoAmI(void)
{
    uint8_t id = 0;
    MPU6500_Read(MPU6500_WHO_AM_I, &id, 1);
    return id;
}

/* Read Data */
void MPU6500_Read_All(float *ax, float *ay, float *az,
                      float *gx, float *gy, float *gz)
{
    int16_t ax_raw, ay_raw, az_raw;
    int16_t gx_raw, gy_raw, gz_raw;

    MPU6500_Read(MPU6500_ACCEL_XOUT_H, buffer, 14);

    ax_raw = (buffer[0] << 8) | buffer[1];
    ay_raw = (buffer[2] << 8) | buffer[3];
    az_raw = (buffer[4] << 8) | buffer[5];

    gx_raw = (buffer[8] << 8) | buffer[9];
    gy_raw = (buffer[10] << 8) | buffer[11];
    gz_raw = (buffer[12] << 8) | buffer[13];

    *ax = ax_raw / 16384.0f;
    *ay = ay_raw / 16384.0f;
    *az = az_raw / 16384.0f;

    *gx = gx_raw / 131.0f;
    *gy = gy_raw / 131.0f;
    *gz = gz_raw / 131.0f;
}

#ifndef __MPU6500_H__
#define __MPU6500_H__

#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef hspi1;

/* CS Pin */
#define MPU6500_CS_PORT GPIOA
#define MPU6500_CS_PIN  GPIO_PIN_4

/* Registers */
#define MPU6500_WHO_AM_I      0x75
#define MPU6500_PWR_MGMT_1    0x6B
#define MPU6500_GYRO_CONFIG   0x1B
#define MPU6500_ACCEL_CONFIG  0x1C
#define MPU6500_ACCEL_XOUT_H  0x3B

/* Functions */
void MPU6500_Init(void);
uint8_t MPU6500_WhoAmI(void);
void MPU6500_Read_All(float *ax, float *ay, float *az,
                      float *gx, float *gy, float *gz);

#endif

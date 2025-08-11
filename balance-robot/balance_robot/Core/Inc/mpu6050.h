/**
  ******************************************************************************
  * @file    mpu6050.h
  * @brief   MPU6050 accelerometer library header
  ******************************************************************************
  */

#ifndef __MPU6050_H
#define __MPU6050_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"

/* Defines -------------------------------------------------------------------*/
// MPU6050 I2C Address (AD0 connected to GND)
#define MPU6050_ADDR 0x68 << 1  // Left shift for HAL I2C

// MPU6050 Register Addresses
#define MPU6050_PWR_MGMT_1    0x6B
#define MPU6050_ACCEL_XOUT_H  0x3B
#define MPU6050_ACCEL_XOUT_L  0x3C
#define MPU6050_ACCEL_YOUT_H  0x3D
#define MPU6050_ACCEL_YOUT_L  0x3E
#define MPU6050_ACCEL_ZOUT_H  0x3F
#define MPU6050_ACCEL_ZOUT_L  0x40
#define MPU6050_WHO_AM_I      0x75

/* Exported types ------------------------------------------------------------*/
typedef struct {
    int16_t x_raw, y_raw, z_raw;        // Raw accelerometer data
    int32_t x_mg, y_mg, z_mg;          // Accelerometer data in milligravity
} MPU6050_Data_t;

/* Exported variables --------------------------------------------------------*/
extern MPU6050_Data_t mpu_data;

/* Exported functions prototypes ---------------------------------------------*/
uint8_t MPU6050_Init(void);
void MPU6050_Read_Accel(void);
int32_t MPU6050_Get_X_mg(void);
int32_t MPU6050_Get_Y_mg(void);
int32_t MPU6050_Get_Z_mg(void);

#ifdef __cplusplus
}
#endif

#endif /* __MPU6050_H */

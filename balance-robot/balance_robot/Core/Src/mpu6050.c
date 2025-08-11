/**
  ******************************************************************************
  * @file    mpu6050.c
  * @brief   MPU6050 accelerometer library implementation
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "mpu6050.h"

/* Private variables ---------------------------------------------------------*/
static uint8_t mpu6050_buffer[6];
MPU6050_Data_t mpu_data = {0};

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/**
  * @brief  Initialize MPU6050
  * @retval 0: Success, 1: Error
  */
uint8_t MPU6050_Init(void)
{
    uint8_t check;
    uint8_t data;

    // Check WHO_AM_I register
    if(HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_WHO_AM_I, 1, &check, 1, 1000) != HAL_OK)
    {
        return 1; // I2C Error
    }

    if(check == 0x68) // MPU6050의 기본 WHO_AM_I 값
    {
        // Wake up MPU6050 (Power Management Register 1)
        data = 0x00;
        if(HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, MPU6050_PWR_MGMT_1, 1, &data, 1, 1000) != HAL_OK)
        {
            return 1; // I2C Error
        }

        return 0; // Success
    }
    return 1; // Wrong device ID
}

/**
  * @brief  Read accelerometer data from MPU6050
  * @retval None
  */
void MPU6050_Read_Accel(void)
{
    // Read 6 bytes starting from ACCEL_XOUT_H
    if(HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, 1, mpu6050_buffer, 6, 1000) == HAL_OK)
    {
        // Combine high and low bytes
        mpu_data.x_raw = (int16_t)(mpu6050_buffer[0] << 8 | mpu6050_buffer[1]);
        mpu_data.y_raw = (int16_t)(mpu6050_buffer[2] << 8 | mpu6050_buffer[3]);
        mpu_data.z_raw = (int16_t)(mpu6050_buffer[4] << 8 | mpu6050_buffer[5]);

        // Convert to milligravity (mg) - avoid float
        // MPU6050 default full scale range is ±2g (16384 LSB/g)
        // 1g = 1000mg, so LSB/mg = 16384/1000 = 16.384
        mpu_data.x_mg = (int32_t)(mpu_data.x_raw * 1000) / 16384;
        mpu_data.y_mg = (int32_t)(mpu_data.y_raw * 1000) / 16384;
        mpu_data.z_mg = (int32_t)(mpu_data.z_raw * 1000) / 16384;
    }
}

/**
  * @brief  Get X-axis acceleration in milligravity
  * @retval X acceleration in mg
  */
int32_t MPU6050_Get_X_mg(void)
{
    return mpu_data.x_mg;
}

/**
  * @brief  Get Y-axis acceleration in milligravity
  * @retval Y acceleration in mg
  */
int32_t MPU6050_Get_Y_mg(void)
{
    return mpu_data.y_mg;
}

/**
  * @brief  Get Z-axis acceleration in milligravity
  * @retval Z acceleration in mg
  */
int32_t MPU6050_Get_Z_mg(void)
{
    return mpu_data.z_mg;
}

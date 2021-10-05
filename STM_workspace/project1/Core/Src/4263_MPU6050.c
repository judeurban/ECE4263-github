#include "main.h"
#include "4263_MPU6050.h"

/*
initialize the MPU6050
pass:
I2C_HandleTypeDef * ----- your initilized I2C bus
*/
void MPU6050_init(I2C_HandleTypeDef * hi2c)
{
  uint8_t check;
  uint8_t data;

  HAL_I2C_Mem_Read(hi2c, MPU6050_I2CADDR_DEFAULT, MPU6050_WHO_AM_I, 1, &check, 1, 1000);
  if(check == 104)
  {
    
		// power management register 0X6B we should write all 0's to wake the sensor up
    data = 0x00;
    HAL_I2C_Mem_Write(hi2c, MPU6050_I2CADDR_DEFAULT, MPU6050_PWR_MGMT_1, 1, &data, 1, 1000);
  
    // Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		data = 0x07;
		HAL_I2C_Mem_Write(hi2c, MPU6050_I2CADDR_DEFAULT, MPU6050_SMPLRT_DIV, 1, &data, 1, 1000);
  
		// Set accelerometer configuration in ACCEL_CONFIG Register
		// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> � 2g
		data = 0x00;
		HAL_I2C_Mem_Write(hi2c, MPU6050_I2CADDR_DEFAULT, MPU6050_ACCEL_CONFIG, 1, &data, 1, 1000);

    // Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> � 250 �/s
		data = 0x00;
		HAL_I2C_Mem_Write(hi2c, MPU6050_I2CADDR_DEFAULT, MPU6050_GYRO_CONFIG, 1, &data, 1, 1000);
  
  }
}

/*
read accelerometer data from the MPU6050
pass:
I2C_HandleTypeDef * ----- your initilized I2C bus
float * ----------------- the float array the function will write to
*/
void MPU6050_Read_Accel(I2C_HandleTypeDef * hi2c, float * A)
{
  uint8_t rcvd_data[6];

  //read all six byes of data from the accelerometer
  //error!!
  HAL_I2C_Mem_Read(hi2c, MPU6050_I2CADDR_DEFAULT, MPU6050_ACCEL_OUT, 1, rcvd_data, 6, 1000);

  //                          MSB(yte)           LSB(yte)
  X_RAW_accel = (uint16_t)(rcvd_data[0] << 8 | rcvd_data[1]);
  Y_RAW_accel = (uint16_t)(rcvd_data[2] << 8 | rcvd_data[3]);
  Z_RAW_accel = (uint16_t)(rcvd_data[4] << 8 | rcvd_data[5]);

  /*  16384.0 is device constant  */

  A[0] = X_RAW_accel / 16384.0;
  A[1] = Y_RAW_accel / 16384.0;
  A[2] = Z_RAW_accel / 16384.0;

  return;

}

/*
read gyroscope data from the MPU6050
I2C_HandleTypeDef * ----- your initilized I2C bus
float * ----------------- the float array the function will write to
*/
void MPU6050_Read_Gyro(I2C_HandleTypeDef * hi2c, float * G)
{
  uint8_t rcvd_data[6];

  //read all six byes of data from the gyro
  HAL_I2C_Mem_Read(hi2c, MPU6050_I2CADDR_DEFAULT, MPU6050_GYRO_OUT, 1, rcvd_data, 6, 1000);

  X_RAW_gyro = (uint16_t)(rcvd_data[0] << 8 | rcvd_data[1]);
  Y_RAW_gyro = (uint16_t)(rcvd_data[2] << 8 | rcvd_data[3]);
  Z_RAW_gyro = (uint16_t)(rcvd_data[4] << 8 | rcvd_data[5]);

  /*  131.0 is device constant  */
  G[0] = X_RAW_gyro / 131.0;
  G[1] = Y_RAW_gyro / 131.0;
  G[2] = Z_RAW_gyro / 131.0;

  return;

}
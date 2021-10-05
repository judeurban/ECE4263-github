#include "main.h"
#include "4263_MPU6050.h"

//initialize the MPU6050. pass the I2C bus!
void MPU6050_init(I2C_HandleTypeDef * hi2c)
{
  uint8_t check;
  uint8_t data;

  /*  
    check if the device is ready  
    a return of 0x68 implies a healthy connection
  */
  

    // HAL_I2C_Mem_Read(&hi2c3,MPU6050_ADDR,WHO_AM_I_REG,1,&check,1,100);
    // if(check == 104)


  // HAL_I2C_Mem_Read(hi2c, MPU6050_I2CADDR_DEFAULT, 0x68, 1, &check, 1, 1000);    //returns 0x20 or 0d32
  HAL_I2C_Mem_Read(hi2c, MPU6050_I2CADDR_DEFAULT, MPU6050_WHO_AM_I, 1, &check, 1, 1000);
  // if(check == (0x68))
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

//read accelerometer data from the MPU6050. pass the I2C bus!
void MPU6050_Read_Accel(I2C_HandleTypeDef * hi2c)
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
  Ax = X_RAW_accel / 16384.0;
  Ay = Y_RAW_accel / 16384.0;
  Az = Z_RAW_accel / 16384.0;

}

//read gyro data from the MPU6050. pass the I2C bus!
void MPU6050_Read_Gyro(I2C_HandleTypeDef * hi2c)
{
  uint8_t rcvd_data[6];

  //read all six byes of data from the gyro
  //error!!
  HAL_I2C_Mem_Read(hi2c, MPU6050_I2CADDR_DEFAULT, MPU6050_GYRO_OUT, 1, rcvd_data, 6, 1000);

  X_RAW_gyro = (uint16_t)(rcvd_data[0] << 8 | rcvd_data[1]);
  Y_RAW_gyro = (uint16_t)(rcvd_data[2] << 8 | rcvd_data[3]);
  Z_RAW_gyro = (uint16_t)(rcvd_data[4] << 8 | rcvd_data[5]);

  /*  131.0 is device constant  */
  Gx = X_RAW_gyro / 131.0;
  Gy = Y_RAW_gyro / 131.0;
  Gz = Z_RAW_gyro / 131.0;

}

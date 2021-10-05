/*  

device registers 

hex     decimal     register

3B      59          ACCEL_XOUT[15:8]
3C      60          ACCEL_XOUT[7:0]
3D      61          ACCEL_YOUT[15:8]
3E      62          ACCEL_YOUT[7:0]
3F      63          ACCEL_ZOUT[15:8]
40      64          ACCEL_ZOUT[7:0]

source: https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf

*/


#define MPU6050_I2CADDR_DEFAULT 0xD0                                         \

#define MPU6050_DEVICE_ID 0x68 ///< The correct MPU6050_WHO_AM_I value

#define MPU6050_SELF_TEST_X                                                    \
  0x0D ///< Self test factory calibrated values register
#define MPU6050_SELF_TEST_Y                                                    \
  0x0E ///< Self test factory calibrated values register
#define MPU6050_SELF_TEST_Z                                                    \
  0x0F ///< Self test factory calibrated values register
#define MPU6050_SELF_TEST_A                                                    \
  0x10 ///< Self test factory calibrated values register

#define MPU6050_SMPLRT_DIV 0x19  ///< sample rate divisor register
#define MPU6050_CONFIG 0x1A      ///< General configuration register
#define MPU6050_GYRO_CONFIG 0x1B ///< Gyro specfic configuration register
#define MPU6050_GYRO_OUT 0x43


#define MPU6050_ACCEL_CONFIG                                                   \
  0x1C ///< Accelerometer specific configration register
#define MPU6050_INT_PIN_CONFIG 0x37    ///< Interrupt pin configuration register
#define MPU6050_WHO_AM_I (0x75)          ///< Divice ID register
#define MPU6050_SIGNAL_PATH_RESET 0x68 ///< Signal path reset register
#define MPU6050_USER_CTRL 0x6A         ///< FIFO and I2C Master control register
#define MPU6050_PWR_MGMT_1 0x6B        ///< Primary power/sleep control register
#define MPU6050_PWR_MGMT_2 0x6C ///< Secondary power/sleep control register
#define MPU6050_TEMP_H 0x41     ///< Temperature data high byte register
#define MPU6050_TEMP_L 0x42     ///< Temperature data low byte register
#define MPU6050_ACCEL_OUT 0x3B  ///< base address for sensor data reads

int16_t X_RAW_accel;
int16_t Y_RAW_accel;
int16_t Z_RAW_accel;

int16_t X_RAW_gyro;
int16_t Y_RAW_gyro;
int16_t Z_RAW_gyro;

float Ax, Ay, Az, Gx, Gy, Gz;

void MPU6050_init(I2C_HandleTypeDef *);
void MPU6050_Read_Accel(I2C_HandleTypeDef *, float *);
void MPU6050_Read_Gyro(I2C_HandleTypeDef *, float *);


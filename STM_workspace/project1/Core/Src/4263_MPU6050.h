// file: 4163_MPU6050.h

/* defines  */

#define MPU6050_I2CADDR_DEFAULT   0xD0      // Device address               
#define MPU6050_WHO_AM_I          0x75      // Device ID register

#define MPU6050_SMPLRT_DIV        0x19      // sample rate divisor register
#define MPU6050_CONFIG            0x1A      // General configuration register
#define MPU6050_GYRO_CONFIG       0x1B      // Gyro specfic configuration register
#define MPU6050_GYRO_OUT          0x43      // Gyro output register

#define MPU6050_ACCEL_CONFIG      0x1C      // Accelerometer specific configration register
#define MPU6050_SIGNAL_PATH_RESET 0x68      // Signal path reset register
#define MPU6050_USER_CTRL         0x6A      // FIFO and I2C Master control register
#define MPU6050_PWR_MGMT_1        0x6B      // Primary power/sleep control register
#define MPU6050_PWR_MGMT_2        0x6C      // Secondary power/sleep control register
#define MPU6050_ACCEL_OUT         0x3B      // base address for sensor data reads

/* variables  */

float Ax, Ay, Az, Gx, Gy, Gz;

int16_t X_RAW_accel, Y_RAW_accel, Z_RAW_accel;
int16_t X_RAW_gyro, Y_RAW_gyro, Z_RAW_gyro;

/* functions  */

void MPU6050_init(I2C_HandleTypeDef *);
void MPU6050_Read_Accel(I2C_HandleTypeDef *, float *);
void MPU6050_Read_Gyro(I2C_HandleTypeDef *, float *);

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

/*

+---------------+-----+-----+-----+
|               |  x  |  y  |  z  |
+===============+=====+=====+=====+
| accelerometer | [0] | [1] | [2] |
+---------------+-----+-----+-----+
|   gyroscope   | [0] | [1] | [2] |
+---------------+-----+-----+-----+

*?




    Ax: -0.274
    Ay: -1.032
    Az: -0.717

    Gx: 197.69
    Gy: 18.916
    Gz: -58.74

    Ax: 0.2612
    Ay: 0.0615
    Az: 0.9470

    Gx: 76.29
    Gy: 1.9084
    Gz: -30.37



    
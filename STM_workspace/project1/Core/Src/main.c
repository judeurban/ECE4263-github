/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "jmuMPU6050.h"

//#include "Adafruit_MPU6050.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

I2C_HandleTypeDef hi2c4;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C4_Init();
  /* USER CODE BEGIN 2 */

  MPU6050_init(&hi2c4);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    MPU6050_Read_Accel(&hi2c4);
    MPU6050_Read_Gyro(&hi2c4);

    HAL_Delay(50);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C4;
  PeriphClkInitStruct.I2c4ClockSelection = RCC_I2C4CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C4_Init(void)
{

  /* USER CODE BEGIN I2C4_Init 0 */

  /* USER CODE END I2C4_Init 0 */

  /* USER CODE BEGIN I2C4_Init 1 */

  /* USER CODE END I2C4_Init 1 */
  hi2c4.Instance = I2C4;
  hi2c4.Init.Timing = 0x00303D5B;
  hi2c4.Init.OwnAddress1 = 0;
  hi2c4.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c4.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c4.Init.OwnAddress2 = 0;
  hi2c4.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c4.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c4.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c4) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c4, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c4, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C4_Init 2 */

  /* USER CODE END I2C4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

void MPU6050_init(I2C_HandleTypeDef * hi2c)
{
  uint8_t check;
  uint8_t data;

  /*  
    check if the device is ready  
    a return of 0x68 implies a healthy connection
  */
  
  // HAL_I2C_Mem_Read(hi2c, MPU6050_I2CADDR_DEFAULT, 0x68, 1, &check, 1, 1000);    //returns 0x20 or 0d32
  HAL_I2C_Mem_Read(hi2c, MPU6050_I2CADDR_DEFAULT, MPU6050_WHO_AM_I, 1, &check, 1, 1000);
  // if(check == (0x68))
  if(check == (0x20))
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
  HAL_I2C_Mem_Read(hi2c, MPU6050_I2CADDR_DEFAULT, MPU6050_ACCEL_OUT, 1, &rcvd_data, 6, 1000);

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
  HAL_I2C_Mem_Read(hi2c, MPU6050_I2CADDR_DEFAULT, MPU6050_GYRO_OUT, 1, &rcvd_data, 6, 1000);

  X_RAW_gyro = (uint16_t)(rcvd_data[0] << 8 | rcvd_data[1]);
  Y_RAW_gyro = (uint16_t)(rcvd_data[2] << 8 | rcvd_data[3]);
  Z_RAW_gyro = (uint16_t)(rcvd_data[4] << 8 | rcvd_data[5]);

  /*  131.0 is device constant  */
  Gx = X_RAW_gyro / 131.0;
  Gy = Y_RAW_gyro / 131.0;
  Gz = Z_RAW_gyro / 131.0;

}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

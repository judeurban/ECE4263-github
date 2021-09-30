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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define HMC5883l_ADDRESS (0x1E << 1)
#define HMC5883l_Enable_A (0x70)        //control REG A, (0x70, measurement set, f = 15 Hz)
#define HMC5883l_Enable_B (0xA0)        //control REG B, (0xA0, gain of 5)
#define HMC5883l_MR (0x00)              //node register, (0x00, continuous measurement)

/*  HMC5883l MSB and LSB addresses  */

#define HMC5883l_ADD_DATAX_MSB  (0x03)
#define HMC5883l_ADD_DATAX_LSB  (0x04)

#define HMC5883l_ADD_DATAY_MSB  (0x07)
#define HMC5883l_ADD_DATAY_LSB  (0x08)

#define HMC5883l_ADD_DATAZ_MSB  (0x05)
#define HMC5883l_ADD_DATAZ_LSB  (0x06)

/*  sum of the two registers  */
#define HMC5883l_ADD_DATAX_MSB_LSB (HMC5883l_ADD_DATAX_MSB | HMC5883l_ADD_DATAX_LSB)
#define HMC5883l_ADD_DATAY_MSB_LSB (HMC5883l_ADD_DATAY_MSB | HMC5883l_ADD_DATAY_LSB)
#define HMC5883l_ADD_DATAZ_MSB_LSB (HMC5883l_ADD_DATAZ_MSB | HMC5883l_ADD_DATAZ_LSB) 

/*  variables to receive data */
uint8_t DataX[2];
uint16_t Xaxis = 0;

uint8_t DataY[2];
uint16_t Yaxis = 0;

uint8_t DataZ[2];
uint16_t Zaxis = 0;

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


  uint8_t RegSettingA = HMC5883l_Enable_A;
  uint8_t RegSettingB = HMC5883l_Enable_B;
  uint8_t RegSettingMR = HMC5883l_MR;
  
  /*  clear all variables   */

  // Xaxis = 0;
  // Yaxis = 0;
  // Zaxis = 0;
  
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  // #define compass _HMC5883L_H_
  // compass = _HMC5883L_H_;
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

/*
  // HAL_I2C_AddrCallback(&hi2c4, (int)hi2c4.hdmarx, hi2c4.Init.AddressingMode);
  HAL_I2C_Init(&hi2c4);
  HAL_I2C_IsDeviceReady(&hi2c4, HMC5883L_ADDRESS, 2, 1);
  HMC5883L_initialize();
*/

   HAL_I2C_Init(&hi2c4);

  //healty
  if(HAL_I2C_IsDeviceReady(&hi2c4, HMC5883l_ADDRESS, 3, 100) == HAL_OK)
  {
    HAL_I2C_Mem_Write(&hi2c4, HMC5883l_ADDRESS, 0x00, 1, HMC5883l_Enable_A, 1, 100);
    HAL_I2C_Mem_Write(&hi2c4, HMC5883l_ADDRESS, 0x01, 1, HMC5883l_Enable_B, 1, 100);
    HAL_I2C_Mem_Write(&hi2c4, HMC5883l_ADDRESS, 0x02, 1, HMC5883l_MR, 1, 100);
  }
  //not healthy
  else
  {
    //return 0;
  }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    HAL_I2C_Mem_Read(&hi2c4, HMC5883l_ADDRESS, HMC5883l_ADD_DATAX_MSB_LSB, 1, DataX, 2, 100);
    Xaxis = ( (DataX[1]<<8) | (DataX[0]) )/660.f;

    /*  read y axis values  */
    HAL_I2C_Mem_Read(&hi2c4, HMC5883l_ADDRESS, HMC5883l_ADD_DATAY_MSB_LSB, 1, DataY, 2, 100);
    Yaxis = ( (DataY[1]<<8) | (DataY[0]) )/660.f;

    HAL_I2C_Mem_Read(&hi2c4, HMC5883l_ADDRESS, HMC5883l_ADD_DATAZ_MSB_LSB, 1, DataZ, 2, 100);
    Zaxis = ( (DataZ[1]<<8) | (DataZ[0]) )/660.f;


    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */

    /*  read x axis values  */
    // storing two bytes into DataX. | operation "adds" the two bytes together.


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

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "i2s.h"
#include "spi.h"
#include "tim.h"
#include "usb_otg.h"
#include "gpio.h"

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

/* USER CODE BEGIN PV */
volatile uint8_t flag = 0;
char trans_str[64] = {0,};
volatile uint16_t adc[2] = {0,};
const int air_value =3770;
const int water_value = 2419;
//volatile float soil_moisture_percent;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile uint32_t tim10_overflows = 0;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance == ADC1)
    {
        flag = 1;
        HAL_ADC_Stop_DMA(&hadc1);
        adc[0] = 0;
        adc[1] = 0;
        HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adc, 2);
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if( htim->Instance == TIM10 )
    {
        ++tim10_overflows;
    }
}

inline uint32_t get_tim10_us()
{
    __HAL_TIM_DISABLE_IT(&htim10, TIM_IT_UPDATE);
    uint32_t res = tim10_overflows * 10000 + __HAL_TIM_GET_COUNTER(&htim10);
    __HAL_TIM_ENABLE_IT(&htim10, TIM_IT_UPDATE);
    return res;
}

inline void udelay_TIM10(uint32_t useconds) {
    uint32_t before = get_tim10_us();
    while( get_tim10_us() < before+useconds){}
}
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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_I2S3_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_TIM3_Init();
  MX_USB_OTG_FS_USB_Init();
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */
    HAL_TIM_Base_Start_IT(&htim10);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adc, 2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
    while (1)
    {
        // setting 1 to a motor pin
        HAL_GPIO_WritePin(GPIOD, MOTOR_Pin, GPIO_PIN_SET);

        // dealing with 2 sensors
        if(flag)
        {
            flag = 0;

            HAL_ADC_Stop_DMA(&hadc1);

            HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adc, 2);

            uint16_t moisture =  adc[0];
            volatile uint16_t light = adc[1];
            HAL_ADC_Stop_DMA(&hadc1);
            float soil_moisture_percent = ((((float)moisture-air_value)*((float)(100))/(water_value - air_value)));


//
            if(soil_moisture_percent >= 85){
                HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
                if(soil_moisture_percent >100){
                    soil_moisture_percent = 100;
                };

            }
            if(soil_moisture_percent <= 84){
                HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
//                if(soil_moisture_percent < 0){
//                    soil_moisture_percent = 0;
                HAL_GPIO_WritePin(GPIOD, RELAY_Pin, GPIO_PIN_SET);
                HAL_Delay(100);
                HAL_GPIO_WritePin(GPIOD, RELAY_Pin, GPIO_PIN_RESET);
                }

//            }
//            else if (soil_moisture_percent > 30 && soil_moisture_percent <= 85) {
//                HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
//                //red
//            }

            // turning on or turning off the light
            if (light > 1000 && light < 2000) {
                HAL_GPIO_WritePin(GPIOD, DIODE1_Pin, GPIO_PIN_SET);
            }
            else if (light < 1000 && (light != 0)) {
                HAL_GPIO_WritePin(GPIOD, DIODE1_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOD, DIODE2_Pin, GPIO_PIN_SET);
            }
            else if (light > 3000) {
                HAL_GPIO_WritePin(GPIOD, DIODE1_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, DIODE2_Pin, GPIO_PIN_RESET);
            }

//            HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
//            udelay_TIM10(16);
//            HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
//
//            while(HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_RESET );
//            {}
//            uint32_t before = get_tim10_us();
//            while(HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_SET );
//            {}
//            uint32_t pulse_time = get_tim10_us()-before;
//            volatile uint32_t distance = pulse_time/58;

            int t_state = HAL_GPIO_ReadPin(TRIG_GPIO_Port, TRIG_Pin);
            while(  t_state == GPIO_PIN_SET )
            {
                //LCD5110_printf(&lcd1,BLACK,"Wrong state\n before triggering,\n Trig is high\n");
            }
            HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
            if ( HAL_GPIO_ReadPin(TRIG_GPIO_Port, TRIG_Pin) != GPIO_PIN_SET )
            {
                //LCD5110_printf(&lcd1,BLACK,"Line Trig\n do not went\n high\n while triggering.\n");
                HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
                HAL_Delay(300);
                continue;
            }
            udelay_TIM10(16);
            HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
            if ( HAL_GPIO_ReadPin(TRIG_GPIO_Port, TRIG_Pin) != GPIO_PIN_RESET )
            {

                //LCD5110_printf(&lcd1,BLACK,"Line Trig\n do not went\n low\n while triggering.\n");
                HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
                HAL_Delay(300);
                continue;
            }
            if ( HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_SET )
            {
                //LCD5110_printf(&lcd1,BLACK,"Line ECHO\n is high\n too early.\n");
                HAL_Delay(300);
                continue;
            }

            uint32_t watch = get_tim10_us();
            int didnt_had_1_at_echo = 0;
            while(HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_RESET )
            {
                if( get_tim10_us() - watch > 500000 )
                {
                    didnt_had_1_at_echo = 1;
                    break;
                }
            }
            if(didnt_had_1_at_echo)
            {
                //LCD5110_printf(&lcd1,BLACK,"Line ECHO\n didn't go\n high for\n a long time.\n");
                HAL_Delay(300);
                continue;
            }

            uint32_t before = get_tim10_us();
            int didnt_had_0_at_echo = 0;
            while(HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_SET )
            {
                if( get_tim10_us() - watch > 500000 )
                {
                    didnt_had_0_at_echo = 1;
                    break;
                }
            }
            if(didnt_had_0_at_echo)
            {
                //LCD5110_printf(&lcd1,BLACK,"Line ECHO\n didn't go\n low for\n a"
                                           //" long time.\n");
                HAL_Delay(300);
                continue;
            }

            volatile uint32_t pulse_time = get_tim10_us()-before;
            volatile double distance = pulse_time/58;
            if (distance < 500) {
                //LCD5110_printf(&lcd1, BLACK, "Distance is\n %lu cm\n", distance);
            }
            else if (distance > 500)
            {
                //LCD5110_printf(&lcd1,BLACK,"Too far\n no echo\n at all");
            }


            // continue the work with DMA
            adc[0] = 0;
            adc[1] = 0;
            //HAL_Delay(10000);
            HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adc, 2);

        }
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 200;
  PeriphClkInitStruct.PLLI2S.PLLI2SM = 5;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

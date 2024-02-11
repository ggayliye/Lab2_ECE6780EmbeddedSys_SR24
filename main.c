/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
// LAB 2
	
	
	//Initializing all of the LED pins
	
	RCC->AHBENR |= 0x80000; //For C port (LED ports), "Bit 19 IOPCEN: I/O port C clock enable". 19th bit position. 
	// We know 19th bit from data sheet RM0091 on page 122.
	// PC6 is connected to RED LED. 
	// PC7 is connected to BLUE LED.
	// PC8 is connected to ORANGE LED.
	// PC9 is connected to GREEN LED.
	
	//HAL_Delay(2); //Delays 2 milli-sec
	
	
	//Enable ALL LEDs for "General purpose output mode, "01" as bits"
  GPIOC->MODER |= (85<<12); // This means: Move Right to left as 12 digits (the digits are in bits).
	//then start adjusting from right to left converting 85 to binary and applying OR "|".
	// 85 in binary will be 01 01 01 01.
	
	GPIOC->OTYPER &= 0x0; //no OR (|) . GPIO port output type register

	GPIOC->OSPEEDR &= 0x0; //GPIO port output speed register to Low speed
	
	GPIOC->PUPDR &= 0x0; //GPIO port pull-up/pull-down register
	
//	///////-----------------PIN A-----------------------//////////
//	//Configure user pushbutton
//	RCC->AHBENR |= (1<<17); // We know 17th bit from data sheet RM0091 on page 122 that says "Bit 17 IOPBEN: I/O port A clock enable".
//	
//	HAL_Delay(2); //Delays 2 milli-sec

//	GPIOA->MODER &= ~(3<<0); //setting A0 to input mode
//	
//	GPIOA->OSPEEDR &= ~(3<<0); //GPIO port output speed register to Low speed
//	GPIOA->PUPDR &= ~(3<<0); //GPIO port pull-up/pull-down register. enable pull down.
//	GPIOA->PUPDR |= (1<<1);
//	

	
//	 //Unmask interrupt generation on EXTI input. line 0
//    EXTI->EMR |= 1;
//   //Set input 0 to have a rising-edge trigger.
//    EXTI->RTSR |= 1;
//	
//	 //Use the RCC to enable the peripheral clock to the SYSCFG peripheral.
//	  RCC->APB2RSTR |=1;
//	  SYSCFG->EXTICR[0] &=0;// Access the EXTICR0 and set it to PA0
	
	
	
	
	
	
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
	//declare the handler function




//__NVIC_EnableIRQ(EXTI0_1_IRQn);
//NVIC_SetPriority(EXTI0_1_IRQn,1);
	
	
		//Set the green LED (PC9) (GREEN) high/ON
	GPIOC->ODR |= (1<<9); // 9th bit (10th digit as bit count starts from 0) = 1. shift 9 digits from right to left and make the next digit 1.
	

				
	GPIOC->ODR |= (1<<6); //// Set red LED (PC6) ON  
	
	
	
	
  while (1)
  {
     HAL_Delay(550);
		
    /* USER CODE END WHILE */

    /* USER CODE END WHILE */
//Toggle the red LED (PC6) with a moderately-slow delay (400-600ms) in the infinite loop
		 // GPIOC->BSRR |= (1<<9);
      
		
		
	if(GPIOC->ODR | (0x40)) // if red is on, red LED (PC6)
		{
	  	GPIOC->ODR  &= 0x3BF;  // make it off
			 HAL_Delay(550); //wait 550 ms so that program can catch the off signal
		  }
	
		GPIOC->ODR |= (0x40); //make it on back 
		
		
		
		
    /* USER CODE BEGIN 3 */
  }
	
  /* USER CODE END 3 */
}



//	// Enable the selected EXTI interrupt by passing its defined name to the NVIC_EnableIRQ() function.

//	void EXTI0_1_IRQHandler(){
//		
//		
//		
//	if(GPIOC->ODR == 0x80)
//		{  
//	GPIOC->ODR = 0x40;
//		}
//		else{
//			GPIOC->ODR = 0x80;
//		}
//	EXTI->PR |=1;







/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

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
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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

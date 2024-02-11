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

volatile short button_count=0;
volatile short led_lit_count=0;

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
	
		

	//Toggle both the green and orange LEDs (PC8 & PC9) in the EXTI interrupt handler.
	void EXTI0_1_IRQHandler(void) {
		
        button_count = 1;

     EXTI->PR |=EXTI_PR_PR0; //EXTI->PR |=EXTI_PR_PR0;
		
//		//debouncer = (debouncer << 1); // Always shift every loop iteration. shift right to left one digit.
//	if(GPIOA->IDR  & (0x3FF)){
//			/* Toggle LED2 */
////		if (debouncer == 0x7FFFFFFF)
////    {}
//        // This code triggers only once when transitioning to steady high!
////        GPIOC->ODR ^= 1 << 6; // "^" is XOR 
////        GPIOC->ODR ^= 1 << 7;

//  
//		
//		/* Clear the EXTI line 0 pending bit */
//		 

//	}	

//		
//		GPIOC->ODR  |= 0x100 ;  // ORANGE ON!
//		
//		
//	if(GPIOA->IDR  & (0x3FF)) // //if the GREEN is ON (PC9). If input is set/high. . reads the pull-down resistance. 
//		{
//	  	GPIOC->ODR  &= 0x1FF;  // make GREEN is OFF
//			GPIOC->ODR  |= 0x100 ;  // ORANGE ON!

//		  }
//	else{
//		GPIOC->ODR &= 0x3FF; //make GREEN back ON. //GPIOC->ODR |= (1<<9);
//		GPIOC->ODR  &= 0x2FF ;  // ORANGE OFF!
//	}
//			//Clear the appropriate flag for input line 0 in the EXTI pending register within the handler.
//		EXTI->PR |=1;
	

	};

	
	// Helper function for toggle handler:
	
void ToggleFunction(void) {

    if (button_count == 1){
			
        if (led_lit_count == 0){

            //GPIOC->BSRR  |= 0x100 ;  // ORANGE ON! GPIOC->BSRR  |= 0x100 | 0x2FF ; 

            GPIOC->ODR &= 0x2FF; //Green On
            GPIOC->ODR |= 0x200;// orange off.(GPIOC->BSRR&0x2FF) | 0x200; //make GREEN back ON. //GPIOC->ODR |= (1<<9);

        }
        led_lit_count++;
        if (led_lit_count > 1){

            GPIOC->ODR &= 0x1FF;// make GREEN OFF.  
            GPIOC->ODR |= 0x100; //orange ON

            led_lit_count = 0;
        }

        button_count = 0;
    }
}

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




	
		//Set the green LED (PC9) (GREEN) high/ON
		//	GPIOC->ODR |= (1<<9); // 9th bit (10th digit as bit count starts from 0) = 1. shift 9 digits from right to left and make the next digit 1.
		

				
		GPIOC->ODR |= (1<<6); //// Set red LED (PC6) ON  

		//	///////-----------------PIN A-----------------------//////////
	
		//1. Configure user pushbutton
		RCC->AHBENR |= (1<<17); //  "Bit 17 IOPBEN: I/O port A clock enable". We know 17th bit from data sheet RM0091 on page 122. 

		HAL_Delay(2); //Delays 2 milli-sec

		GPIOA->MODER &= ~(3<<0); //setting A0 to input mode

		GPIOA->OSPEEDR &= ~(3<<0); //GPIO port output speed register to Low speed
		GPIOA->PUPDR &= ~(3<<0); //GPIO port pull-up/pull-down register. enable pull down.
		GPIOA->PUPDR |= (1<<1);

		//2. Pin PA0 connects to the EXTI input line 0 (EXTI0).


		//3. Enable/unmask interrupt generation on EXTI input line 0 (EXTI0)
		//Unmask interrupt generation on EXTI input line 0. 
		EXTI->IMR |= 0x1;

		//4. Configure the EXTI input line 0 to have a rising-edge trigger.
		//Set input 0 to have a rising-edge trigger.
		EXTI->RTSR |= 0x1;


		// Setting the SYSCFG Pin Multiplexer:
		//Use the RCC to enable the peripheral clock to the SYSCFG peripheral.
		RCC->APB2ENR |=1; //APB peripheral clock enable register 2 (RCC_APB2ENR)
		SYSCFG->EXTICR[0] |=0x0;// Access the EXTICR0 and set it to PA0


		// IRQn_Type for line 0 is EXTI0_1_IRQn ; interrupt no: 5


		// Enable and Set Priority of the EXTI Interrupt:
		//	__NVIC_EnableIRQ(EXTI0_1_IRQn);

		NVIC_EnableIRQ(EXTI0_1_IRQn); //Enable the selected EXTI interrupt by passing its defined name
		NVIC_SetPriority(EXTI0_1_IRQn,1);// Set the priority for the interrupt to 1 (high-priority)

		// ----PART 1 :Lab Assignment: Setting up the Interrupt Handler -----//
		//Writing the EXTI Interrupt Handler:

		//EXTI0_1_IRQHandler ; EXTI Line 0 and 1

		// Look the code after main program ends below:
	
	
while (1){

    ToggleFunction();

    HAL_Delay(550);

    /* USER CODE END WHILE */

    /* USER CODE END WHILE */
	
	
    //Toggle the red LED (PC6) with a moderately-slow delay (400-600ms) in the infinite loop
    // GPIOC->BSRR |= (1<<9);

    if (GPIOC->ODR | (0x40)) // if red is on, red LED (PC6)
    {
        GPIOC->ODR &= 0x3BF;  // make it off
        HAL_Delay(550); //wait 550 ms so that program can catch the off signal
    }

    GPIOC->ODR |= (0x40); //make it on back 

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

/* USER CODE BEGIN Header */
/**
 ****************************************************************************************************
 * @file        main.c
 * @author      锟斤拷锟斤拷原锟斤拷锟脚讹拷(ALIENTEK)
 * @version     V1.0
 * @date        2024-01-01
 * @brief       TFTLCD(MCU锟斤拷) 实锟斤拷
 * @license     Copyright (c) 2020-2032, 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷涌萍锟斤拷锟斤拷薰锟剿�
 ****************************************************************************************************
 * @attention
 *
 * 实锟斤拷平台:锟斤拷锟斤拷原锟斤拷 STM32F103锟斤拷锟斤拷锟斤拷
 * 锟斤拷锟斤拷锟斤拷频:www.yuanzige.com
 * 锟斤拷锟斤拷锟斤拷坛:www.openedv.com
 * 锟斤拷司锟斤拷址:www.alientek.com
 * 锟斤拷锟斤拷锟街�:openedv.taobao.com
 *
 ****************************************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../BSP/LED/led.h"
#include "../../BSP/KEY/key.h"
#include "../../BSP/LCD/lcd.h"
#include "../../BSP/KEYBOARD/keyboard.h"
#include "../../BSP/MUSIC/music.h"
#include "../../SYSTEM/delay/delay.h"
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
int Sync_code[8] = {1,1,1,0,1,0,1,0};
int LED0_code[8] = {0,0,0,0,1,0,1,0};
int LED1_code[8] = {0,0,1,0,1,1,0,1};
int LED2_code[8] = {0,0,0,1,1,0,0,1};
int FFH[8] = {1,1,1,1,1,1,1,1};
int Frame_count = 0;  //帧数记数，每个LED100帧
int LED_choose = 0; //LED选择，0-LED0，1-LED1，2-LED2
int LED_code_count = 0; //LED编码计数
int LED0_message[8] = {0,0,0,0,0,0,0,0}; //LED0消息，此处用来发送数据的位置，从0-255，0代表不发送
int LED1_message[8] = {0,0,0,0,0,0,0,0}; //LED1消息，用来发送数据，使用二进制码，全0代表空数据
int LED2_message[8] = {1,1,1,1,1,1,1,1}; //LED2消息，暂无用处

uint8_t LED0_message_bin = 0; //LED0消息二进制值
uint8_t LED1_message_bin = 0; //LED1消息二进制值
uint8_t LED2_message_bin = 0; //LED2消息二进制值


KeyBoard_t KeyBoardCtrl[ROW_NUM];	//存储行状态
uint8_t KeyBoardBuffer[KEY_BUFFER_SIZE];	//存储按键按下的值, 按键值的范围为1-16,129-144,0代表无值,1-16代表按下1-16,129-144代表抬起对应按键
uint8_t scanRow = 0;				//当前扫描的行
volatile uint8_t KeyBoardBuffW = 0;			//写索引
volatile uint8_t KeyBoardBuffR = 0;			//读索引

uint8_t music[MUSIC_LEN];	//发送的乐谱信息
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

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  delay_init(72);						   /* 锟斤拷始锟斤拷锟斤拷时锟斤拷锟斤拷 */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FSMC_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  //HAL_TIM_Base_Start(&htim1);             /* TIM1计时开始 */
  lcd_init();                            /* LCD初始化 */
  lcd_clear(WHITE);                      /* LCD清屏 */
  keyboard_init();                        /* 矩阵键盘初始化 */
  LED0(0);
  LED1(0);
  LED2(0);
  delay_ms(1000);
  HAL_TIM_Base_Start_IT(&htim1);          /* TIM1计时中断开始 */
  HAL_TIM_Base_Start_IT(&htim6);

  build_led_message(music);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    keyboard_scan();                      /* 键盘扫描 */
    for(int i = 0; i < 8; i++)
    {
      uint8_t led0_message = (LED0_message_bin & (1 << i));
      uint8_t led1_message = (LED1_message_bin & (1 << i));
      LED0_message[7 - i] = led0_message ? 1 : 0; //将LED0消息转换为二进制
      LED1_message[7 - i] = led1_message ? 1 : 0; //将LED1消息转换为二进制
    }
    char led1_message_str[30];
    sprintf(led1_message_str, "messsage: %X", LED1_message_bin);
    lcd_show_string(30, 90, 200, 16, 16, led1_message_str, RED);
    //printf("%d \r\n", LED1_message_bin);

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM1)
  {
    switch (LED_choose)
    {
    case 0: //LED0
      if(HAL_GPIO_ReadPin(LED2_GPIO_Port, LED2_Pin))
      {
    	  LED2(0);
      }
      if (Frame_count < 5)
      {
        if (LED_code_count < 8)
        {
          if (Sync_code[LED_code_count] == 1)
          {
            LED0(1);
          }
          else
          {
              LED0(0);
          }
          LED_code_count++;
        }
        else if(LED_code_count < 16)
        {
          if(LED0_code[LED_code_count - 8] == 1)
          {
              LED0(1);
          }
          else
          {
              LED0(0);
          }
          LED_code_count++;
        }
        else if(LED_code_count < 24)
        {
          if (FFH[LED_code_count - 16] == 1)
          {
        	  LED0(1);
          }
          else
          {
            LED0(0);
          }
          LED_code_count++;
        }
        else if(LED_code_count < 32)
        {
          if (LED0_message[LED_code_count - 24] == 1)
          {
        	  LED0(1);
          }
          else
          {
            LED0(0);
          }

          LED_code_count++;
          if(LED_code_count == 32)
          {
        	  LED_code_count = 0;
              Frame_count++;
              if(Frame_count == 5)
              {
            	  Frame_count = 0;
            	  LED_choose = 1;
              }
          }
        }
      }
      break;
    case 1: //LED1
      if(HAL_GPIO_ReadPin(LED0_GPIO_Port, LED0_Pin))
      {
    	  LED0(0);
      }
      if (Frame_count < 5)
      {
        if (LED_code_count < 8)
        {
          if (Sync_code[LED_code_count] == 1)
          {
              LED1(1);
          }
          else
          {
              LED1(0);
          }
          LED_code_count++;
        }
        else if(LED_code_count < 16)
        {
          if(LED1_code[LED_code_count - 8] == 1)
          {
              LED1(1);
          }
          else
          {
              LED1(0);
          }
          LED_code_count++;
        }
        else if(LED_code_count < 24)
        {
          if (FFH[LED_code_count - 16] == 1)
          {
              LED1(1);
          }
          else
          {
              LED1(0);
          }
          LED_code_count++;
        }
        else if(LED_code_count < 32)
        {
          if (LED1_message[LED_code_count - 24] == 1)
          {
              LED1(1);
          }
          else
          {
              LED1(0);
          }

          LED_code_count++;
          if(LED_code_count == 32)
          {
        	  LED_code_count = 0;
              Frame_count++;
              if(Frame_count == 5)
              {
            	  Frame_count = 0;
            	  LED_choose = 2;
              }
          }
        }
      }
      break;
    case 2: //LED2
      if(HAL_GPIO_ReadPin(LED1_GPIO_Port, LED1_Pin))
      {
    	  LED1(0);
      }
      if (Frame_count < 5)
      {
        if (LED_code_count < 8)
        {
          if (Sync_code[LED_code_count] == 1)
          {
              LED2(1);
          }
          else
          {
              LED2(0);
          }
          LED_code_count++;
        }
        else if(LED_code_count < 16)
        {
          if(LED2_code[LED_code_count - 8] == 1)
          {
              LED2(1);
          }
          else
          {
              LED2(0);
          }
          LED_code_count++;
        }
        else if(LED_code_count < 24)
        {
            if (FFH[LED_code_count - 16] == 1)
            {
                LED2(1);
            }
            else
            {
              LED2(0);
            }
            LED_code_count++;
        }
        else if(LED_code_count < 32)
        {
          if (LED2_message[LED_code_count - 24] == 1)
          {
            LED2(1);
          }
          else
          {
            LED2(0);
          }
        
          LED_code_count++;
          if(LED_code_count == 32)
          {
        	  LED_code_count = 0;
              Frame_count++;
              if(Frame_count == 5)
              {
            	  Frame_count = 0;
            	  LED_choose = 0;
              }
          }
        }
      }
      break;
    default:
      break;
    }
  }
  //按键消抖延时定时器, 1ms调用一次
  else if(htim->Instance == TIM6) {
	  KeyBoardCtrl[scanRow].dec++;
  }

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

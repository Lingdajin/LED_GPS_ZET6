/**
 ****************************************************************************************************
 * @file        led.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2024-01-01
 * @brief       LED 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20240101
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef LED_H_
#define LED_H_
#include "../../SYSTEM/sys/sys.h"

/******************************************************************************************/
/* LED端口定义 */
#define LED0(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET); \
                  }while(0)      /* LED0翻转 */

#define LED1(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET); \
                  }while(0)      /* LED1翻转 */

#define LED2(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); \
                  }while(0)      /* LED1翻转 */

/* LED取反定义 */
#define LED0_TOGGLE()   do{ HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin); }while(0)        /* 翻转LED0 */
#define LED1_TOGGLE()   do{ HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin); }while(0)        /* 翻转LED1 */

#endif /* LED_H_ */

/*
 * keyboard.h
 *
 *  Created on: May 27, 2025
 *      Author: 1
 *
 * 	GPIO Pins map to keyboard
 * 	PG1	 ->	 COL0
 * 	PF15 ->	 COL1
 * 	PF13 ->  COL2
 * 	PF11 ->  COL3
 *	PB1	 ->	 ROW0
 *	PC5	 ->	 ROW1
 *	PA7	 ->	 ROW2
 *	PC3	 ->	 ROW3
 *
 *	默认按键低电平触发, 即未按下时GPIO口为高电平
 *
 *	按键扫描参考: https://github.com/wujique/STM32F407_tech_doc/blob/master/source/base/30%E7%9F%A9%E9%98%B5%E6%8C%89%E9%94%AE%E6%89%AB%E6%8F%8F/%E8%AF%A6%E8%A7%A3%E7%9F%A9%E9%98%B5%E6%8C%89%E9%94%AE%E6%89%AB%E6%8F%8F.md
 */

#ifndef BSP_KEYBOARD_KEYBOARD_H_
#define BSP_KEYBOARD_KEYBOARD_H_

#include <stdint.h>
#include "main.h"

#define ROW_NUM 4
#define COL_NUM 4
#define KEY_BUFFER_SIZE 16
#define KEY_INIT_STATE_MASK 0x0F
#define DEC_TIME 10	//防抖计数 ms
#define KEY_CLOSE_MASK	0x80	//按键释放

typedef struct {
	uint8_t oldstate;
	uint8_t newstate;
	uint8_t dec;
}KeyBoard_t;

extern KeyBoard_t KeyBoardCtrl[ROW_NUM];
extern uint8_t KeyBoardBuffer[KEY_BUFFER_SIZE];
extern volatile uint8_t KeyBoardBuffW;
extern uint8_t scanRow;

void setRow(uint8_t row);
uint8_t readCols();
void keyboard_init();
void keyboard_scan();

#endif /* BSP_KEYBOARD_KEYBOARD_H_ */

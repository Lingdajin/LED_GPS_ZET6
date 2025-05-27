/*
 * keyboard.c
 *
 *  Created on: May 27, 2025
 *      Author: 1
 */

#include "keyboard.h"

/*
 * @brief 初始化矩阵键盘控制结构体
 * @note  需在系统初始化时调用一次，设置初始按键状态为高电平（未按下）
 */
void keyboard_init() {
	for(int i = 0; i < ROW_NUM; i++) {
		KeyBoardCtrl[i].dec = 0;
		KeyBoardCtrl[i].oldstate = KEY_INIT_STATE_MASK;
		KeyBoardCtrl[i].newstate = KEY_INIT_STATE_MASK;
	}
}

/*
 * @brief 设置某一行的输出为低电平，其他三行拉高
 * @param row 行号（0~3）
 * @note  每次扫描前必须先设置当前行为低电平，其余为高电平
 */
void setRow(uint8_t row) {
	//先全部拉高
	HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_SET);
	//再指定行拉低
	switch(row) {
	case 0: HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_RESET); break;
	case 1: HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET); break;
	case 2: HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET); break;
	case 3: HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET); break;
	}
}

/*
 * @brief 读取当前列的输入状态
 * @return 返回值为低四位bit0~bit3，每位对应一列，0表示按下，1表示松开
 * @note  列为输入模式并上拉电阻，按键按下时被选中行拉低列
 */
uint8_t readCols() {
	uint8_t state = 0;

	state |= (HAL_GPIO_ReadPin(COL0_GPIO_Port, COL0_Pin) == GPIO_PIN_RESET) ? (1 << 0) : 0;
	state |= (HAL_GPIO_ReadPin(COL1_GPIO_Port, COL1_Pin) == GPIO_PIN_RESET) ? (1 << 1) : 0;
	state |= (HAL_GPIO_ReadPin(COL2_GPIO_Port, COL2_Pin) == GPIO_PIN_RESET) ? (1 << 2) : 0;
	state |= (HAL_GPIO_ReadPin(COL3_GPIO_Port, COL3_Pin) == GPIO_PIN_RESET) ? (1 << 3) : 0;

	return state;
}

/*
 * @brief 矩阵键盘扫描函数，进行按键状态判断
 * @note  可在主循环或定时器中周期调用，配合TIM6管理消抖计数
 */
void keyboard_scan() {
	//static uint8_t scanRow = 0;
	uint8_t colStates = readCols();
	//如果检测到的列与上一次不同，则重置计时器
	if(colStates != KeyBoardCtrl[scanRow].newstate) {
		KeyBoardCtrl[scanRow].newstate = colStates;
		KeyBoardCtrl[scanRow].dec = 0;
	}

	if(colStates != KeyBoardCtrl[scanRow].oldstate) {
		//将消抖计数器设置在定时器中
		//KeyBoardCtrl[scanRow].dec++;
		//防抖检测
		if(KeyBoardCtrl[scanRow].dec >= DEC_TIME) {
			KeyBoardCtrl[scanRow].dec = 0;
			//通过异或操作找出哪一行发生变化
			//如 0b1111 ^ 0b1101 = 0b0010	发生变化的行置1
			uint8_t chgbit = KeyBoardCtrl[scanRow].oldstate ^ KeyBoardCtrl[scanRow].newstate;
			//遍历列, 找出变化的列
			for(uint8_t i = 0; i < COL_NUM; i++) {
				if(chgbit & (1 << i)) {
					//4x4矩阵键盘对应的值
					uint8_t keyVal = scanRow * 4 + i;
					if((KeyBoardCtrl[scanRow].newstate & (1 << i)) == 0) {
						//按下按键, 可以用串口或指示灯观察
					}
					else {
						//按键释放
						keyVal |= KEY_CLOSE_MASK;
					}

					KeyBoardBuffer[KeyBoardBuffW++] = keyVal + 1;
					if(KeyBoardBuffW >= KEY_BUFFER_SIZE) {
						KeyBoardBuffW = 0;
					}
				}
			}
			KeyBoardCtrl[scanRow].oldstate = KeyBoardCtrl[scanRow].newstate;
		}
	}
	//切换下一行
	scanRow = (scanRow + 1) % ROW_NUM;
	setRow(scanRow);
	HAL_Delay(5);	//延时使电平稳定
}

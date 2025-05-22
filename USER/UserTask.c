#include "UserTask.h"

/*
 * @brief: 处理adc采样的比特
 * @param: bit - 当前adc的采样值判决的bit
 * */
void handleBit(uint8_t bit) {
	static uint8_t syncShiftReg = 0;	//循环移位寄存器, 用于匹配同步码

	syncShiftReg = (syncShiftReg << 1) | (bit & 0x01);

	switch(decodeState) {
	case SYNC:		//匹配同步码
		if(syncShiftReg == SYNC_CODE) {
			decodeState = USER_CODE;
			user_bit_index = 0;
			user_bit = 0;
			syncShiftReg = 0;	//每帧数据都需要进行同步
		}
		break;

	case USER_CODE:		//获取用户码
		user_bit = (user_bit << 1) | bit;
		user_bit_index++;
		if(user_bit_index >= 8) {	//读取到完整的8bit用户码
			user_bit_index = 0;
			if(user_bit == LED1_CODE || user_bit == LED2_CODE || user_bit == LED3_CODE) {
				user_code = user_bit;
				decodeState = SAMPLING;
				sample_index = 0;
			}
			else {		//读取到错误的用户码
				decodeState = SYNC;
			}
		}
		break;

	case SAMPLING:
		if(sample_index < SAMPLE_COUNT) {	//连续采样8次
			sample_buffer[sample_index++] = bit_buffer;
		}
		else {
			sample_index = 0;
			decodeState = PROCESS_RES;
		}
		break;

	case PROCESS_RES:
		uint32_t sum = 0;
		for(uint8_t i = 0; i < SAMPLE_COUNT; i++) {
			sum += sample_buffer[i];
		}
		float avg = (float)sum / SAMPLE_COUNT;
		uint8_t idx = user_code - 1;
		//与前一帧采样的光强值做滑动平均
		if(idx < 3 && user_count[idx] < FRAME_COUNT && !user_ready[idx]) {
			float currentAvg = intensity[idx];
			uint8_t count = user_count[idx];

			intensity[idx] = (currentAvg * count + avg) / (count + 1);
			user_count[idx]++;

			if(user_count[idx] >= RX_FRAME_COUNT) {		//接收到80个帧以上
				user_ready[idx] = 1;
			}
		}
		decodeState = SYNC;
		if(user_ready[0] && user_ready[1] && user_ready[2]) {	//三个时隙接收完毕
			decodeState = DISPLAY;
		}
		break;
	case DISPLAY:
		display();
		decodeState = SYNC;
		break;
	default:
		decodeState = SYNC;
		break;
	}
}

/*
 * @brief: 将光强值映射为距离
 * @param: intensity - 光强度值(adc连续采样的均值)
 * */
float intensity_to_distance(uint16_t intensity) {
	float res = 0.0f;

	return res;
}

/*
 * @brief: 三边定位算法实现
 * @param: r1 r2 r3 - 通过光强度拟合出的目标点离三个LED的距离
 * */
void trilateration(float r1, float r2, float r3) {

}

/*
 * @brief: 接收结果可视化
 * */
void display() {
	lcd_clear(WHITE);
	lcd_show_string(30, 90, 50, 16, 16, "LED1: ", RED);
	lcd_show_string(30, 110, 50, 16, 16, "LED2: ", RED);
	lcd_show_string(30, 130, 50, 16, 16, "LED3: ", RED);
	char str1[30]; char str2[30]; char str3[30];
	sprintf(str1, "%.2f", intensity[0]);
	sprintf(str2, "%.2f", intensity[1]);
	sprintf(str3, "%.2f", intensity[2]);
	lcd_show_string(80, 90, 50, 16, 16, str1, RED);
	lcd_show_string(80, 110, 50, 16, 16, str2, RED);
	lcd_show_string(80, 130, 50, 16, 16, str3, RED);
}

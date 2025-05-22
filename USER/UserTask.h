#ifndef __USERTASK_H__
#define __USERTASK_H__

#include "arm_math.h"
#include "lcd.h"
#include <stdio.h>

#define SAMPLE_COUNT	8	//连续采样8次取平均作为光强度
#define FRAME_COUNT		100		//一个时隙的帧数量
#define RX_FRAME_COUNT	80	//一个时隙捕获80帧即可
#define LED_COUNT	3		//LED数量
#define THRESHOLD	2000	//判决门限
#define SYNC_CODE 0x55		//01010101
#define LED1_CODE 0x0A		//00001010
#define LED2_CODE 0x2D		//00101101
#define LED3_CODE 0x19		//00011001

typedef enum {
	SYNC,
	USER_CODE,
	SAMPLING,
	PROCESS_RES,
	DISPLAY
}DecodeState_t;

extern volatile uint16_t bit_buffer;
extern volatile DecodeState_t decodeState;

extern volatile uint8_t user_bit;
extern volatile uint8_t user_bit_index;
extern volatile uint8_t user_code;

extern volatile uint8_t sample_index;
extern volatile uint16_t sample_buffer[SAMPLE_COUNT];

extern float intensity[LED_COUNT];
extern volatile uint8_t user_count[LED_COUNT];
extern volatile uint8_t user_ready[LED_COUNT];

void handleBit(uint8_t bit);
float intensity_to_distance(uint16_t intensity);
void trilateration(float r1, float r2, float r3);
void display(void);

#endif

/*
 * music.c
 *
 *  Created on: Jun 3, 2025
 *      Author: 1
 */


#include "music.h"

const Note liang_zhi_lao_hu[MUSIC_LEN] = {
		//1 2 3 1
		{7, 4}, {8, 4}, {9, 4}, {7, 4},
		//1 2 3 1
		{7, 4}, {8, 4}, {9, 4}, {7, 4},
		//3 4 5-
		{9, 4}, {10, 4}, {11, 8},
		//3 4 5-
		{9, 4}, {10, 4}, {11, 8},
		//5._ 6__ 5._ 4__ 3 1
		{4, 2}, {12, 1}, {4, 2}, {10, 1}, {9, 4}, {7, 4},
		//5._ 6__ 5._ 4__ 3 1
		{4, 2}, {12, 1}, {4, 2}, {10, 1}, {9, 4}, {7, 4},
		//1 5 1-
		{7, 4}, {11, 4}, {7, 8},
		//1 5 1-
		{7, 4}, {11, 4}, {7, 8}
};

void build_led_message(uint16_t* des) {
	des[0] = MUSIC_START;
	des[MUSIC_LEN + 1] = MUSIC_END;

	for(int i = 1; i < MUSIC_LEN + 1 ; i++) {
		//音调、节拍各占一个字节的后4bit，再合并两个byte
		uint16_t msg = ((liang_zhi_lao_hu[i].tone & 0x0F) << 8) | (liang_zhi_lao_hu[i].beat & 0x0F);
		des[i] = msg;
	}
}

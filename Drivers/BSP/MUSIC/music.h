/*
 * music.h
 *
 *  Created on: Jun 3, 2025
 *      Author: 1
 */

#ifndef BSP_MUSIC_MUSIC_H_
#define BSP_MUSIC_MUSIC_H_

#include <stdint.h>

#define MUSIC_LEN 32

typedef struct {
	uint8_t tone;
	uint8_t beat;
}Note;

void build_led_message(uint8_t* des);

#endif /* BSP_MUSIC_MUSIC_H_ */

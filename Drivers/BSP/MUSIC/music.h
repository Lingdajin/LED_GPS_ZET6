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
#define MUSIC_START	0x0F0F	//涔愯氨寮�濮嬫爣蹇�
#define MUSIC_END	0x0000	//涔愯氨缁撴潫鏍囧織

typedef struct {
	uint8_t tone;
	uint8_t beat;
}Note;

void build_led_message(uint16_t* des);

#endif /* BSP_MUSIC_MUSIC_H_ */

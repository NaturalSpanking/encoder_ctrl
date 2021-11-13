/*
 * encoder_ctrl.h
 *
 *  Created on: 22 θών. 2020 γ.
 *      Author: Maksim Cherkasov
 */

#include "stdint.h"

#ifndef INC_ENCODER_CTRL_H_
#define INC_ENCODER_CTRL_H_

typedef enum {
	ENC_NOTHING, ENC_SHORT, ENC_DOUBLE, ENC_LONG, ENC_LEFT, ENC_LEFT_FAST, ENC_LEFT_PRS, ENC_RIGHT, ENC_RIGHT_FAST, ENC_RIGHT_PRS
} EncResult;

typedef struct{
	uint32_t (*GetSysTick)();
	uint16_t (*GetTimerCounter)();
	uint8_t (*GetBtnState)();
}EncInit_t;

void EncInit(EncInit_t* init_struct);
void EncTick();
EncResult CheckEncoder();

#endif /* INC_ENCODER_CTRL_H_ */

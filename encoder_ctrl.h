/*
 * encoder_ctrl.h
 *
 *  Created on: 22 θών. 2020 γ.
 *      Author: User
 */

#ifndef INC_ENCODER_CTRL_H_
#define INC_ENCODER_CTRL_H_

typedef enum {
	ENC_NOTHING, ENC_SHORT, ENC_DOUBLE, ENC_LONG, ENC_LEFT, ENC_LEFT_FAST, ENC_LEFT_PRS, ENC_RIGHT, ENC_RIGHT_FAST, ENC_RIGHT_PRS
} EncResult;



EncResult CheckEncoder();

#endif /* INC_ENCODER_CTRL_H_ */

/*
 * encoder_ctrl.h
 *
 *  Created on: 22 θών. 2020 γ.
 *      Author: User
 */

#ifndef INC_ENCODER_CTRL_H_
#define INC_ENCODER_CTRL_H_

typedef enum {
	ENC_NOTHING, ENC_LEFT, ENC_RIGHT, ENC_LONG, ENC_SHORT, ENC_DOUBLE
} EncResult;

EncResult CheckEncoder();

#endif /* INC_ENCODER_CTRL_H_ */

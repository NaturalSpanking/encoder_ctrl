/*
 * encoder_ctrl.c
 *
 *  Created on: 22 θών. 2020 γ.
 *      Author: User
 */

#include "encoder_ctrl.h"
#include "main.h"



EncResult CheckEncoder() {
	static int enc_counter;
	static int btn_pressed_counter = 0;
	static int btn_free_counter = 0;
	static int click_counter;

	EncResult result = ENC_NOTHING; //nothing
	if (!HAL_GPIO_ReadPin(ENC_BTN_GPIO_Port, ENC_BTN_Pin)) {
		btn_pressed_counter++;
		btn_free_counter = 0;
	} else {
		btn_pressed_counter = 0;
		btn_free_counter++;
	}
	if (btn_pressed_counter == 10) {
		//btn_short_press();
		click_counter++;
	}
	if ((btn_free_counter == 95) && (click_counter)) { //btn_short_press(click_counter);

		result = click_counter > 1 ? ENC_DOUBLE : ENC_SHORT;
		click_counter = 0;
	}

	if (btn_pressed_counter == 500) { // long click
		btn_pressed_counter = 501;
		click_counter = 0;
		result = ENC_LONG;
	}
	if ((!HAL_GPIO_ReadPin(ENC1_GPIO_Port, ENC1_Pin)) && (HAL_GPIO_ReadPin(ENC_BTN_GPIO_Port, ENC_BTN_Pin))) {
		enc_counter++;
	} else {
		enc_counter = 0;
	}
	if (enc_counter == 1) {
		if (HAL_GPIO_ReadPin(ENC2_GPIO_Port, ENC2_Pin)) {				//up
			result = ENC_RIGHT;
		} else {	  													//down
			result = ENC_LEFT;
		}
	}
	return result;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

}

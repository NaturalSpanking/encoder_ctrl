/*
 * encoder_ctrl.c
 *
 *  Created on: 22 θών. 2020 γ.
 *      Author: User
 */

#include "encoder_ctrl.h"
#include "main.h"
#include "tim.h"

EncResult queue_array[10];
int queue_counter = 0;

void queue_put(EncResult data) {
	if (queue_counter < 10) {
		queue_array[queue_counter] = data;
		queue_counter++;
	}
}

EncResult queue_get() {
	EncResult res = ENC_NOTHING;
	if (queue_counter) {
		res = queue_array[0];
		for (int i = 0; i < queue_counter; i++) {
			queue_array[i] = queue_array[i + 1];
		}
		queue_counter--;
	}
	return res;
}

EncResult CheckEncoder() { // every 5 ms tick
	static int btn_pressed_counter = 0;
	static int btn_free_counter = 0;
	static int click_counter;
	static uint32_t speed_tmr;
	static uint32_t speed_counter;
	static uint16_t last_counter;
	EncResult result = ENC_NOTHING; //nothing
/******************************* BUTTON ****************************/
	if (!HAL_GPIO_ReadPin(ENC_BTN_GPIO_Port, ENC_BTN_Pin)) {
		btn_pressed_counter++;
		btn_free_counter = 0;
	} else {
		btn_pressed_counter = 0;
		btn_free_counter++;
	}
	if (btn_pressed_counter == 2) { //10ms
		click_counter++;
	}
	if ((btn_free_counter == 25) && (click_counter)) { //95ms
		result = click_counter > 1 ? ENC_DOUBLE : ENC_SHORT;
		click_counter = 0;
	}
	if (btn_pressed_counter == 100) { // 500ms long click
		btn_pressed_counter = 101;
		click_counter = 0;
		result = ENC_LONG;
	}
/*************************** ENCODER ******************************/
	speed_tmr++;
	uint16_t c_tmp = __HAL_TIM_GET_COUNTER(&htim1);
	if(abs(c_tmp-last_counter)>=2){
		if(c_tmp>last_counter){
			result = btn_pressed_counter ? ENC_RIGHT_PRS:(speed_tmr-speed_counter<=7 ? ENC_RIGHT_FAST:ENC_RIGHT);
		}else{
			result = btn_pressed_counter ? ENC_LEFT_PRS:(speed_tmr-speed_counter<=7 ? ENC_LEFT_FAST:ENC_LEFT);
		}
		btn_pressed_counter=101;
		click_counter=0;
		last_counter=c_tmp;
		speed_counter=speed_tmr;
	}
	return result;
}

//void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) {
//	HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
//	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) {
//		queue_put(ENC_RIGHT);
//
//	}
//	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4) {
//		queue_put(ENC_LEFT);
//
//	}
//	__HAL_TIM_SET_COUNTER(htim, 0);
//}

//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
//	int16_t tmp = __HAL_TIM_GET_COUNTER(htim);
//	HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
//	if (tmp == 2) {
//		enc_queue_put(ENC_RIGHT);
//		__HAL_TIM_SET_COUNTER(htim, 0);
//	} else if (tmp == -2) {
//		enc_queue_put(ENC_LEFT);
//		__HAL_TIM_SET_COUNTER(htim, 0);
//	} else if (tmp > 2
//			|| tmp < -2) {
//		__HAL_TIM_SET_COUNTER(htim, 0);
//	}

//}

//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//
//}

/*
 * encoder_ctrl.c
 *
 *  Created on: 22 θών. 2020 γ.
 *      Author: Maksim Cherkasov
 */

#include "encoder_ctrl.h"

EncResult queue_array[10];
EncInit_t* enc_cfg;
uint32_t enc_timer;

int queue_counter = 0;

void queue_put(EncResult data) {
	if (queue_counter < 10) {
		queue_array[queue_counter] = data;
		queue_counter++;
	}
}

EncResult CheckEncoder() {
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

void EncInit(EncInit_t* init_struct) {
	enc_cfg = init_struct;
	enc_timer = 0;
}

void EncTick() { // every 5 ms tick
	static int btn_pressed_counter = 0;
	static int btn_free_counter = 0;
	static int click_counter;
	static uint32_t speed_tmr;
	static uint32_t speed_counter;
	static uint16_t last_counter;
	EncResult result = ENC_NOTHING; //nothing

	uint32_t tmp = enc_cfg->GetSysTick();
	if (tmp - enc_timer >= 5) {
		enc_timer = tmp;
		/******************************* BUTTON ****************************/
		if (!enc_cfg->GetBtnState()) {
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
		uint16_t c_tmp = enc_cfg->GetTimerCounter();
		if (abs(c_tmp - last_counter) >= 2) {
			if (c_tmp > last_counter) {
				result =
						btn_pressed_counter ?
								ENC_RIGHT_PRS :
								(speed_tmr - speed_counter <= 7 ?
										ENC_RIGHT_FAST : ENC_RIGHT);
			} else {
				result =
						btn_pressed_counter ?
								ENC_LEFT_PRS :
								(speed_tmr - speed_counter <= 7 ?
										ENC_LEFT_FAST : ENC_LEFT);
			}
			btn_pressed_counter = 101;
			click_counter = 0;
			last_counter = c_tmp;
			speed_counter = speed_tmr;
		}
		queue_put(result);
	}
}


//void Enc_init(){
//	encoder_init_struct.GetSysTick = HAL_GetTick;
//	encoder_init_struct.GetBtnState = enc_read_btn;
//	encoder_init_struct.GetTimerCounter = enc_get_counter;
//	EncInit(&encoder_init_struct);
//}
//
//uint16_t enc_get_counter(){
//	return  __HAL_TIM_GET_COUNTER(&htim1);
//}
//
//uint8_t enc_read_btn(){
//	return HAL_GPIO_ReadPin(ENC_BTN_GPIO_Port,ENC_BTN_Pin);
//}

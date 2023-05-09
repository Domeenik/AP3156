/*
 * ap3156.c
 *
 *  Created on: 26.04.2023
 *      Author: Dominik Reifer
 */

#include "ap3156.h"

// SEND A COMMAND
void send_cmd(uint8_t first, uint8_t sec){
	// FIRST SEQUENCE
	for (uint8_t i = 0; i < first; i++) {
		set_gpio(AP_PORT, AP_PIN, 0);
		set_gpio(AP_PORT, AP_PIN, 1);
	}
	delay_us(T_SEP);

	// SECOND SEQUENCE
	for (uint8_t i = 0; i < sec; i++) {
		set_gpio(AP_PORT, AP_PIN, 0);
		set_gpio(AP_PORT, AP_PIN, 1);
	}
	delay_us(T_SEP);
}

// SOFT RESET THE AP3156
void soft_reset(){
	for (uint8_t i = 0; i < 33; i++) {
		set_gpio(AP_PORT, AP_PIN, 0);
		set_gpio(AP_PORT, AP_PIN, 1);
	}
	delay_us(T_SEP);
}

// INITIALIZE THE AP3156
void ap3156_init() {
	// set AP3156 HIGH for active mode
	set_gpio(AP_PORT, AP_PIN, 0);
	delay_us(1000);
	set_gpio(AP_PORT, AP_PIN, 1);

	// RESET
	soft_reset();
	delay_us(T_SEP);

	// SET HIGHER FREQ
	send_cmd(8, 3);
	delay_us(T_SEP);
}

// SET THE BRIGHTNESS OF A SINGLE LED
void set_led(uint8_t id, uint8_t value) {
	static uint8_t led_values[6] = {32, 32, 32, 32, 32, 32};

	led_values[id] = (value>MAX_BRIGHT)?(4+MAX_BRIGHT):(32-value);

	for (uint8_t i = 0; i < 6; i++){
		switch(i) {
		case LED_0:
			send_cmd(16, led_values[i]);
			break;
		case LED_1:
			send_cmd(17, led_values[i]);
			break;
		case LED_2:
			send_cmd(18, led_values[i]);
			break;
		case LED_3:
			send_cmd(19, led_values[i]);
			break;
		case LED_4:
			send_cmd(20, led_values[i]);
			break;
		case LED_5:
			send_cmd(21, led_values[i]);
			break;
		}
	}
}

// SET ALL LEDS AT ONCE
void set_all_leds(uint8_t value) {
	for (uint8_t i = 0; i < 6; i++) {
		set_led(i, value);
	}
}


// RUNNING LIGHTS AS EXAMPLE ANIMATION
void ex_animation(){
	for (uint8_t i = 0; i < 6; i++) {
		for (uint8_t j = 0; j < (MAX_BRIGHT+1); j++) {
			set_led(i, j);
		}
	}
	for (uint8_t i = 0; i < 6; i++) {
		for (uint8_t j = 0; j < (MAX_BRIGHT+1); j++) {
			set_led(i, MAX_BRIGHT-j);
		}
	}
	for (uint8_t i = 0; i < 6; i++) {
		for (uint8_t j = 0; j < (MAX_BRIGHT+1); j++) {
			set_led(6-i, j);
		}
	}
	for (uint8_t i = 0; i < 6; i++) {
		for (uint8_t j = 0; j < (MAX_BRIGHT+1); j++) {
			set_led(6-i, MAX_BRIGHT-j);
		}
	}
}

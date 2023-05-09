/*
 * ap3156.h
 *
 *  Created on: 26.04.2023
 *      Author: Dominik Reifer
 */

#ifndef INC_AP3156_H_
#define INC_AP3156_H_

#include "stdint.h"

/* external functions */
// THIS FUNCTIONS MUST BE PROVIDED BY THE APPLICATION
// FUNCTION FOR SETTING THE STATE OF A PIN
// pin: pin number
// state: 0 - LOW, 1 - HIGH
extern void set_gpio(uint8_t pin, uint8_t state)

// FUNCTION FOR LETTING THE STM SLEEP IN MICROSECONDS
// us: amount of microseconds to sleep
extern void delay_us(uint16_t us)


/* define block */
// PORT and PIN FOR COMMUNICATING WITH THE AP3156
#define AP_PORT GPIOB
#define AP_PIN 11

// CORRECT LED ORDER HERE IF NECESSARY
#define LED_0 0
#define LED_1 1
#define LED_2 2
#define LED_3 3
#define LED_4 4
#define LED_5 5

// SEPERATION TIME BETWEEN COMMANDS
#define T_SEP 200

// MAXIMUM BRIGHTNESS - SHOULD NOT EXCEED 29
#define MAX_BRIGHT 12


/* function block */
void send_cmd(uint8_t first, uint8_t sec);
void soft_reset();
void ap3156_init();
void set_led(uint8_t id, uint8_t value);
void set_all_leds(uint8_t value);

void ex_animation();

#endif /* INC_AP3156_H_ */

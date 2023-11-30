/*
 * tasks.c
 *
 *  Created on: Nov 27, 2023
 *      Author: DELL
 */


#include "tasks.h"

void testRedLed() {
	HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);
}

void testGreenLed() {
	HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
}

void testYellowLed() {
	HAL_GPIO_TogglePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin);
}

void testPurpleLed() {
	HAL_GPIO_TogglePin(PURPLE_LED_GPIO_Port, PURPLE_LED_Pin);
}

void testBlueLed() {
	HAL_GPIO_TogglePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin);
}

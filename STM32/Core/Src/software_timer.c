/*
 * software_timer.c
 *
 *  Created on: Nov 26, 2023
 *      Author: DELL
 */

#include "software_timer.h"



int timer_flag = 0;

void setTimer()
{
	timer_flag = 1 - timer_flag;
}

/*
 * scheduler.c
 *
 *  Created on: Nov 26, 2023
 *      Author: DELL
 */

#include "scheduler.h"

typedef struct {
	void (* pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
}sTask;

sTask SCH_tasks_G[SCH_MAX_TASK];

int numTask = 0;

void SCH_Init(void) {
	unsigned char i;
	for (i = 0; i < SCH_MAX_TASK; i++) {
		SCH_Delete_Task(i);
	}
}

void SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
	if (numTask < SCH_MAX_TASK) {
		unsigned char index;
		for (index = 0; index < SCH_MAX_TASK; index++) {
			if (SCH_tasks_G[index].pTask != 0) continue;

			SCH_tasks_G[index].pTask = pFunction;
			SCH_tasks_G[index].Delay = DELAY/TIME_CYCLE;
			SCH_tasks_G[index].Period = PERIOD/TIME_CYCLE;
			SCH_tasks_G[index].RunMe = 0;
			numTask++;
			break;
		}
	}
}

void SCH_Update(void) {
	unsigned char index;
	for (index = 0; index < SCH_MAX_TASK; index++) {
		if (SCH_tasks_G[index].pTask) {
			if (SCH_tasks_G[index].Delay == 0) {
				SCH_tasks_G[index].RunMe += 1;
				if (SCH_tasks_G[index].Period) {
					SCH_tasks_G[index].Delay = SCH_tasks_G[index].Period;
				}
			}
			else {
				SCH_tasks_G[index].Delay -= 1;
			}
		}
	}
}

void SCH_Dispatch_Tasks(void) {
	unsigned char index;
	for (index = 0; index < SCH_MAX_TASK; index++) {
		if (SCH_tasks_G[index].RunMe > 0) {
			(*SCH_tasks_G[index].pTask)();
			SCH_tasks_G[index].RunMe -= 1;
			if (SCH_tasks_G[index].Period == 0) SCH_Delete_Task(index);
		}
	}
}

void SCH_Delete_Task(uint32_t taskID) {
	if (taskID >= SCH_MAX_TASK || SCH_tasks_G[taskID].pTask == 0) return;
	SCH_tasks_G[taskID].pTask = 0x0000;
	SCH_tasks_G[taskID].Delay = 0;
	SCH_tasks_G[taskID].Period = 0;
	SCH_tasks_G[taskID].RunMe = 0;
}

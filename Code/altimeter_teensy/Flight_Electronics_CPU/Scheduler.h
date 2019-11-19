/*
 * Scheduler.h
 *
 *  Created on: Jan 26, 2019
 *      Author: erics
 */

#ifndef SOFTSCHEDULER_H_
#define SOFTSCHEDULER_H_

#include <Arduino.h>
#include <queue>
#include <IntervalTimer.h>
#include <stdint.h>

#include "Config.h"


typedef void (*ISR)();
enum TASK_PRIORITY
{
	HIGHEST_PRIORITY = 0,
	HIGHER_PRIORITY = 1,
	HIGH_PRIORITY = 2,
	LOW_PRIORITY
};

struct Task
{
	ISR fun_ptr;
	uint32_t lastExecuteTime; // in microseconds
	uint32_t interval; // in microseconds
	String name;
	TASK_PRIORITY priority;
};

namespace Scheduler
{
	namespace
	{
		std::queue<Task> taskList_LOW_PRIORITY;
		std::queue<Task> taskList_HIGH_PRIORITY;
		volatile uint8_t highPriorty_fast_taskListSize[3] = {0};
		volatile ISR highPriorty_fast_ISRs [3][10];
		volatile int32_t highPriorty_fast_intervals [3][10];
		volatile int32_t highPriorty_fast_lastExec [3][10];
		volatile uint8_t highPriorty_fast_index [3] = {0};

		double averageJitter = 0;
		IntervalTimer hwTimer[3];
		bool hwTimerRunning[3] = {false};
	}
	void addTask(TASK_PRIORITY taskPriortiy, ISR fun_ptr, uint32_t interval);
	void addTask(TASK_PRIORITY taskPriortiy, ISR fun_ptr, uint32_t interval, uint32_t delay, String name);
	void init();
	void tickSoft();
	void tickHard(uint8_t listnum);
	void tickHard_255();
	void tickHard_254();
	void tickHard_253();
	void startHwTimer();
	double getAverageJitter();
	int getLowPriorityQueueSize();
};

#endif /* SOFTSCHEDULER_H_ */

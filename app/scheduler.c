/*
 * scheduler.c
 *
 *  Created on: Jan 30, 2026
 *      Author: manhhai
 */

#include "scheduler.h"

#define MAX_TASKS   5

task_t tasks[MAX_TASKS];
static uint8_t num_tasks = 0;

int sched_add_task(callback_func func, uint32_t hz)
{
	if (num_tasks >= MAX_TASKS)
		return -1;

	tasks[num_tasks].id = num_tasks;
    tasks[num_tasks].func = func;
    tasks[num_tasks].hz = hz;
    num_tasks++;

    return 0;
}

void sched_init ()
 {
    for (uint8_t id = 0; id < num_tasks; id++) {
        tasks[id].prev_tick_us = 0;
    }
}

void sched_run(uint32_t tick_us) {
    for (uint8_t id = 0; id < num_tasks; id++) {
        if (tasks[id].hz == FAST_TASK) {
            tasks[id].func();
            tasks[id].prev_tick_us = tick_us;
        }
        else {
            uint32_t time_passed = tick_us - tasks[id].prev_tick_us;
            if (time_passed > HZ_TO_TICK_US(tasks[id].hz)) {
                tasks[id].func();
                tasks[id].prev_tick_us = tick_us;
            }
        }
    }
}

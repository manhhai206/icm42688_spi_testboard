/*
 * schedule.h
 *
 *  Created on: Jan 30, 2026
 *      Author: manhhai
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

#define HZ_TO_TICK_US(hz) (1000000UL/hz)
#define HZ_TO_TICK_MS(hz) (1000/hz)
#define FAST_TASK 0

typedef uint32_t task_id;
typedef void (*callback_func)(void);

typedef struct {
    uint32_t hz;
    uint32_t prev_tick_us;
    task_id id;
    callback_func func;
} task_t;

int sched_add_task(callback_func func, uint32_t hz);
void sched_init();
void sched_run(uint32_t tick_us);

#endif /* INC_SCHEDULER_H_ */

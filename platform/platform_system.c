/*
 * platform_system.c
 *
 *  Created on: Jan 30, 2026
 *      Author: manhhai
 */


#include "platform.h"

#define TIMER_TICK	((TIM_HandleTypeDef *)&htim1)

extern TIM_HandleTypeDef htim1;

void platform_system_delay_ms(uint32_t ms) {
	HAL_Delay(ms);
}

void platform_system_init() {
    HAL_TIM_Base_Start(TIMER_TICK);
}

uint32_t platform_system_millis() {
    return __HAL_TIM_GET_COUNTER(TIMER_TICK) / 1000;
}

uint32_t platform_system_micros() {
    return __HAL_TIM_GET_COUNTER(TIMER_TICK);
}

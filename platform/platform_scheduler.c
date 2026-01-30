/*
 * platform_scheduler.c
 *
 *  Created on: Jan 30, 2026
 *      Author: manhhai
 */

#include "platform.h"

void platform_scheduler_1hz(void) {
	publish(SCHEDULER_1HZ, NULL, 0);
}

void platform_scheduler_5hz(void) {
	publish(SCHEDULER_5HZ, NULL, 0);
}

void platform_scheduler_10hz(void) {
	publish(SCHEDULER_10HZ, NULL, 0);
}

void platform_scheduler_25hz(void) {
	publish(SCHEDULER_25HZ, NULL, 0);
}

void platform_scheduler_50hz(void) {
	publish(SCHEDULER_50HZ, NULL, 0);
}

void platform_scheduler_100hz(void) {
	publish(SCHEDULER_100HZ, NULL, 0);
}

void platform_scheduler_250hz(void) {
	publish(SCHEDULER_250HZ, NULL, 0);
}

void platform_scheduler_500hz(void) {
	publish(SCHEDULER_500HZ, NULL, 0);
}

void platform_scheduler_1khz(void) {
	publish(SCHEDULER_1KHZ, NULL, 0);
}

void platform_scheduler_2khz(void) {
	publish(SCHEDULER_2KHZ, NULL, 0);
}

void platform_scheduler_4khz(void) {
	publish(SCHEDULER_4KHZ, NULL, 0);
}

void platform_scheduler_8khz(void) {
	publish(SCHEDULER_8KHZ, NULL, 0);
}


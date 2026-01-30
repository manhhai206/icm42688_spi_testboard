/*
 * pubsub.h
 *
 *  Created on: Jan 30, 2026
 *      Author: manhhai
 */

#ifndef INC_PUBSUB_H_
#define INC_PUBSUB_H_

#include <stddef.h>
#include <stdint.h>

typedef enum {
	LOOP = 0,
	SCHEDULER_1HZ,
	SCHEDULER_5HZ,
	SCHEDULER_10HZ,
	SCHEDULER_25HZ,
	SCHEDULER_50HZ,
	SCHEDULER_100HZ,
	SCHEDULER_250HZ,
	SCHEDULER_500HZ,
	SCHEDULER_1KHZ,
	SCHEDULER_2KHZ,
	SCHEDULER_4KHZ,
	SCHEDULER_8KHZ,
	TOPIC_NULL
} topic_t;

typedef void (*subscriber_callback_t)(uint8_t *data, size_t size);

void publish(topic_t topic, uint8_t *data, size_t size);
void subscribe(topic_t topic, subscriber_callback_t callback);


#endif /* INC_PUBSUB_H_ */

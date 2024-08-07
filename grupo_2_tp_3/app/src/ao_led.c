/*
 * Copyright (c) 2023 Sebastian Bedin <sebabedin@gmail.com>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @author : Sebastian Bedin <sebabedin@gmail.com>
 */

/********************** inclusions *******************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "cmsis_os.h"
#include "board.h"
#include "logger.h"
#include "dwt.h"
#include "ao_led.h"

/********************** macros and definitions *******************************/

#define TASK_PERIOD_MS_           (1000u)

#define LED_QUEUE_LEN				  (10u)
#define LED_QUEUE_SIZE_EVEN			  (sizeof (ao_led_even_t))
#define LED_TASK_PRIORITY			  (1u)
#define LED_MS_DELAY				  (2500u)

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data definition *****************************/


ao_t ao_led = (ao_t) {

	.event_queue_h = NULL,
	.event_queue_len = LED_QUEUE_LEN,
	.event_size = LED_QUEUE_SIZE_EVEN,
	.queue_name = "AO LED queue",

		// Thread
	.task_name = "AO LED task",
	.thread_h = NULL,
	.priority = LED_TASK_PRIORITY,
	.stack_size = configMINIMAL_STACK_SIZE,

		/* Process */
	.handler = NULL,

	.run = false,
	.memory_friendly = true,

};

/********************** internal functions definition ************************/

/********************** external functions definition ************************/

void task_led_handler (void* msg) {

	TickType_t delay = pdMS_TO_TICKS(LED_MS_DELAY);

	ao_led_even_t* event = (ao_led_even_t*) msg;

	LOGGER_INFO("[task_led_handler]: proccess %s", event->led_name);

	HAL_GPIO_WritePin(event->led_port, event->led_pin, event->led_state);

	vTaskDelay(delay);

	HAL_GPIO_WritePin(event->led_port, event->led_pin, !event->led_state);

}

/********************** end of file ******************************************/

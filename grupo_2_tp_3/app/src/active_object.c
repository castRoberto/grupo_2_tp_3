/*
 * Copyright (c) 2024 Grupo 2.
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
 * @author : Grupo 2
 */

/********************** inclusions *******************************************/

#include "active_object.h"

/********************** macros and definitions *******************************/

#define C_EMPTY_QUEUE				  (0u)

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data definition *****************************/

/********************** internal functions definition ************************/

static void _task (void *parameters) {

	ao_t* ao = (ao_t*) parameters;

	uint8_t msg[ao->event_size];

	while (1) {

		if (pdPASS == xQueueReceive(ao->event_queue_h, msg, portMAX_DELAY)) {

			LOGGER_INFO("[_task]: %s", ao->task_name);
			ao->handler ((void*)msg);

			if (true == ao->memory_friendly) {

				ao_destroy (ao);

			}

		}


	}

}

/********************** external functions definition ************************/

op_result_e ao_init (ao_t* ao, handlerFunc_t handler) {

	op_result_e result = OP_ERR;

	if (NULL != ao  && NULL != handler) {

		ao->event_queue_h = xQueueCreate (ao->event_queue_len, ao->event_size);
		configASSERT(NULL != ao->event_queue_h);

		vQueueAddToRegistry(ao->event_queue_h, ao->queue_name);


		BaseType_t status =
			xTaskCreate (_task,
						 ao->task_name,
						 ao->stack_size,
						 (void*)ao,
						 ao->priority,
						 &ao->thread_h);

		configASSERT(pdPASS == status);

		ao->handler = handler;

		ao->run = true;

		result = (NULL != ao->event_queue_h && pdPASS == status);

	}

	return result;

}


void ao_destroy (ao_t* ao) {

	if (NULL != ao) {

		if (C_EMPTY_QUEUE == uxQueueMessagesWaiting (ao->event_queue_h)) {

			LOGGER_INFO("[ao_ui_destroy]: destroy %s", ao->task_name);

			ao->thread_h = NULL;

			ao->handler = NULL;

			ao->run = false;

			vQueueDelete (ao->event_queue_h);

			ao->event_queue_h = NULL;

			vTaskDelete (NULL);

		}


	}

}


op_result_e ao_send_msg (ao_t* ao, void* msg) {

	op_result_e result = OP_ERR;

	if (NULL != ao  && NULL != msg && NULL != ao->event_queue_h) {

		result = (pdPASS == xQueueSend (ao->event_queue_h, msg, 0));

	}

	return result;

}

/********************** end of file ******************************************/

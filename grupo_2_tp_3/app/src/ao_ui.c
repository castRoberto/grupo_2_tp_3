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


#include "ao_ui.h"
#include "active_object.h"

/********************** macros and definitions *******************************/

#define UI_QUEUE_LEN				  (15u)
#define UI_QUEUE_SIZE_EVEN			  (sizeof (ao_ui_even_t))
#define UI_TASK_PRIORITY			  (1u)

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal functions definition ************************/

/********************** internal data definition *****************************/

/********************** external data definition *****************************/

ao_t ao_ui = (ao_t) {

	.event_queue_h = NULL,
	.event_queue_len = UI_QUEUE_LEN,
	.event_size = UI_QUEUE_SIZE_EVEN,
	.queue_name = "AO UI queue",

		// Thread
	.task_name = "AO UI task",
	.thread_h = NULL,
	.priority = UI_TASK_PRIORITY,
	.stack_size = configMINIMAL_STACK_SIZE,

		/* Process */
	.handler = NULL,

	.run = false,
	.memory_friendly = false,

};


/********************** external functions definition ************************/

void task_ui_handler (void* msg) {

	ao_ui_even_t* ao_ui_event = (ao_ui_even_t*) msg;

	op_result_e result = ao_send_msg (ao_ui_event->ao, ao_ui_event->msg);

	if (OP_OK != result) {

		if (false == ao_ui_event->ao->run) {

			LOGGER_INFO("[task_ui_handler]: AO init");

			result = ao_init (ao_ui_event->ao, ao_ui_event->handler);

			if (OP_ERR == result) {

				LOGGER_INFO("[task_ui_handler]: Cannot create more resources");

			}

			result = ao_send_msg (ao_ui_event->ao, ao_ui_event->msg);

			if (OP_ERR == result) {

				LOGGER_INFO("[task_ui_handler]: Null message or missized queue");

			}

		} else {

			LOGGER_INFO("[task_ui_handler]: AO QUEUE saturated");

		}

	}

}



/********************** end of file ******************************************/

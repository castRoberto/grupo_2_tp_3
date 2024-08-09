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

#include "main.h"
#include "cmsis_os.h"
#include "logger.h"
#include "dwt.h"
#include "board.h"

#include "task_button.h"
#include "task_led.h"
#include "ao_led.h"
#include "ao_ui.h"
#include "priority_queue.h"

/********************** macros and definitions *******************************/


/********************** internal data declaration ****************************/
static uint8_t memory_pq[MEMORY_SIZE(10)];
/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data declaration *****************************/

TaskHandle_t task_button_h;
ao_ui_even_t ao_ui_event;

/********************** external functions definition ************************/
void app_init(void) {

	void* val;
	int ans = 0;

	int a = 8;
	int b = 12;
	int c = 2;
	int d = 5;
	int e = 45;

	priority_queue_t* pq = pq_create(memory_pq, 10);

	pq_insert(pq, (void*) &a, 2);	print_priority_queue_as_tree (pq);
	pq_insert(pq, (void*) &b, 2);	print_priority_queue_as_tree (pq);
	pq_insert(pq, (void*) &c, 2);	print_priority_queue_as_tree (pq);
	pq_insert(pq, (void*) &d, 2);	print_priority_queue_as_tree (pq);
	pq_insert(pq, (void*) &e, 2);	print_priority_queue_as_tree (pq);

	val = (int*) pq_extract_max(pq);
	ans = *(int*)val;
	val = (int*) pq_extract_max(pq);
	ans = *(int*)val;
	val = (int*) pq_extract_max(pq);
	ans = *(int*)val;
	val = (int*) pq_extract_max(pq);
	ans = *(int*)val;
	val = (int*) pq_extract_max(pq);
	ans = *(int*)val;

	op_result_e result = ao_init (&ao_ui, task_ui_handler);

	if (OP_ERR == result) {

		LOGGER_INFO("[app_init]: Cannot create ui");

	}

	configASSERT(OP_OK == result);

	ao_ui_event.ao = &ao_led;
	ao_ui_event.handler = task_led_handler;

	BaseType_t status;

	status = xTaskCreate (task_button,
		  	  	  	  	  "task_button",
						  configMINIMAL_STACK_SIZE,
						  NULL,
						  tskIDLE_PRIORITY + (1u),
						  &task_button_h);

	configASSERT(pdPASS == status);



	LOGGER_INFO("app init");

	cycle_counter_init();
}

/********************** end of file ******************************************/

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

#ifndef __ACTIVE_OBJECT_H__
#define __ACTIVE_OBJECT_H__

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "cmsis_os.h"
#include "board.h"
#include "logger.h"
#include "dwt.h"

/********************** macros ***********************************************/

/********************** typedef **********************************************/

typedef enum {

	OP_ERR = 0,
	OP_OK = 1,

} op_result_e;


/* Function pointer handler */
typedef void (*handlerFunc_t)(void* event);

/* Active Object definition */
typedef struct {

	/* OS */
	bool run;
	bool memory_friendly;

	// Queue
	QueueHandle_t event_queue_h;
	uint16_t event_queue_len;
	size_t event_size;
	char queue_name[configMAX_TASK_NAME_LEN];

	// Thread
	char task_name[configMAX_TASK_NAME_LEN];
	TaskHandle_t thread_h;
	UBaseType_t priority;
	uint16_t stack_size;

	/* Process */
	handlerFunc_t handler;

} ao_t;

/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/

op_result_e ao_init (ao_t* ao, handlerFunc_t handler);

void ao_destroy (ao_t* ao);

op_result_e ao_send_msg (ao_t* ao, void* msg);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* __ACTIVE_OBJECT_H__ */
/********************** end of file ******************************************/


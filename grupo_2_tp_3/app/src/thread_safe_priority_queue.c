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

#include "thread_safe_priority_queue.h"

/********************** macros and definitions *******************************/


/********************** internal data declaration ****************************/


/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/


/********************** external data definition *****************************/


/********************** internal functions definition ************************/


/********************** external functions definition ************************/

thread_safe_priority_queue_t* pq_create_safe (void* memory_pool, size_t capacity) {

	thread_safe_priority_queue_t* safe_pq = NULL;

	if (memory_pool != NULL && capacity != 0) {

		safe_pq = (thread_safe_priority_queue_t*)memory_pool;

		void* memory_pool_pq = (void*)((char*)memory_pool + sizeof(thread_safe_priority_queue_t));

		// Initialize the safe queue
		safe_pq->mutex = xSemaphoreCreateMutex ();
		configASSERT(NULL != safe_pq->mutex);

		safe_pq->pq = pq_create(memory_pool_pq, capacity);

	}

	return safe_pq;

}

void pq_destroy_safe (thread_safe_priority_queue_t* safe_pq) {

	if (NULL != safe_pq) {

		vSemaphoreDelete (safe_pq->mutex);

		safe_pq->mutex = NULL;

	}

}


bool pq_insert_safe (thread_safe_priority_queue_t* safe_pq, void* data, uint16_t priority) {

	bool success = false;

	if (NULL != safe_pq) {

		if (pdTRUE == xSemaphoreTake (safe_pq->mutex, portMAX_DELAY)) {

			success = pq_insert (safe_pq->pq, data, priority);

			xSemaphoreGive (safe_pq->mutex);

		}

	}


	return success;

}


void* pq_extract_max_safe (thread_safe_priority_queue_t* safe_pq) {

	void* data = NULL;

	if (NULL != safe_pq) {

		if (pdTRUE == xSemaphoreTake (safe_pq->mutex, portMAX_DELAY)) {

			data = pq_extract_max (safe_pq->pq);

			xSemaphoreGive(safe_pq->mutex);

		}

	}

	return data;

}

bool pq_is_empty_safe (thread_safe_priority_queue_t* safe_pq) {

	return pq_is_empty (safe_pq->pq);

}

size_t pq_size_safe (thread_safe_priority_queue_t* safe_pq) {

	return pq_size(safe_pq->pq);

}


void pq_print_priority_queue_safe (thread_safe_priority_queue_t* safe_pq) {

	if (NULL != safe_pq) {

		portENTER_CRITICAL();

		pq_print_priority_queue(safe_pq->pq);

		portEXIT_CRITICAL();

	}

}

/********************** end of file ******************************************/

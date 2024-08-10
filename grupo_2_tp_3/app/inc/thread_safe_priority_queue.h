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

#ifndef __THREAD_SAFE_PRIORITY_QUEUE_H__
#define __THREAD_SAFE_PRIORITY_QUEUE_H__

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

#include "main.h"
#include "cmsis_os.h"
#include "priority_queue.h"

/********************** typedef **********************************************/

// Structure for safe priority queue
typedef struct {

	priority_queue_t* pq;
	SemaphoreHandle_t mutex;

} thread_safe_priority_queue_t;

/********************** macros ***********************************************/

#define SAFE_MEMORY_SIZE    sizeof (thread_safe_priority_queue_t)

/********************** external data declaration ****************************/


/********************** external functions declaration ***********************/

thread_safe_priority_queue_t* pq_create_safe (void* memory_pool, size_t capacity);

void pq_destroy_safe (thread_safe_priority_queue_t* safe_pq);

bool pq_insert_safe (thread_safe_priority_queue_t* safe_pq, void* data, uint16_t priority);

void* pq_extract_max_safe (thread_safe_priority_queue_t* safe_pq);

bool pq_is_empty_safe (thread_safe_priority_queue_t* safe_pq);

size_t pq_size_safe (thread_safe_priority_queue_t* safe_pq);

void pq_print_priority_queue_safe (thread_safe_priority_queue_t* safe_pq);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* __THREAD_SAFE_PRIORITY_QUEUE_H__ */
/********************** end of file ******************************************/

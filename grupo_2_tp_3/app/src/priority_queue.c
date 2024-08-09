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

#include "priority_queue.h"

/********************** macros and definitions *******************************/


/********************** internal data declaration ****************************/


/********************** internal functions declaration ***********************/

static size_t _get_parent (size_t index);

static size_t _get_left (size_t index);

static size_t _get_right (size_t index);

static void _swap (priority_queue_t* pq, size_t i, size_t j);

static void _max_heapify (priority_queue_t* pq, size_t index);

static void _increase_priority (priority_queue_t* pq, size_t index, int16_t priority);

static int _power_of_two (int exp);

static uint16_t _calculate_level (size_t size);

/********************** internal data definition *****************************/


/********************** external data definition *****************************/


/********************** internal functions definition ************************/

static size_t _get_parent (size_t index) {

	return (index - 1) / 2;

}

static size_t _get_left (size_t index) {

	return 2 * index + 1;

}

static size_t _get_right (size_t index) {

	return 2 * index + 2;

}


static int _power_of_two (int exp) {

    return 1 << exp; // 2^exp

}

static uint16_t _calculate_level (size_t size) {

    return (uint16_t) log2 (size);

}


// Function to swap two elements in an array
static void _swap (priority_queue_t* pq, size_t i, size_t j) {

    pq_node_t temp_node = pq->nodes[i];
    pq->nodes[i] = pq->nodes[j];
    pq->nodes[j] = temp_node;

}

static void _max_heapify (priority_queue_t* pq, size_t index) {

	size_t child_left = _get_left (index);
	size_t child_right = _get_right (index);
	size_t largest;

	if (child_left < pq->size && pq->nodes[child_left].priority > pq->nodes[index].priority) {

		largest = child_left;

	} else {

		largest = index;

	}

	if (child_right < pq->size && pq->nodes[child_right].priority > pq->nodes[largest].priority) {

		largest = child_right;

	}

	if (largest != index) {

		_swap (pq, index, largest);
		_max_heapify (pq, largest);

	}

}


static void _increase_priority (priority_queue_t* pq, size_t index, int16_t priority) {

	if (priority > pq->nodes[index].priority) {

		pq->nodes[index].priority = priority;

		while (index > 0 && pq->nodes[_get_parent(index)].priority < pq->nodes[index].priority) {

			size_t parent = _get_parent(index);

			_swap(pq, index, parent);

			index = parent;

		}

	}

}

/********************** external functions definition ************************/

priority_queue_t* pq_create (void* memory_pool, size_t capacity) {

	priority_queue_t* pq = NULL;

	if (memory_pool != NULL && capacity != 0) {

		pq = (priority_queue_t*)memory_pool;

		// Initialize the queue
		pq->nodes = (pq_node_t*)((char*)memory_pool + sizeof(priority_queue_t));
		pq->size = 0;
		pq->capacity = capacity;

	}

	return pq;

}

void pq_destroy (priority_queue_t* pq) {

	// Nothing

}


bool pq_insert (priority_queue_t* pq, void* data, uint16_t priority) {

	bool successful = false;

	if (NULL != pq && NULL != data) {

		if (pq->size != pq->capacity) {

			pq->nodes[pq->size].data = data;
			pq->nodes[pq->size].priority = 0;

			_increase_priority(pq, pq->size, priority);

			pq->size++;

			successful = true;

		}

	}

	return successful;

}


void* pq_extract_max (priority_queue_t* pq) {

	void* data = NULL;

	if (NULL != pq) {

		if (pq->size > 0) {

			data = pq->nodes[0].data;

			pq->nodes[0] = pq->nodes[pq->size - 1];
			pq->size--;

			_max_heapify(pq, 0);

		}

	}

	return data;

}

bool pq_is_empty (priority_queue_t* pq) {

	bool is_empty = true;

	if (NULL != pq) {

		is_empty = pq->size == 0;

	}


	return is_empty;

}

size_t pq_size (priority_queue_t* pq) {

	size_t size = 0;

	if (NULL != pq) {

		size = pq->size;

	}

	return size;

}


void print_priority_queue_as_tree (priority_queue_t* pq) {

	uint16_t levels = _calculate_level (pq->size);

	uint16_t current_level = 0;
	size_t first_node_in_level = 0;
	size_t last_node_in_level = 0;
	uint16_t space_between_nodes = 0;
	uint16_t offset_spaces = 0;


    printf("Priority Queue as Tree:\n\n");

    for (size_t i = 1; i <= pq->size; i++) {

    	current_level = _calculate_level (i);

    	first_node_in_level = _power_of_two (current_level);

    	last_node_in_level = 2 * first_node_in_level - 1;

    	if (i == first_node_in_level) {

    		offset_spaces = _power_of_two (levels - current_level); // 2^(l - n)

    		printf ("%*s%d", offset_spaces, " ", pq->nodes[i-1].priority);

    		fflush (stdout);

    	} else {

    		space_between_nodes = (2 * offset_spaces) - 1;

    		printf ("%*s%d", space_between_nodes, " ", pq->nodes[i-1].priority);

    		fflush (stdout);

    	}


    	if (i == last_node_in_level || i == pq->size) {

    		printf("\n");

    	}

    }

    printf("\n");

}

/********************** end of file ******************************************/

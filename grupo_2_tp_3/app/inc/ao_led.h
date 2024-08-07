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

#ifndef __AO_LED_H__
#define __AO_LED_H__

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

#include "active_object.h"

/********************** macros ***********************************************/

#define LED_NAME_LEN 10

/********************** typedef **********************************************/

/* Led Even definition*/
typedef enum {

  AO_LED_EVENT_OFF = 0,
  AO_LED_EVENT_ON = 1,
  AO_LED_EVENT__N = 2,

} ao_led_state_t;


/* Led Active Object Message definition */
typedef struct {

	/* Hardware */
	GPIO_TypeDef* led_port;
	uint32_t led_pin;
	ao_led_state_t led_state;
	char led_name[LED_NAME_LEN];

} ao_led_even_t;

/********************** external data declaration ****************************/

extern ao_t ao_led;

/********************** external functions declaration ***********************/

void task_led_handler (void* msg);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* __AO_LED_H__ */
/********************** end of file ******************************************/


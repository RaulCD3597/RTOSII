/*=============================================================================
 * Copyright (c) 2020, Raul Camacho <raulc3597@gmail.com>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/06/27
 * Version: 1.0
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "sapi.h"
#include "uart.h"
#include "led.h"

int main(void)
{
   boardInit();

   uart_init();    // tarea C en practico
   led_init();     // tarea A en practico
   buttons_init(); // tarea B en practico

   vTaskStartScheduler(); // Initialize scheduler

   return 0;
}

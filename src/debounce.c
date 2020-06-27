/*
 * debounce.c
 *
 *  Created on: Apr 1, 2020
 *      Author: raul
 */

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "debounce.h"
#include "sapi.h"
#include <stdint.h>
#include <stdbool.h>

void debounceSM_Init(debounceButton_t *pButton, gpioMap_t key)
{
	pButton->buttonPressed = FALSE;
	pButton->buttonReleased = FALSE;
	pButton->key = key;
	pButton->buttonState = UP;
	pButton->time_down = 0;
	pButton->elapsed_time = 0;
}

void debounceSM_Update(debounceButton_t *pButton)
{
	switch (pButton->buttonState)
	{
	case UP:
		if ((TRUE == pButton->buttonReleased) && (TRUE == pButton->buttonPressed))
		{
			pButton->elapsed_time = xTaskGetTickCount() - pButton->time_down;

			pButton->buttonPressed = FALSE;
			pButton->buttonReleased = FALSE;
		}
		else
		{
			pButton->elapsed_time = 0;
			pButton->buttonPressed = FALSE;
			pButton->buttonReleased = FALSE;
		}
		if (!gpioRead(pButton->key))
		{
			pButton->buttonState = FALLING;
		}
		break;
	case FALLING:
		pButton->buttonPressed = TRUE;
		pButton->buttonReleased = FALSE;
		vTaskDelay(pdMS_TO_TICKS(DEBOUNCE_TIME));
		if (!gpioRead(pButton->key))
		{
			pButton->buttonState = DOWN;
		}
		else
		{
			pButton->buttonState = UP;
		}
		break;
	case DOWN:
		if ((TRUE == pButton->buttonPressed) && (FALSE == pButton->buttonReleased))
		{
			pButton->time_down = xTaskGetTickCount();
		}
		pButton->buttonPressed = FALSE;
		pButton->buttonReleased = FALSE;
		if (gpioRead(pButton->key))
		{
			pButton->buttonState = RISING;
		}
		break;
	case RISING:
		pButton->buttonPressed = TRUE;
		pButton->buttonReleased = TRUE;
		vTaskDelay(pdMS_TO_TICKS(DEBOUNCE_TIME));
		if (!gpioRead(pButton->key))
		{
			pButton->buttonState = DOWN;
		}
		else
		{
			pButton->buttonState = UP;
		}
		break;
	default:
		debounceSM_Init(pButton, pButton->key);
		break;
	}
}

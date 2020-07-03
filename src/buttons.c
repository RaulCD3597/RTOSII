/**
 * 
 * @file buttons.c
 * @author Raul Camacho
 * @date June 2020
 * 
 */

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "buttons.h"
#include "debounce.h"
#include "uart.h"

debounceButton_t tecla1, tecla2;

static void buttons_task(void *pvParameters);

void buttons_init(void)
{
    debounceSM_Init(&tecla1, TEC1);
    debounceSM_Init(&tecla2, TEC2);

    BaseType_t ret = xTaskCreate(
        buttons_task,
        (const char *)"tarea B",
        configMINIMAL_STACK_SIZE * 2,
        NULL,
        tskIDLE_PRIORITY + 1,
        NULL);

    if (ret == pdFAIL)
    {
        /**
         * 1. Imprimo mensaje de error
         * 2. Me quedo colgado en un bucle infinito
         */
        printf("Error al crear tarea B!!\n");
        for (;;)
        {
            ;
        }
    }
}

static void buttons_task(void *pvParameters)
{
    uint8_t * button_msg = NULL;

    for (;;)
    {
        debounceSM_Update(&tecla1);
        debounceSM_Update(&tecla2);

        if (tecla1.elapsed_time != 0)
        {
            button_msg = pvPortMalloc(15 * sizeof(uint8_t));
            sprintf(button_msg, "TEC1 T%d", tecla1.elapsed_time);
            uart_print(button_msg);
        }

        if (tecla2.elapsed_time != 0)
        {
            button_msg = pvPortMalloc(15 * sizeof(uint8_t));
            sprintf(button_msg, "TEC2 T%d", tecla2.elapsed_time);
            uart_print(button_msg);
        }
    }
    
}
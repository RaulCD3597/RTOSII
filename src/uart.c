/**
 * 
 * @file led.c
 * @author Raul Camacho
 * @date June 2020
 * 
 */

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"
#include "sapi.h"
#include "uart.h"

#define UART_QUEUE_LENGTH 4

QueueHandle_t uart_queue;

static void uart_task(void *pvParameters);

void uart_init(void)
{
    uartConfig(UART_USB, 115200);

    BaseType_t ret = xTaskCreate(
        uart_task,
        (const char *)"tarea C",
        configMINIMAL_STACK_SIZE * 2,
        NULL,
        tskIDLE_PRIORITY + 2,
        NULL);

    if (ret == pdFAIL)
    {
        /**
         * 1. Imprimo mensaje de error
         * 2. Me quedo colgado en un bucle infinito
         */
        printf("Error al crear tarea C!!\n");
        for (;;)
        {
            ;
        }
    }

    uart_queue = xQueueCreate(UART_QUEUE_LENGTH, sizeof(uint8_t *));

    if (NULL == uart_queue)
    {
        /**
         * 1. Imprimo mensaje de error
         * 2. Me quedo colgado en un bucle infinito
         */
        printf("Error al crear cola 1!!\n");
        for (;;)
        {
            ;
        }
    }
}

static void uart_task(void *pvParameters)
{
    uint8_t * uart_msg;

    for (;;)
    {
        xQueueReceive(uart_queue, (void *) &uart_msg, portMAX_DELAY);
        printf("%s\r\n", uart_msg);
    }
}

void uart_print(uint8_t * msg)
{
    xQueueSend(uart_queue, (void *) &msg, portMAX_DELAY);
}

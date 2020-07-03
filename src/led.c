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
#include "sapi.h"
#include "led.h"
#include "uart.h"
#include <string.h>

static void led_task(void *pvParameters);

void led_init(void)
{
    BaseType_t ret = xTaskCreate(
        led_task,
        (const char *)"tarea A",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 1,
        NULL);

    if (ret == pdFAIL)
    {
        /**
         * 1. Imprimo mensaje de error
         * 2. Me quedo colgado en un bucle infinito
         */
        printf("Error al iniciar sistema!!\n");
        for (;;)
        {
            ;
        }
    }
}

static void led_task(void *pvParameters)
{
    gpioWrite(LED1, OFF);
    uint8_t * led_msg = NULL;
    TickType_t xPeriodicity = 1000 / portTICK_RATE_MS; // Tarea periodica cada 1000 ms
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        gpioWrite(LED1, ON);
        led_msg = pvPortMalloc(7 * sizeof(uint8_t));
        memcpy(led_msg, "LED ON", 6);
        led_msg[6] = 0;
        uart_print(led_msg);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpioWrite(LED1, OFF);

        vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
    }
}

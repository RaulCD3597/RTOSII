/**
 * @file debounce.h
 * @brief Modulo para lectura de botones con antirebote en EDU-CIAA
 * @author Raul Camacho
 * @date Apr 1, 2020
 */

#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

#include "sapi.h"
#include <stdint.h>
#include <stdbool.h>

#define DEBOUNCE_TIME 40

/**
 * @enum debounceState_t
 * @brief enumeracion para los estados de la FSM
 */
typedef enum
{
	UP,
	FALLING,
	DOWN,
	RISING
} debounceState_t;
/**
 * @struct debounceButton_t
 * @brief estructura usada para el manejo  de  la FSM
 */
typedef struct
{
	bool_t buttonPressed;		 /**< flag para saber si el boton esta presionado */
	bool_t buttonReleased;		 /**< flag para saber si el boton esta presionado */
	gpioMap_t key;				 /**< Boton que tiene asignado  la FSM */
	debounceState_t buttonState; /**< estado en el que  se encuentra la  FSM */
	uint32_t time_down;			 /**< momento en que se presiona el boton */
	uint32_t elapsed_time;		 /**< tiempo durante el cual se mantuvo el boton presionado */
} debounceButton_t;
/**
 * @brief Funcion para inicializar la FSM para un boton
 * @param pButton estructura de la FSM que se desea inicializar
 * @param key tecla o boton que se desea asignar a pButton para menejo con la FSM
 */
void debounceSM_Init(debounceButton_t *pButton, gpioMap_t key);
/**
 * @brief Funcion para control de la FSM
 * @param pButton structura de la FSM que se desea controlar
 */
void debounceSM_Update(debounceButton_t *pButton);

#endif /* DEBOUNCE_H_ */

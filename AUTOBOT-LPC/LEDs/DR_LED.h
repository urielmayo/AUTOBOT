/*******************************************************************************************************************************//**
 *
 * @file		DR_LED.h
 * @brief		Módulo para manejo de LEDs
 * @date		25/02/2021
 * @author		Andres Yang
 *
 **********************************************************************************************************************************/

/********************************************************************************************************
*** MODULO
********************************************************************************************************/
#ifndef DR_LED_H_
#define DR_LED_H_

/********************************************************************************************************
*** INCLUDES
********************************************************************************************************/
#include <stdint.h>

/********************************************************************************************************
*** DEFINES
********************************************************************************************************/
/*Cantidad de LEDs que tiene el auto*/
#define MAX_LEDs	3

/*Identificadores de LEDs*/
enum {
	LED_YELLOW = 0,
	LED_GREEN,
	LED_RED
};

/********************************************************************************************************
 *** DATA TYPES
 ********************************************************************************************************/
/*Estructura para inicializar los LEDs*/
typedef struct
{
	uint8_t port;
	uint8_t pin;
}LED_t;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES
 **********************************************************************************************************************************/

/*******************************************************************************************************************************//**
 * @brief		Inicializa el modulo para el manejo de LEDs del auto
 **********************************************************************************************************************************/
void LED_init(void);

/*******************************************************************************************************************************//**
 * @brief		Enciende el color de LED pasado como parametro
 * @param[in]	color: color del LED a utilizar (usar identificadores de LEDs)
 **********************************************************************************************************************************/
void switch_on_LED(uint8_t color);

/*******************************************************************************************************************************//**
 * @brief		Apaga el color de LED pasado como parametro
 * @param[in]	color: color del LED a utilizar (usar identificadores de LEDs)
 **********************************************************************************************************************************/
void switch_off_LED(uint8_t color);

/*******************************************************************************************************************************//**
 * @brief		Prende los LEDs del auto
 **********************************************************************************************************************************/
void switch_on_all_LEDs(void);

/*******************************************************************************************************************************//**
 * @brief		Apaga los LEDs del auto
 **********************************************************************************************************************************/
void switch_off_all_LEDs(void);

/***********************************************************************************************************************************
 *** FIN DEL MODULO
 **********************************************************************************************************************************/

#endif /* DR_LED_H_ */
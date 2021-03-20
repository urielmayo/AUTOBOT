/*******************************************************************************************************************************//**
 *
 * @file		Gpio.h
 * @brief		Módulo para manejo de Entradas y Salidas de Propósito General (GPIO: General Purpose IO).
 * @date		20/02/21
 * @author		Andres Yang, Luis Gindre, Uriel Mayo.com>
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef GPIO_H_
#define GPIO_H_

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "Pin.h"

/***********************************************************************************************************************************
 *** DEFINES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS PUBLICOS
 **********************************************************************************************************************************/
typedef enum {
	DIR_IN = 0, DIR_OUT = 1
} GpioDir_e;

typedef enum {
	LOW = 0, HIGH = 1
} GpioValue_e;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES (extern)
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES
 **********************************************************************************************************************************/

/*******************************************************************************************************************************//**
 * @fn			void Gpio_SetDir(uint8_t port, uint8_t pin, GpioDir_e dir)
 * @brief		Configura un pin de un puerto en entrada o salida.
 * @param[in]	port:		Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @param[in]	dir:		Dirección del Pin. Debe ser uno de los siguientes: DIR_IN o DIR_OUT.
 * @return		void
 **********************************************************************************************************************************/
void Gpio_SetDir(uint8_t port, uint8_t pin, GpioDir_e dir);

/*******************************************************************************************************************************//**
 * @fn			void Gpio_SetPin(uint8_t port, uint8_t pin)
 * @brief		Pone un pin de un puerto en estado alto.
 * @param[in]	port:		Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @return		void
 **********************************************************************************************************************************/
void Gpio_SetPin(uint8_t port, uint8_t pin);

/*******************************************************************************************************************************//**
 * @fn			void Gpio_ClrPin(uint8_t port, uint8_t pin)
 * @brief		Pone un pin de un puerto en estado bajo.
 * @param[in]	port:		Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @return		void
 **********************************************************************************************************************************/
void Gpio_ClrPin(uint8_t port, uint8_t pin);

/*******************************************************************************************************************************//**
 * @fn			void Gpio_SetPinValue(uint8_t port, uint8_t pin, GpioValue_e pinValue)
 * @brief		Pone un pin de un puerto en el estado pasado como parametro.
 * @param[in]	port:		Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @param[in]	pinValue:	Valor del Pin. Debe ser uno de los siguientes: LOW o HIGH.
 * @return		void
 **********************************************************************************************************************************/
void Gpio_SetPinValue(uint8_t port, uint8_t pin, GpioValue_e pinValue);

/*******************************************************************************************************************************//**
 * @fn			GpioValue_e Gpio_GetPinValue(uint8_t port, uint8_t pin)
 * @brief		Retorna el valor de un pin de un puerto.
 * @param[in]	port:		Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @return		valor del pin (LOW, HIGH)
 **********************************************************************************************************************************/
GpioValue_e Gpio_GetPinValue(uint8_t port, uint8_t pin);

/***********************************************************************************************************************************
 *** FIN DEL MODULO
 **********************************************************************************************************************************/

#endif /* GPIO_H_ */

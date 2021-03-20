/*******************************************************************************************************************************//**
 *
 * @file		Gpio.c
 * @brief		Módulo para manejo de Entradas y Salidas de Propósito General (GPIO: General Purpose IO).
 * @date		20/02/21
 * @author		Andres Yang, Luis Gindre, Uriel Mayo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "LPC17xx.h"
#include "Gpio.h"
#include "Pin.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
/** @brief GPIO port  (GPIO_PORT) for LPC1769 */
typedef struct {				/* GPIO_PORT Structure */
	__IO uint32_t DIR;			/*!< Offset 0x0000: GPIO Port Direction control register */
	uint32_t RESERVED0[3];
	__IO uint32_t MASK;			/*!< Offset 0x0010: GPIO Mask register */
	__IO uint32_t PIN;			/*!< Offset 0x0014: Pin value register using FIOMASK */
	__IO uint32_t SET;			/*!< Offset 0x0018: Output Set register using FIOMASK */
	__O  uint32_t CLR;			/*!< Offset 0x001C: Output Clear register using FIOMASK */
} LPC_GPIO_T;

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** VARIABLES GLOBLES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE FUNCIONES PUBLICAS
 **********************************************************************************************************************************/

/*******************************************************************************************************************************//**
 * @fn			void Gpio_SetDir(uint8_t port, uint8_t pin, GpioDir_e dir)
 * @brief		Configura un pin de un puerto en entrada o salida.
 * @param[in]	port:		Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @param[in]	dir:		Dirección del Pin. Debe ser uno de los siguientes: DIR_IN o DIR_OUT.
 * @return		void
 **********************************************************************************************************************************/
void Gpio_SetDir(uint8_t port, uint8_t pin, GpioDir_e dir)
{
	if(dir == DIR_OUT){
		LPC_GPIO[port].DIR |= (1 << pin);
	}
	else{
		LPC_GPIO[port].DIR &= ~(1 << pin);
	}
}

/*******************************************************************************************************************************//**
 * @fn			void Gpio_SetPin(uint8_t port, uint8_t pin)
 * @brief		Pone un pin de un puerto en estado alto.
 * @param[in]	port:		Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @return		void
 **********************************************************************************************************************************/
void Gpio_SetPin(uint8_t port, uint8_t pin)
{
	LPC_GPIO[port].SET |= (1 << pin);
}

/*******************************************************************************************************************************//**
 * @fn			void Gpio_ClrPin(uint8_t port, uint8_t pin)
 * @brief		Pone un pin de un puerto en estado bajo.
 * @param[in]	port:		Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @return		void
 **********************************************************************************************************************************/
void Gpio_ClrPin(uint8_t port, uint8_t pin)
{
	LPC_GPIO[port].CLR |= (1 << pin);
}

/*******************************************************************************************************************************//**
 * @fn			void Gpio_SetPinValue(uint8_t port, uint8_t pin, GpioValue_e pinValue)
 * @brief		Pone un pin de un puerto en el estado pasado como parametro.
 * @param[in]	port:		Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @param[in]	pinValue:	Valor del Pin. Debe ser uno de los siguientes: LOW o HIGH.
 * @return		void
 **********************************************************************************************************************************/
void Gpio_SetPinValue(uint8_t port, uint8_t pin, GpioValue_e pinValue)
{
	if (pinValue == LOW){
		LPC_GPIO[port].CLR = (1UL << pin);
	}
	else{
		LPC_GPIO[port].SET = (1UL << pin);
	}
}

/*******************************************************************************************************************************//**
 * @fn			GpioValue_e Gpio_GetPinValue(uint8_t port, uint8_t pin)
 * @brief		Retorna el valor de un pin de un puerto.
 * @param[in]	port:		Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @return		valor del pin (LOW, HIGH)
 **********************************************************************************************************************************/
GpioValue_e Gpio_GetPinValue(uint8_t port, uint8_t pin)
{
	uint8_t retVal = LOW;

	if(0 != (LPC_GPIO[port].PIN & (1UL << pin)))	// Pongo un 1 en la posición que quiero averiguar el valor.
	{												// Al hacer el & Donde hay un 0 en la máscara el resultado es 0.
		retVal = HIGH;//El bit es 1.				// Donde hay un 1 deja el valor original. Si era un 0 el resultado es 0.
	}
	return retVal;
}

/***********************************************************************************************************************************
 *** IMPLEMNTACION DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------------------*/

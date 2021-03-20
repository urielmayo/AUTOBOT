/*******************************************************************************************************************************//**
 *
 * @file		Pin.c
 * @brief		Módulo para configuración de un pin de puerto
 * @date		20/02/21
 * @author		Andres Yang, Luis Gindre, Uriel Mayo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "LPC17xx.h"
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
/**
 * @brief IOCON register block
 */
typedef struct {
	uint32_t RESERVED0[5];
}LPC_IOCON_T;

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
 * @fn			void Pin_SetFunction(uint8_t port, uint8_t pin, PinFunction_e func)
 * @brief		Setea la Función del Pin pasado como parámetro
 * @param[in]	port:	Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @param[in] 	func 		Funcion. Debe ser uno de los tipos definidos en la enumeración PinFunction_e
 * @return 		void
 **********************************************************************************************************************************/
void Pin_SetFunction_v2(uint8_t port, uint8_t pin, PinFunction_e func)
{
/*
	 * port0 configura con PINSEL[0] PINSEL[1] Si port = 0 ---> Si pin < 16 --> port[0]  Si pin > 15 --> port[1]
	 * port1 configura con PINSEL[2] PINSEL[3]
	 * port2 configura con PINSEL[4] PINSEL[5]
	 * port3 configura con PINSEL[6] PINSEL[7]
	 * port4 configura con PINSEL[8] PINSEL[9]
	*/

	port = port*2 + pin/16;				// Si pin > 15 --> port[port + 1] Si pin < 16 --> port[port + 0]
	pin = (pin%16)*2;
										// 				PINSEL[port]   = ???????????????????????????????
										// 		   MASCARA ~(0x3<<pin) = 1111111111111111111111001111111
	PINSEL[port] &= ~(0x03 << pin);		// 		PINSEL[port] & MASCARA = ??????????????????????00???????
	PINSEL[port] |= func << pin;		//  func = (00 ; 01 ; 10 ; 11) = ??????????????????????10??????? func = 10
}

/*******************************************************************************************************************************//**
 * @fn			void Pin_SetResistorMode ( uint8_t port, uint8_t pin, PinResistorMode_e resMode)
 * @brief		Configura la resistencia asociada a un pin de un puerto
 * @param[in]	port:	Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @param[in] 	resMode		Modo de la Resistencia: Debe ser uno de los tipos definidos en la enumeración PinResistorMode_e
 * @return 		void
 **********************************************************************************************************************************/
void Pin_SetResistorMode_v2(uint8_t port, uint8_t pin, PinResistorMode_e resMode)
{
// IGUAL QUE PINSEL
	port = port*2 + pin/16;
	pin = (pin%16) * 2;
	PINMODE[port] &= ~(0x03 << pin);
	PINMODE[port] |= resMode << pin;
}

/*******************************************************************************************************************************//**
 * @fn			void Pin_SetOpenDrainMode(uint8_t port, uint8_t pin, PinOpenDrainMode_e odMode)
 * @brief		Configura el modo de la salida de un pin de un puerto
 * @param[in]	port:	Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @param[in] 	odMode 	    Modo de la Salida: Debe ser uno de los tipos definidos en la enumeración PinOpenDrainMode_e
 * @return 		void
 **********************************************************************************************************************************/
void Pin_SetOpenDrainMode_v2(uint8_t port, uint8_t pin, PinOpenDrainMode_e odMode)
{
	(odMode == OPEN_DRAIN) ? (PINMODE_OD[port] |= (1UL << pin )) : (PINMODE_OD[port] &= ~(1UL << pin));
}

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------------------*/

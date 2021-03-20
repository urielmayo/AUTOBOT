/*******************************************************************************************************************************//**
 *
 * @file		Pin.h
 * @brief		Módulo para configuración de un pin del puerto
 * @date		25/02/21
 * @author		Andres Yang, Luis Gindre, Uriel Mayo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef PIN_H_
#define PIN_H_

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <stdint.h>

/***********************************************************************************************************************************
 *** DEFINES
 **********************************************************************************************************************************/
// Definición de Puertos
#define PORT_0		 0
#define PORT_1		 1
#define PORT_2		 2
#define PORT_3		 3
#define PORT_4		 4

// Definición de Pines
#define PIN_0		 0
#define PIN_1		 1
#define PIN_2		 2
#define PIN_3		 3
#define PIN_4		 4
#define PIN_5		 5
#define PIN_6		 6
#define PIN_7		 7
#define PIN_8		 8
#define PIN_9		 9
#define PIN_10		10
#define PIN_11		11
#define PIN_12		12
#define PIN_13		13
#define PIN_14		14
#define PIN_15		15
#define PIN_16		16
#define PIN_17		17
#define PIN_18		18
#define PIN_19		19
#define PIN_20		20
#define PIN_21		21
#define PIN_22		22
#define PIN_23		23
#define PIN_24		24
#define PIN_25		25
#define PIN_26		26
#define PIN_27		27
#define PIN_28		28
#define PIN_29		29
#define PIN_30		30
#define PIN_31		31

/***********************************************************************************************************************************
 *** MACROS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS PUBLICOS
 **********************************************************************************************************************************/
typedef enum {
	DEFAULT_FUNC = 0,
	FIRST_ALT_FUNC = 1,
	SECOND_ALT_FUNC = 2,
	THIRD_ALT_FUNC = 3
} PinFunction_e;

typedef enum {
	RES_PULL_UP = 0, RES_LAST_STATE = 1, RES_NONE = 2, RES_PULL_DOWN = 3
} PinResistorMode_e;

typedef enum {
	NOT_OPEN_DRAIN = 0, OPEN_DRAIN = 1
} PinOpenDrainMode_e;


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES (extern)
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES
 **********************************************************************************************************************************/
/*******************************************************************************************************************************//**
 * @fn			void Pin_SetFunction(uint8_t port, uint8_t pin, PinFunction_e func)
 * @brief		Setea la Función del Pin pasado como parámetro
 * @param[in]	port:		Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @param[in] 	func 		Funcion. Debe ser uno de los tipos definidos en la enumeración PinFunction_e
 * @return 		void
 **********************************************************************************************************************************/
void Pin_SetFunction_v2(uint8_t port, uint8_t pin, PinFunction_e func);

/*******************************************************************************************************************************//**
 * @fn			void Pin_SetResistorMode ( uint8_t port, uint8_t pin, PinResistorMode_e resMode)
 * @brief		Configura la resistencia asociada a un pin de un puerto
 * @param[in]	port:		Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @param[in] 	resMode		Modo de la Resistencia: Debe ser uno de los tipos definidos en la enumeración PinResistorMode_e
 * @return 		void
 **********************************************************************************************************************************/
void Pin_SetResistorMode_v2(uint8_t port, uint8_t pin, PinResistorMode_e resMode);

/*******************************************************************************************************************************//**
 * @fn			void Pin_SetOpenDrainMode(uint8_t port, uint8_t pin, PinOpenDrainMode_e odMode)
 * @brief		Configura el modo de la salida de un pin de un puerto
 * @param[in]	port:		Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @param[in] 	odMode 	    Modo de la Salida: Debe ser uno de los tipos definidos en la enumeración PinOpenDrainMode_e
 * @return 		void
 **********************************************************************************************************************************/
void Pin_SetOpenDrainMode_v2(uint8_t port, uint8_t pin, PinOpenDrainMode_e odMode);

/*******************************************************************************************************************************//**
 * @fn			void Pin_Config(uint8_t port, uint8_t pin, PinFunction_e func, PinResistorMode_e resMode, PinOpenDrainMode_e odMode)
 * @brief		Configura el modo de la salida de un pin de un puerto
 * @param[in]	port:		Número de Puerto. Debe ser uno de los siguientes: PORT_0, PORT_1, PORT_2, PORT_3, PORT_4.
 * @param[in]	pin:		Número de Pin. Debe ser uno de los siguientes: Desde PIN_0 hasta PIN_31.
 * @param[in] 	func 		Funcion. Debe ser uno de los tipos definidos en la enumeración PinFunction_e
 * @param[in] 	resMode		Modo de la Resistencia: Debe ser uno de los tipos definidos en la enumeración PinResistorMode_e
 * @param[in] 	odMode 	    Modo de la Salida: Debe ser uno de los tipos definidos en la enumeración PinOpenDrainMode_e
 * @return 		void
 **********************************************************************************************************************************/
void Pin_Config(uint8_t port, uint8_t pin, PinFunction_e func, PinResistorMode_e resMode, PinOpenDrainMode_e odMode);

/***********************************************************************************************************************************
 *** FIN DEL MODULO
 **********************************************************************************************************************************/

#endif /* PIN_H_ */

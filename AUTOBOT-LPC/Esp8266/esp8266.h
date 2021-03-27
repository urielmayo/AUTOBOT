/*******************************************************************************************************************************//**
 *
 * @file		esp8266.h
 * @brief		Modulo para el manejo wifi
 * @date		25/02/21
 * @author		Uriel Mayo
 * @important	Conectarse unicamente a wifi a velocidad inferior a 2.4Ghz
 * 				ya que el modulo no soporta a una velocidad mayor
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef WIFI_H_
#define WIFI_H_

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/***********************************************************************************************************************************
 *** DEFINES
 **********************************************************************************************************************************/

//wifi casa de Luis
#define N_SSID "Fibertel WiFi923 2.4GHz"
#define N_PSWD "0043065082"

//wifi casa random
//#define N_PSWD "00412463343"
//#define N_SSID "Fibertel WiFi042 2.4GHz"

//hotspot celular de luis
//#define N_SSID "Luis cel"
//#define N_PSWD "luis891891"

//wifi casa de Andres
//#define N_SSID "Summer 2.4GHz"
//#define N_PSWD "h34rttounching"

/***********************************************************************************************************************************
 *** MACROS
 **********************************************************************************************************************************/
//estados de mdeWifi()
enum{
	CONFIG_INIT,
	CONNECT,
	SOCKET_CONNECTION,
};

//valor de retorno de procesarMultiple()
enum{
	PROCESANDO = 0,
	EXITO,
};

//estados de procesarMultiple()
enum{
	ESPERANDO_PRIMER_CHAR,
	ESPERANDO_FINAL
};


//comandos de AT
enum{
	ATE0 = 0,
	ATCWMODE,
	CHECK_NET,
	ATCWDHCP,
	ATCWJAP,
	ATCIPSTART,
	ATCIPSEND,
	SENDMSG,
	RECONNECT,
};

//valores de retorno de procesarTrama()
enum{
	WF_PROCESSING = 0,
	WF_CONNECTED,	//1
	WF_ERROR,		//2
	WF_START,		//3
	WF_STOP,		//4
	WF_OTHER,		//5
	WF_WORK,		//6
	WF_MENU,		//7
	WF_CONTINUE,	//8
	WF_CREATIVE,	//9
	WF_EXIT,		//10
};

//estados mdeComunication()
enum{
	ENVIAR = 0,
	RECIBIR,
};


/***********************************************************************************************************************************
 *** TIPO DE DATOS PUBLICOS
 **********************************************************************************************************************************/
typedef struct netID{
	char SSID [32];
	char pswd [32];
}netID_t;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES (extern)
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES
 **********************************************************************************************************************************/

/*******************************************************************************************************************************//**
 * @brief		configura e inicia la conexion del wifi
 * @return 		resultado booleano respecto al exito de la operacion
 **********************************************************************************************************************************/
bool wifiInit();

/*******************************************************************************************************************************//**
 * @brief		funcion que se encarga de conectarse al layer del wifi
 * @return 		void
 **********************************************************************************************************************************/
bool wifiConnect();

/*******************************************************************************************************************************//**
 * @brief		funcion que se encarga de establecer conexion de internet con QT
 * @return 		void
 **********************************************************************************************************************************/
bool socketConnect(void);

/*******************************************************************************************************************************//**
 * @brief		Busca la respuesta del wifi eliminando los \r y \n del principio de la cadena
 * @param[in]	respuesta: puntero al string a guardar la respuesta
 * @return		uint8_t: EXITO si consigue la respuesta o PROCESANDO si todavia esta buscando la respuesta
 **********************************************************************************************************************************/
uint8_t procesarRespuestaComando(char ** respuesta);

/*******************************************************************************************************************************//**
 * @brief		Procesa la trama producido por el modulo wifi y nuestro protocolo hasta encontrar el fin de caracter '#'
 * @return		Valores posibles que puede devolver el modulo wifi y producidos por nuetro modulo del auto
 * 				se encuentra dentro de los identificadores respecto a la funcion
 **********************************************************************************************************************************/
uint8_t procesarTrama(void);

/*******************************************************************************************************************************//**
 * @brief		maquina de estados encargada de estrablecer la conexion al layer wifi e internet
 **********************************************************************************************************************************/
void mdeWifi(void);

/*******************************************************************************************************************************//**
 * @brief		maquina de estados encargada de manejar el proceso de envio y recepcion de mensajes
 **********************************************************************************************************************************/
void mdeComunication(void);

/*******************************************************************************************************************************//**
 * @brief		Segun el estado que se encuentra le pasa como parambetro para enviar el mensaje correspondiente al estado del auto
 * @param[in]	status: estado al que se encuentra el auto para enviar el mensaje correspondiente
 * @return		uint8_t: EXITO si consigue la respuesta o PROCESANDO si todavia esta analizando la respuesta
 **********************************************************************************************************************************/
uint8_t enviarTrama(uint8_t status);

/*******************************************************************************************************************************//**
 * @brief		Segun el estado que se encuentra le pasa como parambetro para enviar el mensaje correspondiente al estado del auto
 * @param[in]	status: estado al que se encuentra el auto para enviar el mensaje correspondiente
 * @return		uint8_t: EXITO si consigue la respuesta o PROCESANDO si todavia esta analizando la respuesta
 **********************************************************************************************************************************/
uint8_t wifiSend(const char * msg);

/*******************************************************************************************************************************//**
 * @brief		Verificacion de la respuesta utilizada despues de recibir una respuesta
 * @param[in]	response: parametro a verificar
 * @return		dependiendo de la respuesta se le asignara un valor segun los identificadores para ser procesada
 **********************************************************************************************************************************/
uint8_t checkResponse(char * response);

/*******************************************************************************************************************************//**
 * @brief
 **********************************************************************************************************************************/
void reconnectWaitTime(void);

/***********************************************************************************************************************************
 *** FIN DEL MODULO
 **********************************************************************************************************************************/


#endif /* WIFI_H_ */

//TODO:
//		sacar funciones del .h ya que son privadas al modulo
//		sacar enums del .h ya que son privadas al modulo


/*		brief pendiente:
		pin
		gpio
		uart
		control y afines
*/

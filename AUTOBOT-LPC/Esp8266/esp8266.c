/*******************************************************************************************************************************//**
 *
 * @file		esp8266.h
 * @brief		Modulo para el manejo wifi y conexion a internet
 * @date		25/02/21
 * @author		Uriel Mayo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "esp8266.h"
#include "Flags.h"
#include "Uart.h"
#include "DR_LED.h"
#include "Lcd.h"
#include "DR_timer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/***********************************************************************************************************************************
 *** MACROS
 **********************************************************************************************************************************/
enum {IPD, READ_TRAMA, READ_MSG, CHECK_RESPONSE};
//#define __DEBUG
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
uint8_t isConnected;
//static netID_t redLocal;

uint8_t AT_Command[][60] = {
		"ATE0\r\n",											//0-echo
		"AT+CWMODE=1\r\n",									//1-server type: client
		"AT+CWJAP?\r\n",									//2-ask if connected
		"AT+CWDHCP=1,1\r\n",								//3-enable DHCP->asignacion de IP dinamica
		"AT+CWJAP=",										//4-connect to AP(access point)
		"AT+CIPSTART=\"TCP\",\"192.168.0.10\",3566\r\n",	//5-establish connection with type, addr, port
		"AT+CIPSEND="										//6-send msg
};

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES
 **********************************************************************************************************************************/
uint8_t procesarRespuestaComando(char ** respuesta)
{
	uint8_t retVal = PROCESANDO, caracterRecibido;
	static char response[70];
	static uint8_t index = 0, estado = ESPERANDO_PRIMER_CHAR;

	if(Uart_IsByteAvailable(UART0)) {
		caracterRecibido = Uart_GetByte(UART0);
		switch(estado){
		case ESPERANDO_PRIMER_CHAR:
			if((caracterRecibido != '\n') && (caracterRecibido != '\r')){
				response[index] = caracterRecibido;
				index++;
				estado = ESPERANDO_FINAL;
			}
			else{
				memset(response,0,sizeof(response));
			}
			break;
		case ESPERANDO_FINAL:
			if(caracterRecibido == '\n'){
				index = 0;
				estado = ESPERANDO_PRIMER_CHAR;
				*respuesta = response;
				retVal = EXITO;
			}
			else{
				response[index] = caracterRecibido;
				index++;
			}
			break;
		default:
			estado = ESPERANDO_PRIMER_CHAR;
			break;
		}
	}
	return retVal;
}

bool wifiInit()
{
	char * buffer;
	uint8_t retVal = false;
	static uint8_t estado = ATE0, msgSend = false;

	switch (estado){
	case ATE0:		//para sacar echo
		if(!msgSend){
			Uart_SendString(UART0, AT_Command[ATE0]);	//envio comando
			msgSend = true;
		}

		if(procesarRespuestaComando(&buffer) == EXITO){	//espera hasta recibir la finalizacion de procesar
			if(strcmp(buffer,"OK\r") == 0){
				msgSend = false;
				estado = ATCWMODE;
			}
			buffer = NULL;
		}
		break;
	case ATCWMODE:		//seteo de modo cliente
		if(!msgSend){
			Uart_SendString(UART0, AT_Command[ATCWMODE]);
			msgSend = true;
		}
		if(procesarRespuestaComando(&buffer) == EXITO){				//si no se logra exito?
			if(strcmp(buffer,"OK\r") == 0){			//hay que setear el msgSend en false again
				estado = ATE0;			//se podria hacer una funcion para comparar los distintos resultado del buffer?
				retVal = true;	 					//modificar para usar retVal
			}
		}
		break;
	default:
		estado = ATE0;
		break;
	}
	return retVal;
}

bool wifiConnect()
{
	bool retVal = false;
	static bool disconnected = true;
	static uint8_t estado = CHECK_NET;
	static bool msgSend = false;
	uint8_t net[40];	//se puede sin utilizar la variable auxiliar response
	char * buffer = NULL;

	switch (estado){
	case CHECK_NET:
		if(!msgSend){
			Uart_SendString(UART0,AT_Command[CHECK_NET]); //checkea si esta conectado
			msgSend = true;
		}
		if(procesarRespuestaComando(&buffer) == EXITO){
			if(strcmp(buffer,"No AP\r") == 0){		//verificacion de respuestasi estoy conectado
				disconnected = true;
			}
			else if(strstr(buffer, N_SSID)){ //busca el N_SSID dentro de buffer
				disconnected = false;
			}
			else if(strcmp(buffer,"OK\r") == 0){
				if(disconnected == true){		//si no esta conectado, me conecto
					estado = ATCWJAP;
				}
				else{							//si ya estoy conectado, solicito ip dinamica
					estado = ATCWDHCP;
				}
				msgSend = false;
			}
			buffer = NULL;
		}
		break;
	case ATCWDHCP:		//solicitud de ip dinamica
		if(!msgSend){
			Uart_SendString(UART0, AT_Command[ATCWDHCP]);
			msgSend = true;
		}
		if(procesarRespuestaComando(&buffer) == EXITO){
			if(strcmp(buffer,"OK\r") == 0){
				buffer = NULL;
				retVal = true;
			}
		}
		break;
	case ATCWJAP:		//para conectarme en caso de no estar conectado
		if(!msgSend){
			sprintf((char *)net,"\"%s\",\"%s\"\r\n",N_SSID,N_PSWD);		//escribo nombre del wifi y contrasena
			strcat((char *)AT_Command[ATCWJAP],(char *)net);
			Uart_SendString(UART0, AT_Command[ATCWJAP]);
			msgSend = true;
		}
		if(procesarRespuestaComando(&buffer)  == EXITO){
			if(strcmp(buffer,"OK\r")){
				msgSend = false;
				buffer = NULL;
				estado = ATCWDHCP;			//paso a solicitar ip dinamica
				retVal = true;				//uso de retVal
			}
		}
		break;
	default:
		estado = CHECK_NET;
		break;
	}
	return retVal;
}

bool socketConnect()
{
	bool retVal = false;
	char *buffer = NULL;
	static uint8_t estado = ATCIPSTART;
	static bool msgSend = false;

	switch (estado) {
	case ATCIPSTART: //abrir socket TCP
		if(!msgSend){
			Uart_SendString(UART0, AT_Command[ATCIPSTART]);
			msgSend = true;
		}
		if(procesarRespuestaComando(&buffer) == EXITO){
			if(strcmp(buffer,"OK\r") == 0){
				buffer = NULL;			//se puede sacar buffer y msg send afuera del if
				msgSend = false;
				retVal = true;
			}
			else if(strcmp(buffer,"CLOSED\r") == 0){	//objetivo de comparar esto? sin comparar ya hace lo mismo)
				msgSend = false;
				timer_start(TIMER_1, 1000, SINGLE_SHOT, reconnectWaitTime);
				estado = RECONNECT;
			}
		}
		break;

	case RECONNECT: //tiempo de espera para reconectarse
		if(reconnectTimeFlag){
			estado = ATCIPSTART;
			reconnectTimeFlag = false;
		}
		break;

	default:
		estado = ATCIPSTART;
		break;
	}
	return retVal;
}

uint8_t procesarTrama()
{
	uint8_t byte;
	uint8_t responseStatus = WF_PROCESSING;

	static uint8_t i = 0;
	static uint8_t bufferTrama_rcv [80];
	static uint8_t mdeProcesarTrama = IPD;

	if(Uart_IsByteAvailable(UART0)){
		byte = Uart_GetByte(UART0);

		switch (mdeProcesarTrama){
		case IPD:
			if( byte == '+'){
				mdeProcesarTrama = READ_TRAMA;
			}
			break;
		case READ_TRAMA:
			if ( byte == ':'){
				mdeProcesarTrama = READ_MSG;
			}
			break;

		case READ_MSG:
			if ( byte != '#'){
				bufferTrama_rcv[i] = byte;
				i++;
			}
			else{
				responseStatus  = checkResponse((char *)bufferTrama_rcv);

				Lcd_SetCursorPosition(LCD_COLUMN1, LCD_ROW1);
				Lcd_printf("                ");
				Lcd_SetCursorPosition(LCD_COLUMN1, LCD_ROW1);
				Lcd_printf("%s",bufferTrama_rcv);
				memset(bufferTrama_rcv,0,sizeof(bufferTrama_rcv));
				i = 0;
				mdeProcesarTrama = IPD;

			}
			break;

		default:
			mdeProcesarTrama = IPD;
			break;
		}
	}
	return responseStatus;
}

uint8_t checkResponse(char * rsp)
{
	if(strcmp(rsp,"$ERROR") == 0){			//que se hace con estos valores devueltos?
		return WF_ERROR;
	}
	else if(strcmp(rsp,"$CONNECTED") == 0){
		return WF_CONNECTED;
	}
	else if(strcmp(rsp,"$START") == 0){
		return WF_START;
	}
	else if(strcmp(rsp,"$STOP") == 0){
		return WF_STOP;
	}
	else if(strcmp(rsp,"$WORK") == 0){
		return WF_WORK;
	}
	else if(strcmp(rsp,"$MENU") == 0){
		return WF_MENU;
	}
	else if(strcmp(rsp,"$CONTINUE") == 0){
		return WF_CONTINUE;
	}
	else if(strcmp(rsp,"$CREAT") == 0){
		return WF_CREATIVE;
	}
	else if(strcmp(rsp,"$EXIT") == 0){
		return WF_EXIT;
	}
	else if(rsp[1] >= '0' && rsp[1] <= '9'){ // checkea la direccion de las flechas enviadas por QT en creativo
		if(strlen(rsp) == 3){
			sprintf(rsp,"%c%c",rsp[1],rsp[2]);
			directionFlag = atoi(rsp);
		}
		else{
			sprintf(rsp,"%c",rsp[1]);
			directionFlag = atoi(rsp);
		}
		return WF_PROCESSING;
	}
	else{
		return WF_OTHER;
	}
}

uint8_t enviarTrama(uint8_t status)
{
	uint8_t retVal = PROCESANDO;

	#ifdef __DEBUG
//	Lcd_printf("                ");
	LCD_CLEARdISPLAY();
	Lcd_SetCursorPosition(LCD_COLUMN1, LCD_ROW1);
	Lcd_printf("%d", status);
	#endif
	switch (status) {
	case WF_CONNECTED:
		if(wifiSend("OK") == EXITO){
			retVal = EXITO;
		}
		break;
	case WF_START:
		rideStatus = CHECK_INLINE;
		retVal = EXITO;

		break;
	case WF_STOP:
		if(wifiSend("stop") == EXITO){
			retVal = EXITO;
			rideStatus = ON_RIDE_STOP;
		}
		break;
	case WF_WORK:
		if(wifiSend("OK") == EXITO){
			retVal = EXITO;
			modoFuncionamiento = MODO_AUTONOMO;
		}
		break;
	case WF_MENU:
		if(wifiSend("OK") == EXITO){
			modoFuncionamiento = ESPERANDO_MODO;
			retVal = EXITO;
		}
		break;
	case WF_CONTINUE:
		if(wifiSend("continue") == EXITO){
			rideStatus = ON_RIDE;
			retVal = EXITO;
		}
		break;
	case WF_CREATIVE:
		if(wifiSend("OK") == EXITO){
			modoFuncionamiento = MODO_CREATIVO;
			retVal = EXITO;
		}
		break;
	case WF_EXIT:
		if(wifiSend("OK") == EXITO){
			modoFuncionamiento = ESPERANDO_MODO;
			retVal = EXITO;
		}
		break;
	default:
		break;
	}
	return retVal;
}

uint8_t wifiSend(const char * msg)
{
	static uint8_t estado = PROCESANDO;
	char  sendMsg [30], *rcvBuffer = NULL;
	static bool sent = false;

	switch (estado){
	case 0:			//usar define para saber en que estado se encuentra para ser mas claro
		if(!sent){
			sprintf(sendMsg,"%s%d\r\n", AT_Command[ATCIPSEND], strlen(msg));
			Uart_SendString(UART0, (uint8_t *)sendMsg);
			sent = true;
		}
		else{
			if(procesarRespuestaComando(&rcvBuffer) == EXITO){
				if(strstr(rcvBuffer,"OK")){
					estado = 1;
					rcvBuffer = NULL;
					sent = false;
					Lcd_SetCursorPosition(LCD_COLUMN1, LCD_ROW2);
					Lcd_printf("                ");
					Lcd_SetCursorPosition(LCD_COLUMN1, LCD_ROW2);
					Lcd_printf("SENDAT");
					switch_off_LED(LED_GREEN);
				}
				else{
					switch_off_all_LEDs();
					Lcd_SetCursorPosition(LCD_COLUMN1, LCD_ROW2);
					Lcd_printf("ERRORAT");
				}
			}
		}
		break;
	case 1:
		if(!sent){
			Uart_SendString(UART0, (uint8_t *)msg);		//envia el msj?
			sent = true;
			switch_off_LED(LED_YELLOW);
			Lcd_SetCursorPosition(LCD_COLUMN1, LCD_ROW2);
			Lcd_printf("                ");
			Lcd_SetCursorPosition(LCD_COLUMN1, LCD_ROW2);
			Lcd_printf("MSG_SEND");
		}
		else{
			if(procesarRespuestaComando(&rcvBuffer) == EXITO){		//verifica la respuesta del envio
				if(strstr(rcvBuffer,"SEND OK")){
					memset(sendMsg,0,sizeof(sendMsg));
					rcvBuffer = NULL;
					sent = false;
					estado = 0;
					switch_on_LED(LED_YELLOW);
					Lcd_SetCursorPosition(LCD_COLUMN1, LCD_ROW2);
					Lcd_printf("                ");
					Lcd_SetCursorPosition(LCD_COLUMN1, LCD_ROW2);
					Lcd_printf("SENDMS");
					return EXITO;		//no se si es mas claro usar retVal
				}
			}
		}
		break;
	default:
		break;
	}
	return PROCESANDO;
}

void reconnectWaitTime(void){
	reconnectTimeFlag = true;
}
/***********************************************************************************************************************************
 *** FIN DEL MODULO
 **********************************************************************************************************************************/

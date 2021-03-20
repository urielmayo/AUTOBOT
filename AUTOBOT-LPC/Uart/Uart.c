/*******************************************************************************************************************************//**
 *
 * @file		Uart.c
 * @brief		Módulo para manejo de las UARTs
 * @date		25/02/2021
 * @note		Basado en las implementacion de NXP
 * @author		Andres Yang, Luis Gindre y Uriel Mayo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "LPC17xx.h"
#include "Uart.h"
#include "Gpio.h"
#include "Pin.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define IIR_RBR			0x02		// Identificador de dato disponible
#define IIR_THER 		0x01		// Identificador de registro de transmision vacio
#define SIZE	256		// Size de los buffers de tx/rx. No modificar, las implementaciones dependen de este valor

extern uint8_t wifiWaitFlag;
/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
/**
 * @brief UART register block structure
 */
typedef struct
{					/*!< UARTn Structure       */
	union {
		__IO uint32_t  DLL;			/*!< Divisor Latch LSB. Least significant byte of the baud rate divisor value. The full divisor is used to generate a baud rate from the fractional rate divider (DLAB = 1). */
		__O  uint32_t  THR;			/*!< Transmit Holding Register. The next character to be transmitted is written here (DLAB = 0). */
		__I  uint32_t  RBR;			/*!< Receiver Buffer Register. Contains the next received character to be read (DLAB = 0). */
	};

	union {
		__IO uint32_t IER;			/*!< Interrupt Enable Register. Contains individual interrupt enable bits for the 7 potential UART interrupts (DLAB = 0). */
		__IO uint32_t DLM;			/*!< Divisor Latch MSB. Most significant byte of the baud rate divisor value. The full divisor is used to generate a baud rate from the fractional rate divider (DLAB = 1). */
	};

	union {
		__O  uint32_t FCR;			/*!< FIFO Control Register. Controls UART FIFO usage and modes. */
		__I  uint32_t IIR;			/*!< Interrupt ID Register. Identifies which interrupt(s) are pending. */
	};

	__IO uint32_t LCR;				/*!< Line Control Register. Contains controls for frame formatting and break generation. */
	__IO uint32_t MCR;				/*!< Modem Control Register. Only present on UART1 */
	__I  uint32_t LSR;				/*!< Line Status Register. Contains flags for transmit and receive status, including line errors. */
	__I  uint32_t MSR;				/*!< Modem Status Register. Only present on UART1 */
	__IO uint32_t SCR;				/*!< Scratch Pad Register. Eight-bit temporary storage for software. */
	__IO uint32_t ACR;				/*!< Auto-baud Control Register. Contains controls for the auto-baud feature. */
	__IO uint32_t ICR;				/*!< IrDA control register. Only present on UART0/2/3 */
	__IO uint32_t FDR;				/*!< Fractional Divider Register. Generates a clock input for the baud rate divider. */
	uint32_t RESERVED0;
	__IO uint32_t TER;				/*!< Transmit Enable Register. Turns off UART transmitter for use with software flow control. */
	uint32_t  RESERVED1[6];
	__IO uint32_t RS485CTRL;		/*!< RS-485/EIA-485 Control. Contains controls to configure various aspects of RS-485/EIA-485 modes. Only present on UART1*/
	__IO uint32_t RS485ADRMATCH;	/*!< RS-485/EIA-485 address match. Contains the address match value for RS-485/EIA-485 mode. Only present on UART1*/
	__IO uint32_t RS485DLY;			/*!< RS-485/EIA-485 direction control delay. Only present on UART1*/
}LPC_UART_T;

typedef struct
{
	volatile uint8_t in;
	volatile uint8_t out;
	volatile uint16_t count;
	volatile uint8_t buffer[SIZE];
}RingBuffer_s;

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBLES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
// Buffers de rx/tx de la UART0/1
static RingBuffer_s Uart0Rx;
static RingBuffer_s Uart0Tx;
static RingBuffer_s Uart1Rx;
static RingBuffer_s Uart1Tx;

// Flags para indicar comunicacion en curso
static volatile bool Uart0_Sending = false;
static volatile bool Uart1_Sending = false;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
static void Push(RingBuffer_s * const rb, uint8_t data);
static uint8_t Pop(RingBuffer_s * const rb);
static bool IsEmpty(RingBuffer_s const * const rb);

/*--------------------------------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE FUNCIONES PUBLICAS
 **********************************************************************************************************************************/

/*******************************************************************************************************************************//**
 * @brief		Inicializa la UART pasada como parametro
 * @param[in]	portNum: UART0/1/2/3
 * @param[in]	baudrate
 * @return		true si la inicializacion fue exitosa, false en caso contrario.
 **********************************************************************************************************************************/
bool Uart_Init(uint8_t portNum, uint32_t baudrate)
{
	bool retVal = false;

	// IMPORTANTE: En esta implementacion el baudrate es fijo y de 9600.
	(void)baudrate;	// Se deja preparado para que el alumno incorpore esta funcionalidad

	switch (portNum)
	{
	case UART0:

		/* UART 9600 Funcionando// Paso 1. Encendido de la UART. Registro PCONP - bit 3 en 1 prende la UART.
				PCONP |= 1UL << 3;

				// Paso 2. Seleccion de clock. Registro PCLKSEL0 - bits 6 y 7 ---> 00 CCLK/4, 01 CCLK, 10 CCLK/2, 11 CCLK/8:
				PCLKSEL0 &= ~(0x03 << 6);	// con un CCLOK = 100 MHz, nos queda PCLCK = 25 MHz

				// Paso 3. Formato del mensaje transmision de 8 bits, 1 bit de stop, sin paridad, sin break cond
				LPC_UART0->LCR = 3;

				// Paso 4.Configuracion del baud rate a 9600 baudios
				LPC_UART0->LCR |= (1UL << 7);	//  Encendido del bit DLAB (Divisor Latch Access Bit)
				LPC_UART0->DLM = 0;
				LPC_UART0->DLL = 73;
				LPC_UART0->FDR |= ( 1 << 0);
				LPC_UART0->FDR |= ( 9 << 4);
				LPC_UART0->LCR &= ~(1UL << 7);	// Apagado del bit DLAB (Divisor Latch Access Bit)
		 */

		//UART0 a 115200 mhz
		// Paso 1. Encendido de la UART. Registro PCONP - bit 3 en 1 prende la UART.
		PCONP |= 1UL << 3;

		// Paso 2. Seleccion de clock. Registro PCLKSEL0 - bits 6 y 7 ---> 00 CCLK/4, 01 CCLK, 10 CCLK/2, 11 CCLK/8:
		// con un CCLOK = 100 MHz, nos queda PCLCK = 12 MHz
		PCLKSEL0 |= (0x3 << 6);
		// Paso 3. Formato del mensaje transmision de 8 bits, 1 bit de stop, sin paridad, sin break cond
		LPC_UART0->LCR = 3;

		// Paso 4.Configuracion del baud rate a 9600 baudios
		LPC_UART0->LCR |= (1UL << 7);	//  Encendido del bit DLAB (Divisor Latch Access Bit)
		LPC_UART0->DLM = 0;
		LPC_UART0->DLL = 0x4;
		LPC_UART0->FDR = 0x5;
		LPC_UART0->FDR |= ( 0x1 << 7);
		LPC_UART0->LCR &= ~(1UL << 7);	// Apagado del bit DLAB (Divisor Latch Access Bit)


		// Paso 5. Seleccion de la funcionalidad de los pines usados para la UART
		Pin_SetFunction_v2(PORT_0, PIN_2, FIRST_ALT_FUNC);	// Pin TX
		Pin_SetFunction_v2(PORT_0, PIN_3, FIRST_ALT_FUNC);	// Pin RX

		// Paso 6. Habilitacion de las interrupciones

		//7. Habilito las interrupciones (En la UART -IER- y en el NVIC -ISER)
		ISER0 |= (1UL << 5);	// Habilitacion en el NVIC
		LPC_UART0->IER = (1UL << 0) | (1UL << 1);	// Habilito fuentes de interrupcion: por rec/tran

		retVal = true;
		break;

	case UART1:
		PCONP |= 1UL << 3;
		PCLKSEL0 |= (3UL << 8); // bits 9 y8
		LPC_UART1->LCR = 3;
		LPC_UART1->LCR |= (1UL << 7);
		LPC_UART1->DLM = 0;
		LPC_UART1->DLL = 73;
		LPC_UART1->FDR |= ( 1 << 0);
		LPC_UART1->FDR |= ( 9 << 4);
		LPC_UART1->LCR &= ~(1UL << 7);
		Pin_SetFunction_v2(PORT_0, PIN_15, FIRST_ALT_FUNC);	// Pin TX
		Pin_SetFunction_v2(PORT_0, PIN_16, FIRST_ALT_FUNC);	// Pin RX
		ISER0 |= (1UL << 6);
		LPC_UART1->IER = (1UL << 0) | (1UL << 1);
		retVal = true;
		break;
	}

	return retVal;
}

// Envio de datos

void Uart_SendByte(uint8_t portNum, uint8_t data)
{
	switch (portNum){
	case UART0:
		LPC_UART0->IER &= ~(1UL << 1);	// Deshabilito interrupcion por transmision

		if (Uart0_Sending == true){
			Push(&Uart0Tx, data);
		}
		else{
			LPC_UART0->THR = data;
			Uart0_Sending = true;
		}

		LPC_UART0->IER |= (1UL << 1);
		break;

	case UART1:
		LPC_UART1->IER &= ~(1UL << 1);	// Deshabilito interrupcion por transmision

		if (Uart1_Sending == true){
			Push(&Uart1Tx, data);
		}
		else{
			LPC_UART1->THR = data;
			Uart1_Sending = true;
		}

		LPC_UART1->IER |= (1UL << 1);
		break;
	}

}

void Uart_Send(uint8_t portNum, const uint8_t *bufferPtr, uint32_t length)
{
	for (uint32_t i = 0; i < length; i++){
		Uart_SendByte(portNum, bufferPtr[i]);
	}

}

void Uart_SendString(uint8_t portNum, uint8_t const * const str)
{
	uint8_t const *data = str;

	while (*data != '\0'){
		Uart_SendByte(portNum, *data);
		data++;
	}
}


// Recepcion de datos
bool Uart_IsByteAvailable(uint8_t portNum)
{
	bool isByteAvailable = false;

	if (portNum == UART0){
		isByteAvailable = !IsEmpty(&Uart0Rx);
	}
	else if (portNum == UART1){
		isByteAvailable = !IsEmpty(&Uart1Rx);
	}

	return isByteAvailable;
}

uint8_t Uart_GetByte(uint8_t portNum)
{
	uint8_t data = 0;

	if (portNum == UART0){
		data = Pop(&Uart0Rx);
	}
	else if (portNum == UART1){
		data = Pop(&Uart1Rx);
	}

	return data;
}

/***********************************************************************************************************************************
 *** IMPLEMNTACION DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
void UART0_IRQHandler(void)
{
	uint32_t iir;	// Se utiliza para la lectura del regitro IIR (que se limpia al leerlo)
	uint32_t intId;	// Se utiliza para identificar la causa de la interrupcion
	uint8_t data;	// Se utiliza para la lectura/escritura de los datos recividos/transmitidos

	do
	{
		iir = LPC_UART0->IIR;
		intId = ((iir >> 1UL) & 7UL);	// Obtiene el "Interrupt identification", que son los bits 3:1 del registro IIR

		switch (intId) {
		case IIR_RBR:	// Se recibio un dato y esta disponible para ser leido
			data = LPC_UART0->RBR;		// Lee el dato recibido
			Push(&Uart0Rx, data);
			// Guarda el dato en el buffer circular
			break;

		case IIR_THER:	// Se finalizo de transmitir un dato
			if (IsEmpty(&Uart0Tx) == false) {
				LPC_UART0->THR = Pop(&Uart0Tx);
			}
			else {
				Uart0_Sending = false;
			}
			break;
		}
	}while(!(iir & 1UL));	// Si el bit 0 es igual a 0, entonces al menos queda una interrupcion pendiente
}

void UART1_IRQHandler(void)
{
	uint32_t iir;	// Se utiliza para la lectura del regitro IIR (que se limpia al leerlo)
	uint32_t intId;	// Se utiliza para identificar la causa de la interrupcion
	uint8_t data;	// Se utiliza para la lectura/escritura de los datos recividos/transmitidos

	do
	{
		iir = LPC_UART1->IIR;
		intId = ((iir >> 1UL) & 7UL);	// Obtiene el "Interrupt identification", que son los bits 3:1 del registro IIR

		switch (intId) {
		case IIR_RBR:	// Se recibio un dato y esta disponible para ser leido
			data = LPC_UART1->RBR;		// Lee el dato recibido
			Push(&Uart1Rx, data);			// Guarda el dato en el buffer circular
			break;

		case IIR_THER:	// Se finalizo de transmitir un dato
			if (IsEmpty(&Uart1Tx) == false){
				LPC_UART1->THR = Pop(&Uart1Tx);
			}
			else{
				Uart1_Sending = false;
			}
			break;
		}
	}while(!(iir & 1UL));	// Si el bit 0 es igual a 0, entonces al menos queda una interrupcion pendiente
}

// Funciones para el manejo del buffer circular.

static void Push(RingBuffer_s * const rb, uint8_t data)
{
	if (rb->count < SIZE){
		rb->buffer[rb->in] = data;
		rb->in++;
		rb->count++;
	}
}

static uint8_t Pop(RingBuffer_s * const rb)
{
	uint8_t data = 0;

	if (rb->count > 0){
		data = rb->buffer[rb->out];
		rb->out++;
		rb->count--;
	}

	return data;
}

static bool IsEmpty(RingBuffer_s const * const rb)
{
	return ((rb->count == 0) ? true : false);
}

/*--------------------------------------------------------------------------------------------------------------------------------*/

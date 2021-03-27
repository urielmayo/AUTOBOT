/*******************************************************************************************************************************//**
 *
 * @file		main.c
 * @brief		marchivo para manejo total del auto
 * @version		1
 * @date		25/02/21
 * @author		Andres Yang, Luis Gindre, Uriel Mayo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include "Uart.h"

#include "init.h"
#include "MDE_ControlGral.h"
#include "MDE_SeguimientoLinea.h"
#include "esp8266.h"
#include "DR_timer.h"
#include "Flags.h"



/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
uint8_t flag_uart = 0;
uint16_t wait = 10000;

/***********************************************************************************************************************************
 *** main
 **********************************************************************************************************************************/
#define __UART_TIMER_TEST

#ifdef __UART_TIMER_TEST
void uart_start(void)
{
	Uart_Init(UART0, 115200);
	flag_uart = 1;
}
#endif

int main(void)
{
	autobot_init();

	#ifdef __UART_TIMER_TEST
	timer_start(TIMER_0, 100000, SINGLE_SHOT, uart_start);
	#endif

	while(1)
	{
		if(wait == 0){
			Uart_Init(UART0, 115200);
			flag_uart = 1;
			wait = -1;
		}
		if(flag_uart == 1){
			if (wifiWaitFlag){
				wifiWaitFlag = 0;

				if(connectionSocketFlg != CONNECTED){
					mdeWifi();
				}
				else {
					mdeComunication();
				}
			}
			maquina_MdE_ControlAutobot();
		}
	}
	return 0;
}

void SysTick_Handler(void)
{
	static uint8_t wifiTicks = 1;
	static uint8_t cnyUpdateTicks = 80;
	static uint16_t finalTrack_ticks = 100;
	static uint16_t lostTicks = 2000;

	if(--wifiTicks == 0)
	{
		wifiWaitFlag ++;
		wifiTicks = 1;
	}

	if(--cnyUpdateTicks == 0)
	{
		cnyFlg = 1;
		cnyUpdateTicks = 80;
	}

	if(endDelayFlag){
		if(finalTrack_ticks > 0){
			endFlag = 1;
			finalTrack_ticks --;
		}
		else{
			endFlag = 0;
		}
	}
	else{
		finalTrack_ticks = 100;
	}
	if(wait > 0){
		wait--;
	}
	if(lostDelayFlag){
		if(--lostTicks == 0){
			lostFlag = 1;
		}
	}
	else{
		lostTicks = 2000;
	}
}
/***********************************************************************************************************************************
 *** FIN DEL MODULO
 **********************************************************************************************************************************/

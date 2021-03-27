/*******************************************************************************************************************************//**
 *
 * @file		DR_LED.c
 * @brief		Módulo para manejo de LEDs
 * @date		25/02/2021
 * @author		Andres Yang
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_LED.h"
#include "Gpio.h"

/***********************************************************************************************************************************
 *** VARIABLES
 **********************************************************************************************************************************/
//puertos y pines correspondientes a los LEDs
LED_t LEDs[] ={{0,15},{0,16},{0,17}};

/***********************************************************************************************************************************
 *** FUNCIONES
 **********************************************************************************************************************************/
void LED_init(void)
{
	for(int i = 0; i < MAX_LEDs; i++)
	{
		Pin_SetFunction_v2(LEDs[i].port, LEDs[i].pin, DEFAULT_FUNC);
		Pin_SetResistorMode_v2(LEDs[i].port, LEDs[i].pin, RES_PULL_UP);
		Pin_SetOpenDrainMode_v2(LEDs[i].port, LEDs[i].pin, NOT_OPEN_DRAIN);
		Gpio_SetDir(LEDs[i].port, LEDs[i].pin, DIR_OUT);
		Gpio_ClrPin(LEDs[i].port, LEDs[i].pin);
	}

}

void switch_on_LED(uint8_t color)
{
	switch(color){
	case LED_YELLOW:
		Gpio_SetPin(LEDs[0].port, LEDs[0].pin);
		break;
	case LED_GREEN:
		Gpio_SetPin(LEDs[1].port, LEDs[1].pin);
		break;
	case LED_RED:
		Gpio_SetPin(LEDs[2].port, LEDs[2].pin);
		break;
	default:
		break;
	}
}

void switch_off_LED(uint8_t color)
{
	switch(color){
	case LED_YELLOW:
		Gpio_ClrPin(LEDs[0].port, LEDs[0].pin);
		break;
	case LED_GREEN:
		Gpio_ClrPin(LEDs[1].port, LEDs[1].pin);
		break;
	case LED_RED:
		Gpio_ClrPin(LEDs[2].port, LEDs[2].pin);
		break;
	default:
		break;
	}
}

void switch_on_all_LEDs(void)
{
	uint8_t i;
	for(i=0; i<MAX_LEDs; i++)
	{
		Gpio_SetPin(LEDs[i].port, LEDs[i].pin);
	}
}

void switch_off_all_LEDs(void)
{
	uint8_t i;
	for(i=0; i<MAX_LEDs; i++)
	{
		Gpio_ClrPin(LEDs[i].port, LEDs[i].pin);
	}
}

/***********************************************************************************************************************************
 *** FIN DEL MODULO
 **********************************************************************************************************************************/

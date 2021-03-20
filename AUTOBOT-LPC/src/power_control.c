/*******************************************************************************************************************************//**
 *
 * @file		power_control.c
 * @brief		Modulo para el manejo de alimentacion de energia a los perifericos
 * @date		25/02/21
 * @author		Andres Yang
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "register_types.h"

/***********************************************************************************************************************************
 *** DEFINES
 **********************************************************************************************************************************/
#define PCONP_t ((register_t *)0x400FC0C4UL)

#define PCTIM0		PCONP_t->bit01
#define PCTIM1		PCONP_t->bit02
#define PCUART0		PCONP_t->bit03
#define PCUART1		PCONP_t->bit04

#define PCPWM1		PCONP_t->bit06
#define PCI2C0		PCONP_t->bit07
#define PCSPI		PCONP_t->bit08
#define PCRTC		PCONP_t->bit09
#define PCSSP1		PCONP_t->bit10

#define PCADC		PCONP_t->bit12
#define PCCAN1		PCONP_t->bit13
#define PCCAN2		PCONP_t->bit14
#define PCGPIO		PCONP_t->bit15
#define PCRIT		PCONP_t->bit16
#define PCMCPWM		PCONP_t->bit17
#define PCQEI		PCONP_t->bit18
#define PCI2C1		PCONP_t->bit19

#define PCSSP0		PCONP_t->bit21
#define PCTIM2		PCONP_t->bit22
#define PCTIM3		PCONP_t->bit23
#define PCUART2		PCONP_t->bit24
#define PCUART3		PCONP_t->bit25
#define PCI2C2		PCONP_t->bit26
#define PCI2S		PCONP_t->bit27

#define PCGPDMA		PCONP_t->bit29
#define PCENET		PCONP_t->bit30
#define PCUSB		PCONP_t->bit31

/***********************************************************************************************************************************
 *** FUNCIONES
 **********************************************************************************************************************************/

void powerControl_init(void)
{
	PCUART1 = 0;
	PCI2C0 	= 0;
	PCSPI	= 0;
	PCRTC	= 0;
	PCSSP1	= 0;
	PCADC	= 0;
	PCCAN1	= 0;
	PCCAN2 	= 0;
	PCMCPWM = 0;
	PCQEI	= 0;
	PCI2C1	= 0;
	PCSSP0	= 0;
	PCUART2 = 0;
	PCUART3 = 0;
	PCI2C2	= 0;
	PCI2S	= 0;
	PCGPDMA = 0;
	PCENET	= 0;
	PCUSB	= 0;
}

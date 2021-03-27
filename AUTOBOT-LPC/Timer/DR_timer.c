/*******************************************************************************************************************************//**
 *
 * @file		DR_timer.h
 * @brief		Modulo para el manejo de timers
 * @date		25/02/21
 * @author		Andres Yang
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "register_types.h"
#include "LPC17xx.h"
#include "DR_timer.h"
#include "DR_NVIC.h"

/***********************************************************************************************************************************
 *** DEFINES
 **********************************************************************************************************************************/
//puntero a los registros de los timers
#define		TIMER0		( ( timer_t  * ) 0x40004000UL )
#define		TIMER1		( ( timer_t  * ) 0x40008000UL )
#define		TIMER2		( ( timer_t  * ) 0x40090000UL )
#define		TIMER3		( ( timer_t  * ) 0x40094000UL )

//***************** TIMER 0 ********************
/** IR - INTERRUPT REGISTER */
#define		T0_IR			TIMER0->IR.dword

#define		T0_IR_MR0		TIMER0->IR.bit00	//for match register 0
#define		T0_IR_MR1		TIMER0->IR.bit01
#define		T0_IR_MR2		TIMER0->IR.bit02
#define		T0_IR_MR3		TIMER0->IR.bit03
#define		T0_IR_CR0		TIMER0->IR.bit04	//interrupt flag for caputre register channel 0 event
#define		T0_IR_CR1		TIMER0->IR.bit05

/** TCR - TIMER CONTROL REGISTER */
#define		T0_TCR			TIMER0->TCR.dword

#define		T0_TCR_CE		TIMER0->TCR.bit00	//counter enable
#define		T0_TCR_CR		TIMER0->TCR.bit01	//counter reset

/** CTCR - COUNT CONTROL REGISTER */
#define		T0_CTCR			TIMER0->CTCR.dword

#define		T0_CTCR_TCM		TIMER0->CTCR.bits0y1 //is incremented in counter/timer mode: 00 timer mode, 01 rising edge, 10 falling edge, 11 both
#define		T0_CTCR_CIS		TIMER0->CTCR.bit02y3 //count input select

/** TC - TIMER COUNTER REGISTER */
#define		T0_TC			TIMER0->TC.dword

/** PR - PRESCALE REGISTER */
#define		T0_PR			TIMER0->PR.dword

/** PC - PRESCALE COUNTER REGISTER */
#define		T0_PC			TIMER0->PC.dword

/** MR - MATCH REGISTER */
#define		T0_MR0			TIMER0->MR[0].dword
#define		T0_MR1			TIMER0->MR[1].dword
#define		T0_MR2			TIMER0->MR[2].dword
#define		T0_MR3			TIMER0->MR[3].dword

/** MCR - MATCH CONTROL REGISTER */
#define		T0_MCR			TIMER0->MCR.dword

#define		T0_MR0I			TIMER0->MCR.bit00	//interrupt on MR0 when matches the value with TC
#define		T0_MR0R			TIMER0->MCR.bit01	//reset on MR0: the TC will be reset if MR0 matches
#define		T0_MR0S			TIMER0->MCR.bit02	//stp[ on MR0: the TC and PC and TCR0 will be set to 0 if MR0 matches the TC

#define		T0_MR1I			TIMER0->MCR.bit03
#define		T0_MR1R			TIMER0->MCR.bit04
#define		T0_MR1S			TIMER0->MCR.bit05

#define		T0_MR2I			TIMER0->MCR.bit06
#define		T0_MR2R			TIMER0->MCR.bit07
#define		T0_MR2S			TIMER0->MCR.bit08

#define		T0_MR3I			TIMER0->MCR.bit09
#define		T0_MR3R			TIMER0->MCR.bit10
#define		T0_MR3S			TIMER0->MCR.bit11

//***************** TIMER 1 ********************
/** IR - INTERRUPT REGISTER */
#define		T1_IR			TIMER1->IR.dword

#define		T1_IR_MR0		TIMER1->IR.bit00
#define		T1_IR_MR1		TIMER1->IR.bit01
#define		T1_IR_MR2		TIMER1->IR.bit02
#define		T1_IR_MR3		TIMER1->IR.bit03
#define		T1_IR_CR0		TIMER1->IR.bit04
#define		T1_IR_CR1		TIMER1->IR.bit05

/** TCR - TIMER CONTROL REGISTER */
#define		T1_TCR			TIMER1->TCR.dword

#define		T1_TCR_CE		TIMER1->TCR.bit00
#define		T1_TCR_CR		TIMER1->TCR.bit01

/** CTCR - COUNT CONTROL REGISTER */
#define		T1_CTCR			TIMER1->CTCR.dword

#define		T1_TCR_TCM		TIMER1->CTCR.bits0y1
#define		T1_TCR_CIS		TIMER1->CTCR.bit02y3

/** TC - TIMER COUNTER REGISTER */
#define		T1_TC			TIMER1->TC.dword

/** PR - PRESCALE REGISTER */
#define		T1_PR			TIMER1->PR.dword

/** PC - PRESCALE COUNTER REGISTER */
#define		T1_PC			TIMER1->PC.dword

/** MR - MATCH CONTROL REGISTER */
#define		T1_MR0			TIMER1->MR[0].dword
#define		T1_MR1			TIMER1->MR[1].dword
#define		T1_MR2			TIMER1->MR[2].dword
#define		T1_MR3			TIMER1->MR[3].dword

/** MCR - MATCH CONTROL REGISTER */
#define		T1_MCR			TIMER1->MCR.dword

#define		T1_MR0I			TIMER1->MCR.bit00
#define		T1_MR0R			TIMER1->MCR.bit01
#define		T1_MR0S			TIMER1->MCR.bit02

#define		T1_MR1I			TIMER1->MCR.bit03
#define		T1_MR1R			TIMER1->MCR.bit04
#define		T1_MR1S			TIMER1->MCR.bit05

#define		T1_MR2I			TIMER1->MCR.bit06
#define		T1_MR2R			TIMER1->MCR.bit07
#define		T1_MR2S			TIMER1->MCR.bit08

#define		T1_MR3I			TIMER1->MCR.bit09
#define		T1_MR3R			TIMER1->MCR.bit10
#define		T1_MR3S			TIMER1->MCR.bit11

//***************** TIMER 0 ********************
/** IR - INTERRUPT REGISTER */
#define		T2_IR			TIMER2->IR.dword

#define		T2_IR_MR0		TIMER2->IR.bit00
#define		T2_IR_MR1		TIMER2->IR.bit01
#define		T2_IR_MR2		TIMER2->IR.bit02
#define		T2_IR_MR3		TIMER2->IR.bit03
#define		T2_IR_CR0		TIMER2->IR.bit04
#define		T2_IR_CR1		TIMER2->IR.bit05

/** TCR - TIMER CONTROL REGISTER */
#define		T2_TCR			TIMER2->TCR.dword

#define		T2_TCR_CE		TIMER2->TCR.bit00
#define		T2_TCR_CR		TIMER2->TCR.bit01

/** CTCR - COUNT CONTROL REGISTER */
#define		T2_CTCR			TIMER2->CTCR.dword

#define		T2_TCR_TCM		TIMER2->CTCR.bits0y1
#define		T2_TCR_CIS		TIMER2->CTCR.bit02y3

/** TC - TIMER COUNTER REGISTER */
#define		T2_TC			TIMER2->TC.dword

/** PR - PRESCALE REGISTER */
#define		T2_PR			TIMER2->PR.dword

/** PC - PRESCALE COUNTER REGISTER */
#define		T2_PC			TIMER2->PC.dword

/** MR - MATCH CONTROL REGISTER */
#define		T2_MR0			TIMER2->MR[0].dword
#define		T2_MR1			TIMER2->MR[1].dword
#define		T2_MR2			TIMER2->MR[2].dword
#define		T2_MR3			TIMER2->MR[3].dword

/** MCR - MATCH CONTROL REGISTER */
#define		T2_MCR			TIMER2->MCR.dword

#define		T2_MR0I			TIMER2->MCR.bit00
#define		T2_MR0R			TIMER2->MCR.bit01
#define		T2_MR0S			TIMER2->MCR.bit02

#define		T2_MR1I			TIMER2->MCR.bit03
#define		T2_MR1R			TIMER2->MCR.bit04
#define		T2_MR1S			TIMER2->MCR.bit05

#define		T2_MR2I			TIMER2->MCR.bit06
#define		T2_MR2R			TIMER2->MCR.bit07
#define		T2_MR2S			TIMER2->MCR.bit08

#define		T2_MR3I			TIMER2->MCR.bit09
#define		T2_MR3R			TIMER2->MCR.bit10
#define		T2_MR3S			TIMER2->MCR.bit11

//***************** TIMER 3 ********************
/** IR - INTERRUPT REGISTER */
#define		T3_IR			TIMER3->IR.dword

#define		T3_IR_MR0		TIMER3->IR.bit00
#define		T3_IR_MR1		TIMER3->IR.bit01
#define		T3_IR_MR2		TIMER3->IR.bit02
#define		T3_IR_MR3		TIMER3->IR.bit03
#define		T3_IR_CR0		TIMER3->IR.bit04
#define		T3_IR_CR1		TIMER3->IR.bit05

/** TCR - TIMER CONTROL REGISTER */
#define		T3_TCR			TIMER3->TCR.dword

#define		T3_TCR_CE		TIMER3->TCR.bit00
#define		T3_TCR_CR		TIMER3->TCR.bit01

/** CTCR - COUNT CONTROL REGISTER */
#define		T3_CTCR			TIMER3->CTCR.dword

#define		T3_TCR_TCM		TIMER3->CTCR.bits0y1
#define		T3_TCR_CIS		TIMER3->CTCR.bit02y3

/** TC - TIMER COUNTER REGISTER */
#define		T3_TC			TIMER3->TC.dword

/** PR - PRESCALE REGISTER */
#define		T3_PR			TIMER3->PR.dword

/** PC - PRESCALE COUNTER REGISTER */
#define		T3_PC			TIMER3->PC.dword

/** MR - MATCH CONTROL REGISTER */
#define		T3_MR0			TIMER3->MR[0].dword
#define		T3_MR1			TIMER3->MR[1].dword
#define		T3_MR2			TIMER3->MR[2].dword
#define		T3_MR3			TIMER3->MR[3].dword

/** MCR - MATCH CONTROL REGISTER */
#define		T3_MCR			TIMER3->MCR.dword

#define		T3_MR0I			TIMER3->MCR.bit00
#define		T3_MR0R			TIMER3->MCR.bit01
#define		T3_MR0S			TIMER3->MCR.bit02

#define		T3_MR1I			TIMER3->MCR.bit03
#define		T3_MR1R			TIMER3->MCR.bit04
#define		T3_MR1S			TIMER3->MCR.bit05

#define		T3_MR2I			TIMER3->MCR.bit06
#define		T3_MR2R			TIMER3->MCR.bit07
#define		T3_MR2S			TIMER3->MCR.bit08

#define		T3_MR3I			TIMER3->MCR.bit09
#define		T3_MR3R			TIMER3->MCR.bit10
#define		T3_MR3S			TIMER3->MCR.bit11

#define TICKS					12500 	//ticks needed for 1ms using a clock with 12.5Mhz
#define CANT_TIMERS_FUNCTIONS	4		//cantidad de funciones que recibiran el total de los timer handlers

/********************************************************************************************************
 *** DATA TYPES PRIVADA AL MODULO
 ********************************************************************************************************/
typedef struct
{
	__IO register_t		IR;				//interrupt register
	__IO register_t 	TCR;			//timer counter register
	__IO register_t 	TC;				//timer counter
	__IO register_t 	PR;				//prescale register
	__IO register_t 	PC;				//prescale counter
	__IO register_t 	MCR;			//match control register
	__IO register_t 	MR[4];			//match register 0-3
	__IO register_t 	CCR;			//capture control register
	__O register_t 		CR[2];			//capture register
	__IO register_t 	EMR;			//external match register
	__IO register_t 	CTCR;			//count control register
}timer_t;


void (*function_4timers[CANT_TIMERS_FUNCTIONS])(void);

/***********************************************************************************************************************************
 *** FUNCIONES
 **********************************************************************************************************************************/

void timer_init(timer_id timer)
{
	switch(timer)
	{
	case 0:
		PCONP |= 1 << 1; 				// enable timer 0
		PCLKSEL0 |= 3 << 2; 			// Clock for timer0 = CCLK/8 Selecciono clock
		break;
	case 1:
		PCONP |= 1 << 2; 				// enable timer 1
		PCLKSEL0 |= 3 << 4; 			// Clock for timer1 = CCLK/8 Selecciono clock
		break;
	case 2:
		PCONP |= 1 << 22; 				// enable timer 2
		PCLKSEL1 |= 3 << 12; 			// Clock for timer2 = CCLK/8 Selecciono clock
		break;
	case 3:
		PCONP |= 1 << 23;				// enable timer 3
		PCLKSEL1 |= 3 << 14;			// Clock for timer3 = CCLK/8 Selecciono clock
		break;
	default:
		break;
	}
}

void timer_start(timer_id timer, time value, timer_types type, void (*handler)(void))
{
	//	ticks every s = 0.00000008 ----------- 1
	//	time required =	0.001 ---------------- x =12500

	switch(timer) {
	case TIMER_0:
		T0_MR0 = TICKS*value;			//setting MR value
		if(type == PERIODIC) {
			T0_MR0R = 1;	//reset TC when MR matches
			T0_MR0S = 0;	//dont stop on match
		}
		else if(type == SINGLE_SHOT) {
			T0_MR0R = 0;	//dont reset TC when MR matches
			T0_MR0S = 1;	//stop on match
		}
		function_4timers[0] = handler;	//setting function to be called when TC match
		NVIC_enableIRQ(TIMER0_IRQn);	//enable interruption
		T0_MR0I = 1;					//interrupt owhen TC match with MR
		T0_TCR_CR=1;					//reset TCR
		T0_TCR_CR=0;					//clear reset
		T0_TCR_CE=1;					//enable TCR
		break;
	case TIMER_1:
		T1_MR0 = TICKS*value;
		if(type == PERIODIC) {
			T0_MR0R = 1;
			T1_MR0S = 0;
		}
		else if(type == SINGLE_SHOT) {
			T0_MR0R = 0;
			T1_MR0S = 1;
		}
		function_4timers[1] = handler;
		NVIC_enableIRQ(TIMER1_IRQn);
		T1_MR0I = 1;
		T1_TCR_CR = 1;
		T1_TCR_CR = 0;
		T1_TCR_CE = 1;
		break;
	case TIMER_2:
		T2_MR0 = TICKS*value;
		if(type == PERIODIC) {
			T1_MR0R = 1;
			T2_MR0S = 0;
		}
		else if(type == SINGLE_SHOT) {
			T1_MR0R = 0;
			T2_MR0S = 1;
		}
		function_4timers[2] = handler;
		NVIC_enableIRQ(TIMER2_IRQn);
		T2_MR0I = 1;
		T2_TCR_CR = 1;
		T2_TCR_CR = 0;
		T2_TCR_CE = 1;
		break;
	case TIMER_3:
		T3_MR0 = TICKS*value;
		if(type == PERIODIC) {
			T1_MR0R = 1;
			T3_MR0S = 0;
		}
		else if(type == SINGLE_SHOT) {
			T1_MR0R = 0;
			T3_MR0S = 1;
		}
		function_4timers[3] = handler;
		NVIC_enableIRQ(TIMER3_IRQn);
		T3_MR0I = 1;
		T3_TCR_CR = 1;
		T3_TCR_CR = 0;
		T3_TCR_CE = 1;
		break;
	}
}

void timer_stop(timer_id timer)
{
	switch(timer)
	{
	case TIMER_0:
		T0_TCR_CE = 0;	//dissable enable for TCR
		break;
	case TIMER_1:
		T1_TCR_CE = 0;
		break;
	case TIMER_2:
		T2_TCR_CE = 0;
		break;
	case TIMER_3:
		T3_TCR_CE = 0;
		break;
	}
}

void TIMER0_IRQHandler (void)
{
	T0_IR_MR0 = 1;			//Atendi la interrupcion

	(*function_4timers[0])();

	T0_TCR_CR = 1;			//reset TCR
	T0_TCR_CR = 0;			//clear reset for TCR
}

void TIMER1_IRQHandler (void)
{
	T1_IR_MR0 = 1;			//Atendi la interrupcion

	(*function_4timers[1])();

	T1_TCR_CR=1;
	T1_TCR_CR=0;
}


void TIMER2_IRQHandler (void)
{
	T2_IR_MR0 = 1;			//Atendi la interrupcion

	(*function_4timers[2])();

	T1_TCR_CR=1;
	T1_TCR_CR=0;
}


void TIMER3_IRQHandler (void)
{
	T3_IR_MR0 = 1;			//Atendi la interrupcion

	(*function_4timers[3])();

	T1_TCR_CR=1;
	T1_TCR_CR=0;
}

/***********************************************************************************************************************************
 *** FIN DEL MODULO
 **********************************************************************************************************************************/

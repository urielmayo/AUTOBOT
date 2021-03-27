/*******************************************************************************************************************************//**
 *
 * @file		DR_PWM.c
 * @brief		Modulo para el manejo PWM
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
#include "LPC17xx.h"
#include "Pin.h"
#include "Gpio.h"
#include "DR_PWM.h"

/***********************************************************************************************************************************
 *** DEFINES
 **********************************************************************************************************************************/
//PWM1 register map
#define     DIR_PWM1 ((uint32_t *)0x40018000)

//PWM1 register
#define     PWM1IR      DIR_PWM1[0]     //interrupt register
#define     PWM1TCR     DIR_PWM1[1]     //timer control register
#define     PWM1TC      DIR_PWM1[2]     //timer counter
#define     PWM1PR      DIR_PWM1[3]     //prescale register
#define     PWM1PC      DIR_PWM1[4]     //prescale counter
#define     PWM1MCR     DIR_PWM1[5]     //match control register
#define     PWM1MR0     DIR_PWM1[6]     //match register 0
#define     PWM1MR1     DIR_PWM1[7]     //match register 1
#define     PWM1MR2     DIR_PWM1[8]     //match register 2
#define     PWM1MR3     DIR_PWM1[9]     //match register 3
#define     PWM1CCR     DIR_PWM1[10]    //capture control register
#define     PWM1CR0     DIR_PWM1[11]    //capture register 0
#define     PWM1CR1     DIR_PWM1[12]    //capture register 1
#define     PWM1CR2     DIR_PWM1[13]    //capture register 2
#define     PWM1CR3     DIR_PWM1[14]    //capture register 3

#define     PWM1MR4     DIR_PWM1[16]    //match register 4
#define     PWM1MR5     DIR_PWM1[17]    //match register 5
#define     PWM1MR6     DIR_PWM1[18]    //match register 6
#define     PWM1PCR     DIR_PWM1[19]    //PWM control register
#define     PWM1LER     DIR_PWM1[20]    //load enable register
#define     PWM1CTCR    DIR_PWM1[21]    //count control register

//declaracion de puertos y pines para manejo de motores
#define MOTOR_IZQ		PORT_2, PIN_0
#define MOTOR_DER		PORT_2, PIN_1

//Declaracion de prescaler, duty y frecuencia maxima del duty
#define PWM_MAX_DUTY		255		//max value reachable for dutys
#define PWM_FREC			1000
#define PWM_PRESCALE_NS		(1000000000/(PWM_FREC*PWM_MAX_DUTY))	//in ns

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
uint8_t duty1 = 0;		//starting LED OFF
uint8_t duty2 = 0;

/***********************************************************************************************************************************
 *** FUNCIONES PRIVADA AL MODULO
 **********************************************************************************************************************************/

/*******************************************************************************************************************************//**
 * @brief		Update de los registro de los match para el duty de PWM
 **********************************************************************************************************************************/
void PWM1_duty_update(void)
{
	PWM1MR1 = duty1;	//setting value for match registers
	PWM1MR2 = duty2;

	PWM1LER = 0x06;		//enable latch for match 1 and 2
}

/***********************************************************************************************************************************
 *** FUNCIONES
 **********************************************************************************************************************************/

void PWM_init(void)
{
	uint32_t aux_prescale;

    PCONP |= (0x01 << 6); 			//enable power for PWM1
    PCLKSEL0 &= ~(0x03 << 12);   	//selecting 25MHz for PWM1

    Pin_SetFunction_v2(MOTOR_IZQ, FIRST_ALT_FUNC);
    Pin_SetFunction_v2(MOTOR_DER, FIRST_ALT_FUNC);

	Gpio_SetDir(MOTOR_IZQ, DIR_OUT);
	Gpio_SetDir(MOTOR_DER, DIR_OUT);

	//PWM registers configuration
    PWM1IR = 0x0000073F;			//reseting all match register
    //reseting all
    PWM1TCR = 0x00;
	PWM1CTCR = 0x00;
	PWM1MCR = 0x00;
	PWM1CCR = 0x00;
	PWM1PCR = 0x00;
	PWM1LER = 0x00;

	//redondeo para abajo o para arriba
    if( (PWM_PRESCALE_NS%1000) <500 )
		aux_prescale = 	 PWM_PRESCALE_NS/1000;
	else
		aux_prescale = 	 PWM_PRESCALE_NS/1000 + 1;

    PWM1PR = (aux_prescale*25000000/1000000)/2 -1; //setting prescaler

    PWM1MCR |= (1 << 1);        //enabling reset PWM1MR0 (match register 0)
    PWM1MR0 = PWM_MAX_DUTY;   	// PWM cycle
    PWM1MR1 = duty1;      		// PWM duty cycle
    PWM1MR2 = duty2;

    PWM1LER = 0x07;             //enabling  update after MR (match register)

    PWM1PCR |= (1 << 9);		//enabling PWM1.0 output
	PWM1PCR	|= (1 << 10);   	//enabling PWM1.1 output

    PWM1TCR |= (1 << 1);		//reseting counter
	PWM1TCR = (0x09);          	//enabling "counter enable" and "PWM enable"
}

void PWM1_duty_set(matchNumbers match, uint8_t value)
{
	switch(match)
	{
	case MATCH_IZQ:
		duty1 = value;
		break;
	case MATCH_DER:
		duty2 = value;
		break;
	}
	PWM1_duty_update();
}

/***********************************************************************************************************************************
 *** FIN DEL MODULO
 **********************************************************************************************************************************/

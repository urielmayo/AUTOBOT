/*******************************************************************************************************************************//**
 *
 * @file		PR_motor.c
 * @brief		Modulo para el manejo de motores
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
#include "Pin.h"
#include "Gpio.h"
#include "DR_PWM.h"
#include "PR_motor.h"

/***********************************************************************************************************************************
 *** DEFINES
 **********************************************************************************************************************************/
//ports and pins for motors control
#define MOTOR_IZQ_EN1 		PORT_2, PIN_2
#define MOTOR_IZQ_EN2		PORT_2, PIN_3
#define MOTOR_DER_EN2		PORT_2, PIN_8
#define MOTOR_DER_EN1		PORT_2, PIN_10

/***********************************************************************************************************************************
 *** FUNCIONES
 **********************************************************************************************************************************/
void motor_init(void)
{
	PWM_init();

	Pin_SetFunction_v2(MOTOR_IZQ_EN1, DEFAULT_FUNC);
	Pin_SetFunction_v2(MOTOR_IZQ_EN2, DEFAULT_FUNC);
	Gpio_SetDir(MOTOR_IZQ_EN1, DIR_OUT);
	Gpio_SetDir(MOTOR_IZQ_EN2, DIR_OUT);
	Pin_SetResistorMode_v2(MOTOR_IZQ_EN1, RES_PULL_UP);
	Pin_SetResistorMode_v2(MOTOR_IZQ_EN2, RES_PULL_UP);

	Pin_SetFunction_v2(MOTOR_DER_EN1, DEFAULT_FUNC);
	Pin_SetFunction_v2(MOTOR_DER_EN2, DEFAULT_FUNC);
	Gpio_SetDir(MOTOR_DER_EN1, DIR_OUT);
	Gpio_SetDir(MOTOR_DER_EN2, DIR_OUT);
	Pin_SetResistorMode_v2(MOTOR_DER_EN1, RES_PULL_UP);
	Pin_SetResistorMode_v2(MOTOR_DER_EN2, RES_PULL_UP);

	motor_stop();
}

void motor_stop(void)
{
	Gpio_ClrPin(MOTOR_IZQ_EN1);
	Gpio_ClrPin(MOTOR_IZQ_EN2);
	Gpio_ClrPin(MOTOR_DER_EN1);
	Gpio_ClrPin(MOTOR_DER_EN2);
}

void motor_forward(uint8_t speed)
{
	Gpio_ClrPin(MOTOR_IZQ_EN2);
	Gpio_SetPin(MOTOR_IZQ_EN1);
	Gpio_ClrPin(MOTOR_DER_EN2);
	Gpio_SetPin(MOTOR_DER_EN1);

	PWM1_duty_set(MATCH_IZQ, speed);
	PWM1_duty_set(MATCH_DER, speed);
}

void motor_backward(uint8_t speed)
{
	Gpio_ClrPin(MOTOR_IZQ_EN1);
	Gpio_SetPin(MOTOR_IZQ_EN2);
	Gpio_ClrPin(MOTOR_DER_EN1);
	Gpio_SetPin(MOTOR_DER_EN2);

	PWM1_duty_set(MATCH_IZQ, speed);
	PWM1_duty_set(MATCH_DER, speed);
}

void motor_turn(uint8_t speed,uint8_t direction, uint8_t mode)
{
	if((direction != TURN_LEFT) && (direction != TURN_RIGHT)) {return;}

	if(direction == TURN_LEFT){
		if(mode == CORRECTION){
			leftMotor_direction(speed,BACKWARD);
			rightMotor_direction(speed,FORWARD);
		}
		else{
			leftMotor_direction(speed +30 ,BACKWARD);
			rightMotor_direction(speed,FORWARD);
		}
	}
	else{
		if(mode == CORRECTION){
			rightMotor_direction(speed,BACKWARD);
			leftMotor_direction(speed,FORWARD);
		}
		else{
			rightMotor_direction(speed+30,BACKWARD);
			leftMotor_direction(speed,FORWARD);
		}
	}
}

void leftMotor_direction(uint8_t speed, uint8_t direction)
{
	if(direction == FORWARD){
		Gpio_SetPin(MOTOR_IZQ_EN1);
		Gpio_ClrPin(MOTOR_IZQ_EN2);
	}
	else if(direction == BACKWARD){
		Gpio_ClrPin(MOTOR_IZQ_EN1);
		Gpio_SetPin(MOTOR_IZQ_EN2);
	}
	else{
		Gpio_ClrPin(MOTOR_IZQ_EN1);
		Gpio_ClrPin(MOTOR_IZQ_EN2);
	}

	PWM1_duty_set(MATCH_IZQ, speed);
}

void rightMotor_direction(uint8_t speed, uint8_t direction)
{
	if(direction == FORWARD){
		Gpio_SetPin(MOTOR_DER_EN1);
		Gpio_ClrPin(MOTOR_DER_EN2);
	}
	else if(direction == BACKWARD){
		Gpio_ClrPin(MOTOR_DER_EN1);
		Gpio_SetPin(MOTOR_DER_EN2);
	}
	else{
		Gpio_ClrPin(MOTOR_DER_EN1);
		Gpio_ClrPin(MOTOR_DER_EN2);
	}

	PWM1_duty_set(MATCH_DER, speed);
}

void motor_go_up_right(void)
{
	Gpio_ClrPin(MOTOR_IZQ_EN2);
	Gpio_SetPin(MOTOR_IZQ_EN1);
	Gpio_ClrPin(MOTOR_DER_EN2);
	Gpio_SetPin(MOTOR_DER_EN1);

	PWM1_duty_set(MATCH_IZQ, 180);
	PWM1_duty_set(MATCH_DER, 0);
}

void motor_go_up_left(void)
{
	Gpio_ClrPin(MOTOR_IZQ_EN2);
	Gpio_SetPin(MOTOR_IZQ_EN1);
	Gpio_ClrPin(MOTOR_DER_EN2);
	Gpio_SetPin(MOTOR_DER_EN1);

	PWM1_duty_set(MATCH_IZQ, 0);
	PWM1_duty_set(MATCH_DER, 180);
}

void motor_go_down_right(void)
{
	Gpio_ClrPin(MOTOR_IZQ_EN1);
	Gpio_SetPin(MOTOR_IZQ_EN2);
	Gpio_ClrPin(MOTOR_DER_EN1);
	Gpio_SetPin(MOTOR_DER_EN2);

	PWM1_duty_set(MATCH_IZQ, 180);
	PWM1_duty_set(MATCH_DER, 0);
}

void motor_go_down_left(void)
{
	Gpio_ClrPin(MOTOR_IZQ_EN1);
	Gpio_SetPin(MOTOR_IZQ_EN2);
	Gpio_ClrPin(MOTOR_DER_EN1);
	Gpio_SetPin(MOTOR_DER_EN2);

	PWM1_duty_set(MATCH_IZQ, 0);
	PWM1_duty_set(MATCH_DER, 180);
}

/***********************************************************************************************************************************
 *** FIN DEL MODULO
 **********************************************************************************************************************************/

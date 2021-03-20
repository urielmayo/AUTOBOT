/*******************************************************************************************************************************//**
 *
 * @file		MDE_workMode.c
 * @brief		Módulo para manejo del modo trabajo
 * @date		25/02/2021
 * @author		Andres Yang
 *
 **********************************************************************************************************************************/

/********************************************************************************************************
 *** MODULO
 ********************************************************************************************************/

/********************************************************************************************************
 *** INCLUDES
 ********************************************************************************************************/
#include <stdbool.h>
#include "Flags.h"
#include "MDE_workMode.h"
#include "MDE_SeguimientoLinea.h"
#include "esp8266.h"
#include "PR_motor.h"

#include "DR_sensorInfrarojo.h"

/********************************************************************************************************
 *** DEFINE
 ********************************************************************************************************/
//#define __DEBUG


#ifdef __DEBUG
#include "Lcd.h"
#endif

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES
 **********************************************************************************************************************************/
void MDE_workMode()
{
	switch (rideStatus){
	case STANDBY:

		break;
	case CHECK_INLINE:
		sensorInfrarojo_update();

		if(getRightSensorStatus() || getLeftSensorStatus() || !getMiddleSensorStatus()){
			#ifdef __DEBUG
			Lcd_SetCursorPosition(LCD_COLUMN1, LCD_ROW1);
			Lcd_printf("%d", getRightSensorStatus());
			Lcd_SetCursorPosition(LCD_COLUMN1, LCD_ROW2);
			Lcd_printf("%d", getLeftSensorStatus());
			#endif
			if(wifiSend("not_line") == EXITO){
				rideStatus = STANDBY;
			}
		}
		else{
			if(wifiSend("start") == EXITO){
				rideStatus = ON_RIDE;
			}
		}
		break;
	case ON_RIDE:
		maquina_MdESeguimientoLinea();
		break;
	case ON_RIDE_STOP:
		motor_stop();
		break;
	case FINISHED:
		if(wifiSend("end") == EXITO){
			endFlag = 0;
			endDelayFlag = false;
			rideStatus = STANDBY;
		}
		break;
	case LOST:
		if(wifiSend("lost") == EXITO){
			lostFlag = false;
			lostDelayFlag = false;
			rideStatus = STANDBY;
		}
		break;
	default:
		break;
	}
}

/***********************************************************************************************************************************
 *** FIN DEL MODULO
 **********************************************************************************************************************************/

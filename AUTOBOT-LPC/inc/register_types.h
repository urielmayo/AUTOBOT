/*******************************************************************************************************************************//**
 *
 * @file		register_types.h
 * @brief		definicion de tipo de estructuras y uniones para menjo de bits
 * @date		25/02/21
 * @author		Andres Yang
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef REGISTER_TYPES_H_
#define REGISTER_TYPES_H_

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <stdint.h>

/***********************************************************************************************************************************
 *** DEFINES
 **********************************************************************************************************************************/
/* IO definitions (access restrictions to peripheral registers) */
#define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#define   __O     volatile             /*!< Defines 'write only' permissions                */
#define   __IO    volatile             /*!< Defines 'read / write' permissions              */

/********************************************************************************************************
 *** DATA TYPES
 ********************************************************************************************************/
typedef union
{
	__IO uint32_t dword;
	__O  uint32_t dWord;
	struct
	{
		__IO uint16_t wordL;
		__IO uint16_t wordH;
	};

	struct
	{
		__IO uint8_t  byte0;
		__IO uint8_t  byte1;
		__IO uint8_t  byte2;
		__IO uint8_t  byte3;
	};

	struct
	{
		__O uint8_t  byte0;
		__O uint8_t  byte1;
		__O uint8_t  byte2;
		__O uint8_t  byte3;
	}r;

	struct
	{
		__I uint8_t  byte0;
		__I uint8_t  byte1;
		__I uint8_t  byte2;
		__I uint8_t  byte3;
	}w;

	struct
	{
		__IO uint32_t	bit00:1;
		__IO uint32_t	bit01:1;
		__IO uint32_t	bit02:1;
		__IO uint32_t	bit03:1;
		__IO uint32_t	bit04:1;
		__IO uint32_t	bit05:1;
		__IO uint32_t	bit06:1;
		__IO uint32_t	bit07:1;
		__IO uint32_t	bit08:1;
		__IO uint32_t	bit09:1;
		__IO uint32_t	bit10:1;
		__IO uint32_t	bit11:1;
		__IO uint32_t	bit12:1;
		__IO uint32_t	bit13:1;
		__IO uint32_t	bit14:1;
		__IO uint32_t	bit15:1;
		__IO uint32_t	bit16:1;
		__IO uint32_t	bit17:1;
		__IO uint32_t	bit18:1;
		__IO uint32_t	bit19:1;
		__IO uint32_t	bit20:1;
		__IO uint32_t	bit21:1;
		__IO uint32_t	bit22:1;
		__IO uint32_t	bit23:1;
		__IO uint32_t	bit24:1;
		__IO uint32_t	bit25:1;
		__IO uint32_t	bit26:1;
		__IO uint32_t	bit27:1;
		__IO uint32_t	bit28:1;
		__IO uint32_t	bit29:1;
		__IO uint32_t	bit30:1;
		__IO uint32_t	bit31:1;
	};
}register_t;

/***********************************************************************************************************************************
 *** FIN DEL MODULO
 **********************************************************************************************************************************/

#endif /* REGISTER_TYPES_H_ */

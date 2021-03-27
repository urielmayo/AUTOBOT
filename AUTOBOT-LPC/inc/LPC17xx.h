/*******************************************************************************************************************************//**
 *
 * @file		LPC17xx.h
 * @brief    	CMSIS Cortex-M3 Core Peripheral Access Layer Header File for NXP LPC17xx Device Series
 * @note		Se adapta el formato al utilizado en Informatica II
 * @note		Se deja lo estrictamente necesario para el ejemplo aqui desarrollado.
 * 				El objetivo es que el alumno, agregue en este archivo lo necesario
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef __LPC17xx_H__
#define __LPC17xx_H__

/***********************************************************************************************************************************
 *** DEFINES
 **********************************************************************************************************************************/
/* IO definitions (access restrictions to peripheral registers) */
#define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#define   __O     volatile             /*!< Defines 'write only' permissions                */
#define   __IO    volatile             /*!< Defines 'read / write' permissions              */

/* Memory mapping of Cortex-M3 Hardware */
#define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
#define SysTick_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address              */

/* SysTick configuration struct */
#define SysTick             ((SysTick_Type *)       SysTick_BASE)     /*!< SysTick configuration struct      */



/* Direccion de inicio de los registros PINSEL*/

#define		PINSEL		((__IO uint32_t *) 0x4002C000UL)

#define		PINSEL0		PINSEL[0]	//!< PINSEL0------>P0[15:0] 		(0x4002C000)
#define		PINSEL1		PINSEL[1]	//!< PINSEL1------>P0[31:16] 		(0x4002C004)
#define		PINSEL2		PINSEL[2]	//!< PINSEL2------>P1[15:0] 		(0x4002C008)
#define		PINSEL3		PINSEL[3]	//!< PINSEL3------>P1[31:16] 		(0x4002C00C)
#define		PINSEL4		PINSEL[4]	//!< PINSEL4------>P2[15:0] 		(0x4002C010)
#define		PINSEL5		PINSEL[5]	//!< PINSEL5------>P2[31:16] 		NOT USED
#define		PINSEL6		PINSEL[6]	//!< PINSEL6------>P3[15:0]			NOT USED
#define		PINSEL7		PINSEL[7]	//!< PINSEL7------>P3[31:16] 		(0x4002C01C)
#define		PINSEL8		PINSEL[8]	//!< PINSEL8------>P4[15:0]			NOT USED
#define		PINSEL9		PINSEL[9]	//!< PINSEL9------>P4[31:16] 		(0x4002C024)

/* Direccion de inicio de los registros de modo de los pines del GPIO */
#define		PINMODE		((__IO uint32_t *) 0x4002C040UL)

#define		PINMODE0	PINMODE[0]		//!< 0x4002C040
#define		PINMODE1	PINMODE[1]		//!< 0x4002C044
#define		PINMODE2	PINMODE[2]		//!< 0x4002C048
#define		PINMODE3	PINMODE[3]		//!< 0x4002C04C
#define		PINMODE4	PINMODE[4]		//!< 0x4002C050
#define		PINMODE5	PINMODE[5]		//!< 0x4002C054
#define		PINMODE6	PINMODE[6]		//!< 0x4002C058
#define		PINMODE7	PINMODE[7]		//!< 0x4002C05C
#define		PINMODE9	PINMODE[9]		//!< 0x4002C064

/* Direccion de inicio de los registros de control del modo OPEN DRAIN */
#define		PINMODE_OD		( (__IO uint32_t *) 0x4002C068UL )

#define		PINMODE_OD0		PINMODE_OD[0]
#define		PINMODE_OD1		PINMODE_OD[1]
#define		PINMODE_OD2		PINMODE_OD[2]
#define		PINMODE_OD3		PINMODE_OD[3]
#define		PINMODE_OD4		PINMODE_OD[4]



/** LPC175x/6x Peripheral addresses and register set declarations */
#define LPC_GPIO0_BASE            0x2009C000
#define LPC_GPIO1_BASE            0x2009C020
#define LPC_GPIO2_BASE            0x2009C040
#define LPC_GPIO3_BASE            0x2009C060
#define LPC_GPIO4_BASE            0x2009C080
#define LPC_IOCON_BASE            0x4002C000
#define LPC_UART0_BASE            0x4000C000
#define LPC_UART1_BASE            0x40010000
#define LPC_UART2_BASE            0x40098000
#define LPC_UART3_BASE            0x4009C000


/* Assign LPC_* names to structures mapped to addresses */
#define LPC_GPIO                  ((LPC_GPIO_T             *) LPC_GPIO0_BASE)
#define LPC_GPIO1                 ((LPC_GPIO_T             *) LPC_GPIO1_BASE)
#define LPC_GPIO2                 ((LPC_GPIO_T             *) LPC_GPIO2_BASE)
#define LPC_GPIO3                 ((LPC_GPIO_T             *) LPC_GPIO3_BASE)
#define LPC_GPIO4                 ((LPC_GPIO_T             *) LPC_GPIO4_BASE)
#define LPC_GPIOINT               ((LPC_GPIOINT_T          *) LPC_GPIOINT_BASE)
#define LPC_IOCON                 ((LPC_IOCON_T            *) LPC_IOCON_BASE)
#define LPC_UART0                 ((LPC_UART_T            *) LPC_UART0_BASE)
#define LPC_UART1                 ((LPC_UART_T            *) LPC_UART1_BASE)
#define LPC_UART2                 ((LPC_UART_T            *) LPC_UART2_BASE)
#define LPC_UART3                 ((LPC_UART_T            *) LPC_UART3_BASE)

/* Registros definidos individualmente */
#define PCONP	    (*((__IO uint32_t *)0x400FC0C4UL))	/* Registro de Control de Alimentación de Periféricos */
#define PCLKSEL0	(*((__IO uint32_t *)0x400FC1A8UL))	/* Registro de Selección de Clock de Periféricos 0 */
#define PCLKSEL1	(*((__IO uint32_t *)0x400FC1ACUL))	/* Registro de Selección de Clock de Periféricos 1 */
#define ISER0		(*(__IO uint32_t *)0xE000E100UL)	/* Registro para habilitacion de interrupciones en el NVIC */

/***********************************************************************************************************************************
 *** FIN DEL MODULO
 **********************************************************************************************************************************/

#endif /* __LPC17xx_H__ */

/* ***************************************************************** */
/* File name:        gpio_hal.h                                     */
/* File description: This file has a couple of useful macros to      */
/*                   control and init the GPIO pins from the KLM25Z  */
/* Author name:      ddello                                          */
/* Creation date:    01abr2016                                       */
/* Revision date:    13abr2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_GPIO_GPIO_HAL_H_
#define SOURCES_GPIO_GPIO_HAL_H_

#include "KL25Z/es670_peripheral_board.h"

/**
 * Ungates the clock for a gpio port
 * @param PORT_ID the GPIO port id(A,B)
 */
#define GPIO_UNGATE_PORT(PORT_ID)\
	_GPIO_UNGATE_PORT(PORT_ID)

//Wrapper macro above is needed for argument expansion when using concatenation
#define _GPIO_UNGATE_PORT(PORT_ID)\
	/* un-gate port clock*/\
    SIM_SCGC5 |= SIM_SCGC5_PORT ## PORT_ID (CGC_CLOCK_ENABLED)

/**
 * inits a pin as GPIO in the given direction
 * @param PORT_ID the GPIO port id(A,B)
 * @param PIN_NUM pin number in port
 * @param DIR pin direction (GPIO_HIGH, GPIO_LOW)
 */
#define GPIO_INIT_PIN(PORT_ID, PIN_NUM, DIR)\
    _GPIO_INIT_PIN(PORT_ID, PIN_NUM, DIR)

//Wrapper macro above is needed for argument expansion when using concatenation
#define _GPIO_INIT_PIN(PORT_ID, PIN_NUM, DIR)\
    /* set pin as gpio */\
	PORT_PCR_REG(PORT ## PORT_ID , PIN_NUM) = PORT_PCR_MUX(GPIO_MUX_ALT);\
    /* Set pin direction */\
    if(DIR == GPIO_OUTPUT){\
    	GPIO ## PORT_ID ## _PDDR |= GPIO_PDDR_PDD(0x01 << PIN_NUM);\
    }else{\
    	GPIO ## PORT_ID ## _PDDR &= ~GPIO_PDDR_PDD(0x01 << PIN_NUM);\
    }


/**
 * Writes a pin with the given value
 * @param PORT_ID the GPIO port id(A,B)
 * @oaram PIN_NUM pin number in port
 * @param VAL pin value (GPIO_HIGH, GPIO_LOW)
 */
#define GPIO_WRITE_PIN(PORT_ID, PIN_NUM, VAL)\
    _GPIO_WRITE_PIN(PORT_ID, PIN_NUM, VAL)

//Wrapper macro above is needed for argument expansion when using concatenation
#define _GPIO_WRITE_PIN(PORT_ID, PIN_NUM, VAL)\
	if(VAL == GPIO_HIGH){\
		GPIO ## PORT_ID ## _PSOR = GPIO_PSOR_PTSO( (0x01U << PIN_NUM) );\
	}else{\
		GPIO ## PORT_ID ## _PCOR = GPIO_PCOR_PTCO( (0x01U << PIN_NUM) );\
	}

/**
 * Writes the given value to the pins given in the MASK
 * @param PORT_ID the GPIO port id(A,B)
 * @param MASK 31 bit Mask with 1 in the bits corresponding to the pins of interest.
 * @param VAL pins value (GPIO_HIGH, GPIO_LOW)
 */
#define GPIO_WRITE_MASK(PORT_ID, MASK, VAL)\
    _GPIO_WRITE_MASK(PORT_ID, MASK, VAL)

#define _GPIO_WRITE_MASK(PORT_ID, MASK, VAL)\
	if(VAL == GPIO_HIGH){\
		GPIO ## PORT_ID ## _PSOR = GPIO_PSOR_PTSO(MASK);\
	}else{\
		GPIO ## PORT_ID ## _PCOR = GPIO_PCOR_PTCO(MASK);\
	}


/**
 * Reads the status of a GPIO PIN
 * @param PORT_ID the GPIO port id(A,B)
 * @param PIN_NUM pin number in port
 * @param VAL pin value (GPIO_HIGH, GPIO_LOW)
 */
#define GPIO_READ_PIN(PORT_ID, PIN_NUM)\
    _GPIO_READ_PIN(PORT_ID, PIN_NUM)

//Wrapper macro above is needed for argument expansion when using concatenation
#define _GPIO_READ_PIN(PORT_ID, PIN_NUM)\
		( ((GPIO ## PORT_ID ## _PDIR & (0x01u << PIN_NUM)) >> PIN_NUM) )

/**
 * Reads the driven status of a output GPIO PIN
 * @param PORT_ID the GPIO port id(A,B)
 * @param PIN_NUM pin number in port
 * @param VAL pin value (GPIO_HIGH, GPIO_LOW)
 */
#define GPIO_GET_OUTPUT_STATE(PORT_ID, PIN_NUM)\
    _GPIO_GET_OUTPUT_STATE(PORT_ID, PIN_NUM)

//Wrapper macro above is needed for argument expansion when using concatenation
#define _GPIO_GET_OUTPUT_STATE(PORT_ID, PIN_NUM)\
		( ((GPIO ## PORT_ID ## _PDOR & (0x01u << PIN_NUM)) >> PIN_NUM) )

#endif /* SOURCES_GPIO_GPIO_HAL_H_ */

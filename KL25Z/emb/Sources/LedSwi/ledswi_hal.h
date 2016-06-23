/* ***************************************************************** */
/* File name:        ledswi_hal.h                                    */
/* File description: Header file containing the function/methods     */
/*                   prototypes of ledswi.c                          */
/* Author name:      dloubach                                        */
/* Creation date:    09jan2015                                       */
/* Revision date:    13abr2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_LEDSWI_LEDSWI_HAL_H_
#define SOURCES_LEDSWI_LEDSWI_HAL_H_

#include "KL25Z/es670_peripheral_board.h"


#define MAX_LED_SWI        04

typedef enum
{
    LS_1 =	LS1_PIN,
	LS_2 = 	LS2_PIN,
	LS_3 = 	LS3_PIN,
	LS_4 = 	LS4_PIN,
	UNKNOWN = -1
} ledswi_pin_type_e;

typedef enum
{
    SWITCH_ON,
    SWITCH_OFF
} switch_status_type_e;

typedef enum
{
    LED_OFF,
    LED_ON
} led_status_type_e;

/**
 * As the hardware board was designed with LEDs/Switches sharing
 * 	the same pins, this method configures how many LEDS and switches
 * 	will be available for the application
 * @param cLedNum num of LEDs
 * @param cSwitchNum num of Switches (cLedNum + cSwitchNum <= MAX_LED_SWI)
 */
void ledswi_initLedSwitch(char cLedNum, char cSwitchNum);


/**
 * initializes pin as LED
 * @param ePin which pin {1..4}
 */
void ledswi_initLed(ledswi_pin_type_e ePin);

/**
 * initializes pin as SWITCH
 * @param ePin which pin {1..4}
 */
void ledswi_initSwitch(ledswi_pin_type_e ePin);

/**
 * set the led ON
 * @param eLedPin which LED {1..4}
 */
void ledswi_setLed(ledswi_pin_type_e eLedPin);



/**
 * set the led OFF
 * @param eLedPin which LED {1..4}
 */
void ledswi_clearLed(ledswi_pin_type_e eLedPin);


/**
 * return the led status
 *
 * @param eLedPin which LED {1..4}
 *
 * @return If the led is ON or OFF
 */
led_status_type_e ledswi_getLedStatus(ledswi_pin_type_e eLedPin);

/**
 * return the switch status
 *
 * @param eSwPin which Switch {1..4}
 *
 * @return If the switch is ON or OFF
 */
switch_status_type_e ledswi_getSwitchStatus(ledswi_pin_type_e eSwPin);
#endif /* SOURCES_LEDSWI_LEDSWI_HAL_H_ */

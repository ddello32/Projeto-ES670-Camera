/* ***************************************************************** */
/* File name:        ledswi_hal.c                                    */
/* File description: This file has a couple of useful functions to   */
/*                   control LEDs and Switches from peripheral board */
/* Author name:      dloubach                                        */
/* Creation date:    20jan2015                                       */
/* Revision date:    13abr2016                                       */
/* ***************************************************************** */

#include "ledswi_hal.h"
#include "GPIO/gpio_hal.h"

#define USING_OPENSDA_DEBUG

/**
 * As the hardware board was designed with LEDs/Switches sharing
 * 	the same pins, this method configures how many LEDS and switches
 * 	will be available for the application
 * @param cLedNum num of LEDs
 * @param cSwitchNum num of Switches (cLedNum + cSwitchNum <= MAX_LED_SWI)
 */
void ledswi_initLedSwitch(char cLedNum, char cSwitchNum)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

    /* set pin as gpio */
#ifndef USING_OPENSDA_DEBUG
    PORTA_PCR1 = PORT_PCR_MUX(LS1_ALT);
    PORTA_PCR2 = PORT_PCR_MUX(LS2_ALT);
#endif
    PORTA_PCR4 = PORT_PCR_MUX(LS3_ALT);
    PORTA_PCR5 = PORT_PCR_MUX(LS4_ALT);


    /* check if the number to configured is according to
    hardware dev kit */
    if((cLedNum + cSwitchNum) <= MAX_LED_SWI)
    {
        /* max number of peripherals to configure is ok, carry on */
        switch(cSwitchNum)
        {
            case 0:
                /* no switches in system configuration */
                /* all leds */
                GPIOA_PDDR |= GPIO_PDDR_PDD(LS1_DIR_OUTPUT | LS2_DIR_OUTPUT | LS3_DIR_OUTPUT | LS4_DIR_OUTPUT);
                break;

            case 1:
                /* just 1 switch */
                GPIOA_PDDR |= GPIO_PDDR_PDD(LS2_DIR_OUTPUT | LS3_DIR_OUTPUT | LS4_DIR_OUTPUT);
                GPIOA_PDDR &= ~GPIO_PDDR_PDD(LS1_DIR_INPUT);
                break;

            case 2:
                /* just 2 switches */
                GPIOA_PDDR |= GPIO_PDDR_PDD(LS3_DIR_OUTPUT | LS4_DIR_OUTPUT);
                GPIOA_PDDR &= ~GPIO_PDDR_PDD(LS1_DIR_INPUT | LS2_DIR_INPUT);
                break;

            case 3:
                /* 3 switches */
                GPIOA_PDDR |= GPIO_PDDR_PDD(LS4_DIR_OUTPUT);
                GPIOA_PDDR &= ~GPIO_PDDR_PDD(LS1_DIR_INPUT | LS2_DIR_INPUT | LS3_DIR_INPUT);
                break;

            case 4:
                /* 4 switches */
                GPIOA_PDDR &= ~GPIO_PDDR_PDD(LS1_DIR_INPUT | LS2_DIR_INPUT | LS3_DIR_INPUT | LS4_DIR_INPUT);
                break;
        } /* switch(cSwitchNum) */

    } /* if((cLedNum + cSwitchNum) <= MAX_LED_SWI) */

}


/**
 * initializes pin as LED
 * @param ePin which pin {1..4}
 */
void ledswi_initLed(ledswi_pin_type_e ePin){
	GPIO_INIT_PIN(LS_PORT_ID, ePin, GPIO_OUTPUT);
}

/**
 * initializes pin as SWITCH
 * @param ePin which pin {1..4}
 */
void ledswi_initSwitch(ledswi_pin_type_e ePin){
	GPIO_INIT_PIN(LS_PORT_ID, ePin, GPIO_INPUT);
}

/**
 * set the led ON
 * @param eLedPin which LED {1..4}
 */
void ledswi_setLed(ledswi_pin_type_e eLedPin)
{
   GPIO_WRITE_PIN(LS_PORT_ID, eLedPin, GPIO_HIGH);
}



/**
 * set the led OFF
 * @param eLedPin which LED {1..4}
 */
void ledswi_clearLed(ledswi_pin_type_e eLedPin)
{
   GPIO_WRITE_PIN(LS_PORT_ID, eLedPin, GPIO_LOW);
}


/**
 * return the led status
 *
 * @param eLedPin which LED {1..4}
 *
 * @return If the led is ON or OFF
 */
led_status_type_e ledswi_getLedStatus(ledswi_pin_type_e eLedPin){
	  led_status_type_e lstReturn = LED_OFF;
	  if(GPIO_GET_OUTPUT_STATE(LS_PORT_ID, eLedPin) == LED_ON){
		  lstReturn = LED_ON;
	  }
	  return(lstReturn);
}

/**
 * return the switch status
 *
 * @param eSwPin which Switch {1..4}
 *
 * @return If the switch is ON or OFF
 */
switch_status_type_e ledswi_getSwitchStatus(ledswi_pin_type_e eSwPin){
	  switch_status_type_e sstReturn = SWITCH_OFF;
	  if(GPIO_READ_PIN(LS_PORT_ID, eSwPin) == SWITCH_ON){
		  sstReturn = SWITCH_ON;
	  }
	  return(sstReturn);
}

/* ***************************************************************** */
/* File name:        buzzer_hal.c                                    */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related buzzer from the peripheral board        */
/* Author name:      dloubach                                        */
/* Creation date:    12jan2016                                       */
/* Revision date:    13abr2016                                       */
/* ***************************************************************** */

#include "GPIO/gpio_hal.h"
#include "buzzer_hal.h"
#include "KL25Z/es670_peripheral_board.h"
#include "PIT/pit_hal.h"

static volatile int interrupt_counter = -1;

/**
 * Initialize the buzzer device
 */
void buzzer_init(void)
{
	GPIO_UNGATE_PORT(BUZZER_PORT_ID);
	GPIO_INIT_PIN(BUZZER_PORT_ID, BUZZER_PIN, GPIO_OUTPUT);
	pit_enable();
}



/**
 * Clear the buzzer
 */
void buzzer_clearBuzz(void)
{
    GPIO_WRITE_PIN(BUZZER_PORT_ID, BUZZER_PIN, GPIO_LOW);
}



/**
 * Set the buzzer
 */
void buzzer_setBuzz(void)
{
	GPIO_WRITE_PIN(BUZZER_PORT_ID, BUZZER_PIN, GPIO_HIGH);
}

/**
 * Handler for buzzer interruptions
 */
void _buzzer_interrupt_handler(void){
	static volatile unsigned short usBusOn = 0;
	if(!usBusOn){
		buzzer_setBuzz();
	}else{
		buzzer_clearBuzz();
	}
	usBusOn = !usBusOn;
	//If not in undefined mode decrease counter
	if(interrupt_counter > 0){
		interrupt_counter--;
	}
	//Stop interruptions when signal duration is finished
	if(!interrupt_counter){
		buzzer_stopPeriodic();
	}
	//Mark interruption as handled
	pit_mark_interrupt_handled(BUZZER_PIT_TIMER_NUMB);
}

/**
 * Starts the buzzer with the specified period
 *
 * @param uiBuzzFreq_hz The frequency of the buzzer signal, in Hz
 * @param uiDuration_ms How many milliseconds the buzzer should be producing sound
 * 							if 0 buzzer will stay on indeterminaly.
 */
void buzzer_initPeriodic(unsigned int uiBuzzFreq_hz, unsigned int uiDuration_ms){
	unsigned int uiPeriod_us = 500000/uiBuzzFreq_hz;	/* 50% duty cycle */
	if(uiDuration_ms > 0){
		interrupt_counter = uiDuration_ms/(uiPeriod_us/1000);
	}else{
		interrupt_counter = -1;
	}
	//Init timer 1
	pit_start_timer_interrupt(BUZZER_PIT_TIMER_NUMB, uiPeriod_us, &_buzzer_interrupt_handler);
}

/**
 * Stops any periodic buzzer signal
 */
void buzzer_stopPeriodic(void){
	interrupt_counter = -1;
	pit_stop_timer_interrupt(BUZZER_PIT_TIMER_NUMB);
	buzzer_clearBuzz();
}

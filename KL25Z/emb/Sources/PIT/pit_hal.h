/* ***************************************************************** */
/* File name:        pit_hal.h                                       */
/* File description: Header file containing the functions/methods    */
/*                  interfaces for handling the Periodic Interruption*/
/*                  timer module                                	 */
/* Author name:      ddello	                                         */
/* Creation date:    10abr2016                                       */
/* Revision date:    10mai2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_PIT_PIT_HAL_H_
#define SOURCES_PIT_PIT_HAL_H_

/**
 * Enables Periodic Interruption Timer module.
 * (With the stop on debug flag set to on)
 */
void pit_enable(void);

/**
 * Start interruptions for given timer, unchained mode.
 * Timer interruptions are masked.
 *
 * @param usTimer_numb 	The number for the desired timer (0,1)
 * @param uiTimer_period_ms  The number of microseconds between interrupts
 * @param fpInterrupt_handler   	Timer interrupt handler routine address pointer
 */
void pit_start_timer_interrupt(unsigned short usTimer_numb, unsigned int uiTimer_period_us, void (*fpInterrupt_handler)(void));

/**
 * Stop interruptions for given timer, unchained mode.
 *
 * @param usTimer_numb 	The number for the desired timer (0,1)
 */
void pit_stop_timer_interrupt(unsigned short usTimer_numb);

/**
 * Mark interruption as handled for the given timer, this should be called by timer
 * interruption handlers once they are finished.
 *
 * @param usTimer_numb 	The number for the desired timer (0,1)
 */
void pit_mark_interrupt_handled(unsigned short usTimer_numb);

/**
 * Pit interruption handler. Checks what timer caused the interruption and call the
 * correct timer interruption handler.
 */
void PIT_IRQHandler(void);

/**
 * Disables PIT interruptions temporarily
 */
void pit_mask_interrupts();

/**
 * Re-enables PIT interruptions
 */
void pit_unmask_interrupts();
#endif /* SOURCES_PIT_PIT_HAL_H_ */

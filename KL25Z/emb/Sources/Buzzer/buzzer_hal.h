/* ***************************************************************** */
/* File name:        buzzer_hal.h                                    */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for handling BUZZER from the         */
/*                   peripheral board                                */
/* Author name:      dloubach                                        */
/* Creation date:    12jan2016                                       */
/* Revision date:    13abr2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_BUZZER_HAL_H_
#define SOURCES_BUZZER_HAL_H_

/**
 * Initialize the buzzer device
 */
void buzzer_init(void);


/**
 * Clear the buzzer
 */
void buzzer_clearBuzz(void);


/**
 * Set the buzzer
 */
void buzzer_setBuzz(void);

/**
 * Starts the buzzer with the specified period
 *
 * @param uiBuzzFreq_hz The frequency of the buzzer signal, in Hz
 * @param uiDuration_ms How many milliseconds the buzzer should be producing sound
 * 							if 0 buzzer will stay on indeterminaly.
 */
void  buzzer_initPeriodic(unsigned int uiBuzzFreq_hz, unsigned int uiDuration_ms);

/**
 * Stops any periodic buzzer signal
 */
void buzzer_stopPeriodic(void);


#endif /* SOURCES_BUZZER_HAL_H_ */

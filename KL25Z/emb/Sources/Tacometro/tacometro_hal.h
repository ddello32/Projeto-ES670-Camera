/* ***************************************************************** */
/* File name:        tacometro_hal.h                                 */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for tacometer 						 */
/* Author name:      ddello		                                     */
/* Creation date:    13maio2016                                      */
/* Revision date:    13maio2016                                      */
/* ***************************************************************** */

#ifndef SOURCES_TACOMETRO_HAL_H_
#define SOURCES_TACOMETRO_HAL_H_

/**
 * Initialize the tacometer module
 */
void tacometro_init(void);


/**
 * @param uiPeriod Time ellapsed since last getSpeedCall in ms
 *
 * @return current tacometer speed in rps
 */
unsigned int tacometro_getSpeed(unsigned int uiPeriod);

#endif /* SOURCES_TACOMETRO_HAL_H_ */

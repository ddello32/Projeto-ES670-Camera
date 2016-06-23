/* ***************************************************************** */
/* File name:        heater_hal.h                                    */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for heater control	  	     */
/* Author name:      ddello		                             */
/* Creation date:    14jun2016                                       */
/* Revision date:    14jun2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_HEATER_HAL_H_
#define SOURCES_HEATER_HAL_H_

#include <stdint.h>

/**
 * Initialize the heater module
 */
void heater_initHeater(void);


/**
 * Set the heater intensity
 *
 * @param uiIntensity heater intensity from 0 (stopped) to 0xFFFF (max)
 */
void heater_setIntensity(uint16_t uiIntensity);

#endif /* SOURCES_HEATER_HAL_H_ */

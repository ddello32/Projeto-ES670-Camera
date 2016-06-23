/* ***************************************************************** */
/* File name:        cooler_hal.h                                    */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for cooler control	  			     */
/* Author name:      ddello		                                     */
/* Creation date:    13maio2016                                      */
/* Revision date:    13maio2016                                      */
/* ***************************************************************** */

#ifndef SOURCES_SERVO_HAL_H_
#define SOURCES_SERVO_HAL_H_

#include <stdint.h>

/**
 * Initialize the cooler module
 */
void servo_init(void);


/**
 * Set the cooler velocity
 *
 * @param uiVelocity Cooler velocity from 0 (stopped) to 0xFFFF (max)
 */
void servo_setAngle(uint16_t uiAngle);

#endif /* SOURCES_SERVO_HAL_H_ */

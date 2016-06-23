/* ***************************************************************** */
/* File name:        tempSesnor_hal.h                                */
/* File description: Header file containing the functions/methods    */
/*                   for temperature sensor							 */
/* Author name:      ddello		                             		 */
/* Creation date:    16jun2016                                       */
/* Revision date:    16jun2016                                       */
/* ***************************************************************** */

#include <stdint.h>

/**
 * Init temperature sensor
 */
void tempSensor_init();

/**
 * Updates temperature sensor readings and starts a new conversion
 */
void tempSensor_executeTask();

/**
 * Checks if last triggered conversion is finished
 *
 * @return 1 if conversion is complete, 0 otherwise
 */
short tempSensor_isConversionFinished();

/**
 * @return Raw result from last successful conversion
 */
uint16_t tempSensor_getLastConversionRawResult();

/**
 * @return Last read temperature (in Celcius Degrees)
 */
int tempSensor_getLastConversionTemperature();

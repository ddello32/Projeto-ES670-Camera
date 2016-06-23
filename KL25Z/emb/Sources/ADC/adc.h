/*
 * File name: adc.h
 *
 *  Created on: 06/06/2016
 *      Author: msoliveira
 */

#include <stdint.h>

/**
 *  Configure ADC module
 */
void adc_initADCModule(void);

/**
 * Init conversion from A to D
 */
void adc_initConvertion(void);

/**
 * Check if conversion is done
 * @return 1 if done, 0 otherwise
 */
short adc_isAdcDone(void);

/**
 * Retrieve converted value
 * @return The conversion result
 */
uint16_t adc_getConversionValue(void);

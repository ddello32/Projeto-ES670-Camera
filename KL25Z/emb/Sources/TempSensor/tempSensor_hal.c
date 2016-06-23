/* ***************************************************************** */
/* File name:        tempSesnor_hal.c                                */
/* File description: File containing the functions/methods    		 */
/*                   for temperature sensor							 */
/* Author name:      ddello		                             		 */
/* Creation date:    16jun2016                                       */
/* Revision date:    16jun2016                                       */
/* ***************************************************************** */

#include "tempSensor_hal.h"
#include "ADC/adc.h"

#define TEMP_ADC_TRANSF_EQ_PARAM_A 0.4073
#define TEMP_ADC_TRANSF_EQ_PARAM_B -123.75

static uint16_t rawReading = 0;

/**
 * Init temperature sensor
 */
void tempSensor_init(){
	adc_initADCModule();
}

/**
 * Updates temperature sensor readings and starts a new conversion
 */
void tempSensor_executeTask(){
	if(tempSensor_isConversionFinished()){
		rawReading = adc_getConversionValue();
	}
	adc_initConvertion();
}

/**
 * Checks if last triggered conversion is finished
 *
 * @return 1 if conversion is complete, 0 otherwise
 */
short tempSensor_isConversionFinished(){
	return adc_isAdcDone();
}

/**
 * @return Raw result from last successful conversion
 */
uint16_t tempSensor_getLastConversionRawResult(){
	return rawReading;
}

/**
 * @return Last read temperature (in Celcius Degrees)
 */
int tempSensor_getLastConversionTemperature(){
	return TEMP_ADC_TRANSF_EQ_PARAM_A * tempSensor_getLastConversionRawResult() + TEMP_ADC_TRANSF_EQ_PARAM_B;
}

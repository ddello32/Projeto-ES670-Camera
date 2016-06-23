/*
 * File name: adc.c
 *
 *  Created on: 06/06/2016
 *      Author: msoliveira
 */

#include "KL25Z/es670_peripheral_board.h"

#define ADC0_SC1A_COCO (ADC0_SC1A >> 7)

/**
 *  Configure ADC module
 */
void adc_initADCModule(void) {
	/* un-gate port clock*/
	SIM_SCGC6 |= SIM_SCGC6_ADC0(CGC_CLOCK_ENABLED);	//Enable clock for ADC

    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED);

    /* set pin as ADC In */
    PORT_PCR_REG(ADC_PORT_BASE_PNT, ADC_VOLT_PIN) = PORT_PCR_MUX(ADC_VOLT_PIN_MUX_ALT);	  //Voltage Sensor
    PORT_PCR_REG(ADC_PORT_BASE_PNT, ADC_TEMP_PIN) = PORT_PCR_MUX(ADC_TEMP_PIN_MUX_ALT);   //Temperature Sensor

    ADC_WR_CFG1(ADC_NUM_BASE_PNT,
    		(
    				ADC_CFG1_ADICLK(0x1)  		// bus/2 clock selection
    				| ADC_CFG1_MODE(0x3)  		// 16-bit Conversion mode selection
					| ADC_CFG1_ADLSMP(0x0) 		// Short sample time configuration
					| ADC_CFG1_ADIV(0x0) 		// Clock Divide Select (Divide by 1)
					| ADC_CFG1_ADLPC(0x1)		// Normal power Configuration
			)
	);

    ADC_WR_SC2(ADC_NUM_BASE_PNT,
    		(
    				ADC_SC2_REFSEL(0x0) 			//external pins
					| ADC_SC2_DMAEN(0x0) 			//dma disabled
					| ADC_SC2_ACFE(0x0) 			//compare disabled
					| ADC_SC2_ADTRG(0x0)			//sw trigger
			)
	);

    ADC_WR_CFG2(ADC_NUM_BASE_PNT,
    		(
    				ADC_CFG2_ADLSTS(0) 				// default time
    				| ADC_CFG2_ADHSC(0) 			// normal conversion sequence
					| ADC_CFG2_ADACKEN(0) 			// adack clock disabled
					| ADC_CFG2_MUXSEL(ADC_MUX_IDX)	// 'a' channels
			)
	);
}


/**
 * Init conversion from A to D
 */
void adc_initConvertion(void) {
	ADC_WR_SC1(ADC_NUM_BASE_PNT, ADC_MUX_IDX,
		(
			ADC_SC1_ADCH(ADC_CHANNEL_SEL) 			//Channel 4 - SE4A
			| ADC_SC1_DIFF(0) 						//single ended
			| ADC_SC1_AIEN(0)						//interrupt disabled
		)
	);
}

/**
 * Check if conversion is done
 * @return 1 if done, 0 otherwise
 */
short adc_isAdcDone(void)
{
	return ADC_BRD_SC1_COCO(ADC_NUM_BASE_PNT, ADC_MUX_IDX);
}

/**
 * Retrieve converted value
 * @return The conversion result
 */
uint16_t adc_getConversionValue(void)
{
	return ADC_RD_R(ADC_NUM_BASE_PNT, ADC_MUX_IDX); // return the register value that keeps the result of convertion
}

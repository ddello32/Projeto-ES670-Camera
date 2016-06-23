/* ***************************************************************** */
/* File name:        heater_hal.c                                    */
/* File description: File containing the functions/methods           */
/*                   for heater control                              */
/* Author name:      ddello		                             		 */
/* Creation date:    14jun2016                                       */
/* Revision date:    14jun2016                                       */
/* ***************************************************************** */

#include "heater_hal.h"
#include "KL25Z/es670_peripheral_board.h"
#include "GPIO/gpio_hal.h"

/**
 * Initialize the heater module
 */
void heater_initHeater(void){
	/* Init HEATER pin */
	SIM_SCGC5 |= SIM_SCGC5_PORTA(1u);
	PORT_PCR_REG(HEATER_PORT_BASE_PNT , HEATER_PIN) = PORT_PCR_MUX(HEATER_PIN_MUX_ALT);

	/* INIT TPM */
	//Init TPM Clock source as OSCERCLOCK
	SIM_WR_SOPT2_TPMSRC(SIM,0x2);
	//Enable clock to TPM1
	SIM_SCGC6 |= SIM_SCGC6_TPM1(0x1);
	//PWM mode
	TPM_WR_SC_CPWMS(HEATER_TPM_BASE_PNT, 0x0);	//Edge Aligned
	/* Channel mode configuration should be done with the channel disabled and need acknowledge*/
	TPM_WR_CnSC(HEATER_TPM_BASE_PNT, HEATER_TPM_CHANNEL_INDEX, TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
    /* Wait till mode change is acknowledged */
    while (!
    		(
				TPM_RD_CnSC(HEATER_TPM_BASE_PNT, HEATER_TPM_CHANNEL_INDEX)
				& (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1))
			)
		  );
	//Same period as OSCRCLK
	TPM_WR_MOD(HEATER_TPM_BASE_PNT, 0xFFFE);
	//Duty cycle
	TPM_WR_CnV_VAL(HEATER_TPM_BASE_PNT, HEATER_TPM_CHANNEL_INDEX, 0);
	//Prescale 1:1
	TPM_WR_SC_PS(HEATER_TPM_BASE_PNT, 0x0);
	//Select LTPM Clock Source for TPM module
	TPM_WR_SC_CMOD(HEATER_TPM_BASE_PNT, 0x1);
}


/**
 * Set the heater intensity
 *
 * @param uiIntensity heater intensity from 0 (stopped) to 0xFFFF (max)
 */
void heater_setIntensity(uint16_t uiIntensity){
	TPM_WR_CnV_VAL(HEATER_TPM_BASE_PNT, HEATER_TPM_CHANNEL_INDEX, uiIntensity);
}

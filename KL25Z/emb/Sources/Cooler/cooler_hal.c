/* ***************************************************************** */
/* File name:        cooler_hal.c                                    */
/* File description: File containing the functions/methods   		 */
/*                   for cooler control	  						     */
/* Author name:      ddello		                                     */
/* Creation date:    13maio2016                                      */
/* Revision date:    13maio2016                                      */
/* ***************************************************************** */

#include "cooler_hal.h"
#include "KL25Z/es670_peripheral_board.h"
#include "GPIO/gpio_hal.h"

/**
 * Initialize the cooler module
 */
void cooler_initCooler(void){
	/* Init cooler pin */
	SIM_SCGC5 |= SIM_SCGC5_PORTA(1u);
	PORT_PCR_REG(COOLER_PORT_BASE_PNT , COOLER_PIN) = PORT_PCR_MUX(COOLER_PIN_MUX_ALT);

	/* INIT TPM */
	//Init TPM Clock source as OSCERCLOCK
	SIM_WR_SOPT2_TPMSRC(SIM,0x2);
	//Enable clock to TPM1
	SIM_SCGC6 |= SIM_SCGC6_TPM1(0x1);
	//PWM mode
	TPM_WR_SC_CPWMS(COOLER_TPM_BASE_PNT, 0x0);	//Edge Aligned
	/* Channel mode configuration should be done with the channel disabled and need acknowledge*/
	TPM_WR_CnSC(COOLER_TPM_BASE_PNT, COOLER_TPM_CHANNEL_INDEX, TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
    /* Wait till mode change is acknowledged */
    while (!
    		(
				TPM_RD_CnSC(COOLER_TPM_BASE_PNT, COOLER_TPM_CHANNEL_INDEX)
				& (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1))
			)
		  );
	//Same period as OSCRCLK
	TPM_WR_MOD(COOLER_TPM_BASE_PNT, 0xFFFE);
	//Duty cycle
	TPM_WR_CnV_VAL(COOLER_TPM_BASE_PNT, COOLER_TPM_CHANNEL_INDEX, 0);
	//Prescale 1:1
	TPM_WR_SC_PS(COOLER_TPM_BASE_PNT, 0x0);
	//Select LTPM Clock Source for TPM module
	TPM_WR_SC_CMOD(COOLER_TPM_BASE_PNT, 0x1);
}


/**
 * Set the cooler velocity
 *
 * @param uiVelocity Cooler velocity from 0 (stopped) to 0xFFFF (max)
 */
void cooler_setVelocity(uint16_t uiVelocity){
	TPM_WR_CnV_VAL(COOLER_TPM_BASE_PNT, COOLER_TPM_CHANNEL_INDEX, uiVelocity);
}

/**
 * Get the cooler PWM duty cicle in %.
 *
 * @return Duty Cicle (0 to 100)
 */
unsigned short cooler_getDutyCicle(){
	return 	(TPM_RD_CnV_VAL(COOLER_TPM_BASE_PNT, COOLER_TPM_CHANNEL_INDEX)*100)/0xFFFF;
}

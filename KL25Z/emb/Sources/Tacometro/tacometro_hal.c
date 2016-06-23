/* ***************************************************************** */
/* File name:        tacometro_hal.c                                 */
/* File description: File containing the functions/methods           */
/*                   for tacometer				     */
/* Author name:      ddello		                             */
/* Creation date:    13maio2016                                      */
/* Revision date:    13maio2016                                      */
/* ***************************************************************** */
#include "tacometro_hal.h"
#include "KL25Z/es670_peripheral_board.h"

#define TACOMETRO_SCALER 7

/**
 * Initialize the tacometer module
 */
void tacometro_init(void){
	/* Init tacometer pin */
	SIM_SCGC5 |= SIM_SCGC5_PORTE(1u);
	PORT_PCR_REG(TACOMETRO_PORT_BASE_PNT , TACOMETRO_PIN) = PORT_PCR_MUX(TACOMETRO_PIN_ALT);

	/* INIT TPM */
	//Init TPM Clock source as OSCERCLOCK
	SIM_WR_SOPT2_TPMSRC(SIM,0x2);
	//TPM0 ClockIn0
	SIM_WR_SOPT4_TPM0CLKSEL(SIM, 0x0);
	//Enable clock to TPM0
	SIM_SCGC6 |= SIM_SCGC6_TPM0(0x1);
	//Select External Clock Source for TPM module
	TPM_WR_SC_CMOD(TACOMETRO_TPM_BASE, 0x2);
	//Prescale 1:1
	TPM_WR_SC_PS(TACOMETRO_TPM_BASE, 0x0);
	//Init mod as maximum value
	TPM_WR_MOD(TACOMETRO_TPM_BASE, 0xFFFF);
}


/**
 * @param uiPeriod Time ellapsed since last getSpeedCall in ms
 *
 * @return current tacometer speed in rps
 */
unsigned int tacometro_getSpeed(unsigned int uiPeriod){
	unsigned int ret = TPM_RD_CNT(TACOMETRO_TPM_BASE)/TACOMETRO_SCALER*1000/uiPeriod;
	TPM_WR_CNT(TACOMETRO_TPM_BASE, 0x0);	/*Reset counter */
	return ret;
}

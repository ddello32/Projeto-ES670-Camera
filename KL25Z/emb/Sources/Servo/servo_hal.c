#include "servo_hal.h"
#include "KL25Z/es670_peripheral_board.h"
#include "Util/util.h"

/**
 * Initialize the cooler module
 */
void servo_init(void){
	/* Init cooler pin */
	SIM_SCGC5 |= SIM_SCGC5_PORTD(1u);
	PORT_PCR_REG(SERVO_PORT_BASE_PNT , SERVO_PIN) = PORT_PCR_MUX(SERVO_PIN_MUX_ALT);

	/* INIT TPM */
	//Init TPM Clock source as OSCERCLOCK
	SIM_WR_SOPT2_TPMSRC(SIM,0x2);
	//Enable clock to TPM0
	SIM_SCGC6 |= SIM_SCGC6_TPM0(0x1);
	//PWM mode
	TPM_WR_SC_CPWMS(SERVO_TPM_BASE_PNT, 0x0);	//Edge Aligned
	/* Channel mode configuration should be done with the channel disabled and need acknowledge*/
	TPM_WR_CnSC(SERVO_TPM_BASE_PNT, SERVO_TPM_CHANNEL_INDEX, TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	/* Wait till mode change is acknowledged */
	while (!
			(
				TPM_RD_CnSC(SERVO_TPM_BASE_PNT, SERVO_TPM_CHANNEL_INDEX)
				& (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1))
			)
		  );
	//Same period as OSCRCLK
	TPM_WR_MOD(SERVO_TPM_BASE_PNT, 0x04E1);
	//Duty cycle
	TPM_WR_CnV_VAL(SERVO_TPM_BASE_PNT, SERVO_TPM_CHANNEL_INDEX, 0x3E);
	//Prescale 1:128
	TPM_WR_SC_PS(SERVO_TPM_BASE_PNT, 0x7);
	//Select LTPM Clock Source for TPM module
	TPM_WR_SC_CMOD(SERVO_TPM_BASE_PNT, 0x0);
}


/**
 * Set the cooler velocity
 *
 * @param uiVelocity Cooler velocity from 0 (stopped) to 0xFFFF (max)
 */
void servo_setAngle(uint16_t uiAngle){
	TPM_WR_SC_CMOD(SERVO_TPM_BASE_PNT, 0x1);
	int dc = (uiAngle*(0x7C - 0x3E))/180 + 0x3E;
	TPM_WR_CnV_VAL(SERVO_TPM_BASE_PNT, SERVO_TPM_CHANNEL_INDEX, dc);
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	util_genDelay10ms();
	TPM_WR_SC_CMOD(SERVO_TPM_BASE_PNT, 0x0);
}

/* ***************************************************************** */
/* File name:        sevenseg_hal.c                                  */
/* File description: File containing the functions/methods           */
/*                   for handling SEVEN SEGMENT DISPLAY              */
/*                    from the peripheral board                      */
/* Author name:      ddello	                                         */
/* Creation date:    18mar2016                                       */
/* Revision date:    13abr2016          	                         */
/* ***************************************************************** */

#include "GPIO/gpio_hal.h"
#include "sevenseg_hal.h"
#include "math.h"
#include "KL25Z/es670_peripheral_board.h"
#include "PIT/pit_hal.h"

#define SEV_SEG_SEGMENT_MASK GPIO_HIGH << SEGA_PIN | GPIO_HIGH << SEGB_PIN | GPIO_HIGH << SEGC_PIN | GPIO_HIGH << SEGD_PIN | GPIO_HIGH << SEGE_PIN | GPIO_HIGH << SEGF_PIN | GPIO_HIGH << SEGG_PIN | GPIO_HIGH << SEGDP_PIN
#define SEV_SEG_DISP_MASK GPIO_HIGH << SEG_DISP1_PIN | GPIO_HIGH << SEG_DISP2_PIN | GPIO_HIGH << SEG_DISP3_PIN | GPIO_HIGH << SEG_DISP4_PIN

#define SEVEN_SEG_PIT_PERIOD	3125		/*3.125ms*/

static unsigned short usIsHex = 0;
static unsigned int uiPrintVal = 0;

static seven_segment_seg_type_e epSeg_Matrix[MAX_DISP_NUMBER][MAX_SEGMENT_NUMBER+1];
/**
 * Interrupt handler for updating in display configuration
 */
void _sevenseg_interrupt_handler(void){
	static seven_segment_disp_type_e epDisplays[] = {DISP_1, DISP_2, DISP_3, DISP_4};
	static volatile unsigned short usCur_disp = 0;
	sevenseg_setSegs(epSeg_Matrix[usCur_disp]);
	sevenseg_setDisp(epDisplays[usCur_disp]);
	usCur_disp = (usCur_disp+1)%MAX_DISP_NUMBER;
	pit_mark_interrupt_handled(SEV_SEG_PIT_TIMER_NUMB);
}

/**
* Initialize the seven segment display
*/
void sevenseg_init(void){
	GPIO_UNGATE_PORT(SEV_SEG_PORT_ID);

	// Init the Seven Segment segment control pins as OUTPUT
	GPIO_INIT_PIN(SEV_SEG_PORT_ID, SEGA_PIN, GPIO_OUTPUT);
	GPIO_INIT_PIN(SEV_SEG_PORT_ID, SEGB_PIN, GPIO_OUTPUT);
	GPIO_INIT_PIN(SEV_SEG_PORT_ID, SEGC_PIN, GPIO_OUTPUT);
	GPIO_INIT_PIN(SEV_SEG_PORT_ID, SEGD_PIN, GPIO_OUTPUT);
	GPIO_INIT_PIN(SEV_SEG_PORT_ID, SEGE_PIN, GPIO_OUTPUT);
	GPIO_INIT_PIN(SEV_SEG_PORT_ID, SEGF_PIN, GPIO_OUTPUT);
	GPIO_INIT_PIN(SEV_SEG_PORT_ID, SEGG_PIN, GPIO_OUTPUT);
	GPIO_INIT_PIN(SEV_SEG_PORT_ID, SEGDP_PIN, GPIO_OUTPUT);
	// Init the Seven Segment segment display pins as OUTPUT
	GPIO_INIT_PIN(SEV_SEG_PORT_ID, SEG_DISP1_PIN, GPIO_OUTPUT);
	GPIO_INIT_PIN(SEV_SEG_PORT_ID, SEG_DISP2_PIN, GPIO_OUTPUT);
	GPIO_INIT_PIN(SEV_SEG_PORT_ID, SEG_DISP3_PIN, GPIO_OUTPUT);
	GPIO_INIT_PIN(SEV_SEG_PORT_ID, SEG_DISP4_PIN, GPIO_OUTPUT);

	sevenseg_printDec(0);
	//Init pit interrupts
	pit_enable();
	//Init timer 0
	pit_start_timer_interrupt(SEV_SEG_PIT_TIMER_NUMB, SEVEN_SEG_PIT_PERIOD, &_sevenseg_interrupt_handler);
}


/**
 * Sets only the selected segments as high. Setting the others as low
 * @param epDet_segments = Array with the segments that should be set as on (Last element should be SEG_END)
 */
void sevenseg_setSegs(seven_segment_seg_type_e* epSet_segments){
	//Clear all segments.
	GPIO_WRITE_MASK(SEV_SEG_PORT_ID, SEV_SEG_SEGMENT_MASK, GPIO_LOW);
	//Set the selected segments to high
	for(unsigned short usCounter = 0; epSet_segments[usCounter] != SEG_END; usCounter++){
		GPIO_WRITE_PIN(SEV_SEG_PORT_ID, epSet_segments[usCounter], GPIO_HIGH);
	}
}

/**
 * Shows the value written in the segment pins to the
 *  given display after clearing the others
 * @param eDisplay the display to initialize.
 */
void sevenseg_setDisp(seven_segment_disp_type_e eDisplay){
	//Clear all displays
	GPIO_WRITE_MASK(SEV_SEG_PORT_ID, SEV_SEG_DISP_MASK, GPIO_LOW);
	//Activate the selected display
	GPIO_WRITE_PIN(SEV_SEG_PORT_ID, eDisplay, GPIO_HIGH);
}

/**
 * Shows the passed value in hexadecimal format in the seven segment display.
 * @param uiHex the value to be printed
 */
void sevenseg_printHex(unsigned int uiHex){
	for(unsigned short usCur_disp = 0; usCur_disp < MAX_DISP_NUMBER; usCur_disp++){
		sevenseg_hex2segArray(uiHex/pow(16,MAX_DISP_NUMBER-1-usCur_disp), epSeg_Matrix[usCur_disp]);
	}
}

/**
 * Shows the passed value in decimal format in the seven segment display.
 * @param uiDec the value to be printed
 */
void sevenseg_printDec(unsigned int uiDec){
	for(unsigned short usCur_disp = 0; usCur_disp < MAX_DISP_NUMBER; usCur_disp++){
		sevenseg_dec2segArray(uiDec/pow(10,MAX_DISP_NUMBER-1-usCur_disp), epSeg_Matrix[usCur_disp]);
	}
}

/**
 * Converts the less significative decimal digit of the argument into it's seven
 * segment display configuration
 * @param usDec the value to be converted (-1 if none should be displayed)
 * @param epRet address for results (should be a allocated array of minimal 9 elements)
 *
 * @return epRet
 */
seven_segment_seg_type_e* sevenseg_dec2segArray(unsigned short usDec, seven_segment_seg_type_e* epRet){
	if(usDec < 0){
		epRet[0] = SEG_END;
		return epRet;
	}
	epRet[0] = SEG_A;
	epRet[1] = SEG_B;
	epRet[2] = SEG_C;
	epRet[3] = SEG_D;
	epRet[4] = SEG_E;
	epRet[5] = SEG_F;
	epRet[6] = SEG_G;
	epRet[7] = SEG_END;
	switch(usDec%10){
	case 0:
		//{SEG_A,SEG_B,SEG_C,SEG_D,SEG_G,SEG_E,SEG_F,SEG_END};
		epRet[6] = SEG_END;
		break;
	case 1:
		//{SEG_B,SEG_C,SEG_END};
		epRet[0] = SEG_B;
		epRet[1] = SEG_C;
		epRet[2] = SEG_END;
		break;
	case 2:
		//{SEG_A,SEG_B,SEG_G,SEG_D,SEG_E,SEG_END};
		epRet[2] = SEG_G;
		epRet[5] = SEG_END;
		break;
	case 3:
		//{SEG_A,SEG_B,SEG_C,SEG_D,SEG_G,SEG_END}
		epRet[4] = SEG_G;
		epRet[5] = SEG_END;
		break;
	case 4:
		//{SEG_G, SEG_B,SEG_C,SEG_F, SEG_END}
		epRet[0] = SEG_G;
		epRet[3] = SEG_F;
		epRet[4] = SEG_END;
		break;
	case 5:
		//{SEG_A,SEG_G,SEG_C,SEG_D,SEG_F,SEG_END}
		epRet[1] = SEG_G;
		epRet[4] = SEG_F;
		epRet[5] = SEG_END;
		break;
	case 6:
		//{SEG_A,SEG_G,SEG_C,SEG_D,SEG_E,SEG_F,SEG_END}
		epRet[1] = SEG_G;
		epRet[6] = SEG_END;
		break;
	case 7:
		//{SEG_A,SEG_B,SEG_C,SEG_END}
		epRet[3] = SEG_END;
		break;
	case 8:
		//{SEG_A,SEG_B,SEG_C,SEG_D,SEG_E,SEG_F,SEG_G,SEG_END}
		break;
	case 9:
		//SEG_A,SEG_B,SEG_C,SEG_F,SEG_G,SEG_END}
		epRet[3] = SEG_F;
		epRet[4] = SEG_G;
		epRet[5] = SEG_END;
		break;
	}
	return epRet;
}

/**
 * Converts the less significative hexadecimal digit of the argument into it's seven
 * segment display configuration
 * @param usHex the value to be converted (-1 if none should be displayed)
 * @param epRet address for results (should be a allocated array of minimal 9 elements)
 *
 * @return epRet
 */
seven_segment_seg_type_e* sevenseg_hex2segArray(unsigned short usHex, seven_segment_seg_type_e* epRet){
	if(usHex < 0){
		epRet[0] = SEG_END;
		return epRet;
	}
	epRet[0] = SEG_A;
	epRet[1] = SEG_B;
	epRet[2] = SEG_C;
	epRet[3] = SEG_D;
	epRet[4] = SEG_E;
	epRet[5] = SEG_F;
	epRet[6] = SEG_G;
	epRet[7] = SEG_END;
	switch(usHex%16){
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			return sevenseg_dec2segArray(usHex%16, epRet);
			break;
		case 10: //A
			//{SEG_A,SEG_B,SEG_C,SEG_G,SEG_E,SEG_F,SEG_END}
			epRet[3] = SEG_G;
			epRet[6] = SEG_END;
			break;
		case 11: //B (b)
			//{SEG_G,SEG_F,SEG_C,SEG_D,SEG_E,SEG_END}
			epRet[0] = SEG_G;
			epRet[1] = SEG_F;
			epRet[5] = SEG_END;
			break;
		case 12: //C
			//{SEG_A,SEG_E,SEG_F,SEG_D,SEG_END}
			epRet[1] = SEG_E;
			epRet[2] = SEG_F;
			epRet[4] = SEG_END;
			break;
		case 13: //D (d)
			//{SEG_G,SEG_B,SEG_C,SEG_D,SEG_E,SEG_END}
			epRet[0] = SEG_G;
			epRet[5] = SEG_END;
			break;
		case 14: //E
			//{SEG_A,SEG_G,SEG_F,SEG_D,SEG_E,SEG_END}
			epRet[1] = SEG_G;
			epRet[2] = SEG_F;
			epRet[5] = SEG_END;
			break;
		case 15: //F
			//{SEG_A,SEG_E,SEG_F,SEG_G,SEG_END}
			epRet[1] = SEG_E;
			epRet[2] = SEG_F;
			epRet[3] = SEG_G;
			epRet[4] = SEG_END;
			break;
	}
	return epRet;
}

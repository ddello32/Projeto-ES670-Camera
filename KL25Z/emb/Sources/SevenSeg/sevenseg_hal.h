/* ***************************************************************** */
/* File name:        sevenseg_hal.h                                  */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for handling SEVEN SEGMENT DISPLAY   */
/*                    from the peripheral board                      */
/* Author name:      ddello	                                         */
/* Creation date:    18mar2016                                       */
/* Revision date:    13abr2016          	                         */
/* ***************************************************************** */

#ifndef SOURCES_SEVEN_SEGMENT_HAL_H_
#define SOURCES_SEVEN_SEGMENT_HAL_H_

#include "KL25Z/es670_peripheral_board.h"

#define MAX_SEGMENT_NUMBER 8
#define MAX_DISP_NUMBER 4


typedef enum
{
    SEG_A =	 SEGA_PIN,
    SEG_B =	 SEGB_PIN,
    SEG_C =	 SEGC_PIN,
    SEG_D =	 SEGD_PIN,
    SEG_E =	 SEGE_PIN,
    SEG_F =	 SEGF_PIN,
    SEG_G =	 SEGG_PIN,
    SEG_DP = SEGDP_PIN,
	SEG_END = -1
} seven_segment_seg_type_e;

typedef enum
{
    DISP_1 =	 SEG_DISP1_PIN,
	DISP_2 =	 SEG_DISP2_PIN,
	DISP_3 =	 SEG_DISP3_PIN,
	DISP_4 =	 SEG_DISP4_PIN,
} seven_segment_disp_type_e;

/**
* Initialize the seven segment display
*/
void sevenseg_init(void);

/**
 * Sets only the selected segments as high. Setting the others as low
 * @param epDet_segments = Array with the segments that should be set as on (Last element should be SEG_END)
 */
void sevenseg_setSegs(seven_segment_seg_type_e* epSet_segments);

/**
 * Shows the value written in the segment pins to the
 *  given display after clearing the others
 * @param eDisplay the display to initialize.
 */
void sevenseg_setDisp(seven_segment_disp_type_e eDisplay);

/**
 * Shows the passed value in hexadecimal format in the seven segment display.
 * @param uiHex the value to be printed
 */
void sevenseg_printHex(unsigned int uiHex);

/**
 * Shows the passed value in decimal format in the seven segment display.
 * @param uiDec the value to be printed
 */
void sevenseg_printDec(unsigned int uiDec);

/**
 * Converts the less significative decimal digit of the argument into it's seven
 * segment display configuration
 * @param usDec the value to be converted (-1 if none should be displayed)
 * @param epRet address for results (should be a allocated array of minimal 9 elements)
 *
 * @return epRet
 */
seven_segment_seg_type_e* sevenseg_dec2segArray(unsigned short usDec, seven_segment_seg_type_e* epRet);

/**
 * Converts the less significative hexadecimal digit of the argument into it's seven
 * segment display configuration
 * @param usHex the value to be converted (-1 if none should be displayed)
 * @param epRet address for results (should be a allocated array of minimal 9 elements)
 *
 * @return epRet
 */
seven_segment_seg_type_e* sevenseg_hex2segArray(unsigned short usHex, seven_segment_seg_type_e* epRet);

#endif /* SOURCES_SEVEN_SEGMENT_HAL_H_ */

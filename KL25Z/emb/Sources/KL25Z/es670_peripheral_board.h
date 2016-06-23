/* ***************************************************************** */
/* File name:        es670_peripheral_board.h                        */
/* File description: Header file containing the peripherals mapping  */
/*                     of the peripheral board for the ES670 hardware*/
/* Author name:      dloubach                                        */
/* Creation date:    16out2015                                       */
/* Revision date:    25fev2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_ES670_PERIPHERAL_BOARD_H_
#define SOURCES_ES670_PERIPHERAL_BOARD_H_

/* system includes */
#include <MKL25Z4.h>
#include "MKL25Z4_extension.h"

/*                 General uC definitions                 */

/* Clock gate control */
#define  CGC_CLOCK_DISABLED         0x00U
#define  CGC_CLOCK_ENABLED          0x01U

/* GPIO input / output */
#define GPIO_INPUT                  0x00U
#define GPIO_OUTPUT                 0x01U

#define GPIO_MUX_ALT                0x01u

#define GPIO_HIGH					1
#define GPIO_LOW					0

/*	Workaround for PORT_ID macro expansion to stop at port level*/
typedef int A;
typedef int B;
typedef int C;
typedef int D;
typedef int E;

/*                 END OF General uC definitions         */


/*                 BUZZER Definitions                    */
#define BUZZER_PORT_BASE_PNT        PORTD                                   /* peripheral port base pointer */
#define BUZZER_GPIO_BASE_PNT        PTD                                     /* peripheral gpio base pointer */
#define BUZZER_PORT_ID				D                                       /* peripheral port identifier*/

#define BUZZER_PIT_TIMER_NUMB		1

#define BUZZER_PIN                  0                                      /* buzzer pin */
#define BUZZER_DIR                  kGpioDigitalOutput
#define BUZZER_ALT                  0x01u
/*                 END OF BUZZER definitions             */


/*                 LED and SWITCH Definitions                    */
#define LS_PORT_BASE_PNT            PORTA                                   /* peripheral port base pointer */
#define LS_PORT_ID                  A                                      /* peripheral port identifier*/
#define LS_GPIO_BASE_PNT            PTA                                     /* peripheral gpio base pointer */

/* THIS PIN CONFLICTS WITH PTA1 USED AS UART0_RX IN THE OPENSDA SERIAL DEBUG PORT */
#define LS1_PIN                     1                                      /* led/switch #1 pin */
#define LS1_DIR_OUTPUT              (GPIO_OUTPUT << LS1_PIN)
#define LS1_DIR_INPUT               (GPIO_OUTPUT << LS1_PIN)
#define LS1_ALT                     0x01u                                   /* GPIO alternative */

/* THIS PIN CONFLICTS WITH PTA2 USED AS UART0_TX IN THE OPENSDA SERIAL DEBUG PORT */
#define LS2_PIN                     2                                      /* led/switch #2 pin */
#define LS2_DIR_OUTPUT              (GPIO_OUTPUT << LS2_PIN)
#define LS2_DIR_INPUT               (GPIO_OUTPUT << LS2_PIN)
#define LS2_ALT                     LS1_ALT

#define LS3_PIN                     4                                      /* led/switch #3 pin */
#define LS3_DIR_OUTPUT              (GPIO_OUTPUT << LS3_PIN)
#define LS3_DIR_INPUT               (GPIO_OUTPUT << LS3_PIN)
#define LS3_ALT                     LS1_ALT

#define LS4_PIN                     5                                      /* led/switch #4 pin */
#define LS4_DIR_OUTPUT              (GPIO_OUTPUT << LS4_PIN)
#define LS4_DIR_INPUT               (GPIO_OUTPUT << LS4_PIN)
#define LS4_ALT                     LS1_ALT

/*                 END OF LED and SWITCH definitions             */

/*                 SEVEN SEGMENT DISPLAY Definitions                    */
#define SEV_SEG_PORT_BASE_PNT      PORTC                                   /* peripheral port base pointer */
#define SEV_SEG_PORT_ID            C                                       /* peripheral port identifier*/
#define SEV_SEG_GPIO_BASE_PNT      PTC                                     /* peripheral gpio base pointer */

#define SEV_SEG_PIT_TIMER_NUMB		 0										/* timer number for seven seg PIT */

#define SEGA_PIN                     0                                      /* Segment A*/
#define SEGA_DIR_OUTPUT              (GPIO_OUTPUT << SEGA_PIN)
#define SEGA_ALT                     0x01u                                   /* GPIO alternative */

#define SEGB_PIN                     1
#define SEGB_DIR_OUTPUT              (GPIO_OUTPUT << SEGB_PIN)
#define SEGB_ALT                     SEGA_ALT

#define SEGC_PIN                     2
#define SEGC_DIR_OUTPUT              (GPIO_OUTPUT << SEGC_PIN)
#define SEGC_ALT                     SEGA_ALT

#define SEGD_PIN                     3
#define SEGD_DIR_OUTPUT              (GPIO_OUTPUT << SEGD_PIN)
#define SEGD_ALT                     SEGA_ALT

#define SEGE_PIN                     4
#define SEGE_DIR_OUTPUT              (GPIO_OUTPUT << SEGE_PIN)
#define SEGE_ALT                     SEGA_ALT

#define SEGF_PIN                     5
#define SEGF_DIR_OUTPUT              (GPIO_OUTPUT << SEGF_PIN)
#define SEGF_ALT                     SEGA_ALT

#define SEGG_PIN                     6
#define SEGG_DIR_OUTPUT              (GPIO_OUTPUT << SEGG_PIN)
#define SEGG_ALT                     SEGA_ALT

#define SEGDP_PIN                     7
#define SEGDP_DIR_OUTPUT              (GPIO_OUTPUT << SEGDP_PIN)
#define SEGDP_ALT                     SEGA_ALT

#define SEG_DISP1_PIN                 13
#define SEG_DISP1_DIR_OUTPUT          (GPIO_OUTPUT << SEG_DISP1_PIN)
#define SEG_DISP1_ALT                 SEGA_ALT

#define SEG_DISP2_PIN                 12
#define SEG_DISP2_DIR_OUTPUT          (GPIO_OUTPUT << SEG_DISP2_PIN)
#define SEG_DISP2_ALT                 SEGA_ALT

#define SEG_DISP3_PIN                 11
#define SEG_DISP3_DIR_OUTPUT          (GPIO_OUTPUT << SEG_DISP3_PIN)
#define SEG_DISP3_ALT                 SEGA_ALT

#define SEG_DISP4_PIN                 10
#define SEG_DISP4_DIR_OUTPUT          (GPIO_OUTPUT << SEG_DISP4_PIN)
#define SEG_DISP4_ALT                 SEGA_ALT

/*                 END of SEVEN SEGMENT DISPLAY Definitions                    */


/*                 END OF General uC definitions         */


/*                 LCD definitions                 */

/* LCD Register Selector
 * Used as register selector input
 * When (LCD_RS = LCD_RS_HIGH) => DATA register is selected
 * When (LCD_RS = LCD_RS_LOW)  => INSTRUCTION register is selected
*/
#define LCD_PORT_BASE_PNT           PORTC                                   /* peripheral port base pointer */
#define LCD_PORT_ID					C
#define LCD_GPIO_BASE_PNT           PTC                                     /* peripheral gpio base pointer */

#define LCD_RS_PIN                  8                                      /* register selector */
#define LCD_RS_DIR                  GPIO_OUTPUT

#define LCD_ENABLE_PIN              9                                      /* enable pin */
#define LCD_ENABLE_DIR              GPIO_OUTPUT

#define LCD_RS_HIGH                 GPIO_HIGH
#define LCD_RS_DATA                 LCD_RS_HIGH

#define LCD_RS_LOW                  GPIO_LOW
#define LCD_RS_CMD                  LCD_RS_LOW

#define LCD_ENABLED                 1U
#define LCD_DISABLED                0U

#define LCD_DATA_DIR                GPIO_OUTPUT                      /* LCD data pins */

#define LCD_DATA_DB0_PIN            0
#define LCD_DATA_DB1_PIN            1
#define LCD_DATA_DB2_PIN            2
#define LCD_DATA_DB3_PIN            3
#define LCD_DATA_DB4_PIN            4
#define LCD_DATA_DB5_PIN            5
#define LCD_DATA_DB6_PIN            6
#define LCD_DATA_DB7_PIN            7
/*                 END OF LCD definitions                 */

/*					COOLER DEFINITIONS 					  */
#define COOLER_PORT_ID				A
#define COOLER_PORT_BASE_PNT		PORTA
#define COOLER_PIN					13
#define COOLER_PIN_MUX_ALT			0x3

#define COOLER_TPM_BASE_PNT			TPM1
#define COOLER_TPM_CHANNEL_INDEX	1


/*					END OF COOLER DEFINITIONS 					  */

/*					SERVO DEFINITIONS 					  */
#define SERVO_PORT_ID				D
#define SERVO_PORT_BASE_PNT			PORTD
#define SERVO_PIN					5
#define SERVO_PIN_MUX_ALT			0x4

#define SERVO_TPM_BASE_PNT			TPM0
#define SERVO_TPM_CHANNEL_INDEX		5


/*					END OF SERVO DEFINITIONS 					  */

/*					HEATER DEFINITIONS 					  */
#define HEATER_PORT_ID				A
#define HEATER_PORT_BASE_PNT		PORTA
#define HEATER_PIN					12
#define HEATER_PIN_MUX_ALT			0x3

#define HEATER_TPM_BASE_PNT			TPM1
#define HEATER_TPM_CHANNEL_INDEX	0


/*					END OF HEATER DEFINITIONS 					  */

/*					TACOMETER DEFINITIONS				*/
#define TACOMETRO_PORT_ID			E
#define TACOMETRO_PORT_BASE_PNT		PORTE
#define TACOMETRO_PIN				29
#define TACOMETRO_PIN_ALT			0x4		/*ALT4 FTM_CLOCKIN0*/

#define TACOMETRO_TPM_BASE			TPM0

/*					END OF TACOMETER DEFINITIONS		*/

/*					ADC DEFINITIONS 					  */
#define ADC_PORT_ID					E
#define ADC_PORT_BASE_PNT			PORTE
#define ADC_NUM_BASE_PNT			ADC0_BASE_PTR
#define ADC_MUX_IDX					0		//MUX A
#define ADC_CHANNEL_SEL				0x4
#define ADC_TEMP_PIN				21
#define ADC_VOLT_PIN				20
#define ADC_TEMP_PIN_MUX_ALT		0x0
#define ADC_VOLT_PIN_MUX_ALT		0x0

#define HEATER_TPM_BASE_PNT			TPM1
#define HEATER_TPM_CHANNEL_INDEX	0


/*					END OF ADC DEFINITIONS 					  */


#endif /* SOURCES_ES670_PERIPHERAL_BOARD_H_ */

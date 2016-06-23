/* ***************************************************************** */
/* File name:        lcd_hal.h                                       */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for handling the LCD hardware from   */
/*                   the hardware kit                                */
/* Author name:      dloubach                                        */
/* Creation date:    16out2015                                       */
/* Revision date:    13mai2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_LCD_HAL_H_
#define SOURCES_LCD_HAL_H_

/* lcd basic commands list */
#define CMD_INIT_LCD        0x0F
#define CMD_CLEAR           0x01
#define CMD_NO_CURSOR       0x0C
#define CMD_CURSOR2R        0x06 /* cursor to right */
#define CMD_NO_CUR_NO_BLINK 0x38 /* no cursor, no blink */


/**
 * Initialize the LCD function
 */
void lcd_initLcd(void);


/**
 * Send command or data to LCD
 * @param ucBuffer Char to be send
 * @param cDataType Command LCD_RS_CMD or data LCD_RS_DATA
 */
void lcd_writeData(unsigned char ucData);


/**
 * Write command to LCD
 * @param ucCmd Command to be executed
 */
void lcd_sendCommand(unsigned char ucCmd);


/**
 * Write string to be displayed
 * @param cBuffer String to be written in LCD
 */
void lcd_writeString(const char *cBuffer);

/**
/* Print string to the display, clears display and handles cursor
/* @param cBuffer String to be written in LCD
 */
void lcd_printString(const char *cBuffer);

/**
 * Set cursor line and column
 * @param cLine = LINE0..LINE1
 * @param cColumn = COLUMN0..MAX_COLUMN
 */
void lcd_setCursor(unsigned char cLine, unsigned char cColumn);


/**
 * Write a dummy hard coded text
 */
void lcd_dummyText(void);


#endif /* SOURCES_LCD_HAL_H_ */

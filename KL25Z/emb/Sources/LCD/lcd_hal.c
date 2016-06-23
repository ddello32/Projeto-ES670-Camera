/* ***************************************************************** */
/* File name:        lcd_hal.c                                       */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related to the LCD HARDWARE based on the KS006U */
/*                   controller                                      */
/* Author name:      dloubach                                        */
/* Creation date:    16out2015                                       */
/* Revision date:    13mai2016                                       */
/* ***************************************************************** */

#include "lcd_hal.h"
#include "KL25Z/es670_peripheral_board.h"
#include "Util/util.h"
#include "GPIO/gpio_hal.h"

/* line and columns */
#define LINE0        0U
#define COLUMN0        0U

#define L0C0_BASE    0x80 /* line 0, column 0 */
#define L1C0_BASE    0xC0 /* line 1, column 0 */
#define MAX_COLUMN  15U

/**
 * Initialize the LCD function
 */
void lcd_initLcd(void)
{
    /* pins configured as outputs */

    /* un-gate port clock*/
    GPIO_UNGATE_PORT(LCD_PORT_ID);

    /* set pin as gpio output*/
    GPIO_INIT_PIN(LCD_PORT_ID, LCD_RS_PIN, LCD_RS_DIR);
    GPIO_INIT_PIN(LCD_PORT_ID, LCD_ENABLE_PIN, LCD_ENABLE_DIR);
    GPIO_INIT_PIN(LCD_PORT_ID, LCD_DATA_DB0_PIN, LCD_DATA_DIR);
    GPIO_INIT_PIN(LCD_PORT_ID, LCD_DATA_DB1_PIN, LCD_DATA_DIR);
    GPIO_INIT_PIN(LCD_PORT_ID, LCD_DATA_DB2_PIN, LCD_DATA_DIR);
    GPIO_INIT_PIN(LCD_PORT_ID, LCD_DATA_DB3_PIN, LCD_DATA_DIR);
    GPIO_INIT_PIN(LCD_PORT_ID, LCD_DATA_DB4_PIN, LCD_DATA_DIR);
    GPIO_INIT_PIN(LCD_PORT_ID, LCD_DATA_DB5_PIN, LCD_DATA_DIR);
    GPIO_INIT_PIN(LCD_PORT_ID, LCD_DATA_DB6_PIN, LCD_DATA_DIR);
    GPIO_INIT_PIN(LCD_PORT_ID, LCD_DATA_DB7_PIN, LCD_DATA_DIR);

    // turn-on LCD, with no cursor and no blink
    lcd_sendCommand(CMD_NO_CUR_NO_BLINK);

    // init LCD
    lcd_sendCommand(CMD_INIT_LCD);

    // clear LCD
    lcd_sendCommand(CMD_CLEAR);

    // LCD with no cursor
    lcd_sendCommand(CMD_NO_CURSOR);

    // cursor shift to right
    lcd_sendCommand(CMD_CURSOR2R);

}



/**
 * Send command or data to LCD
 * @param ucBuffer Char to be send
 * @param cDataType Command LCD_RS_CMD or data LCD_RS_DATA
 */
void lcd_write2Lcd(unsigned char ucBuffer,  unsigned char cDataType)
{
    /* writing data or command */
    if(LCD_RS_CMD == cDataType){
        /* will send a command */
        GPIO_WRITE_PIN(LCD_PORT_ID, LCD_RS_PIN, LCD_RS_CMD);
    } else{
        /* will send data */
    	GPIO_WRITE_PIN(LCD_PORT_ID, LCD_RS_PIN, LCD_RS_DATA);
    }

    /* write in the LCD bus */
    GPIO_WRITE_PIN(LCD_PORT_ID, LCD_DATA_DB0_PIN, ((ucBuffer & (1u << 0u)) >> 0u));
    GPIO_WRITE_PIN(LCD_PORT_ID, LCD_DATA_DB1_PIN, ((ucBuffer & (1u << 1u)) >> 1u));
    GPIO_WRITE_PIN(LCD_PORT_ID, LCD_DATA_DB2_PIN, ((ucBuffer & (1u << 2u)) >> 2u));
    GPIO_WRITE_PIN(LCD_PORT_ID, LCD_DATA_DB3_PIN, ((ucBuffer & (1u << 3u)) >> 3u));
    GPIO_WRITE_PIN(LCD_PORT_ID, LCD_DATA_DB4_PIN, ((ucBuffer & (1u << 4u)) >> 4u));
    GPIO_WRITE_PIN(LCD_PORT_ID, LCD_DATA_DB5_PIN, ((ucBuffer & (1u << 5u)) >> 5u));
    GPIO_WRITE_PIN(LCD_PORT_ID, LCD_DATA_DB6_PIN, ((ucBuffer & (1u << 6u)) >> 6u));
    GPIO_WRITE_PIN(LCD_PORT_ID, LCD_DATA_DB7_PIN, ((ucBuffer & (1u << 7u)) >> 7u));

    pit_mask_interrupts();
    /* enable, delay, disable LCD */
    /* this generates a pulse in the enable pin */
    GPIO_WRITE_PIN(LCD_PORT_ID, LCD_ENABLE_PIN, LCD_ENABLED);
    util_genDelay1ms();
    GPIO_WRITE_PIN(LCD_PORT_ID, LCD_ENABLE_PIN, LCD_DISABLED);
    util_genDelay1ms();
    util_genDelay1ms();
    pit_unmask_interrupts();
}



/**
 * Write data to be displayed
 * @param ucData Char to be written
 */
void lcd_writeData(unsigned char ucData)
{
    /* just a relay to send data */
    lcd_write2Lcd(ucData, LCD_RS_DATA);
}



/**
 * Write command to LCD
 * @param ucCmd Command to be executed
 */
void lcd_sendCommand(unsigned char ucCmd)
{
    /* just a relay to send command */
    lcd_write2Lcd(ucCmd, LCD_RS_CMD);
}



/**
 * Set cursor line and column
 * @param cLine = LINE0..LINE1
 * @param cColumn = COLUMN0..MAX_COLUMN
 */
void lcd_setCursor(unsigned char cLine, unsigned char cColumn)
{
    char cCommand;

    if(LINE0 == cLine)
        /* line 0 */
        cCommand = L0C0_BASE;
    else
        /* line 1 */
        cCommand = L1C0_BASE;

    /* maximum MAX_COLUMN columns */
    cCommand += (cColumn & MAX_COLUMN);

    // send the command to set the cursor
    lcd_sendCommand(cCommand);
}



/**
 * Write string to be displayed
 * @param cBuffer String to be written in LCD
 */
void lcd_writeString(const char *cBuffer)
{
    while(*cBuffer)
    {
        lcd_writeData(*cBuffer++);
    };
}

/**
/* Print string to the display, clears display and handles cursor
/* @param cBuffer String to be written in LCD
 */
void lcd_printString(const char *cBuffer)
{
    // clear LCD
    lcd_sendCommand(CMD_CLEAR);

    // set the cursor line 0, column 1
    lcd_setCursor(0,1);
    unsigned int uiCursorCollum = 0;
    while(*cBuffer)
    {
        lcd_writeData(*cBuffer++);
        if(++uiCursorCollum == MAX_COLUMN){
            lcd_setCursor(1,0);
            uiCursorCollum = 0;
        }
    };
}


/**
 * Write a dummy hard coded text
 */
void lcd_dummyText(void)
{
    // clear LCD
    lcd_sendCommand(CMD_CLEAR);

    // set the cursor line 0, column 1
    lcd_setCursor(0,1);

    // send string
    lcd_writeString("*** ES670 ***");

    // set the cursor line 1, column 0
    lcd_setCursor(1,0);
    lcd_writeString("Prj Sis Embarcad");
}

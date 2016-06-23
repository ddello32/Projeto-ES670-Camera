/* ***************************************************************** */
/* File name:        serial_hal.h                                    */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for serial communication		     */
/* Author name:      ddello		                                     */
/* Creation date:    27abr2016                                       */
/* Revision date:    27abr2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_SERIAL_HAL_H_
#define SOURCES_SERIAL_HAL_H_

/**
 * Initialize the serial device configuration
 */
void serial_initUart(void);


/**
 * Write buffer content to serial port
 *
 * @param cpBuffer Pointer to the start of the buffer
 * @param uiSize Number of characters to write
 */
void serial_sendBuffer(char *cpBuffer, unsigned int uiSize);


/**
 * Receive content from serial port to buffer.
 *
 * This function will read until one of {\n, \0} is found
 *
 * @param cpBuffer Pointer to the start of the buffer
 * @param uiSize Maximum number of characters to be read from serial port
 *
 * @return The number of characters actually read if the successful,
 * 				-1 in case of buffer overRun
 */
int serial_recieveBuffer(char *cpBuffer, unsigned int uiSize);

#endif /* SOURCES_SERIAL_HAL_H_ */

/* ***************************************************************** */
/* File name:        cmdmachine_hal.h                                */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for protocol command machine		 */
/* Author name:      ddello		                                     */
/* Creation date:    27abr2016                                       */
/* Revision date:    27abr2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_CMDMACHINE_HAL_H_
#define SOURCES_CMDMACHINE_HAL_H_

/**
 * Interpret all commands in the given command buffer.
 * Will trigger the command execution an format an output string for printing
 * Ignores blanks (\r,\n, ,\t,\0) between commands.
 *
 * For each valid command, the string ACK will be concatenated to the response string
 * followed by a line-break and the command response (if any).
 *
 * If invalid command syntax is found ERR will be concatenated to the response string
 * and all the characters before the next blank (\r,\n, ,\t,\0) will be ignored.
 *
 * @param cpCmdBuffer Pointer to command buffer
 * @param uiSize Size of the command buffer
 * @param cpCmdRes Pointer for response string.
 *
 * @after cpCmdRes with the response string for this cmdBuffer,
 * 				this will contain a ACK for each valid commmand in the cmdBuffer
 * 				followed by a line break and the command output (if any).
 * 				If an invalid command syntax is found the output string will contain
 * 				an ERR\n for that command and all characters before the next blank
 * 				(\r,\n, ,\t,\0) will be ignored.
 */
void cmdmachine_interpretCmdBuffer(char *cpCmdBuffer, unsigned int uiSize, char* cpCmdRes);

#endif /* SOURCES_CMDMACHINE_HAL_H_ */

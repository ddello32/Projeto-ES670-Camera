/* ***************************************************************** */
/* File name:        util.h                                          */
/* File description: Header file containing the function/methods     */
/*                   prototypes of util.c                            */
/*                   Those delays were tested under the following:   */
/*                   core clock @ 40MHz                              */
/*                   bus clock @ 20MHz                               */
/* Author name:      dloubach                                        */
/* Creation date:    09jan2015                                       */
/* Revision date:    13abr2016                                       */
/* ***************************************************************** */

#ifndef UTIL_H
#define UTIL_H

/**
 * generates ~ 088 micro sec
 */
void util_genDelay088us(void);


/**
 * generates ~   250 micro sec
 */
void util_genDelay250us(void);


/**
/* generates ~   1 mili sec
 */
void util_genDelay1ms(void);


/**
 * generates ~   10 mili sec
 */
void util_genDelay10ms(void);


#endif /* UTIL_H */

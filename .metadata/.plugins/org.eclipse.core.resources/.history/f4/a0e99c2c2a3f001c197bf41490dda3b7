 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*****************************************
 *  		ENUMS AND CONFIG STRUCT		 *
 *****************************************/

/* enum for choose parity mode */
typedef enum {
	DISABLED = 0,
	EVEN = 2,
	ODD = 3
}UART_ParityMode;

/* enum for choosing no. of Stop bits */
typedef enum {
	ONE , TWO
}UART_StopBits;

/* enum for choosing no. of data bits */
typedef enum {
	FIVE = 0,
	SIX = 1,
	SEVEN = 2,
	EIGHT = 3,
	NINE = 7
}UART_DataBits;

/*Struct for initiazlie the UART module */
typedef struct {
	uint8 RxEn; 			/* Enable Rx */
	uint8 TxEn; 			/* Enable Tx */
	uint8 doublespeed; 		/* double transmission speed rate */
	uint8 RxInt; 			/* Enable Rx Interrupt */
	uint8 TxInt; 			/* Enable Tx Interrupt */
	uint8 EMPInt; 			/* Enable Data register Empty Interrupt */
	UART_ParityMode parity; /* Parity Mode */
	UART_StopBits stopbits; /* No of Stop Bits */
	UART_DataBits databits; /* No of Data bits */
	uint16 baudrate; 		/* Choosing the baudrate*/
}UART_Config;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(UART_Config*);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

/* Call back functions Definitions */

void UART_RX_SetCallBack(volatile void(*a_ptr)(void));

void UART_TX_SetCallBack(volatile void(*a_ptr)(void));

void UART_UDRE_SetCallBack(volatile void(*a_ptr)(void));

#endif /* UART_H_ */

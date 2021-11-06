
#include "uart.h"
#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "std_types.h"
#include "avr/interrupt.h"

/* Global variables to hold the address of the call back function */
static volatile void (*g_callBackPtr_UART_RXC)(void) = NULL_PTR;
static volatile void (*g_callBackPtr_UART_TXC)(void) = NULL_PTR;
static volatile void (*g_callBackPtr_UART_UDRE)(void) = NULL_PTR;

/* Interrupt service routine when the UART recieves data */
ISR(USART_RXC_vect)
{
	if(g_callBackPtr_UART_RXC != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr_UART_RXC)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/* Interrupt service routine when the UART send data */
ISR(USART_TXC_vect)
{
	if(g_callBackPtr_UART_TXC != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr_UART_TXC)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/* Interrupt service routine when the UART send data */
ISR(USART_UDRE_vect)
{
	if(g_callBackPtr_UART_UDRE != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr_UART_UDRE)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */

void UART_init(UART_Config* config)
{
	uint16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed*/
	if(config->doublespeed)
	{
	SET_BIT(UCSRA,U2X);
	}

	/* For Rx Enable */
	if(config->RxEn)
	{
		SET_BIT(UCSRB,RXEN);
	}

	/* For Tx Enable */
	if(config->TxEn)
	{
		SET_BIT(UCSRB,TXEN);
	}

	/* For Rx Interrupt Enable */
	if(config->RxInt)
	{
		SET_BIT(UCSRB,RXCIE);
	}

	/* For Tx Interrupt Enable */
	if (config->TxInt)
	{
		SET_BIT(UCSRB,TXCIE);
	}

	/* For Data register Empty Interrupt Enable*/
	if (config->EMPInt)
	{
		SET_BIT(UCSRB,UDRIE);
	}
	
	/* URSEL must be one when writing the UCSRC	*/
	SET_BIT(UCSRC,URSEL);

	/* Parity settings */
	/* 1100 1111 */			   			/* 0011 0000 */
	UCSRC = (UCSRC & 0xCF ) | (config->parity & 0x30);

	/* Stop bit select */
	UCSRC |= (config->stopbits<<USBS);

	/* Data bits */
	switch(config->databits)
	{
	case FIVE :
	case SIX  :
	case SEVEN:
	case EIGHT:
		/* 1111 1001 */					/* 0000 0110 */
		UCSRC = (UCSRC & 0xF9 ) | (config->parity & 0x06);
		break;
	case NINE:
		UCSRC = (UCSRC & 0xF9 ) | (config->parity & 0x06);
		SET_BIT(UCSRB,UCSZ2);
		break;
	}
	
	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / (config->baudrate * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;

	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
    return UDR;		
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	UART_sendByte('#');
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}		
	*******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}

/***************************
 * Set Call Back Functions *
 ***************************/

void UART_RX_SetCallBack(volatile void(*a_ptr)(void))
{
	g_callBackPtr_UART_RXC = a_ptr;
}

void UART_TX_SetCallBack(volatile void(*a_ptr)(void))
{
	g_callBackPtr_UART_TXC = a_ptr;
}

void UART_UDRE_SetCallBack(volatile void(*a_ptr)(void))
{
	g_callBackPtr_UART_UDRE = a_ptr;
}

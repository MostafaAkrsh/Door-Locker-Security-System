#include "buzzer.h"
#include "gpio.h"

/* port and pin to only used in the same file */
static uint8 port;
static uint8 pin;

/* function to initialize the buzzer pin*/
void Buzzer_init(uint8 Port , uint8 Pin)
{
	/* Make the wanted pin Output Pin */
	GPIO_setupPinDirection(Port, Pin, PIN_OUTPUT);
	port = Port;
	pin = Pin;
}

/* function to make the buzzer ON */
void Buzzer_ON(void)
{
	GPIO_writePin(port , pin , LOGIC_HIGH);
}

/* function to make the buzzer OFF */
void Buzzer_OFF(void)
{
	GPIO_writePin(port , pin , LOGIC_LOW);
}

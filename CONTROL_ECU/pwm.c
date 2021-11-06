
#include "pwm.h"
#include "avr/io.h"
#include "std_types.h"

void PWM_Timer0_Start(uint8 duty_cycle)
{
	/* Set Timer Initial value */
	TCNT0 = 0;

	/* Set the compare Value */
	OCR0 = (uint8)((float32)duty_cycle * (255.0/100.0));

	/* set PB3/OC0 as output pin */
	DDRB |= (1<<PB3);

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
void PWM_Timer0_Stop(){
	TCCR0 = 0;
}

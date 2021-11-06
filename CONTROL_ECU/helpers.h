
#ifndef HELPERS_H_
#define HELPERS_H_

#include "lcd.h"
#include "common_macros.h"
#include "dcmotor.h"
#include "buzzer.h"
#include "std_types.h"
#include "gpio.h"
#include "util/delay.h"
#include "uart.h"
#include "avr/io.h"
#include "external_eeprom.h"
#include "std_types.h"
#include "timer.h"

/* define the passsize */
#define PASS_SIZE 5



/* Steps to control the flow of the system */
typedef enum {
	IDLE,SAVE_PASSWORD,CHECK_PASSWORD,OPEN_DOOR,CLOSE_DOOR,THIEF,OPTIONS
}State;


/* functions prototype */
uint8 check_identical(uint8* pass1, uint8* pass2);

#endif /* HELPERS_H_ */

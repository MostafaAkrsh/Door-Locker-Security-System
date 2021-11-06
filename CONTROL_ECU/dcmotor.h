
#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"
/*
 * enum to choose the state of motor
 * STOP: to stop the motor
 * CW  : to rotate the motor clock wise
 * A-CW: to rotate the motor anti clock wise
 */

typedef enum {
	STOP,CW,A_CW
}DcMotor_State;

/*
 * Initialization function
 */
void DcMotor_Init(uint8 Port , uint8 Pin1, uint8 Pin2);

/*
 * Control the motor state and speed
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DCMOTOR_H_ */

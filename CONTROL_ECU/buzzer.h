
#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Buzzer_init(uint8 Port , uint8 Pin);
void Buzzer_ON(void);
void Buzzer_OFF(void);


#endif /* BUZZER_H_ */

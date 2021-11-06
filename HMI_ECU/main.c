#include "helpers.h"

uint8 password1[PASS_SIZE];
uint8 password2[PASS_SIZE];
uint8 passwordCheck[PASS_SIZE];

int main()
{
	/* Configure Timer1 to make interrupt every 1 SEC
	 * timer_frequency = ECU_Frequency / Prescaler
	 * 				   = 8M/256 = 31250
	 * clock time = 	1/timer_frequency
	 * 			  = 	1/31250
	 * compare value =  ( timer_required ) / ( clock_time )
	 * 				 = 1/(1/31250) = 31250*/
	TIMER_Config config;

	config.timer_id = TIMER1_ID;
	config.timer_mode = COMPARE_MODE;
	config.timer_clk = PRESCALER256;
	config.oc_mode = TOGGLE;
	config.interrupt = ON;
	config.inital_value = 0;
	config.compare_value = 31250;

	Timer_Init(&config);

	Timer_SetCallBack(TIMER1_ID,ledony,COMPARE_MODE);

	/********************** Modules Initialization ************************/

	/* Uart Initialization */
	UART_Config uconfig;

	uconfig.RxEn = ON;
	uconfig.TxEn = ON;
	uconfig.EMPInt = OFF;
	uconfig.RxInt = OFF;
	uconfig.TxInt = OFF;
	uconfig.doublespeed = ON;
	uconfig.parity = EVEN;
	uconfig.stopbits = ONE;
	uconfig.databits = EIGHT;
	uconfig.baudrate = 9600;

	UART_init(&uconfig);


	/* LCD Initialization */
	LCD_init();


	/* Enable The global Interrupt */
	SREG |= (1<<7);
	uint8 key;

	State state = CHANGE_PW_STATE;
	uint8 no_of_trials = 0;
	  while(1)
	    {
		  switch(state)
		  {
		  case CHANGE_PW_STATE:
			  enter_password();
			  uint8 iscorrect = reenter_password();
			  if(iscorrect == YES)
				  {
				  state = OPTIONS_STATE;
				  }
			  else
			  {
			   password_not_identical();
			  }
			  break;
		  case OPTIONS_STATE:
			  key++; 		/* any trivial instruction due I can't initialize any thing in the fist line of case block */
			  Option option = main_options();
			  if(option == CHANGEPW)
				  {
				  state = CHANGE_PW_STATE;
				  }
			  else if(option == OPENDOOR)
			  {
				  state = ENTER_PW_STATE;
			  }
			  break;

		  case ENTER_PW_STATE:
			  if(enter_saved_password())
			  {
				  state = OPEN_DOOR_STATE;
			  }
			  else if (no_of_trials >= 2)
			  {
				  state = THIEF_STATE;
			  }
			  else
			  {
				  LCD_displayString("THEIF");

				  no_of_trials++;
			  }
			  break;

		  case OPEN_DOOR_STATE:
			  open_door();
			  //wait
			  state = CLOSE_DOOR_STATE;
			  break;

		  case CLOSE_DOOR_STATE:
			  key++;
		  	  uint8 close = ask_to_close();
		  	  if(close == YES) close_door();
		  	  //wait
		  	  state = OPTIONS_STATE;
		  break;

		  case THIEF_STATE:
			  LCD_displayString("THEIF");
				UART_sendByte('0');
			  break;
		  }
	    }
}

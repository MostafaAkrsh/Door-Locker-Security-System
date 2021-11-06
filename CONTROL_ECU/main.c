#include "helpers.h"


uint8 g_pass[PASS_SIZE];


uint8 EEPROM_pass[PASS_SIZE];
uint8 EE[PASS_SIZE];

uint8 key;

int main()
{
	LCD_init();
	LCD_displayString("meme");

	/* Buzzer Initialization */
	Buzzer_init(PORTB_ID ,PIN0_ID);

	/* Motor Initialization */
	DcMotor_Init(PORTB_ID,PIN5_ID,PIN4_ID);

	/* EEPROM Init */
	EEPROM_init();

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

	LCD_displayString("meme");

	//Buzzer_ON();
	//DcMotor_Rotate(CW,10);
	State state = IDLE;

	while(1)
	{
		switch(state)
			{
			case IDLE:
				key = UART_recieveByte();
				if( key=='!' )
				{
					LCD_clearScreen();
					state = SAVE_PASSWORD;
				}
			break;
			case SAVE_PASSWORD:
				UART_sendByte('!');
				UART_receiveString(g_pass);
				LCD_displayString(g_pass);
				EEPROM_writeString(g_pass, PASS_SIZE);
				LCD_displayString("written");
				state = CHECK_PASSWORD;

				break;
			case CHECK_PASSWORD:
				LCD_clearScreen();

				key = UART_recieveByte();
				LCD_displayCharacter(key);
				if(key == '0')
				{
					state = THIEF;
					break;
				}

				if(key == '+'){
				UART_sendByte('!');

				UART_receiveString(g_pass);
				EEPROM_readString(EEPROM_pass, PASS_SIZE);
				LCD_moveCursor(1,0);

				if(check_identical(EE,g_pass))
				{
					LCD_displayString("identical");

					state = OPEN_DOOR;
				}
				else
				{
					key = UART_recieveByte();
					if(key == '+')
					{
					UART_sendByte('X');
					}
					LCD_displayString("not");
				}
				}
				break;
			case OPEN_DOOR:

				key = UART_recieveByte();
				if(key == '+')
				UART_sendByte('+');
				state = CHECK_PASSWORD;
				break;
			case CLOSE_DOOR:
				break;
			case THIEF:
				LCD_displayString("ttt");
				Buzzer_ON();
				_delay_ms(100);
				Buzzer_OFF();
				_delay_ms(100);
				break;

	}

	}
}

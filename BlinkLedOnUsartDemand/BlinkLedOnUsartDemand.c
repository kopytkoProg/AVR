/*
* BlinkLedOnUsartDemand.c
*
* Created: 2014-12-19 15:30:15
*  Author: michal
*/
// F_CPU=8000000UL DEFINED IN COPILATION OPTIONS
#include "BlinkLedOnUsartDemand.h"
//--------------------------------------------------------------


//--------------------------------------------------------------
int main(void)
{
	

	DDRB |= _BV(DDB0);														// set out PB0 (for diode)
	init_my_buss();
	sei();																	// Enables interrupts
	PORTB |= (_BV(PB0));
	
	while(1)
	{
		
		
		if (usart_rx_bufor_ind >= 4 && usart_rx_bufor[MSG_DATA_LENGTH] + 4 == usart_rx_bufor_ind)	// great or equal 4 because packet always have address, command,  length and CRC
		{																							//(End is when usart_rx_bufor_ind is equals 4(addr, cmd, length, crc) + usart_rx_bufor_ind[1](length of data field))
			
			if(usart_rx_bufor[usart_rx_bufor_ind-1] == crc(usart_rx_bufor, usart_rx_bufor_ind - 1)	// check CRC
			&& usart_rx_bufor[MSG_ADDRESS] == MY_ADDRESS)											// check Address
			{
				//char msg[] = {1, 2, 2, 'O', 'K', 0};
				usart_rx_bufor[0] = MASTER_ADDRESS;
				usart_rx_bufor[usart_rx_bufor_ind - 1] = crc(usart_rx_bufor, usart_rx_bufor_ind - 1);
				
				send_data(usart_rx_bufor, usart_rx_bufor_ind);
				
				switch (usart_rx_bufor[MSG_COMMAND])
				{
					case CMD_ENABLE_LED0:
					//--------------------------------------------------------------
					PORTB |= (_BV(PB0));
					//--------------------------------------------------------------
					break;
					case CMD_DISABLE_LED0:
					//--------------------------------------------------------------
					PORTB &= ~(_BV(PB0));
					//--------------------------------------------------------------
					break;
					case CMD_TOGGLE_LED0:
					//--------------------------------------------------------------
					PORTB ^= (_BV(PB0));
					//--------------------------------------------------------------
					break;
					default:
					/* UNKNOWN */
					break;
				}
				usart_rx_bufor_ind = 0;
			}
			else
			{
				usart_rx_bufor_ind = 0;
			}
		}
	}
}
//--------------------------------------------------------------
//--------------------------------------------------------------



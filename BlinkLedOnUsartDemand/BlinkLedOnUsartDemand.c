/*
* BlinkLedOnUsartDemand.c
*
* Created: 2014-12-19 15:30:15
*  Author: michal
*/

# define F_CPU 8000000UL
//#include <stddef.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//definiowanie parametrów transmisji za pomoc¹ makr zawartych w pliku
//nag³ówkowym setbaud.h. Je¿eli wybierzesz prêdkoœæ, która nie bêdzie
//mo¿liwa do realizacji otrzymasz ostrze¿enie:
//#warning "Baud rate achieved is higher than allowed"

#define BAUD 9600 //57600													//tutaj podaj ¿¹dan¹ prêdkoœæ transmisji
#include <util/setbaud.h>													//linkowanie tego pliku musi byæ po zdefiniowaniu BAUD

# define BUFFER_SIZE 32
volatile unsigned int usart_bufor_ind;										//indeks bufora nadawania
char usart_bufor[BUFFER_SIZE];												//bufor nadawania

void clear_buffer(void)
{
	for (int i = 0; i < BUFFER_SIZE; i++ ) usart_bufor[i] = 0;
}
//--------------------------------------------------------------
uint8_t can_send(void)
{
	return (UCSR0A & (1<<UDRE0)) && !usart_bufor[0]);
}
//--------------------------------------------------------------
void usart_inicjuj(void)
{

	// set computed by 'setbaud' values 
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	#if USE_2X
	UCSR0A |=  (1<<U2X0);
	#else
	UCSR0A &= ~(1<<U2X0);
	#endif
	

	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	// 8 bits
	// 1 bit stop
	// parity none
	UCSR0B = (1<<TXEN0) | (1<<RXEN0); //| (1<<RXCIE0);
}
//--------------------------------------------------------------
ISR(USART_RX_vect)
{
	//przerwanie generowane po odebraniu bajtu
}
//--------------------------------------------------------------
ISR(USART_UDRE_vect)
{
	
	if(usart_bufor[usart_bufor_ind]!= 0)
	{
		UDR0 = usart_bufor[usart_bufor_ind++];
	}
	else
	{
		clear_buffer();
		usart_bufor_ind = 0;
		UCSR0B &= ~(1<<UDRIE0);												//wy³¹cz przerwania pustego bufora nadawania
	}
}
//--------------------------------------------------------------
void send_buffer(void)
{
	UCSR0B |= (1<<UDRIE0);
}
//--------------------------------------------------------------
//--------------------------------------------------------------

char* cp_to_buffer(char *s1, const char *s2)
{
	char *s = s1;
	while ((*s++ = *s2++) != 0);
	return (s1);
}

int main(void)
{
	clear_buffer();
	
	DDRB |= _BV(DDB0);														// set out PB0 (for diode)
	
	usart_inicjuj();														// initialize USART (RS-232)
	
	sei();																	// Enables interrupts
	
	while(1)
	{
		if (can_send())
		{
			cp_to_buffer(usart_bufor, "To jest test \r\n");
		}
		PORTB ^= _BV(PB0);
		_delay_ms(1000);
	}
}
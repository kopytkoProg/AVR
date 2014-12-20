/*
 * IncFile1.h
 *
 * Created: 2014-12-20 12:38:36
 *  Author: michal
 */ 

# define F_CPU 8000000UL
//#include <stddef.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>


//=================================================================================================================================
#define MY_ADDRESS 10
#define MASTER_ADDRESS 1

// COMMANDS :

#define CMD_ENABLE_LED0		1		// No data
#define CMD_DISABLE_LED0	2		// No data
#define CMD_TOGLE_LED0		3		// No data
#define CMD_TEXT			101		// No data

// Fields of message

#define MSG_ADDRESS 0
#define MSG_COMMAND 1
#define MSG_DATA_LENGTH 2


//#define MSG_CRC 
//=================================================================================================================================




//definiowanie parametrów transmisji za pomoc¹ makr zawartych w pliku
//nag³ówkowym setbaud.h. Je¿eli wybierzesz prêdkoœæ, która nie bêdzie
//mo¿liwa do realizacji otrzymasz ostrze¿enie:
//#warning "Baud rate achieved is higher than allowed"

#define BAUD 9600 //57600													//tutaj podaj ¿¹dan¹ prêdkoœæ transmisji
#include <util/setbaud.h>													//linkowanie tego pliku musi byæ po zdefiniowaniu BAUD

#define TX_BUFFER_SIZE 32
#define RX_BUFFER_SIZE 32

void clear_tx_buffer(void);
uint8_t can_send(void);
char* cp_to_buffer(char *s1, const char *s2);
void send_text(char *s, uint8_t length);
void usart_inicjuj(void);
void send_buffer(uint8_t byte_to_send);
void init_timer0(void);
void enable_timer0(void);
void disable_timer0(void);
void reset_timer0(void);
void send_data (char *s, uint8_t length);
uint8_t crc (char *s, uint8_t length);



volatile unsigned int usart_tx_bufor_ind;									//indeks bufora nadawania
char usart_tx_bufor[TX_BUFFER_SIZE];										//bufor nadawania

volatile unsigned int usart_rx_bufor_ind;									//indeks bufora nadawania
char usart_rx_bufor[RX_BUFFER_SIZE];										//bufor nadawania




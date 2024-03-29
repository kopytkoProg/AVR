/*
* MyBus.h
*
* Created: 2014-12-21 11:04:53
*  Author: michal
*/


#ifndef MYBUS_H_
#define MYBUS_H_

/*
* IncFile1.h
*
* Created: 2014-12-20 12:38:36
*  Author: michal
*/

//#include <stddef.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//definiowanie parametr�w transmisji za pomoc� makr zawartych w pliku
//nag��wkowym setbaud.h. Je�eli wybierzesz pr�dko��, kt�ra nie b�dzie
//mo�liwa do realizacji otrzymasz ostrze�enie:
//#warning "Baud rate achieved is higher than allowed"

#define BAUD 9600 //5760													//tutaj podaj ��dan� pr�dko�� transmisji
#include <util/setbaud.h>													//linkowanie tego pliku musi by� po zdefiniowaniu BAUD

#define TX_BUFFER_SIZE 32
#define RX_BUFFER_SIZE 32

// =================== Fields of message ===================

#define MSG_ADDRESS			0
#define MSG_COMMAND			1
#define MSG_DATA_LENGTH		2												// Data length field		
#define MSG_DATA_START		3												// Place where the data start 

// =========================================================

volatile unsigned int usart_tx_bufor_ind;									//indeks bufora nadawania
char volatile usart_tx_bufor[TX_BUFFER_SIZE];								//bufor nadawania

volatile unsigned int usart_rx_bufor_ind;									//indeks bufora nadawania
char volatile usart_rx_bufor[RX_BUFFER_SIZE];								//bufor nadawania


void send_data (volatile char *s, uint8_t length);
void init_my_buss(void);
uint8_t crc (volatile char *s, uint8_t length);


#endif /* MYBUS_H_ */
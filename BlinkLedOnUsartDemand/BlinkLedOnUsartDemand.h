/*
 * IncFile1.h
 *
 * Created: 2014-12-20 12:38:36
 *  Author: michal
 */ 




#include "MyBus/MyBus.h"

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
#define CMD_TOGGLE_LED0		3		// No data
#define CMD_TEXT			101		// No data


//#define MSG_CRC 
//=================================================================================================================================
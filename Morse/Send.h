//==============================================================================
//
// Title:		Send.h
// Purpose:		A short description of the interface.
//
// Created on:	05.12.2019 at 19:17:28 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================
#ifndef __Send_H__
#define __Send_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "Buzz.h"
#include "dio.h"
#include "MorseLine.h"
//==============================================================================
// Constants
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
//==============================================================================
// Types
typedef struct
{
	Buzz* buzzer;
	Led* led;
	Flags status;
	char *morseText;
	int timerState;
	int state;
	unsigned short int (*GetStatus)(void *this); 
	int (*SetStatus)(void *this,unsigned short int a);
	int (*Transmit)(void *this, MorseLine *line);
}Send;

//==============================================================================
// External variables

//==============================================================================
// Global functions
Send* ConstructSend(void);
void DestructSend(Send *sender); 



#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Send_H__  */

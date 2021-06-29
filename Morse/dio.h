//==============================================================================
//
// Title:		dio.h
// Purpose:		A short description of the interface.
//
// Created on:	05.12.2019 at 17:33:56 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __dio_H__
#define __dio_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include <NIDAQmx.h>   
#include "Buzz.h" 
//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	Flags flags;
	TaskHandle doTask;
	int timerLed;
	int val;
	short int bool;
	void (*On)(void *callbackData);
	void (*Off)(void *callbackData);
	
}Led;

//==============================================================================
// External variables

//==============================================================================
// Global functions
Led* ConstructLed();
void DestructLed(Led* led);



#ifdef __cplusplus
    }
#endif

#endif  /* ndef __dio_H__ */

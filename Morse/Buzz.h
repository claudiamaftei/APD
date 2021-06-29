//==============================================================================
//
// Title:		Buzz.h
// Purpose:		A short description of the interface.
//
// Created on:	26.11.2019 at 09:46:51 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Buzz_H__
#define __Buzz_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include <NIDAQmx.h>   

//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	unsigned short int taskStatus;
}Flags;

typedef struct
{
	Flags flags;
	TaskHandle aoTask;
	int timer;
	void (*On)(void *callbackData);
	void (*Off)(void *callbackData);
	
}Buzz;

//==============================================================================
// External variables

//==============================================================================
// Global functions

Buzz* ConstructBuzzer();
void DestructBuzzer(Buzz* buzz);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Buzz_H__ */

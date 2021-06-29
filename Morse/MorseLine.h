//==============================================================================
//
// Title:		MorseLine.h
// Purpose:		A short description of the interface.
//
// Created on:	05.12.2019 at 13:00:37 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __MorseLine_H__
#define __MorseLine_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	char *alfaTxt;
	char *morseTxt;
	int morseLen;
	
	int (*SetAlfaText)(void *this, char *txt);
	char* (*GetAlfaText)(void *this, char *txt);
	char* (*GetMorseTxt)(void *this);
	int (*GetMorseTxtLength)(void *this);
}MorseLine;
		
//==============================================================================
// External variables

//==============================================================================
// Global functions
MorseLine* ConstructMorseLine(void);
void DestructMorseLine(MorseLine *line); 

		
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __MorseLine_H__ */

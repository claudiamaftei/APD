//==============================================================================
//
// Title:       AiSafeTail.h
// Purpose:     A thread safe tail class declaration.
//
// Created on:  7.11.2014 at 16:11:35 by Robert Gabriel Lupu.
// Copyright:   Terran. All Rights Reserved.
//
//==============================================================================

#ifndef __AiSafeTail_H__
#define __AiSafeTail_H__

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

typedef struct _aitem_
{
	void *m_data;
	unsigned int m_size;
	unsigned int m_id;
	
	struct _aitem_ *m_next;
}AiItem;

typedef struct 
{
	AiItem *m_head;
	AiItem *m_tail;
	unsigned int m_items;
	
	int (*AddData)( void *callData, void *data, unsigned int size, unsigned int id );
	int (*GetData)( void *callData, void **data, unsigned int *size, unsigned int *id );
	int (*GetSize)(void *callData );
}AiTail;
		
typedef struct 
{
	int (*AddData)( void *callData, void *data, unsigned int nChanels, unsigned nSamples );
	int (*GetData)( void *callData, void **data, unsigned int *nChanels, unsigned int *nSamples );
	int (*GetSize)(void *callData );
}AiSafeTail;

//==============================================================================
// External variables

//==============================================================================
// Global functions



AiSafeTail *ConstructAiSafeTail( void );
AiSafeTail *DestructAiSafeTail( AiSafeTail *safeTail );

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __AiSafeTail_H__ */

//==============================================================================
//
// Title:       AiSafeTail.c
// Purpose:     A thread safe tail class definition.
//
// Created on:  7.11.2014 at 16:11:35 by Robert Gabriel Lupu.
// Copyright:   Terran. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include "AiSafeTail.h"
#include <utility.h>
#include <cvirte.h>

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
DefineThreadSafeVar(AiTail, AiSafeTail); 

//==============================================================================
// Static functions
int AiTailAddData( void *callData, void *data, unsigned int size, unsigned int id );
int AiTailGetData( void *callData, void **data, unsigned int *size, unsigned int *id );
int AiTailGetSize(void *callData );

//==============================================================================
// Global variables

//==============================================================================
// Global functions
AiTail *ConstructAiTail( void );
AiTail *DestructAiTail( AiTail *tail );
/*******************************************************************************

*******************************************************************************/

AiTail *ConstructAiTail( void )
{
	AiTail *tail;
	
	tail = (AiTail*)malloc( sizeof( AiTail ));
	
	tail->m_head = 0;
	tail->m_tail = 0;

	tail->AddData = AiTailAddData;
	tail->GetData = AiTailGetData;
	tail->GetSize = AiTailGetSize;
	tail->m_items = 0;
	
	return tail;
}
/*******************************************************************************

*******************************************************************************/

AiTail *DestructAiTail( AiTail *tail )
{
	AiItem *item = 0;
	
	while( tail->m_head )
	{
		item = tail->m_head;
		tail->m_head = tail->m_head->m_next;
		
		if( item->m_data )
		{
			free( item->m_data );
			item->m_data = 0;
			item->m_size = 0;
			
		}
		item->m_next = 0;
		free( item );
		item = 0;
	}
	tail->m_items = 0;
	
	return 0;
}
/*******************************************************************************

*******************************************************************************/

int AiTailAddData( void *callData, void *data, unsigned int size, unsigned int id )
{
	int error = 0;
	AiTail *tail = 0;
	AiItem *item = 0;
	
	tail = (AiTail*)callData;
	
	item = (AiItem *)malloc( sizeof( AiItem ));
	item->m_data = data;	
	item->m_size = size;
	item->m_id = id;
	item->m_next = 0;
	
	if( !(tail->m_head))
	{
		tail->m_head = item;
		tail->m_tail = item;
		tail->m_items = 1;
	}
	else
	{
		tail->m_tail->m_next = item;
		tail->m_tail = item;
		tail->m_items = tail->m_items + 1;
	}
	
	return error;
}
/*******************************************************************************

*******************************************************************************/

int AiTailGetData( void *callData, void **data, unsigned int *size, unsigned int *id )
{
	int error = 0;
	AiTail *tail = 0;
	AiItem *item = 0;
	
	tail = (AiTail*)callData;

	if( !(tail->m_head))
	{
		error = -1;	
	}
	else
	{
		*data = tail->m_head->m_data;
		*size = tail->m_head->m_size;
		*id = tail->m_head->m_id;
		tail->m_items = tail->m_items - 1;

		item = tail->m_head;
	
		tail->m_head = tail->m_head->m_next;
		free( item );
		item = 0;
	}
	
	return error;
}
/*******************************************************************************

*******************************************************************************/

int AiTailGetSize(void *callData )
{
	AiTail *tail = 0;
	
	tail = (AiTail*)callData;
	
	return tail->m_items;
}

/*******************************************************************************

*******************************************************************************/

void AiSafeTailInit( void )
{
	AiTail *safeTail = 0;

	InitializeAiSafeTail();
	safeTail = GetPointerToAiSafeTail();
		
		safeTail->m_head = 0;
		safeTail->m_tail = 0;
		safeTail->AddData = AiTailAddData;
		safeTail->GetData = AiTailGetData;
		safeTail->GetSize = AiTailGetSize;
		safeTail->m_items = 0;
		
	ReleasePointerToAiSafeTail();
	safeTail = 0;
}
/*******************************************************************************

*******************************************************************************/

int AiSafeTailAddData( void *callData, void *data, unsigned int size, unsigned int id )
{
	int error = 0;
	AiTail *safeTail = 0;
	
	safeTail = GetPointerToAiSafeTail();	
		
		safeTail->AddData( safeTail, data, size, id );
	
	ReleasePointerToAiSafeTail();
	safeTail = 0;
	
	return error;
}
/*******************************************************************************

*******************************************************************************/

int AiSafeTailGetData( void *callData, void **data, unsigned int *size, unsigned int *id )
{
	int error = 0;
	AiTail *safeTail = 0;
	
	safeTail = GetPointerToAiSafeTail();	

		error = safeTail->GetData( safeTail, data, size, id );	
	
	ReleasePointerToAiSafeTail();
	safeTail = 0;
	return error;
}
/*******************************************************************************

*******************************************************************************/


int AiSafeTailGetSize(void *callData )
{
	int items = 0;
	AiTail *safeTail = 0;
	
	safeTail = GetPointerToAiSafeTail();	
	
		items = safeTail->GetSize( safeTail ); 

	ReleasePointerToAiSafeTail();
	safeTail = 0;
		
	return items;
}
/*******************************************************************************

*******************************************************************************/

AiSafeTail* ConstructAiSafeTail( void )
{
	AiSafeTail* safeTail = 0;
	
	safeTail = ( AiSafeTail *) malloc( sizeof(AiSafeTail));
	safeTail->AddData = AiSafeTailAddData;
	safeTail->GetData = AiSafeTailGetData;
	safeTail->GetSize = AiSafeTailGetSize;
	
	AiSafeTailInit();
	
	return safeTail;
}
/*******************************************************************************

*******************************************************************************/

AiSafeTail* DestructAiSafeTail( AiSafeTail *tail )
{
	AiTail *safeTail = 0;
	AiItem *item = 0;
	
	safeTail = GetPointerToAiSafeTail();	
	
		while( safeTail->m_head )
		{
			item = safeTail->m_head;
			safeTail->m_head = safeTail->m_head->m_next;
		
			if( item->m_data )
			{
				free( item->m_data );
				item->m_data = 0;
				item->m_size = 0;
			}
			item->m_next = 0;
			free( item );
			item = 0;
		}
		safeTail->m_items = 0;
	
	ReleasePointerToAiSafeTail();
	safeTail = 0;
	
	UninitializeAiSafeTail();

	free( tail );
	tail = 0;
	return 0;
}

//==============================================================================
//
// Title:		Send.c
// Purpose:		A short description of the implementation.
//
// Created on:	05.12.2019 at 19:17:28 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
						
#include <ansi_c.h>
#include "asynctmr.h"
#include "Send.h"
#include "Buzz.h"
#include "MorseLine.h"
#include "dio.h"
//==============================================================================
// Constants
 static const double StateInterval=0.15;
//==============================================================================
// Types

//==============================================================================
// Static global variables
   static int count =0;  
 int poz=0; 
//==============================================================================
// Static functions
 static int CVICALLBACK StateTimer(int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2); 
 static unsigned short int GetStatus(void *this); 
 static int SetStatus(void *this,unsigned short int a);
 static int Transmit(void *this, MorseLine *line);
//=======================================================================
 //extern int length;
 extern int length;
 extern Send *sender;
//==============================================================================
// Global functions

 Send* ConstructSend(void)
 {
	  
	Send* sender = (Send*)malloc(sizeof(Send));
	sender->morseText=0;
	sender->status.taskStatus=0;
	sender->timerState=NewAsyncTimer( StateInterval,-1,0,StateTimer,sender);
	sender->buzzer=ConstructBuzzer();
	sender->led=ConstructLed();
	sender->GetStatus=GetStatus;
	sender->Transmit=Transmit;
	sender->state=S1;
	sender->SetStatus=SetStatus;
	return sender;
 }
/*******************************************************************************

*******************************************************************************/
 void DestructSend(Send *sender)
 {
	 if(sender->status.taskStatus)
	{
		free(sender->morseText); 
		DestructBuzzer(sender->buzzer);
		DestructLed(sender->led); 
		sender->status.taskStatus = 0;
		sender->GetStatus=0;
		sender->Transmit=0;
		sender->SetStatus=0;
		sender->state=S1;
	}
	free(sender);
	 
 }
 /*******************************************************************************

*******************************************************************************/
 static int Transmit(void *this, MorseLine *line)
 {
	int err=0;
    SetStatus(sender,1);
	Send *self=(Send*)this;  
	 if(self->morseText!=0)
	 {
		 free(self->morseText);
	 } 
	
	self->morseText=(char*)malloc((strlen(line->morseTxt)+1)*sizeof(char));
	strcpy(self->morseText,line->morseTxt);
	
	SetAsyncTimerAttribute(self->timerState,ASYNC_ATTR_ENABLED,1); 
	SetAsyncTimerAttribute(self->led->timerLed,ASYNC_ATTR_ENABLED,1);
	SetAsyncTimerAttribute(self->buzzer->timer,ASYNC_ATTR_ENABLED,1);
	return err;
	
	
	
 }
 /*******************************************************************************

*******************************************************************************/
 static int CVICALLBACK StateTimer(int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2)
 {
		
	 Send *this=(Send*)callbackData;
	 
		if(poz<length)
		{
			
			switch(this->state)
			{
				
				case S1:
						switch(this->morseText[poz])
						{
								 
							case '.':
								this->state=S2;
								this->led->bool=1;
							break;
							case '_':
								this->state=S3;
								this->led->bool=1;
							break;
							case ' ':
								 this->state=S4;
								 this->led->bool=0;
							break;
							case '/':
								this->state=S5;
								this->led->bool=0;
							break;
				
						}	
				
					poz++;
					count=0;
					
				 
				break;
				case S2:						   
		
					this->state=S1;
					this->led->bool=0;
					count=0;
			
				break;
				case S3:
					if(count==3)
					{
						this->led->bool=0;
						this->state=S1;
						count=0;
					}
			
			
				break;
				case S4:
					  if(count==3)
					{
						this->led->bool=0;
						this->state=S1;
						count=0;
					}
			
			
				break;
				case S5:
					   if(count==7)
					{
						this->led->bool=0;
						this->state=S1;
						count=0;
					}
			
			
				break;
			
			
			}
		}
		else
		{
			this->led->bool=0;  
			poz=0;
			SetAsyncTimerAttribute(sender->timerState,ASYNC_ATTR_ENABLED,0);
			SetAsyncTimerAttribute(sender->led->timerLed,ASYNC_ATTR_ENABLED,0);
			SetAsyncTimerAttribute(sender->buzzer->timer,ASYNC_ATTR_ENABLED,0);
			SetStatus(sender,0); 
		}
   count++;
	return 0;
 }  
/*******************************************************************************

*******************************************************************************/
 static unsigned short int GetStatus(void *this)
 {
	   	Send* sender = (Send*)this;
	
	return sender->status.taskStatus;	
	  
 } 
/*******************************************************************************

*******************************************************************************/

static int SetStatus(void *this,unsigned short int a)
{
	
	int err=0;
	Send* sender = (Send*)this;   
	sender->status.taskStatus=a;
	
	
	return err;
}

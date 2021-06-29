//==============================================================================
//
// Title:		dio.c
// Purpose:		A short description of the implementation.
//
// Created on:	05.12.2019 at 17:33:56 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <userint.h>
#include <ansi_c.h>
#include <NIDAQmx.h>
#include "dio.h"
#include "asynctmr.h"
#include "Morse.h" 

//==============================================================================
// Constants
#define HIGH 5.0
static const double ledInterval=0.001; 
//==============================================================================
// Types
typedef union
{
	unsigned char byte;
	struct
	{
		unsigned char b0:1;	
		unsigned char b1:1;	
		unsigned char b2:1;	
		unsigned char b3:1;	
		unsigned char b4:1;	
		unsigned char b5:1;	
		unsigned char b6:1;	
		unsigned char b7:1;	
	};
}uByte;

extern int mainPanel; 


//==============================================================================
// Static global variables
//==============================================================================
// Static functions
static int CVICALLBACK LedTimer(int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);
static void On(void *callBackData);
static void Off(void *callbackData);
//==============================================================================
// Global variables
//==============================================================================
// Global functions
int CVICALLBACK FunctionLed (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?

Led* ConstructLed()
{
	Led*led=(Led*)malloc(sizeof(Led));
	led->flags.taskStatus=0;
	led->val=0;
	DAQmxCreateTask("",&(led->doTask));
	DAQmxCreateDOChan(led->doTask, "Dev4/port0/line0", "", DAQmx_Val_ChanPerLine);
	DAQmxStartTask(led->doTask);
	led->flags.taskStatus=1;
	led->timerLed=NewAsyncTimer(ledInterval,-1,0,FunctionLed,led);
    led->On=On;
	led->Off=Off;
	led->bool=0;
	return led;
   
}
 /*******************************************************************************

*******************************************************************************/
void DestructLed(Led* led)
{

	if(led->flags.taskStatus)
	{
		DAQmxStopTask(led->doTask);
		led->flags.taskStatus = 0;
		led->val=0;
		led->bool=0;
	}
	
	DAQmxClearTask(led->doTask);
	free(led);
}

/*******************************************************************************

*******************************************************************************/
static int CVICALLBACK FunctionLed (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2)
{  
	Led *this=(Led*)callbackData;
	this->val= this->bool*HIGH;
	unsigned char xxx = !(this->val);
	int n = 0;
	PlotStripChart(mainPanel, MAIN_PANEL_PANEL_STRIPCHART, &(this->val), 1, 0, 0, VAL_INTEGER);
	DAQmxWriteDigitalLines(this->doTask, 1, 1, 0, DAQmx_Val_GroupByChannel, &xxx, &n, 0); 
	
		
	return 0;
}
/*******************************************************************************

*******************************************************************************/
 static void On(void *callbackData)
{
	Led* led = (Led*)callbackData;
	SetAsyncTimerAttribute(led->timerLed,ASYNC_ATTR_ENABLED,1);
}

/*******************************************************************************
																			   
*******************************************************************************/
static void Off(void *callbackData)
{
	Led* led = (Led*)callbackData;
	SetAsyncTimerAttribute(led->timerLed,ASYNC_ATTR_ENABLED,0);
}

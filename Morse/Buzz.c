//==============================================================================
//
// Title:		Buzz.c
// Purpose:		A short description of the implementation.
//
// Created on:	26.11.2019 at 09:47:12 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
 #include <ansi_c.h>
#include <NIDAQmx.h>
#include "Buzz.h"
#include "asynctmr.h"


//==============================================================================
// Constants

#define AO_CHANNEL "Dev4/ao0"
static const double buzInterval=0.002;
//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
 static int CVICALLBACK BuzzTimer(int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);
 static void On(void *callBackData);
 static void Off(void *callbackData);
//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
Buzz* ConstructBuzzer()
{
	Buzz*buzz=(Buzz*)malloc(sizeof(Buzz));
	buzz->flags.taskStatus=0;
	
	DAQmxCreateTask("",&(buzz->aoTask));
	DAQmxCreateAOVoltageChan(buzz->aoTask,AO_CHANNEL,"",0.0,5.0,DAQmx_Val_Volts,0);
	DAQmxStartTask(buzz->aoTask);
	buzz->flags.taskStatus=1;
	buzz->timer=NewAsyncTimer( buzInterval,-1,0,BuzzTimer,buzz);
   //BuzzTimer=fct callback timer Buzz

    buzz->On=On;
	buzz->Off=Off;
	
	return buzz;
   
}
/*******************************************************************************

*******************************************************************************/

void DestructBuzzer(Buzz* buzz)
{

	if(buzz->flags.taskStatus)
	{
		DAQmxStopTask(buzz->aoTask);
		buzz->flags.taskStatus = 0;
	}
	
	DAQmxClearTask(buzz->aoTask);
	free(buzz);
}

/*******************************************************************************

*******************************************************************************/
static int CVICALLBACK BuzzTimer (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2)
{		
	Buzz* buzz= (Buzz*)callbackData;
	static unsigned short int x = 0; 
	const double amplitude = 2.5;
	double output = x * amplitude; 
	
	DAQmxWriteAnalogF64(buzz->aoTask, 1, 1, -1, DAQmx_Val_GroupByChannel, &output, 0, 0);
	x = !x;
	return 0;
}
/*******************************************************************************

*******************************************************************************/
 static void On(void *callbackData)
{
	Buzz* buzz = (Buzz*)callbackData;
	SetAsyncTimerAttribute(buzz->timer,ASYNC_ATTR_ENABLED,1);
}

/*******************************************************************************
																			   
*******************************************************************************/
static void Off(void *callbackData)
{
	Buzz* buzz = (Buzz*)callbackData;
	SetAsyncTimerAttribute(buzz->timer,ASYNC_ATTR_ENABLED,0);
}




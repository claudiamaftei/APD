//==============================================================================
//
// Title:		Morse
// Purpose:		A short description of the application.
//
// Created on:	05.12.2019 at 12:59:56 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <cviauto.h>
#include "asynctmr.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "Morse.h"
#include "toolbox.h"
#include "MorseLine.h"
#include "toolbox.h"
#include <utility.h> 
#include "AiSafeTail.h"
#include "Send.h"
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

int mainPanel = 0;

//==============================================================================
// Static functions

//==============================================================================
// Global variables
AiSafeTail *tail = 0;
Send *sender=0;
int length=0;
//==============================================================================
// Global functions

/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
	int error = 0;
	
	/* initialize and load resources */
	nullChk (InitCVIRTE (0, argv, 0));
	errChk (mainPanel = LoadPanel (0, "Morse.uir", MAIN_PANEL));

	tail = ConstructAiSafeTail();
	SetCtrlAttribute(mainPanel, MAIN_PANEL_IDC_TAIL_TIMER, ATTR_ENABLED, 1);
	sender=ConstructSend();
	/* display the panel and run the user interface */
	errChk (DisplayPanel (mainPanel));
	errChk (RunUserInterface ());

Error:
	/* clean up */  
	SetCtrlAttribute(mainPanel, MAIN_PANEL_IDC_TAIL_TIMER, ATTR_ENABLED, 0);
	DestructAiSafeTail(tail); 
	DestructSend(sender);
	if (mainPanel > 0)
		DiscardPanel (mainPanel);
	return 0;
}

//==============================================================================
// UI callback function prototypes
/// HIFN Exit when the user dismisses the panel.
int CVICALLBACK OnMainPanelCB (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	if (event == EVENT_CLOSE)
		QuitUserInterface (0);
	return 0;
}
 /*******************************************************************************

*******************************************************************************/

int CVICALLBACK OnAlfaTxtCB (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	char str[256];
	switch (event)
	{
		case EVENT_COMMIT:  //când se apasã tasta ENTER
			GetCtrlVal(panel, MAIN_PANEL_IDC_ALFA_TXT, str);
			MorseLine *line = ConstructMorseLine();
			line->SetAlfaText(line, str);
			tail->AddData(tail, line, 0, 0);
			SetCtrlVal(panel, MAIN_PANEL_IDC_ALFA_TXT, "");
			break;
	}
	return 0;
}
/*******************************************************************************

*******************************************************************************/

int CVICALLBACK OnTailTimerCB (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	MorseLine *line = 0;
	unsigned int v1 = 0;
	unsigned int v2 = 0;

	switch (event)
	{
		case EVENT_TIMER_TICK:
			while((tail->GetSize(tail) > 0)&&((sender->GetStatus((void*)sender))==0))
			{
				tail->GetData(tail, (void**)(&line), &v1, &v2);
				InsertTextBoxLine(panel, MAIN_PANEL_IDC_MORSE_TXT, -1, line->GetMorseTxt(line)); 
				length=0;
				length=line->GetMorseTxtLength(line);
				sender->Transmit(sender,line); 
				DestructMorseLine(line);
				line = 0;
				
			}   
				
				
			break;
	}
	return 0;
}

//==============================================================================
//
// Title:		MorseLine.c
// Purpose:		A short description of the implementation.
//
// Created on:	05.12.2019 at 13:00:37 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <ansi_c.h>
#include "MorseLine.h"
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
static int SetAlfaText(void *this, char *txt);
static char* GetAlfaText(void *this, char *txt);
static char* GetMorseTxt(void *this);
static void ConvertToMorse(char*alphaTxt,char*morseTxt) ;
static int GetMorseTxtLength(void *this);
//==============================================================================
// Global variables

//==============================================================================
// Global functions
MorseLine* ConstructMorseLine(void)
{
	MorseLine* line = (MorseLine*)malloc(sizeof(MorseLine));
	line->alfaTxt = 0;
	line->morseTxt = 0;
	line->SetAlfaText = SetAlfaText;
	line->GetAlfaText = GetAlfaText;
	line->GetMorseTxt = GetMorseTxt;
	line->GetMorseTxtLength = GetMorseTxtLength;
	return line;
}
/*******************************************************************************

*******************************************************************************/

void DestructMorseLine(MorseLine *line)
{
	free(line->alfaTxt);
	line->alfaTxt = 0;
	free(line->morseTxt);
	line->morseTxt = 0;
	free(line);
}
/*******************************************************************************

*******************************************************************************/

static int SetAlfaText(void *this, char *txt)
{
	int err = 0;
	MorseLine *line = (MorseLine*)this;

	line->alfaTxt = (char*)malloc((strlen(txt) + 1) * sizeof(char));
	strcpy(line->alfaTxt, txt); 
	
	line->morseTxt = (char*)malloc(7 * strlen(txt) * sizeof(char));
	ConvertToMorse(line->alfaTxt, line->morseTxt); 
	line->morseLen = strlen(line->morseTxt);
	
	return err;
}
/*******************************************************************************

*******************************************************************************/

static void ConvertToMorse(char*alphaTxt,char*morseTxt)
{	 
	int i;
	int j;
	int lengthAlpha = strlen(alphaTxt);
	int lengthMorse=0 ;
	for(i = 0; i < lengthAlpha; i++)
	{
		if((alphaTxt[i] >= 'a') && (alphaTxt[i] <= 'z'))
		{
			alphaTxt[i] = alphaTxt[i] - 32;
		}
	}
	char alpha_char[41] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z','0', '1', '2', '3', '4', '5', '6', '7', '8', '9','.', ',', ':', ';'};
	char (**morse_char) = (char**)malloc(256 * sizeof(char*));
	for(i = 0; i < 256; i++)
	{
			morse_char[i] = (char*)malloc(7 * sizeof(char));
	}
		   
	strcpy(morse_char[' '], "/");
	strcpy(morse_char['A'], "._");
	strcpy(morse_char['B'], "_...");
	strcpy(morse_char['C'], "_._.");
	strcpy(morse_char['D'], "_..");
	strcpy(morse_char['E'], ".");
	strcpy(morse_char['F'], ".._.");
	strcpy(morse_char['G'], "__.");
	strcpy(morse_char['H'], "....");
	strcpy(morse_char['I'], "..");
	strcpy(morse_char['J'], ".___");
	strcpy(morse_char['K'], "_._");
	strcpy(morse_char['L'], "._..");
	strcpy(morse_char['M'], "__");
	strcpy(morse_char['N'], "_.");
	strcpy(morse_char['O'], "___");
	strcpy(morse_char['P'], ".__.");
	strcpy(morse_char['Q'], "__._");
	strcpy(morse_char['R'], "._.");
	strcpy(morse_char['S'], "...");
	strcpy(morse_char['T'], "_");
	strcpy(morse_char['U'], ".._");
	strcpy(morse_char['V'], "..._");
	strcpy(morse_char['W'], ".__");
	strcpy(morse_char['X'], "_.._");
	strcpy(morse_char['Y'], "_.__");
	strcpy(morse_char['Z'], "__..");
	strcpy(morse_char['0'], "_____");
	strcpy(morse_char['1'], ".____");
	strcpy(morse_char['2'], "..___");
	strcpy(morse_char['3'], "...__");
	strcpy(morse_char['4'], "...._");
	strcpy(morse_char['5'], ".....");
	strcpy(morse_char['6'],	"_....");
	strcpy(morse_char['7'], "__...");
	strcpy(morse_char['8'], "___..");
	strcpy(morse_char['9'], "____.");
	strcpy(morse_char['.'], "._._._");
	strcpy(morse_char[','], "__..__");
	strcpy(morse_char[':'], "___...");
	strcpy(morse_char[';'], "_._._.");
	
	strcpy(morseTxt,"");
	for(i = 0; i < lengthAlpha; i++)
	{
		for(j = 0; j < 41; j++)
		{
			if(alphaTxt[i] == alpha_char[j])
			{
				strcat(&(morseTxt[lengthMorse]), morse_char[alpha_char[j]]);
				lengthMorse+=strlen(morse_char[alpha_char[j]]);
				strcat(&(morseTxt[lengthMorse])," ");  
				lengthMorse+=1;
			}
		}
	}
	
}
/*******************************************************************************

*******************************************************************************/
 
static char* GetAlfaText(void *this, char *txt)	   
{
	MorseLine* line = (MorseLine*)this;
	
	return line->alfaTxt;
}
/*******************************************************************************

*******************************************************************************/

static char* GetMorseTxt(void *this)
{
	MorseLine* line = (MorseLine*)this;
	
	return line->morseTxt;	
}
/*******************************************************************************

*******************************************************************************/

static int GetMorseTxtLength(void *this)
{
	MorseLine* line = (MorseLine*)this;
	
	if(line->morseTxt)
	{
		return strlen(line->morseTxt);
	}
	else
	{
		return 0;	
	}
}

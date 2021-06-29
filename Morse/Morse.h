/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  MAIN_PANEL                       1       /* callback function: OnMainPanelCB */
#define  MAIN_PANEL_IDC_ALFA_TXT          2       /* control type: string, callback function: OnAlfaTxtCB */
#define  MAIN_PANEL_IDC_MORSE_TXT         3       /* control type: textBox, callback function: (none) */
#define  MAIN_PANEL_IDC_TAIL_TIMER        4       /* control type: timer, callback function: OnTailTimerCB */
#define  MAIN_PANEL_PANEL_STRIPCHART      5       /* control type: strip, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnAlfaTxtCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnMainPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnTailTimerCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif

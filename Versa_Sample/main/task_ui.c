//******************************************************************************
// File: task_ui.c
// Description: user interface task
// Author: Juan Ramon Vadillo (Versa Design S.L.)
// Licencia: Creative Commons No Comercial (CC BY-NC)
//
// Este archivo está sujeto a la Licencia Creative Commons No Comercial (CC BY-NC).
// Esto significa que puedes compartir, copiar, modificar y distribuir este archivo
// siempre y cuando sea para uso personal y no comercial, y siempre que se proporcione
// atribución al autor original. No se permite el uso comercial de este archivo ni la
// creación de obras derivadas sin el consentimiento expreso del autor.
//
// Para más detalles sobre la Licencia Creative Commons No Comercial (CC BY-NC), puedes
// consultar: [https://creativecommons.org/licenses/by-nc/4.0/]
//******************************************************************************

//******************************************************************************
// INCLUDES

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "global.h"

#include "hwplatform.h"
#include "tftdriver.h"
#include "scr_main.h"
#include "task_ui.h"

//******************************************************************************
// DEFINES & TYPEDEFS

//----------------------------------------------------------------------------
// Redraw levels
#define REDRAW_NONE      0
#define REDRAW_PARTIAL   1
#define REDRAW_ALL       2

typedef struct
{
  uint32_t keyCode;
  uint32_t keyEventPress;
  uint32_t keyEventRelease;
} tKeyEventMappingEntry;

//******************************************************************************
// VARIABLES

static uint8_t redrawLevel = REDRAW_ALL;   // global redraw flag
static uint32_t veryLongKeyTimeout = 0;
static uint32_t shortKeyTimeout = 0;
static uint32_t longKeyTimeout = 0;

static uint8_t taskCount20ms = 0;
static uint32_t uwTickCounter20ms = 0;

static portMUX_TYPE taskLock = portMUX_INITIALIZER_UNLOCKED;

static EventGroupHandle_t xEventGroup = NULL;

static uint32_t keyTimer[MAX_KEYS],keyRep[MAX_KEYS];  // Key up timer

static const uint16_t interKeyTimer[] =
{
  0,
  400,400,400,400,
  200,200,200,200,200,200,200,
  100,100,100,100,100,100,100,100,100,100,100,100,
  10,10
};

static const tKeyEventMappingEntry keyEventMap[] =
{
  {ID_KEY_UP        ,EV_KEY_UP_PRESS        ,EV_KEY_UP_RELEASE        },
  {ID_KEY_DOWN      ,EV_KEY_DOWN_PRESS      ,EV_KEY_DOWN_RELEASE      },
  {ID_KEY_LEFT      ,EV_KEY_LEFT_PRESS      ,EV_KEY_LEFT_RELEASE      },
  {ID_KEY_RIGHT     ,EV_KEY_RIGHT_PRESS     ,EV_KEY_RIGHT_RELEASE     },
  {ID_KEY_OK        ,EV_KEY_OK_PRESS        ,EV_KEY_OK_RELEASE        },
  {ID_KEY_RETURN    ,EV_KEY_RETURN_PRESS    ,EV_KEY_RETURN_RELEASE    },
  {ID_KEY_L_TRIGGER ,EV_KEY_L_TRIGGER_PRESS ,EV_KEY_L_TRIGGER_RELEASE },
  {ID_KEY_R_TRIGGER ,EV_KEY_R_TRIGGER_PRESS ,EV_KEY_R_TRIGGER_RELEASE },
  {ID_KEY_START     ,EV_KEY_START_PRESS   ,  EV_KEY_START_RELEASE  },
  {ID_KEY_SELECT    ,EV_KEY_SELECT_PRESS  ,  EV_KEY_SELECT_RELEASE },


  //-----
  {U32_INVALID      ,U32_INVALID            ,U32_INVALID},
};

static xTaskHandle taskHandleUI = NULL;

//******************************************************************************
// FUNCTIONS

//******************************************************************************
void UIForceFullRedraw(void)
//******************************************************************************
// Description: Update the screen
// Return:      None
//******************************************************************************
{
  redrawLevel = REDRAW_ALL;
}

//******************************************************************************
void UIForcePartialRedraw(void)
//******************************************************************************
// Description: Update the screen
// Return:      None
//******************************************************************************
{
  redrawLevel |= REDRAW_PARTIAL;
}

//******************************************************************************
static uint32_t ManageKeyboardEvents(uint32_t keyid, uint16_t pressEvent,
                                     uint16_t releaseEvent)
//******************************************************************************
// Description: Manage keyboard events
// Return:      Event
//******************************************************************************
{
  uint32_t kr;
  if (!IsKeyPressedLowLevel(keyid))
  {
    keyTimer[keyid] = 0;
    kr = keyRep[keyid];
    keyRep[keyid] = 0;
    if (kr) return releaseEvent;
    return EV_NONE;
  }
  if (keyTimer[keyid] > 0) return EV_NONE; // Check if the timer has expired

  if (keyRep[keyid] < sizeof(interKeyTimer)/2-1) keyRep[keyid]++;
  keyTimer[keyid] = interKeyTimer[keyRep[keyid]];
  longKeyTimeout = 0; shortKeyTimeout = 0; veryLongKeyTimeout = 0;
  PlayMelody((uint16_t *)melKeyBeep);
  
  return pressEvent;
}


//******************************************************************************
void ManageUITimers(void)
//******************************************************************************
// Description: To be called once per millisecond
// Return:      None
//******************************************************************************
{
  uint32_t i;
  for (i = 0; i < MAX_KEYS; i++)
  {
    if (keyTimer[i] > 0) keyTimer[i]--;
  }

  if (++uwTickCounter20ms >= 20)
  {
    uwTickCounter20ms = 0;
    ENTER_CRITICAL(&taskLock);
    if (taskCount20ms < 255) taskCount20ms++;
    EXIT_CRITICAL(&taskLock);
    UINotify();
  }
  if (IsKeyPressedLowLevel(0xFFFF)) UINotify();
}

//******************************************************************************
tUIEvent GetUserInterfaceEvent(void)
//******************************************************************************
// Description: this function manages the screen server function. This means
// that if there are keys pending or redraw orders, this function injects
// the corresponding events into the current screen server functions
// Parameters: none
// Returns:
//    uint32_t with the optional event that the function may have generated
//    during its execution
//******************************************************************************
{
  uint32_t i;
  tUIEvent res = EV_NONE;
  if (redrawLevel & REDRAW_ALL)
  {
    redrawLevel = REDRAW_NONE;
    return EV_FULL_REDRAW;
  }
  if (redrawLevel & REDRAW_PARTIAL)
  {
    redrawLevel = REDRAW_NONE;
    return EV_PARTIAL_REDRAW;
  }
  if (taskCount20ms)
  {
    if (veryLongKeyTimeout < 0xFFFFFFFFL) veryLongKeyTimeout++;
    if (longKeyTimeout     < 0xFFFFFFFFL) longKeyTimeout++;
    if (shortKeyTimeout    < 0xFFFFFFFFL) shortKeyTimeout++;
    ENTER_CRITICAL(&taskLock);
    taskCount20ms--;
    EXIT_CRITICAL(&taskLock);
    return EV_TIMER_20MS;
  }
  if (veryLongKeyTimeout > 540000L) { veryLongKeyTimeout = 0; return EV_VERY_LONG_KEY_TIMEOUT; }  // 3 hours
  if (longKeyTimeout     > 45000)   { longKeyTimeout = 0;     return EV_LONG_KEY_TIMEOUT; }
  if (shortKeyTimeout    > 15000)   { shortKeyTimeout = 0;    return EV_KEY_TIMEOUT; }


  i = 0;
  while (keyEventMap[i].keyCode != U32_INVALID)
  {
    res = ManageKeyboardEvents(keyEventMap[i].keyCode,
                               keyEventMap[i].keyEventPress,
                               keyEventMap[i].keyEventRelease);
    if (res != EV_NONE)
    {
      return res;
    }
    i++;
  }
  return res;
}

//******************************************************************************
void UINotify(void)
//******************************************************************************
// Description: this function notifies the user interface task that there is
// something to do
// Parameters: none
// Returns: nothing
//******************************************************************************
{
  if (xEventGroup == NULL) return;
  xEventGroupSetBits(xEventGroup,1);
}

//******************************************************************************
void UIIdle(void)
//******************************************************************************
// Description: set of actions to be executed by the GUI task when no event is
// being treated.
// Parameters: none - Returns: nothing
//******************************************************************************
{
  xEventGroupWaitBits( xEventGroup,  /* The event group that contains the event bits being queried. */
                     1,              /* The bit to wait for. */
                     pdTRUE,         /* Clear the bit on exit. */
                     pdTRUE,         /* Wait for all the bits (only one in this case anyway). */
                     20/ portTICK_PERIOD_MS ); /* Block indefinitely to wait for the condition to be met. */
}

//******************************************************************************
static void TaskExecFunc(void * par)
//******************************************************************************
// Description: user interface task call
// Parameters:
//   uint8_t lt: launch timer event
//******************************************************************************
{
  printf("TFT Init\n");
  TFT_Init();

  UIForceFullRedraw();

  TFT_SetBacklight(100);

  PlayMelody((uint16_t *)melIntro);

  for (;;)
  {
    MainMenuScreenHandler();
  }
}

//******************************************************************************
tRetCode InitUITask(void)
//******************************************************************************
// Description: user interface initialization
// Parameters: none
// Returns:
//    RES_OK: if the initialization was successfull
//    RES_ERROR: if the user interface task could not be initialized
//******************************************************************************
{
  xEventGroup = xEventGroupCreate();
  if (xEventGroup == NULL) return RES_ERROR;
  xTaskCreate( TaskExecFunc, (const char *)"GUI",
                configMINIMAL_STACK_SIZE*12, NULL, 5, &taskHandleUI );
  return RES_OK;
}
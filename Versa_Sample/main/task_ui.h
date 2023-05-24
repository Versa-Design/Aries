//******************************************************************************
// File: task_ui.h
// Description: user interface task header file
// Author: Juan Ramon Vadillo
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

#ifndef TASK_UI_H_INCLUDED
#define TASK_UI_H_INCLUDED

//******************************************************************************
// INCLUDES

#include <stdint.h>
#include "global.h"

//******************************************************************************
// DEFINES & TYPEDEFS

//------------------------------------------------------------------------------
// User interface events

// First 64 events are reserved for system events
typedef enum
{

  EV_NONE                                =  0,
  EV_INIT                                    ,// Initialization event
  EV_FULL_REDRAW                             ,// Full screen redraw event
  EV_PARTIAL_REDRAW                          ,// Partial screen redraw
  EV_TIMER_20MS                              ,
  EV_KEY_UP_PRESS                            ,
  EV_KEY_UP_RELEASE                          ,
  EV_KEY_DOWN_PRESS                          ,
  EV_KEY_DOWN_RELEASE                        ,
  EV_KEY_LEFT_PRESS                          ,
  EV_KEY_LEFT_RELEASE                        ,
  EV_KEY_RIGHT_PRESS                         ,
  EV_KEY_RIGHT_RELEASE                       ,
  EV_KEY_OK_PRESS                            ,
  EV_KEY_OK_RELEASE                          ,
  EV_KEY_RETURN_PRESS                        ,
  EV_KEY_RETURN_RELEASE                      ,
  EV_KEY_L_TRIGGER_PRESS                     ,
  EV_KEY_L_TRIGGER_RELEASE                   ,
  EV_KEY_R_TRIGGER_PRESS                     ,
  EV_KEY_R_TRIGGER_RELEASE                   ,
  EV_KEY_START_PRESS                         ,
  EV_KEY_START_RELEASE                       ,
  EV_KEY_SELECT_PRESS                        ,
  EV_KEY_SELECT_RELEASE                      ,


  EV_KEY_TIMEOUT                             ,  // 5 minutes without touching a key
  EV_LONG_KEY_TIMEOUT                        ,  // 15 minutes without touching a key
  EV_VERY_LONG_KEY_TIMEOUT                   ,  // 180 minutes without touching a key
} tUIEvent;

typedef enum
{
  ID_KEY_START     = 0,// 0x01
  ID_KEY_SELECT    = 1,// 0x02
  ID_KEY_R_TRIGGER = 2,// 0x04
  ID_KEY_DOWN      = 3,// 0x08
  ID_KEY_RIGHT     = 4,// 0x10
  ID_KEY_UP        = 5,// 0x20
  ID_KEY_OK        = 6,// 0x40
  ID_KEY_LEFT      = 7,// 0x80
  ID_KEY_L_TRIGGER = 8,// 0x100
  ID_KEY_RETURN    = 9,// 0x200
} tKeyId;

//******************************************************************************
// FUNCTIONS

void     UIForceFullRedraw(void);
void     UIForcePartialRedraw(void);
tUIEvent GetUserInterfaceEvent(void);
void     UIIdle(void);
tRetCode InitUITask(void);
void     ManageUITimers(void);

void    UINotify(void);

#endif

//******************************************************************************
// File: scr_main.c
// Description: Main menu
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
#include "hwplatform.h"
#include <stdio.h>
#include "task_ui.h"

//******************************************************************************
// DEFINES & TYPEDEFS

#define GREY_COLOR  RGB565(240, 240, 240)
#define GREEN_COLOR RGB565(0, 255, 0)

//******************************************************************************
// FUNCTIONS

//******************************************************************************
static void EmphasizeButton(tUIEvent button)
//******************************************************************************
// Description: Emphasize a button setting it to green
// Parameters: button - button to emphasize
// Returns: none
//******************************************************************************
{
  switch (button)
  {
  case EV_FULL_REDRAW:
  case EV_PARTIAL_REDRAW: // All grey
    LCD_DrawRectangle(70,  65, 20, 10, GREY_COLOR);
    LCD_DrawRectangle(150, 65, 20, 10, GREY_COLOR);

    LCD_DrawRectangle(60, 120, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(30, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(90, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(60, 180, 20, 20, GREY_COLOR);

    LCD_DrawRectangle(190, 135, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(160, 165, 20, 20, GREY_COLOR);
    break;
  case EV_KEY_UP_PRESS:
    LCD_DrawRectangle(70,  65, 20, 10, GREY_COLOR);
    LCD_DrawRectangle(150, 65, 20, 10, GREY_COLOR);

    LCD_DrawRectangle(60, 120, 20, 20, GREEN_COLOR);
    LCD_DrawRectangle(30, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(90, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(60, 180, 20, 20, GREY_COLOR);

    LCD_DrawRectangle(190, 135, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(160, 165, 20, 20, GREY_COLOR);
    break;
  case EV_KEY_DOWN_PRESS:
    LCD_DrawRectangle(70,  65, 20, 10, GREY_COLOR);
    LCD_DrawRectangle(150, 65, 20, 10, GREY_COLOR);

    LCD_DrawRectangle(60, 120, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(30, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(90, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(60, 180, 20, 20, GREEN_COLOR);

    LCD_DrawRectangle(190, 135, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(160, 165, 20, 20, GREY_COLOR);
    break;
  case EV_KEY_LEFT_PRESS:
    LCD_DrawRectangle(70,  65, 20, 10, GREY_COLOR);
    LCD_DrawRectangle(150, 65, 20, 10, GREY_COLOR);

    LCD_DrawRectangle(60, 120, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(30, 150, 20, 20, GREEN_COLOR);
    LCD_DrawRectangle(90, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(60, 180, 20, 20, GREY_COLOR);

    LCD_DrawRectangle(190, 135, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(160, 165, 20, 20, GREY_COLOR);
    break;
  case EV_KEY_RIGHT_PRESS:
    LCD_DrawRectangle(70,  65, 20, 10, GREY_COLOR);
    LCD_DrawRectangle(150, 65, 20, 10, GREY_COLOR);

    LCD_DrawRectangle(60, 120, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(30, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(90, 150, 20, 20, GREEN_COLOR);
    LCD_DrawRectangle(60, 180, 20, 20, GREY_COLOR);

    LCD_DrawRectangle(190, 135, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(160, 165, 20, 20, GREY_COLOR);
    break;
  case EV_KEY_OK_PRESS:
    LCD_DrawRectangle(70,  65, 20, 10, GREY_COLOR);
    LCD_DrawRectangle(150, 65, 20, 10, GREY_COLOR);

    LCD_DrawRectangle(60, 120, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(30, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(90, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(60, 180, 20, 20, GREY_COLOR);

    LCD_DrawRectangle(190, 135, 20, 20, GREEN_COLOR);
    LCD_DrawRectangle(160, 165, 20, 20, GREY_COLOR);
    break;
  case EV_KEY_RETURN_PRESS:
    LCD_DrawRectangle(70,  65, 20, 10, GREY_COLOR);
    LCD_DrawRectangle(150, 65, 20, 10, GREY_COLOR);

    LCD_DrawRectangle(60, 120, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(30, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(90, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(60, 180, 20, 20, GREY_COLOR);

    LCD_DrawRectangle(190, 135, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(160, 165, 20, 20, GREEN_COLOR);
    break;
  case EV_KEY_L_TRIGGER_PRESS:
    LCD_DrawRectangle(70,  65, 20, 10, GREEN_COLOR);
    LCD_DrawRectangle(150, 65, 20, 10, GREY_COLOR);

    LCD_DrawRectangle(60, 120, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(30, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(90, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(60, 180, 20, 20, GREY_COLOR);

    LCD_DrawRectangle(190, 135, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(160, 165, 20, 20, GREY_COLOR);
    break;
  case EV_KEY_R_TRIGGER_PRESS:
    LCD_DrawRectangle(70,  65, 20, 10, GREY_COLOR);
    LCD_DrawRectangle(150, 65, 20, 10, GREEN_COLOR);

    LCD_DrawRectangle(60, 120, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(30, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(90, 150, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(60, 180, 20, 20, GREY_COLOR);

    LCD_DrawRectangle(190, 135, 20, 20, GREY_COLOR);
    LCD_DrawRectangle(160, 165, 20, 20, GREY_COLOR);
    break;
  default:
    break;
  }
}

//******************************************************************************
void MainMenuScreenHandler(void)
//******************************************************************************
// Description: Main screen handler
//******************************************************************************
{
  tUIEvent event;

  UIForceFullRedraw(); // When we enter this menu, we have to force full redraw

  for (;;)
  {
    event = GetUserInterfaceEvent();
    switch (event)
    {
    case EV_INIT: break;// Initialization event
    case EV_FULL_REDRAW:
    case EV_PARTIAL_REDRAW:
      // Clear screen
      LCD_DrawRectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0);

      EmphasizeButton(event);
      break;
    case EV_TIMER_20MS:
      break;
    case EV_KEY_UP_PRESS:
      EmphasizeButton(event);
      break;
    case EV_KEY_DOWN_PRESS:
      EmphasizeButton(event);
      break;
    case EV_KEY_LEFT_PRESS:
      EmphasizeButton(event);
      break;
    case EV_KEY_RIGHT_PRESS:
      EmphasizeButton(event);
      break;
    case EV_KEY_OK_PRESS:
      EmphasizeButton(event);
      break;
    case EV_KEY_RETURN_PRESS:
      EmphasizeButton(event);
      break;
    case EV_KEY_L_TRIGGER_PRESS:
      EmphasizeButton(event);
      break;
    case EV_KEY_R_TRIGGER_PRESS:
      EmphasizeButton(event);
      break;
    case EV_KEY_START_PRESS:
      // Apagar
      LCD_DrawRectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0);
      DisablePower();
      SysSleep(500);
      break;
    case EV_KEY_SELECT_PRESS:
      // Apagar
      LCD_DrawRectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0);
      DisablePower();
      SysSleep(500);
      break;
    default: UIIdle();
    }
  }
}


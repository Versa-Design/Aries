//******************************************************************************
// File: sysTick.c
// Description: Systick driver
// Author: Francisco Jose Fabra Collado (VERSA DESIGN S.L.)
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

#include "sysTick.h"
#include "task_ui.h"

#include "tftdriver.h"
#include "sound.h"

//******************************************************************************
// VARIABLES

static const char* TAG = "SYSTICK";

//******************************************************************************
// FUNCTIONS

//******************************************************************************
static bool SysTick_TimerHandler(void* arg)
//******************************************************************************
// Description: systick timer handler
// Parameters: void* arg: not used
// Returns: bool: always true
//******************************************************************************
{
  ManageUITimers();
  TFT_BacklightManage();
  ManageMelody();
  return true;
}

//******************************************************************************
tRetCode SysTick_Init(void)
//******************************************************************************
// Description: initialize systick timer
// Parameters: none
// Returns:
//      tRetCode: error check
//******************************************************************************
{
  timer_config_t timerConf =
  {
    .divider = 8000 , //timer_config_t = 80MHz, so uS precision
    .counter_dir = TIMER_COUNT_UP,
    .counter_en = TIMER_PAUSE,
    .alarm_en = TIMER_ALARM_EN,
    // .intr_type = TIMER_INTR_LEVEL,
    .auto_reload = TIMER_AUTORELOAD_EN,
  };
  
  //Init the timer
  if (ESP_OK != timer_init(SYS_TICK_TIMER_GROUP,SYS_TICK_TIMER_NUM,&timerConf))
  { return RES_ERROR;}
  if (ESP_OK != timer_set_alarm_value(SYS_TICK_TIMER_GROUP, SYS_TICK_TIMER_NUM,
                                      10))
  { return RES_ERROR;}
  if (ESP_OK != timer_enable_intr(SYS_TICK_TIMER_GROUP, SYS_TICK_TIMER_NUM))
  { return RES_ERROR;}
  if (ESP_OK != timer_isr_callback_add(SYS_TICK_TIMER_GROUP, SYS_TICK_TIMER_NUM, 
                                       SysTick_TimerHandler , NULL, 0))
  { return RES_ERROR;}                          
  if (ESP_OK != timer_start(SYS_TICK_TIMER_GROUP, SYS_TICK_TIMER_NUM))
  { return RES_ERROR;}                          
  
  ESP_LOGI(TAG, "SysTick Initialized");
  return RES_OK;
}
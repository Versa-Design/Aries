//******************************************************************************
// File: buzzer.c
// Description: Source code of buzzer controller
// Author: Noe San Fabian (Versa Design S.L.)
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

#include "buzzer.h"

// Common libraries
#include "pcbdefs.h"

// ESP32 libraries
#include "driver/ledc.h"

//******************************************************************************
// DEFINES & TYPEDEFS

#define BUZZER_PWM_RES        LEDC_TIMER_10_BIT    // Duty cycle resolution
#define BUZZER_PWM_MODE       LEDC_LOW_SPEED_MODE  // PWM mode
#define BUZZER_PWM_CH         LEDC_CHANNEL_1       // PWM channel

#define BUZZER_MAX_FREQ       5000 // [Hz]
#define BUZZER_MIN_FREQ       100

//******************************************************************************
// VARIABLES

static uint32_t buzzerDuty = 0;

//******************************************************************************
// FUNCTIONS

//******************************************************************************
tRetCode Buzzer_Init(void)
//******************************************************************************
// Description: This function initializes the buzzer controller
// Parameters: None
// Returns: Error check
//******************************************************************************
{
  ledc_timer_config_t bklTimerCfg = 
  {
    .speed_mode = BUZZER_PWM_MODE,
    .duty_resolution = BUZZER_PWM_RES,
    .timer_num = BUZZER_TIMER_NUM,
    .freq_hz = BUZZER_MIN_FREQ,
    .clk_cfg = LEDC_USE_APB_CLK
  };

  ledc_channel_config_t bklChCfg =
  {
    .channel    = BUZZER_PWM_CH,
    .duty       = buzzerDuty,
    .gpio_num   = GPIO_BUZZER,
    .speed_mode = BUZZER_PWM_MODE,
    .hpoint     = 0,
    .timer_sel  = BUZZER_TIMER_NUM,
    .flags.output_invert = 0
  };

  // Configure PWM timer
  if (ESP_OK != ledc_timer_config(&bklTimerCfg)) { return RES_ERROR;}
  // Configure PWM channel
  if (ESP_OK != ledc_channel_config(&bklChCfg)) { return RES_ERROR;}

  return RES_OK;  
}

//******************************************************************************
static tRetCode Buzzer_Enable(uint32_t enable)
//******************************************************************************
// Description: This function enables/disables the buzzer
// Parameters:
//   uint32_t enable: [0] Disable the buzzer || [>0] Enable the buzzer
// Returns: Error check
//******************************************************************************
{
  if ((buzzerDuty && enable) || (!buzzerDuty && !enable)) {return RES_OK;}
  
  buzzerDuty = (enable) ? ((2 << (BUZZER_PWM_RES - 1)) >> 1) : 0;
  // Set new duty
  if (ESP_OK != ledc_set_duty(BUZZER_PWM_MODE, BUZZER_PWM_CH, buzzerDuty))
  { return RES_ERROR;}
  // Apply duty change
  if (ESP_OK != ledc_update_duty(BUZZER_PWM_MODE, BUZZER_PWM_CH))
  { return RES_ERROR;}

  return RES_OK;
}

//******************************************************************************
tRetCode Buzzer_SetFreq(uint32_t freq)
//******************************************************************************
// Description: This function sets the frequency of the buzzer PWM
// Parameters:
//   uint32_t freq: [Hz] Frequency to set
// Returns: Error check
//******************************************************************************
{
  ledc_timer_config_t bklTimerCfg = 
  {
    .speed_mode = BUZZER_PWM_MODE,
    .duty_resolution = BUZZER_PWM_RES,
    .timer_num = BUZZER_TIMER_NUM,
    .freq_hz = freq,
    .clk_cfg = LEDC_USE_APB_CLK
  };

  // Check if the buzzer should be disabled
  if (0 == freq) { return Buzzer_Enable(0);}

  // Configure PWM frequency
  if ((BUZZER_MIN_FREQ > freq) || (BUZZER_MAX_FREQ < freq))
  { return RES_ERROR_PARAM;}  
  if (ESP_OK != ledc_timer_config(&bklTimerCfg)) { return RES_ERROR;}
  
  return Buzzer_Enable(1);
}


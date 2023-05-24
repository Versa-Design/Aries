//******************************************************************************
// File: screen_backlight.c
// Description: Source code of screen backlight controller
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

#include "screen_backlight.h"

// Common libraries
#include "pcbdefs.h"

//******************************************************************************
// DEFINES & TYPEDEFS

#define BACKLIGHT_PWM_FREQ       1000                // [Hz] PWM frequency
#define BACKLIGHT_PWM_MODE       LEDC_LOW_SPEED_MODE // PWM mode
#define BACKLIGHT_PWM_CH         LEDC_CHANNEL_0      // PWM channel

//******************************************************************************
// VARIABLES

static uint8_t bklInit = 0;

//******************************************************************************
// FUNCTIONS

//******************************************************************************
tRetCode BKL_Init(uint32_t duty)
//******************************************************************************
// Description: This function initializes the screen backlight controller
// Parameters:
//   uint32_t duty: Initial duty cycle to set
// Returns: Error check
//******************************************************************************
{
  ledc_timer_config_t bklTimerCfg = 
  {
    .speed_mode = BACKLIGHT_PWM_MODE,
    .duty_resolution = BACKLIGHT_PWM_RES,
    .timer_num = BACKLIGHT_TIMER_NUM,
    .freq_hz = BACKLIGHT_PWM_FREQ,
    .clk_cfg = LEDC_AUTO_CLK
  };

  ledc_channel_config_t bklChCfg =
  {
    .channel    = BACKLIGHT_PWM_CH,
    .duty       = duty,
    .gpio_num   = GPIO_LCD_BACKLIGHT,
    .speed_mode = BACKLIGHT_PWM_MODE,
    .hpoint     = 0,
    .timer_sel  = BACKLIGHT_TIMER_NUM,
    .flags.output_invert = 0,
    .intr_type  = LEDC_INTR_DISABLE
  };

  if ((2 << (BACKLIGHT_PWM_RES - 1)) <= duty)
  { duty = 2 << (BACKLIGHT_PWM_RES - 1);}
  
  // Configure PWM timer
  if (ESP_OK != ledc_timer_config(&bklTimerCfg)) { return RES_ERROR;}
  // Configure PWM channel
  if (ESP_OK != ledc_channel_config(&bklChCfg)) { return RES_ERROR;}
  bklInit = 1;

  return RES_OK;  
}

//******************************************************************************
tRetCode BKL_Set(uint32_t duty)
//******************************************************************************
// Description: This function sets the duty cycle of the backlight PWM
// Parameters:
//   uint32_t duty: Duty cycle to set
// Returns: Error check
//******************************************************************************
{  
  if (0 == bklInit) { return RES_ERROR;}

  if ((2 << (BACKLIGHT_PWM_RES - 1)) <= duty)
  { duty = 2 << (BACKLIGHT_PWM_RES - 1);}
  // Set new duty
  if (ESP_OK != ledc_set_duty(BACKLIGHT_PWM_MODE, BACKLIGHT_PWM_CH, duty))
  { return RES_ERROR;}
  // Apply duty change
  if (ESP_OK != ledc_update_duty(BACKLIGHT_PWM_MODE, BACKLIGHT_PWM_CH))
  { return RES_ERROR;}

  return RES_OK;
}
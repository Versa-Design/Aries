//******************************************************************************
// File: screen_backlight.h
// Description: Header of screen backlight controller
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

#ifndef SCREEN_BACKLIGHT_H_INCLUDE
#define SCREEN_BACKLIGHT_H_INCLUDE

//******************************************************************************
// INCLUDES

#include "global.h"

// ESP32 libraries
#include "driver/ledc.h"

//******************************************************************************
// DEFINES & TYPEDEFS

#define BACKLIGHT_PWM_RES     LEDC_TIMER_10_BIT   // Duty cycle resolution

//******************************************************************************
// VARIABLES

//******************************************************************************
// FUNCTIONS

tRetCode BKL_Init(uint32_t duty);

tRetCode BKL_Set(uint32_t duty);


#endif
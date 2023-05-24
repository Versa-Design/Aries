//******************************************************************************
// File: sysTick.h
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

#ifndef SYS_TICK_H
#define SYS_TICK_H

//******************************************************************************
// INCLUDES

#include "driver/periph_ctrl.h"
#include "soc/timer_group_struct.h"
#include "driver/timer.h"
#include "global.h"
#include "pcbdefs.h"
#include "esp_log.h"

//******************************************************************************
// FUNCTIONS

tRetCode SysTick_Init(void);



#endif
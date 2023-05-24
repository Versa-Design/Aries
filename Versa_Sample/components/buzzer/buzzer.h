//******************************************************************************
// File: buzzer.h
// Description: Header of buzzer controller
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

#ifndef BUZZER_H_INCLUDE
#define BUZZER_H_INCLUDE

//******************************************************************************
// INCLUDES

#include "global.h"

//******************************************************************************
// FUNCTIONS

tRetCode Buzzer_Init(void);

tRetCode Buzzer_SetFreq(uint32_t freq);

#endif
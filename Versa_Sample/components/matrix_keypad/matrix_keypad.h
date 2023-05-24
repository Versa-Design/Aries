//******************************************************************************
// File: matrix_keypad.h
// Description: header file for matrix keypad
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

#ifndef MATRIX_KEYPAD_H_INCLUDE
#define MATRIX_KEYPAD_H_INCLUDE

//******************************************************************************
// INCLUDES

// Project
#include "global.h" // tRetCode


//-----------------------------------------------------------------------------
// Module definitions

#define MAX_BUTTON_COUNTER         30
#define BUTTON_PRESSED_THRESHOLD   (2*MAX_BUTTON_COUNTER/3)
#define BUTTON_RELEASED_THRESHOLD  (1*MAX_BUTTON_COUNTER/3)

//-----------------------------------------------------------------------------
// Exported functions
uint32_t Keypad_GetPressedCode(void);
tRetCode Keypad_Init(void);

#endif
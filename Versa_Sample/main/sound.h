//******************************************************************************
// File: sound.h
// Description: sound manager
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

#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

//******************************************************************************
// INCLUDES

#include <stdint.h>

//******************************************************************************
// VARIABLES

extern const uint16_t melKeyBeep[];
extern const uint16_t melIntro[];

//******************************************************************************
// FUNCTIONS

void ManageMelody(void);
void PlayMelody(const uint16_t *array);

#endif
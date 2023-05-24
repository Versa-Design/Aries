//******************************************************************************
// File: sound.c
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

//******************************************************************************
// INCLUDES

#include <stdint.h>
#include "global.h"
#include "hwplatform.h"
#include "buzzer.h"

//******************************************************************************
// VARIABLES

//------------------------------------------------------------------------------
// Melodies

const uint16_t melKeyBeep[] =
{
  2000,20,
  0,0
};

const uint16_t melIntro[] = 
{
  2000,20,
  2200,20,
  2400,20,
  0,0
};

//------------------------------------------------------------------------------
// Local variables

static uint16_t *currMelodyPtr;   // Pointer to the current melody
static uint16_t remTime;          // Remaining ticks for the current sound

//******************************************************************************
// FUNCTIONS

//******************************************************************************
static void DoBeep(uint16_t f)
//******************************************************************************
// Description: starts/stops the timer that generates the sound
// Parameter:
//   uint16_t f: frequency
//******************************************************************************
{
  Buzzer_SetFreq(f);
}

//******************************************************************************
void ManageMelody(void)
//******************************************************************************
// Description: manages the current melody in the systick interrupt
// Parameters: none - Returns: none
//******************************************************************************
{
  uint16_t freq;
  if (currMelodyPtr == NULL) return;
  if (remTime > 0) { remTime--; return; }
  freq = *currMelodyPtr++;
  remTime = *currMelodyPtr++;
  if (remTime == 0) { currMelodyPtr = NULL; DoBeep(0); return; }
  DoBeep(freq);
}

//******************************************************************************
void PlayMelody(const uint16_t *array)
//******************************************************************************
// Description: plays a melody
// Parameters: array - pointer to the array that contains the melody
// Returns: none
//******************************************************************************
{
  if (array == NULL) { currMelodyPtr = NULL; DoBeep(0); }

  currMelodyPtr = (uint16_t *) array;
  remTime = 0;
}
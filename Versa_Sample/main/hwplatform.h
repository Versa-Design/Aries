//******************************************************************************
// File: hwplatform.h
// Description: Hardware platform export
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

#ifndef HWPLATFORM_H_INCLUDE
#define HWPLATFORM_H_INCLUDE

//******************************************************************************
// INCLUDES

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "esp_system.h"
#include "esp_log.h"

#include <esp_types.h>
#include "esp_err.h"
#include "esp_intr_alloc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/xtensa_api.h"
#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "soc/soc.h"
#include "esp_log.h"
#include "soc/gpio_periph.h"
#include "esp_ipc.h"
#include "esp_system.h"

#include "sound.h"

//******************************************************************************
// DEFINES & TYPEDEFS

#ifndef ENTER_CRITICAL
#define ENTER_CRITICAL(a) portENTER_CRITICAL(a)
#endif // portENTER_CRITICAL

#ifndef EXIT_CRITICAL
#define EXIT_CRITICAL(a) portEXIT_CRITICAL(a)
#endif



//******************************************************************************
// FUNCTIONS

void SysSleep(uint32_t waitTime);

uint8_t IsKeyPressedLowLevel(uint32_t i);

void EnablePower(void);
void DisablePower(void);

#endif

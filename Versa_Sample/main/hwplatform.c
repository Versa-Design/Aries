//******************************************************************************
// File: hwplatform.c
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

//******************************************************************************
// INCLUDES

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hwplatform.h"
#include "pcbdefs.h"
#include "matrix_keypad.h"

//******************************************************************************
// FUNCTIONS

//******************************************************************************
void SysSleep(uint32_t waitTime)
//******************************************************************************
// Description: this function implements a delay in milliseconds
// Parameters: waitTime: delay in milliseconds
// Returns: nothing
//******************************************************************************
{
  vTaskDelay(waitTime / portTICK_PERIOD_MS);
}

//******************************************************************************
uint8_t IsKeyPressedLowLevel(uint32_t i)
//******************************************************************************
// Description: this function returns the status of a key
// Parameters: i: key number
// Returns: TRUE if the key is pressed, FALSE otherwise
//******************************************************************************
{
  return (Keypad_GetPressedCode() & (1<<i))?TRUE:FALSE;
}

//******************************************************************************
void EnablePower(void)
//******************************************************************************
// Description: this function initializes the GPIOs for normal operation
// Parameters: none
// Returns: nothing
//******************************************************************************
{
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE; // disable interrupt
  io_conf.mode = GPIO_MODE_OUTPUT; //set as output mode
  io_conf.pin_bit_mask = 1<<GPIO_ENPWR;
  io_conf.pull_down_en = 0; //disable pull-down mode
  io_conf.pull_up_en = 0;   //disable pull-up mode
  gpio_config(&io_conf);    //configure GPIO with the given settings

  gpio_set_level(GPIO_ENPWR, 1);
}

//******************************************************************************
void DisablePower(void)
//******************************************************************************
// Description: this function removes power from the device
// Parameters: none
// Returns: nothing
//******************************************************************************
{
  gpio_set_level(GPIO_ENPWR, 0);
}
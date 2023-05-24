//******************************************************************************
// File: main.c
// Description: main program
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

//******************************************************************************
// INCLUDES

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "nvs_flash.h"

#include "rom/gpio.h"
#include "driver/gpio.h"
#include "driver/periph_ctrl.h"

#include "global.h"
#include "pcbdefs.h"
#include "hwplatform.h"
#include "sysTick.h"
#include "task_ui.h"
#include "matrix_keypad.h"
#include "buzzer.h"

//******************************************************************************
// VARIABLES

static const char* TAG = "MAIN";

//******************************************************************************
// FUNCTIONS

//******************************************************************************
static void NvsFlash_Init(void)
//******************************************************************************
// Description: nvs flash initialization
// Parameters: none - Returns: error check
//******************************************************************************
{
  esp_err_t ret = nvs_flash_init();
  if ( (ret == ESP_ERR_NVS_NO_FREE_PAGES) || 
       (ret == ESP_ERR_NVS_NEW_VERSION_FOUND) )
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

}

//******************************************************************************
void app_main()
//******************************************************************************
// Description: main entry function
// Parameters: none - Returns: nothing
//******************************************************************************
{
  EnablePower();
  //Display mC info
  ESP_LOGI(TAG, "Free memory: %d bytes", esp_get_free_heap_size());
  ESP_LOGI(TAG, "IDF version: %s", esp_get_idf_version());
  
  esp_log_level_set("gpio", ESP_LOG_WARN); //reset them all to log info level
  
  // Initialize NVS.
  NvsFlash_Init();

  // Initialize buzzer
  if (RES_OK != Buzzer_Init())
  { ESP_LOGE(TAG, "Initializing buzzer controller"); goto error; }

  //Initialize system tick
  if (SysTick_Init() != RES_OK)
  { ESP_LOGE(TAG, "Initializing sys tick"); goto error; }

  Keypad_Init();

  InitUITask();

  while (1) SysSleep(1000);


  return;
error:
  while(1)
  {
    SysSleep(1000);
    ESP_LOGE(TAG, "[FATAL ERROR] Initialization"); 
  }
}
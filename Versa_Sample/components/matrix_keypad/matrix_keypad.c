//******************************************************************************
// File: matrix_keypad.c
// Description: source file for button manager. 
// This is done for a 3x3 matrix with an extra button
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

// Project
#include "pcbdefs.h"

// SDK
#include "driver/timer.h"
#include "driver/gpio.h"

// Module include
#include "matrix_keypad.h"

//******************************************************************************
// DEFINES

// This definition is internal and should not be exported outside
typedef enum
{
  KEYPAD_STATE_UNDEFINED = 0,
  KEYPAD_STATE_1 = 1,
  KEYPAD_STATE_2 = 2,
  KEYPAD_STATE_3 = 3,
} tKeypadState;

#define BTN_KEY_CODE 0x200

#define KEYPAD_MASK_OFF_PIN_1 ((((uint64_t)1) << KEYPAD_COLUMN_PIN_2) | \
                               (((uint64_t)1) << KEYPAD_COLUMN_PIN_3))
#define KEYPAD_MASK_OFF_PIN_2 ((((uint64_t)1) << KEYPAD_COLUMN_PIN_1) | \
                               (((uint64_t)1) << KEYPAD_COLUMN_PIN_3))
#define KEYPAD_MASK_OFF_PIN_3 ((((uint64_t)1) << KEYPAD_COLUMN_PIN_1) | \
                               (((uint64_t)1) << KEYPAD_COLUMN_PIN_2))

#define KEYPAD_MASK_ON_PIN_1  (((uint64_t)1) << KEYPAD_COLUMN_PIN_1)
#define KEYPAD_MASK_ON_PIN_2  (((uint64_t)1) << KEYPAD_COLUMN_PIN_2)
#define KEYPAD_MASK_ON_PIN_3  (((uint64_t)1) << KEYPAD_COLUMN_PIN_3)

//-----------------------------------------------------------------------------
// Module variables
static tKeypadState keypadState = KEYPAD_STATE_UNDEFINED;
static uint32_t currentKeyMask = 0;
static uint32_t buttonCounter[MAX_KEYS] = {0};
static uint32_t keyMask = 0;

//******************************************************************************
static void GetKeypadInputState(void)
//******************************************************************************
// Description: this function updates the currentKeyMask variable with the
//              current state of the keypad at the given row
// Parameters: none
// Returns: nothing
//******************************************************************************
{
  uint32_t v;
  switch (keypadState)
  {
  case KEYPAD_STATE_1: v = 1 << 0; break; 
  case KEYPAD_STATE_2: v = 1 << 3; break;
  case KEYPAD_STATE_3: v = 1 << 6; break;
  case KEYPAD_STATE_UNDEFINED: 
  default: return;
  }
  if (!gpio_get_level(KEYPAD_ROW_PIN_1)) { currentKeyMask |= v;}
  else                                  { currentKeyMask &= ~v;}
  v <<= 1;
  if (!gpio_get_level(KEYPAD_ROW_PIN_2)) { currentKeyMask |= v;}
  else                                  { currentKeyMask &= ~v;}
  v <<= 1;
  if (!gpio_get_level(KEYPAD_ROW_PIN_3)) { currentKeyMask |= v;}
  else                                  { currentKeyMask &= ~v;}
  if (!gpio_get_level(DIRECT_BUTTON_PIN)){ currentKeyMask |= BTN_KEY_CODE;}
  else                                  { currentKeyMask &= ~BTN_KEY_CODE;}
}

//******************************************************************************
static void ManageKeyAntiBounce(void)
//******************************************************************************
// Description: this function manages the anti-bouncing algorithm of the keys
// To be called once each exploration cycle
// Parameters: none
// Returns: nothing
//******************************************************************************
{
  uint32_t i;
  for (i = 0; i<MAX_KEYS; i++)
  {
    if (currentKeyMask & (1 << i))
    {
      if (buttonCounter[i] < MAX_BUTTON_COUNTER)       { buttonCounter[i]++;}
      if (buttonCounter[i] > BUTTON_PRESSED_THRESHOLD) {keyMask |= (1 << i);}
    }
    else
    {
      if (buttonCounter[i] > 0)                         { buttonCounter[i]--;}
      if (buttonCounter[i] < BUTTON_RELEASED_THRESHOLD) { keyMask &= ~(1 << i);}
    }
  }
}

//******************************************************************************
void KeypadStateMachine(void)
//******************************************************************************
// Description: keypad state machine. This explores the key matrix and detects
//              key presses and releases.
// Parameters: none
// Returns: none
//******************************************************************************
{    
  switch (keypadState)
  {
  case KEYPAD_STATE_UNDEFINED:
    keypadState = KEYPAD_STATE_1;
    break;
  case KEYPAD_STATE_1:
    GetKeypadInputState();
    gpio_set_direction(KEYPAD_COLUMN_PIN_2, GPIO_MODE_INPUT);
    gpio_set_direction(KEYPAD_COLUMN_PIN_3, GPIO_MODE_INPUT);
    gpio_set_direction(KEYPAD_COLUMN_PIN_1, GPIO_MODE_OUTPUT);
    gpio_set_level(KEYPAD_COLUMN_PIN_1, 0);
    keypadState = KEYPAD_STATE_2;
    break;
  case KEYPAD_STATE_2:
    GetKeypadInputState();
    gpio_set_direction(KEYPAD_COLUMN_PIN_1, GPIO_MODE_INPUT);
    gpio_set_direction(KEYPAD_COLUMN_PIN_3, GPIO_MODE_INPUT);
    gpio_set_direction(KEYPAD_COLUMN_PIN_2, GPIO_MODE_OUTPUT);
    gpio_set_level(KEYPAD_COLUMN_PIN_2, 0);
    keypadState = KEYPAD_STATE_3;
    break;
  case KEYPAD_STATE_3:
    GetKeypadInputState();
    gpio_set_direction(KEYPAD_COLUMN_PIN_1, GPIO_MODE_INPUT);
    gpio_set_direction(KEYPAD_COLUMN_PIN_2, GPIO_MODE_INPUT);
    gpio_set_direction(KEYPAD_COLUMN_PIN_3, GPIO_MODE_OUTPUT);
    gpio_set_level(KEYPAD_COLUMN_PIN_3, 0);
    ManageKeyAntiBounce(); // In the last state we have to update the key mask
    keypadState = KEYPAD_STATE_1;
    break;
  }
}

//******************************************************************************
static bool Keypad_TimerHandler(void* arg)
//******************************************************************************
// Description: This function handles the timer handler
// Parameters: None
// Returns: bool
//******************************************************************************
{
  KeypadStateMachine();
  return true;
}

//******************************************************************************
uint32_t Keypad_GetPressedCode(void)
//******************************************************************************
// Description: this function returns the key mask of the keys that are pressed
// Parameters: none
// Returns: key mask
//******************************************************************************
{
  return keyMask;
}

//******************************************************************************
tRetCode Keypad_Init(void)
//******************************************************************************
// Description: this function initializes the keypad
// Parameters: None
// Returns: error check
//******************************************************************************
{
  gpio_config_t cfgRowGpio = {0}, cfgColGpio = {0};

  // Configure row gpio as input
  cfgRowGpio.mode = GPIO_MODE_INPUT;
  cfgRowGpio.pull_up_en = GPIO_PULLUP_DISABLE;
  cfgRowGpio.pull_down_en = GPIO_PULLDOWN_DISABLE;
  cfgRowGpio.pin_bit_mask = (((uint64_t)1) << KEYPAD_ROW_PIN_1) | 
                            (((uint64_t)1) << KEYPAD_ROW_PIN_2) | 
                            (((uint64_t)1) << KEYPAD_ROW_PIN_3) | 
                            (((uint64_t)1) << DIRECT_BUTTON_PIN);
  cfgRowGpio.intr_type = GPIO_INTR_DISABLE;
  if (ESP_OK != gpio_config(&cfgRowGpio)) return RES_ERROR;

  // Configure column gpio
  cfgColGpio.mode = GPIO_MODE_DISABLE;
  cfgColGpio.pull_up_en = GPIO_PULLUP_DISABLE;
  cfgColGpio.pull_down_en = GPIO_PULLDOWN_DISABLE;
  cfgColGpio.pin_bit_mask = (((uint64_t)1) << KEYPAD_COLUMN_PIN_1) | 
                            (((uint64_t)1) << KEYPAD_COLUMN_PIN_2) | 
                            (((uint64_t)1) << KEYPAD_COLUMN_PIN_3);
  cfgColGpio.intr_type = GPIO_INTR_DISABLE;
  if (ESP_OK != gpio_config(&cfgColGpio)) return RES_ERROR;

  // Configure timer, default clock source is APB
  timer_config_t cfgTimer = {
      .divider = 800,         // 100000 ticks/s
      .counter_dir = TIMER_COUNT_UP,
      .counter_en = TIMER_PAUSE,
      .alarm_en = TIMER_ALARM_EN,
      .auto_reload = TIMER_AUTORELOAD_EN,
  }; 
  if (ESP_OK != timer_init(KEYPAD_TIMER_GROUP, KEYPAD_TIMER_NUM, &cfgTimer))
    { return RES_ERROR;}
  if (ESP_OK != timer_set_alarm_value(KEYPAD_TIMER_GROUP, KEYPAD_TIMER_NUM, 
                                      10))
    { return RES_ERROR;}                                    
  if (ESP_OK != timer_enable_intr(KEYPAD_TIMER_GROUP, KEYPAD_TIMER_NUM))
    { return RES_ERROR;}
  if (ESP_OK != timer_isr_callback_add(KEYPAD_TIMER_GROUP, KEYPAD_TIMER_NUM, 
                          Keypad_TimerHandler , NULL, 0))
    { return RES_ERROR;}                          

  if (ESP_OK != timer_start(KEYPAD_TIMER_GROUP, KEYPAD_TIMER_NUM))
  { return RES_ERROR;}

  return RES_OK;
}
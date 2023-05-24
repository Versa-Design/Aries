//******************************************************************************
//  File: pcbdefs.h
//  Description: PCB specific pins defines
//  Author: Francisco Jose Fabra Collado (VERSA DESIGN S.L.)
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

#ifndef _PCBDEFS_H_INCLUDED_
#define _PCBDEFS_H_INCLUDED_

//******************************************************************************
// INCLUDES

#include "driver/gpio.h"

//******************************************************************************
// DEFINES & TYPEDEFS

//** SYS TICK **
#define SYS_TICK_TIMER_GROUP    TIMER_GROUP_0
#define SYS_TICK_TIMER_NUM      TIMER_1

#define KEYPAD_TIMER_GROUP      TIMER_GROUP_1
#define KEYPAD_TIMER_NUM        TIMER_0

#define BACKLIGHT_TIMER_NUM     LEDC_TIMER_0

#define BUZZER_TIMER_NUM        LEDC_TIMER_3

#define GPIO_LCD_D0     2
#define GPIO_LCD_D1     4
#define GPIO_LCD_D2    16
#define GPIO_LCD_D3    17
#define GPIO_LCD_D4     5
#define GPIO_LCD_D5    18
#define GPIO_LCD_D6    19
#define GPIO_LCD_D7    21
#define GPIO_LCD_DATA_BUS_MASK  ((1ULL<<GPIO_LCD_D0) |  \
                                 (1ULL<<GPIO_LCD_D1) |  \
                                 (1ULL<<GPIO_LCD_D2) |  \
                                 (1ULL<<GPIO_LCD_D3) |  \
                                 (1ULL<<GPIO_LCD_D4) |  \
                                 (1ULL<<GPIO_LCD_D5) |  \
                                 (1ULL<<GPIO_LCD_D6) |  \
                                 (1ULL<<GPIO_LCD_D7))



#define GPIO_LCD_RD    27
#define GPIO_LCD_WR    14
#define GPIO_LCD_DC    12
#define GPIO_LCD_CS    13
#define GPIO_LCD_RESET 22

#define GPIO_LCD_CTRL_BUS_MASK  ((1ULL<<GPIO_LCD_RD) |  (1ULL<<GPIO_LCD_WR) |  \
                                 (1ULL<<GPIO_LCD_DC) |  (1ULL<<GPIO_LCD_CS) |  \
                                 (1ULL<<GPIO_LCD_RESET))



#define GPIO_ENPWR 23


#define GPIO_LCD_BACKLIGHT    15

#define GPIO_BUZZER           26

#define MAX_KEYS 10

#define KEYPAD_COLUMN_PIN_1 GPIO_NUM_32
#define KEYPAD_COLUMN_PIN_2 GPIO_NUM_25
#define KEYPAD_COLUMN_PIN_3 GPIO_NUM_33

#define KEYPAD_ROW_PIN_1  GPIO_NUM_34
#define KEYPAD_ROW_PIN_2  GPIO_NUM_39
#define KEYPAD_ROW_PIN_3  GPIO_NUM_36
#define DIRECT_BUTTON_PIN GPIO_NUM_35

#endif

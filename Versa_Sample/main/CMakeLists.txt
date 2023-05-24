
idf_component_register(SRCS "main.c" "hwplatform.c" "sound.c" "sysTick.c" "task_ui.c" "tftdriver.c" "scr_main.c"
                       INCLUDE_DIRS "."
                       REQUIRES "driver" "freertos" "esp_system" "matrix_keypad" "screen" "buzzer" "nvs_flash")

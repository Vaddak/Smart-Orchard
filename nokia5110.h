// LIBRERÍA PARA EL DISPLAY NOKIA 5110

#ifndef NOKIA5110_H
#define NOKIA5110_H

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void lcd_send_byte(uint8_t data, bool is_data);
void LCD_init();
void LCD_clrScr();
void LCD_goXY(int x, int y);
void LCD_print_char(char c);
void LCD_print(const char* str, int x, int y) ;
void spi_initial_config();

#endif


/*

x (columna) de 0 a 13
y (fila) de 0 a 5

EJEMPLO DE UN HOLA MUNDO BÁSICO


void app_main() {
   spi_initial_config();
   LCD_init();
   LCD_clrScr();
   while (true) {
       
       LCD_print("Esto", 0, 0);
       vTaskDelay(SLEEP_DEFAULT / portTICK_PERIOD_MS);
       LCD_print("Es Una", 0, 1);
       vTaskDelay(SLEEP_DEFAULT / portTICK_PERIOD_MS);
       LCD_print("Pruebita", 0, 2);
       vTaskDelay(SLEEP_DEFAULT / portTICK_PERIOD_MS);
       

   }
}

*/
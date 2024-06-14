#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h> // Incluir inttypes.h para PRIu32
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "rom/ets_sys.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#include "sdkconfig.h"

#include "KY-018.h"
#include "nokia5110.h"
#include "YL-69.h"
#include "dht22.h"


#ifndef portTICK_RATE_MS
#define portTICK_RATE_MS portTICK_PERIOD_MS
#endif

#define pin_relay_bomba 25
#define pin_relay_ventilador 27

void setup_gpio() {
    gpio_set_direction(pin_relay_bomba, GPIO_MODE_OUTPUT);
    gpio_set_level(pin_relay_bomba, 0);
    gpio_set_direction(pin_relay_ventilador, GPIO_MODE_OUTPUT);
    gpio_set_level(pin_relay_ventilador, 0);
}


void app_main(){
   setup_gpio();
   init_adc();
   init_light_sensor(); 
   nvs_flash_init();
   spi_initial_config();
   LCD_init();
   LCD_clrScr();
   
   
  
    while(1){

      // Leer la humedad y temperatura del aire
      
      int ret = readDHT();
      errorHandler(ret);
      printf("Humedad Aire %.2f %%\n", getHumidity());
      printf("Temperatura Aire %.2f degC\n\n", getTemperature());


      // Leer la intensidad de luz
      uint32_t light_intensity = read_light_intensity(); // Leer la intensidad de luz
      uint32_t light_percentage = map_light_intensity_to_percentage(light_intensity); // Convertir la intensidad de luz a un porcentaje
      printf("Intensidad de luz: %" PRIu32 "%%\n", light_percentage); // Imprimir la intensidad de la luz

      // Leer la humedad del suelo
       uint32_t humidity = read_humidity();
      // Leer voltaje del sensor de humedad del suelo
      int voltage = read_voltage();
      printf("Voltaje del sensor: %d mV, Humedad del suelo: %" PRIu32 "%%\n", voltage, humidity); // Imprimir el voltaje y la humedad del suelo

       // Imprimir por nokia 5110
        char hum[10];
        char temperatura[10];
        char luz[10];
        char suelo[10];
        snprintf(hum, sizeof(hum), "%.2f%%", getHumidity());
        snprintf(temperatura, sizeof(temperatura), "%.2fC", getTemperature());
        snprintf(luz, sizeof(luz), "%" PRIu32 "%%", light_percentage);
        snprintf(suelo, sizeof(suelo), "%" PRIu32 "%%", humidity);
 
       LCD_print("Air Hum", 0, 0);
       LCD_print(hum, 50, 0);

       LCD_print("Air Temp", 0, 1);
       LCD_print(temperatura, 60, 1);

       LCD_print("Light", 0, 2);
       LCD_print(luz, 50, 2);

       LCD_print("Soil Hum", 0, 3);
       LCD_print(suelo, 60, 3);

       if(*luz > 80){
         printf("Mucha Luz!\n");
         LCD_print("Mucha Luz!", 0, 4);
         gpio_set_level(pin_relay_ventilador, 1);
       }

      // Encender la bomba si la humedad del suelo es menor a 5% durante 1 segundo
      if(*hum < 5){
        LCD_print("Falta de Humedad!", 0, 5);
        LCD_print("Encendiendo Bomba", 0, 6);
        printf("Falta de Humedad!\n");
        printf("Encendiendo Bomba\n");
        gpio_set_level(pin_relay_bomba, 1);
        vTaskDelay(1000 / portTICK_RATE_MS);
      }

      //
      
}

}
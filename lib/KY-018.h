#ifndef KY_018_H
#define KY_018_H

#include <stdint.h>
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"

// Declaraciones de funciones
void init_light_sensor(void);
uint32_t read_light_intensity(void);
int read_light_voltage(void);
uint32_t map_light_intensity_to_percentage(uint32_t adc_value);

#endif // KY_018_H


/*
EJEMPLO CON GPIO39  (ADC1_CHANNEL_3)


static const char *TAG = "Light Sensor Example";

void app_main() {
   init_light_sensor();

   while (1) {
       // Leer la intensidad de luz
       uint32_t light_intensity = read_light_intensity();

       // Convertir la intensidad de luz a un porcentaje
       uint32_t light_percentage = map_light_intensity_to_percentage(light_intensity);

       // Leer el voltaje del sensor de luz
       int voltage = read_light_voltage();
       
       ESP_LOGI(TAG, "Voltaje del sensor: %d mV, Intensidad de luz: %" PRIu32 "%% (ADC: %" PRIu32 ")", voltage, light_percentage, light_intensity);

       // Esperar un segundo antes de la siguiente lectura
       vTaskDelay(pdMS_TO_TICKS(1000));
   }
}
*/
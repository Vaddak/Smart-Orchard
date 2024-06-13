#ifndef YL_69_H
#define YL_69_H

#include <stdint.h>
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"

// Declaraciones de funciones
void init_adc(void);
uint32_t map_humidity(uint32_t adc_value);
uint32_t read_humidity(void);
int read_voltage(void);

#endif // YL_69_H



/*
    EJEMPLO USANDO GPIO 38

    static const char *TAG = "ADC Example";

void app_main() {
   init_adc();

   while (1) {
       // Leer la humedad del suelo
       uint32_t humidity = read_humidity();

       // Leer el voltaje del sensor
       int voltage = read_voltage();
       
       ESP_LOGI(TAG, "Voltaje del sensor: %d mV, Humedad del suelo: %" PRIu32 "%%", voltage, humidity);

       // Esperar un segundo antes de la siguiente lectura
       vTaskDelay(pdMS_TO_TICKS(1000));
   }
}

*/

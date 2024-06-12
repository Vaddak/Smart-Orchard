#include "YL-69.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_adc/adc_cali_scheme.h"

#define NO_OF_SAMPLES   64          // Número de muestras para promediar

static const char *TAG = "ADC Example";
static adc_oneshot_unit_handle_t adc1_handle;
static adc_cali_handle_t cali_handle;

void init_adc() {
   // Inicializar el ADC
   adc_oneshot_unit_init_cfg_t init_config = {
       .unit_id = ADC_UNIT_1,
   };
   adc_oneshot_new_unit(&init_config, &adc1_handle);

   adc_oneshot_chan_cfg_t config = {
       .bitwidth = ADC_BITWIDTH_DEFAULT,
       .atten = ADC_ATTEN_DB_0,
   };
   adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_0, &config); // Usando GPIO36

   // Calibración del ADC
   adc_cali_line_fitting_config_t cali_config = {
       .unit_id = ADC_UNIT_1,
       .atten = ADC_ATTEN_DB_0,
       .bitwidth = ADC_BITWIDTH_DEFAULT,
   };
   esp_err_t cali_ret = adc_cali_create_scheme_line_fitting(&cali_config, &cali_handle);
   if (cali_ret != ESP_OK) {
       ESP_LOGE(TAG, "Calibración del ADC fallida");
       cali_handle = NULL;
   }
}

// Función para mapear el valor del ADC a un porcentaje de humedad
uint32_t map_humidity(uint32_t adc_value) {
   // El valor del ADC va de 0 a 4095 para un ESP32 (12 bits)
   // Normalizamos a una escala de 0 a 100
   uint32_t humidity = (100 * (4095 - adc_value)) / 4095;
   return humidity;
}

uint32_t read_humidity() {
   uint32_t adc_reading = 0;
   // Multisampling
   for (int i = 0; i < NO_OF_SAMPLES; i++) {
       int raw;
       adc_oneshot_read(adc1_handle, ADC_CHANNEL_0, &raw); // Usando GPIO36
       adc_reading += raw;
   }
   adc_reading /= NO_OF_SAMPLES;
   return map_humidity(adc_reading);
}

int read_voltage() {
   uint32_t adc_reading = 0;
   // Multisampling
   for (int i = 0; i < NO_OF_SAMPLES; i++) {
       int raw;
       adc_oneshot_read(adc1_handle, ADC_CHANNEL_0, &raw); // Usando GPIO36
       adc_reading += raw;
   }
   adc_reading /= NO_OF_SAMPLES;

   // Convertir la lectura ADC a voltaje en mV
   int voltage = 0;
   if (cali_handle != NULL) {
       adc_cali_raw_to_voltage(cali_handle, adc_reading, &voltage);
   } else {
       ESP_LOGW(TAG, "Calibración no disponible, usando lectura sin calibrar");
       voltage = adc_reading * 3300 / 4095; // Aproximación del voltaje sin calibración
   }
   return voltage;
}
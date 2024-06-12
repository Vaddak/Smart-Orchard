#include "KY-018.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_adc/adc_cali_scheme.h"

#define NO_OF_SAMPLES   64          // Número de muestras para promediar

static const char *TAG = "Light Sensor";
static adc_oneshot_unit_handle_t adc1_handle;
static adc_cali_handle_t cali_handle;

void init_light_sensor() {
   // Inicializar el ADC
   adc_oneshot_unit_init_cfg_t init_config = {
       .unit_id = ADC_UNIT_1,
   };
   adc_oneshot_new_unit(&init_config, &adc1_handle);

   adc_oneshot_chan_cfg_t config = {
       .bitwidth = ADC_BITWIDTH_DEFAULT,
       .atten = ADC_ATTEN_DB_0,
   };
   adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_3, &config); // Usando GPIO39

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

uint32_t read_light_intensity() {
   uint32_t adc_reading = 0;
   // Multisampling
   for (int i = 0; i < NO_OF_SAMPLES; i++) {
       int raw;
       adc_oneshot_read(adc1_handle, ADC_CHANNEL_3, &raw); // Usando GPIO39
       adc_reading += raw;
   }
   adc_reading /= NO_OF_SAMPLES;
   return adc_reading;
}

int read_light_voltage() {
   uint32_t adc_reading = 0;
   // Multisampling
   for (int i = 0; i < NO_OF_SAMPLES; i++) {
       int raw;
       adc_oneshot_read(adc1_handle, ADC_CHANNEL_3, &raw); // Usando GPIO39
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

uint32_t map_light_intensity_to_percentage(uint32_t adc_value) {
   // Invertir el valor del ADC para que 0 sea 100% y 4095 sea 0%
   return 100 - ((adc_value * 100) / 4095);
}

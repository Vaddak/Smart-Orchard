#ifndef DHT22_H_  
#define DHT22_H_

#define DHT_OK 0
#define DHT_CHECKSUM_ERROR -1
#define DHT_TIMEOUT_ERROR -2

// == function prototypes =======================================
void  setDHTgpio(int gpio);
void  errorHandler(int response);
int   readDHT();
float getHumidity();
float getTemperature();
int   getSignalLevel( int usTimeOut, bool state );

#endif



/*
    ejemplo con gpio 17

    #ifndef portTICK_RATE_MS
#define portTICK_RATE_MS portTICK_PERIOD_MS
#endif

void DHT_reader_task(void *pvParameter)
{
   setDHTgpio(17);

   while(1) {
       printf("DHT Sensor Readings\n" );
       int ret = readDHT();
       
       errorHandler(ret);

       printf("Humidity %.2f %%\n", getHumidity());
       printf("Temperature %.2f degC\n\n", getTemperature());
       
       vTaskDelay(2000 / portTICK_RATE_MS);
   }
}

void app_main()
{
   nvs_flash_init();
   vTaskDelay(2000 / portTICK_RATE_MS);
   xTaskCreate(&DHT_reader_task, "DHT_reader_task", 2048, NULL, 5, NULL);
}


*/
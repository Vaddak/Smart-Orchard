#ifndef MYWIFI_H
#define MYWIFI_H

#include "esp_err.h"

#define DEFAULT_SSID "sebas"
#define DEFAULT_PWD "1234567890"

void wifi_init_sta(void);

#endif // MYWIFI_H

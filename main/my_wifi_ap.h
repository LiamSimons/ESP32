#ifndef MY_WIFI_AP_H
#define MY_WIFI_AP_H

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

void wifi_init_sta(void);
static void event_handler(void* arg, esp_event_base_t event_base,
                                  int32_t event_id, void* event_data);

#endif
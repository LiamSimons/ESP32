#ifndef MY_CONFIG_H
#define MY_CONFIG_H

#include <esp_event.h>

#define AP_ESP_WIFI_SSID      CONFIG_ESP_WIFI_SSID
#define AP_ESP_WIFI_PASS      CONFIG_ESP_WIFI_PASSWORD
#define AP_ESP_WIFI_CHANNEL   CONFIG_ESP_WIFI_CHANNEL
#define AP_MAX_STA_CONN       CONFIG_ESP_MAX_STA_CONN

static const char *TAG = "FreeRTOSDemo";
SemaphoreHandle_t xMutex_ON;
SemaphoreHandle_t xMutex_OFF;

#endif
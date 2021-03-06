#ifndef MY_CONFIG_H
#define MY_CONFIG_H

#include <esp_event.h>
#include <esp_sleep.h>

#define AP_ESP_WIFI_SSID      CONFIG_ESP_WIFI_SSID
#define AP_ESP_WIFI_PASS      CONFIG_ESP_WIFI_PASSWORD
#define AP_ESP_WIFI_CHANNEL   CONFIG_ESP_WIFI_CHANNEL
#define AP_MAX_STA_CONN       CONFIG_ESP_MAX_STA_CONN
#define configSUPPORT_DYNAMIC_ALLOCATION 1

static const gpio_num_t led_pin = GPIO_NUM_4;
static const char *TAG = "FreeRTOSDemo";
SemaphoreHandle_t xMutex_TOGGLE;

#endif
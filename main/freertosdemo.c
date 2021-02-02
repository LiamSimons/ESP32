#include "my_config.h"
#include <stdio.h>
#include <esp_vfs_fat.h>
#include "my_wifi_ap.h"
#include "my_server.h"
#include "my_manager.h"

void app_main(void)
{
    // Initialize mutex
    xMutex_TOGGLE = xSemaphoreCreateBinary();

    // Set output pin for LED
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);
    gpio_set_level(led_pin, 0);

    //Initialize NVS to read WiFi configuration (SSID, Password, ...)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Start the WiFi Access Point
    ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
    wifi_init_softap();

    // Create Tasks for Socket listener and Button event handler
    xTaskCreate(tcp_server_task, "tcp_server", 4096, (void*)NULL, 5, NULL);
    xTaskCreate(led_manager_task, "led_manager", 4096, (void*)NULL, 5, NULL);

}

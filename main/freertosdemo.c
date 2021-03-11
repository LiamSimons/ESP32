#include "my_config.h"
#include <stdio.h>
#include <esp_vfs_fat.h>
#include "my_wifi_ap.h"
#include "my_server.h"
#include "my_manager.h"
#include <esp_http_client.h>

int led_level=0;
void app_main(void)
{

    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    wifi_init_sta();



}

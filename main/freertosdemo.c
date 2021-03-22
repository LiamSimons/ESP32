#include "my_config.h"
#include <stdio.h>
#include <esp_vfs_fat.h>
#include "my_wifi_ap.h"
#include "my_server.h"
#include "my_manager.h"
#include <esp_http_client.h>
#include "my_server.h"
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"
#include "esp_tls.h"

#include "esp_http_client.h"
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
    esp_http_client_handle_t client = http_init_connections();
    http_post_request(client,3,100);
    http_post_request(client,3,200);
    http_post_request(client,3,300);
    http_post_request(client,3,400);
    http_post_request(client,3,500);
    http_post_request(client,3,600);
    http_post_request(client,3,700);
    http_post_request(client,3,800);
    http_post_request(client,3,900);
    http_post_request(client,3,1000);
    http_close_connection(client);
    while (1) {
        vTaskDelay(3000/portTICK_RATE_MS);
    }


}

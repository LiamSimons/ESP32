#include "my_config.h"
#include "my_wifi_ap.h"

void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data)
{
    // Handle incoming events like clients joining/leaving the WiFi Access Point
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG, "station " MACSTR " join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG, "station " MACSTR " leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else{
        printf("Other Wifi event %d", event_id);
    }
}

void wifi_init_softap(void)
{
    // Configure the WiFi Access Point using configuration from menuconfig
    //
    // https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_netif.html?highlight=wifi
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT,
                                               ESP_EVENT_ANY_ID,
                                               &wifi_event_handler,
                                               NULL
    ));

    // Create the configuration for the WiFi
    wifi_config_t wifi_config = {};
    strcpy((char*)wifi_config.ap.ssid, AP_ESP_WIFI_SSID);
    wifi_config.ap.ssid_len = strlen(AP_ESP_WIFI_SSID);
    wifi_config.ap.channel = AP_ESP_WIFI_CHANNEL;
    strcpy((char*)wifi_config.ap.password, AP_ESP_WIFI_PASS);
    wifi_config.ap.max_connection = AP_MAX_STA_CONN;
    wifi_config.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;
    // If no password was given, set AUTH_OPEN
    if (strlen(AP_ESP_WIFI_PASS) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    // You can use these event handlers if you wish to perform some action when a clients connects/disconnects
    // ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &connect_handler, &server));
    // ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, &server));

    // Set the WiFi in AP mode and configure, next start the WiFi
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s channel:%d",
             AP_ESP_WIFI_SSID, AP_ESP_WIFI_PASS, AP_ESP_WIFI_CHANNEL);
}
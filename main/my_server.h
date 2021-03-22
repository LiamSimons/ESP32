#ifndef MY_SERVER_H
#define MY_SERVER_H

#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>
#include "esp_http_client.h"

esp_err_t _http_event_handle(esp_http_client_event_t *evt);
esp_http_client_handle_t  http_init_connections();
void http_post_request(esp_http_client_handle_t client, int id, double value);
void http_close_connection(esp_http_client_handle_t client);


#endif
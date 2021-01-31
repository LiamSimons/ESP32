#include "my_config.h"
#include "my_server.h"

void process_incoming_data(const int sock)
{
    int len;
    char rx_buffer[128];

    do {
        len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);
        if (len < 0) {
            ESP_LOGE(TAG, "Error occurred during receiving: errno %d", errno);
        } else if (len == 0) {
            ESP_LOGW(TAG, "Connection closed");
        } else {
            rx_buffer[len] = 0; // Null-terminate whatever is received and treat it like a string
            ESP_LOGI(TAG, "%lld : Received %d bytes: %s", esp_timer_get_time(), len, rx_buffer);
            char data[128];
            memset(data, '\0', sizeof(data));
            if (strcmp(rx_buffer,"ON")==0){
//                BaseType_t xHigherPriorityTaskWoken = pdFALSE;
                xSemaphoreGive( xMutex_ON );
                ESP_LOGI(TAG, "%lld : Mutex_ON processed...", esp_timer_get_time());
                strncpy(data, "OK", 3);
                data[2]='\0';
            }else if (strcmp(rx_buffer,"OFF")==0){
                xSemaphoreGive( xMutex_OFF );
                ESP_LOGI(TAG, "%lld : Mutex_OFF processed...", esp_timer_get_time());
                strncpy(data, "OK", 3);
                data[2]='\0';
            }
            // send() can return less bytes than supplied length.
            // Walk-around for robust implementation.
            int to_write = strlen(data);
            while (to_write > 0) {
                int written = send(sock, data + (strlen(data) - to_write), to_write, 0);
                if (written < 0) {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                }
                to_write -= written;
            }
        }
    } while (len > 0);
}

void tcp_server_task(void *pvParameters)
{
    char addr_str[128];
    int addr_family = AF_INET;
    int ip_protocol = 0;
    struct sockaddr_in dest_addr;

    struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&dest_addr;
    dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
    dest_addr_ip4->sin_family = AF_INET;
    dest_addr_ip4->sin_port = htons(PORT);
    ip_protocol = IPPROTO_IP;

    int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
    if (listen_sock < 0) {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        vTaskDelete(NULL);
        return;
    }

    int opt = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct linger sl;
    sl.l_onoff = 1;		/* non-zero value enables linger option in kernel */
    sl.l_linger = 0;	/* timeout interval in seconds */
    setsockopt(listen_sock, SOL_SOCKET, SO_LINGER, &sl, sizeof(sl));
    ESP_LOGI(TAG, "Socket created");

    int err = bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err != 0) {
        ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
        ESP_LOGE(TAG, "IPPROTO: %d", addr_family);
        close(listen_sock);
        vTaskDelete(NULL);
    }
    ESP_LOGI(TAG, "Socket bound, port %d proto %d", PORT, addr_family);

    err = listen(listen_sock, 1);
    if (err != 0) {
        ESP_LOGE(TAG, "Error occurred during listen: errno %d", errno);
        close(listen_sock);
        vTaskDelete(NULL);
    }

    while (1) {
        //ESP_LOGI(TAG, "Socket listening");
        struct sockaddr_storage source_addr;
        uint addr_len = sizeof(source_addr);
        int sock = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);
        if (sock < 0) {
            ESP_LOGI(TAG, "Socket < 0");
            ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
            break;
        }

        // Convert ip address to string
        if (source_addr.ss_family == PF_INET) {
            inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, addr_str, sizeof(addr_str) - 1);
        }
        // ESP_LOGI(TAG, "Socket accepted ip address: %s", addr_str);

        //ESP_LOGI(TAG, "Socket do retransmit");
        process_incoming_data(sock);

        shutdown(sock, 0);
        close(sock);
    }

    close(listen_sock);
    vTaskDelete(NULL);
}
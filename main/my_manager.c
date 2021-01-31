#include <dirent.h>
#include "my_config.h"
#include "my_manager.h"

_Noreturn void led_manager_task(void *pvParameters){
    while(1){
        //ulTaskNotifyTake
        if (xMutex_ON != NULL){
            if( xSemaphoreTake( xMutex_ON, portMAX_DELAY) == pdTRUE )
            {
                // We were able to obtain the semaphore and can now access the
                // shared resource.
                ESP_LOGI(TAG, "%lld : Led turned ON...", esp_timer_get_time());
            }
            else
            {
                // We could not obtain the semaphore and can therefore not access
                // the shared resource safely.
                ESP_LOGI(TAG, "%lld : Mutex_ON timeout...", esp_timer_get_time());
            }
        }
        if (xMutex_OFF != NULL){
            if( xSemaphoreTake( xMutex_OFF, portMAX_DELAY) == pdTRUE )
            {
                // We were able to obtain the semaphore and can now access the
                // shared resource.
                ESP_LOGI(TAG, "%lld : Led turned OFF...", esp_timer_get_time());
            }
            else
            {
                // We could not obtain the semaphore and can therefore not access
                // the shared resource safely.
                ESP_LOGI(TAG, "%lld : Mutex_OFF timeout...", esp_timer_get_time());
            }
        }
    }
}
#include <dirent.h>
#include <esp_vfs_fat.h>
#include "my_config.h"
#include "my_manager.h"

_Noreturn void led_manager_task(void *pvParameters){

    int led_level = 0;
    while(1){
        //ulTaskNotifyTake
        if (xMutex_TOGGLE != NULL){
            if(xSemaphoreTake(xMutex_TOGGLE, portMAX_DELAY) == pdTRUE )
            {
                // We were able to obtain the semaphore and can now access the
                // shared resource.
                led_level = 1-led_level;
                gpio_set_level(led_pin, led_level);
                ESP_LOGI(TAG, "%lld : Led toggled... %d", esp_timer_get_time(),led_level);
            }
            else
            {
                // We could not obtain the semaphore and can therefore not access
                // the shared resource safely.
                ESP_LOGI(TAG, "%lld : Mutex_TOGGLE timeout...", esp_timer_get_time());
            }
        }
    }
}
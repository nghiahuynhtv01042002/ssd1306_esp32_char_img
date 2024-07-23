#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "ssd1306.h"




void app_main(void)
{
    ESP_ERROR_CHECK(i2c_master_init());
    ssd1306_init();
    ssd1306_clear();
    int cnt = 1;
    ssd1306_set_cursor(0, 0);
    ssd1306_print("Hello i am TXN");
    ssd1306_set_cursor(0, 8);
    ssd1306_print("i am embedded engineer");
    ssd1306_set_cursor(0, 16);
    ssd1306_print("i study at HMCUT VNU");
    ssd1306_set_cursor(0, 24);
    ssd1306_print("i live at HCM city");
    ssd1306_set_cursor(0, 32);
    ssd1306_print("i am single:<");
    vTaskDelay(pdMS_TO_TICKS(3000));
    while (1)
    {
        if(cnt %2 == 0){
            ssd1306_clear();
            ssd1306_set_cursor(0, 0);
            ssd1306_display_bitmap(logobk);

        }
        else{
            ssd1306_clear();
            ssd1306_set_cursor(0, 0);
            ssd1306_display_bitmap(esplogo);
        }
        cnt ++;
        vTaskDelay(pdMS_TO_TICKS(3000));

    }
}



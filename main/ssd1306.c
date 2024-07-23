#include "ssd1306.h"



esp_err_t i2c_master_init() {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    esp_err_t err = i2c_param_config(I2C_MASTER_NUM, &conf);
    if (err != ESP_OK) return err;

    return i2c_driver_install(I2C_MASTER_NUM, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}
void ssd1306_command(uint8_t cmd) {
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (I2C_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x00, true);
    i2c_master_write_byte(handle, cmd, true);
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_MASTER_NUM, handle, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(handle);
}

void ssd1306_data(uint8_t data) {
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (I2C_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x40, true);
    i2c_master_write_byte(handle, data, true);
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_MASTER_NUM, handle, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(handle);
}
void ssd1306_init() {
    ssd1306_command(SSD1306_CMD_DISPLAY_OFF);
    ssd1306_command(SSD1306_CMD_SET_DISPLAY_CLOCK_DIV);
    ssd1306_command(0x80);
    ssd1306_command(SSD1306_CMD_SET_MULTIPLEX);
    ssd1306_command(HEIGHT - 1);
    ssd1306_command(SSD1306_CMD_SET_DISPLAY_OFFSET);
    ssd1306_command(0x00);
    ssd1306_command(SSD1306_CMD_SET_START_LINE | 0x00);
    ssd1306_command(SSD1306_CMD_CHARGE_PUMP);
    ssd1306_command(0x14);
    ssd1306_command(SSD1306_CMD_MEMORY_MODE);
    ssd1306_command(0x00);
    ssd1306_command(SSD1306_CMD_SEG_REMAP | 0x01);
    ssd1306_command(SSD1306_CMD_COM_SCAN_DEC);
    ssd1306_command(SSD1306_CMD_SET_COM_PINS);
    ssd1306_command(0x12);
    ssd1306_command(SSD1306_CMD_SET_CONTRAST);
    ssd1306_command(0xCF);
    ssd1306_command(SSD1306_CMD_SET_PRECHARGE);
    ssd1306_command(0xF1);
    ssd1306_command(SSD1306_CMD_SET_VCOM_DETECT);
    ssd1306_command(0x40);
    ssd1306_command(SSD1306_CMD_DISPLAY_ALL_ON_RESUME);
    ssd1306_command(SSD1306_CMD_NORMAL_DISPLAY);
    ssd1306_command(SSD1306_CMD_DISPLAY_ON);
}

void ssd1306_clear() {
    for (int page = 0; page < PAGES; page++) {
        ssd1306_command(0xB0 + page);
        ssd1306_command(0x00);
        ssd1306_command(0x10);
        for (int i = 0; i < WIDTH; i++) {
            ssd1306_data(0x00);
        }
    }
}

void ssd1306_set_cursor(uint8_t x, uint8_t y) {
    ssd1306_command(0xB0 + (y / 8));
    ssd1306_command(0x00 + (x & 0x0F));
    ssd1306_command(0x10 + ((x >> 4) & 0x0F));
}

void ssd1306_print_char(char c) {
    if (c < 32 || c > 127) {
        c = 32;
    }
    for (int i = 0; i < 5; i++) {
        ssd1306_data(font[c - 32][i]);
    }
}

void ssd1306_print(const char* str) {
    while (*str) {
        ssd1306_print_char(*str++);
    }
}
void ssd1306_display_bitmap(const char* bitmap){
        for (uint8_t page = 0; page < PAGES; ++page) {
        ssd1306_command(0xB0 + page);  // Set page address
        ssd1306_command(0x00);  // Set lower column start address
        ssd1306_command(0x10);  // Set higher column start address
        
        for (uint8_t i = 0; i < WIDTH; ++i) {
            ssd1306_data(bitmap[page * WIDTH + i]);
        }
    }
}

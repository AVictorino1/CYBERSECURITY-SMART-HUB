#include <stdio.h>
#include "display.h"
#include "ssd1306.h"
#include "driver/i2c_master.h"

static i2c_master_bus_handle_t master_handle;

static ssd1306_handle_t ssd1306_handle;

void init_display(void)
{   
   i2c_master_bus_config_t i2c_config = {
    .i2c_port = I2C_NUM_0,
    .sda_io_num = GPIO_NUM_21,
    .scl_io_num = GPIO_NUM_22,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,
    .flags.enable_internal_pullup = true
    };

    i2c_new_master_bus(&i2c_config, &master_handle);

    
    ssd1306_config_t ssd1306_config = I2C_SSD1306_128x64_CONFIG_DEFAULT;
    ssd1306_init(master_handle, &ssd1306_config, &ssd1306_handle);
    ssd1306_clear_display(ssd1306_handle, false);

}



void show_text(uint8_t page, const char *text){
    
    ssd1306_display_text(ssd1306_handle, page, text, false);
}
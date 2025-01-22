/* 
 * File:   SSD1306.c
 * Author: Luis Mora
 * 
 * Driver to run SSD1306 OLED through I2C.
 * 
 * Notes:
 *  -   Scrolling not developed
 *
 * Created on January 5, 2025, 6:23 PM
 */

#include "SSD1306.h"

void send_command(uint8_t command)
{
    int8_t status = 0;
    status = i2c_start();
    status = i2c_write(SSD1306_ADDRESS);
    status = i2c_write(SSD1306_COMMAND);
    status = i2c_write(command);
    i2c_stop();
}

void send_data(uint8_t data)
{
    int8_t status = 0;
    status = i2c_start();
    status = i2c_write(SSD1306_ADDRESS);
    status = i2c_write(SSD1306_DATA);
    status = i2c_write(data);
    i2c_stop();
}

void set_start_end(uint8_t column_start, uint8_t column_end, uint8_t page_start, uint8_t page_end)
{
    send_command(SSD1306_SET_COLUMN_ADDRESS);
    send_command(column_start);
    send_command(column_end);
    send_command(SSD1306_SET_PAGE_ADDRESS);
    send_command(page_start);
    send_command(page_end);
}

void SSD1306_init(void)
{
    i2c_init();
    send_command(SSD1306_SET_DISPLAY_OFF);
    send_command(SSD1306_SET_DISPLAY_CLOCK_DIVIDE_RATIO);
    send_command(0x80);
    send_command(SSD1306_SET_MULTIPLEX_RATIO);
    send_command(SSD1306_HEIGHT - 0x01);
    send_command(SSD1306_SET_DISPLAY_OFFSET);
    send_command(0x00);
    send_command(SSD1306_SET_DISPLAY_START_LINE | 0x00);
    send_command(SSD1306_SET_CHARGE_PUMP);
    send_command(0x14);
    send_command(SSD1306_SET_MEMORY_ADDRESSING_MODE);
    send_command(0x00);
    send_command(SSD1306_SET_SEGMENT_REMAP | 0x01);
    send_command(SSD1306_SET_COM_OUTPUT_SCAN_TO_LOW);
    send_command(SSD1306_SET_COM_PINS_HARDWARE_CONFIG);
    send_command(0x12);
    send_command(SSD1306_SET_CONTRAST_CONTROL);
    send_command(0xCF);
    send_command(SSD1306_SET_PRECHARGE_PERIOD);
    send_command(0xF1);
    send_command(SSD1306_SET_VCOMH_DESELECT_LEVEL);
    send_command(0x40);
    send_command(SSD1306_DISPLAY_GDDRAM);
    send_command(SSD1306_SET_NORMAL);
    send_command(SSD1306_SET_DISPLAY_ON);
    _delay_ms(100);
    SSD1306_clear();
}

void SSD1306_clear(void)
{
    uint16_t index = 0x00;
    set_start_end(0x00, 0x7F, 0x00, 0x07);
    while(index < SSD1306_BUFFER)
    {
        send_data(0x00);
        index++;
    }
}

void SSD1306_draw_pixel(uint8_t x, uint8_t y)
{
    if((x <= (SSD1306_WIDTH - 0x01)) && (y <= (SSD1306_HEIGHT - 0x01)))
    {
        set_start_end(x, x, (y >> 3), (y >> 3));
        send_data(0x01 << (y & 0x07));
    }
}

void SSD1306_debug(void)
{
    uint8_t x,y;
    for(x = 0; x < SSD1306_WIDTH; x++)
    {
        for(y = 0; y <SSD1306_HEIGHT; y++) 
        {
            SSD1306_draw_pixel(x, y);
            _delay_ms(1000);
        }
    }
}



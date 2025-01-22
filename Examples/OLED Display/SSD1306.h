/* 
 * File:   SSD1306.h
 * Author: Luis Mora
 * 
 * Driver to run SSD1306 OLED through I2C.
 * 
 * Notes:
 *  -   Scrolling not developed
 * 
 * Important:
 *  -   Slave Address:  b7  b6  b5  b4  b3  b2  b1  b0
 *                      0   1   1   1   1   0   SA0 R/W#
 *      
 *      where SA0 bit provides an extension bit for the slave address. 
 *      Either ?0111100b0? or ?0111101b0?, can be selected as the slave 
 *      address of SSD1306. D/C# physical pin acts as SA0 for slave address 
 *      selection; R/W# bit is used to determine the operation mode of the 
 *      I2C-bus interface. R/W#=1, for read mode. R/W#=0, for write mode.
 *      
 *      This library is only for write mode, R/W#=0, does not use the 
 *      extension bit, SA0=0. So, the slave address is 01111000 or 0x78.
 *      
 * Created on January 5, 2025, 6:23 PM
 */
#ifndef SSD1306_H
#define SSD1306_H

#ifdef	__cplusplus
extern "C" {
#endif

//************DEBUG************************
#include <avr/io.h>
//*****************************************
    
#include <util/delay.h>
#include "i2c.h"
    
/********************************************************************************************************************************
 * Configuration
 *******************************************************************************************************************************/
#define SSD1306_WIDTH 0x80 //  Display Width
#define SSD1306_HEIGHT 0x40 //  Display Height
#define SSD1306_BUFFER (SSD1306_WIDTH*SSD1306_HEIGHT)/0x08 //  Buffer size = (128 columns * 64 rows)/8 rows per page = 1024 bytes 

/********************************************************************************************************************************
 * I2C Interface
 *******************************************************************************************************************************/
#define SSD1306_ADDRESS 0x78 //  I2C Slave Address. Check notes for more information.
#define SSD1306_COMMAND 0x00 //  (Control byte) Begins a stream of a command.
#define SSD1306_DATA 0x40 //  (Control byte) Begins a stream of data that will be written to the GDDRAM.

/********************************************************************************************************************************
 * COMMANDS
 *******************************************************************************************************************************/
//  Fundamental Commands
#define SSD1306_SET_CONTRAST_CONTROL 0x81 //  Adjust display brightness (0x00 = dim, 0xFF = bright).
#define SSD1306_DISPLAY_GDDRAM 0xA4 //  Normal operation (show GDDRAM content).
#define SSD1306_ENTIRE_DISPLAY_ON 0xA5 //  All pixels ON (test mode).
#define SSD1306_SET_NORMAL 0xA6 //  Display shows light pixels on a black background.
#define SSD1306_INVERSE_DISPLAY 0xA7 //  Display shows black pixels on a light background.
#define SSD1306_SET_DISPLAY_OFF 0xAE //  Display OFF (sleep mode).
#define SSD1306_SET_DISPLAY_ON 0xAF //  Display ON (normal mode).

//  Scrolling Commands
#define SSD1306_SET_HORIZONTAL_SCROLL_RIGHT 0x26 //  Smooth horizontal scrolling to the right.
#define SSD1306_SET_HORIZONTAL_SCROLL_LEFT 0x27 //  Smooth horizontal scrolling to the left.
#define SSD1306_SET_DIAGONAL_SCROLL_RIGHT 0x29 //  Scroll from the bottom-left corner to the top-right corner.
#define SSD1306_SET_DIAGONAL_SCROLL_LEFT 0x2A //  Scroll from the top-right corner to the bottom-left corner.
#define SSD1306_DEACTIVATE_SCROLL 0x2E //  Stop any active scrolling.
#define SSD1306_ACTIVATE_SCROLL 0x2F //  Start a scroll.
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3 //  Set the display's top and the number of rows for vertical scrolling.

//  Addressing Setting Commands
#define SSD1306_SET_MEMORY_ADDRESSING_MODE 0x20 //  Horizontal (0x00), Vertical (0x01), or Page (0x02).
#define SSD1306_SET_COLUMN_ADDRESS 0x21 //  Specify start and end columns for data writes.
#define SSD1306_SET_PAGE_ADDRESS 0x22 //  Specify start and end pages for data writes.

//  Hardware Configuration (Panel resolution & layout related) Commands
#define SSD1306_SET_DISPLAY_START_LINE 0x40 //  Define the starting line for display content.
#define SSD1306_SET_SEGMENT_REMAP 0xA0 //  Mirror the display horizontally.
#define SSD1306_SET_MULTIPLEX_RATIO 0xA8
#define SSD1306_SET_COM_OUTPUT_SCAN_TO_HIGH 0xC0 //  Scan from COM0 to COM[N –1].
#define SSD1306_SET_COM_OUTPUT_SCAN_TO_LOW 0xC8 //  Scan from COM[N-1] to COM0.
#define SSD1306_SET_DISPLAY_OFFSET 0xD3 //  Adjust vertical shift of the display (0x00 to 0x3F).
#define SSD1306_SET_COM_PINS_HARDWARE_CONFIG 0xDA //  Adjust COM pin setup.

//  Timing & Driving Scheme Setting Commands
#define SSD1306_SET_DISPLAY_CLOCK_DIVIDE_RATIO 0xD5 //  Control display refresh rate.
#define SSD1306_SET_PRECHARGE_PERIOD 0xD9 //  Adjust pre-charge phase timing for pixel lighting
#define SSD1306_SET_VCOMH_DESELECT_LEVEL 0xDB //  Set VCOM voltage (affects contrast stability).
#define SSD1306_NOP 0xE3 //  Command for no operation.

//  Charge Pump Commands
#define SSD1306_SET_CHARGE_PUMP 0x8D //  0x14 = Enable, 0x10 = Disable.

/********************************************************************************************************************************
 * COMMANDS
 *******************************************************************************************************************************/
void SSD1306_init(void);
void SSD1306_clear(void);
void SSD1306_draw_pixel(uint8_t, uint8_t);
void SSD1306_debug(void);

#ifdef	__cplusplus
}
#endif

#endif  /* SSD1306_H */
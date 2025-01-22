/* 
 * File:   main.c
 * Author: ljmor
 *
 * Created on January 13, 2025, 9:48 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include "SSD1306.h"

int main(int argc, char** argv) 
{
    SSD1306_init();
    SSD1306_debug();
    while(1)
    {
        asm("nop");
    }
    return (EXIT_SUCCESS);
}


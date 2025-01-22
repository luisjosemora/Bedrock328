/* 
 * File:   i2c.c
 * Author: Luis Mora
 * 
 * TWI(I2C) Interface for Master Transmitter Mode
 * 
 * ATmega328p
 * I2C Standard Mode
 *
 * Created on January 5, 2025, 6:23 PM
 */
#include "i2c.h"

void i2c_init(void)
{
    DDRC &= ~((1<<4) | (1<<5));   //  Set the i2c pins
    switch (PRESC)
    {
        case 1:
            TWSR &= ~((1<<TWPS0) | (1<<TWPS1)); // Set prescaler bits to 00 (prescaler = 1)
            break;
        case 4:
            TWSR &= ~((0<<TWPS0) | (1<<TWPS1)); // Set prescaler bits to 01 (prescaler = 4)
            break;
        case 16:
            TWSR &= ~((1<<TWPS0) | (0<<TWPS1)); // Set prescaler bits to 10 (prescaler = 16)
            break;
        case 64:
            TWSR &= ~((1<<TWPS0) | (1<<TWPS1)); // Set prescaler bits to 11 (prescaler = 64)
            break;
    }    
    TWBR = ((F_CPU/F_I2C) - 16)/(2*PRESC); //  Set the value of the TWI Bit rate register
    TWCR |= (1<<TWEN);  //  Enables TWI operation and activates the TWI interface
}

uint8_t i2c_start(void)
{
    int8_t status = 0;
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); //  Send START condition
    while (!(TWCR & (1<<TWINT)));   //  Wait for TWINT flag set. Yhis indicates that the START condition has been transmitted
    switch (TWSR & 0xF8)    //  Check the TWSR Status Code
    {
        case 0x08:
            status = 0x08;  //  A START condition has been transmitted
            break;
        case 0x10:
            status = 0x10;  //  A repeated START condition has been transmitted
            break;
        default:
            status = 0x0; //  Error when transmitting START condition
            break;
    }
    return status;
}

uint8_t i2c_write(uint8_t data)
{
    int8_t status = 0;
    TWDR = data;    //  Load 8-Bits data into TWDR register, can be device address or general data
    TWCR = (1<<TWINT) | (1<<TWEN);  //  Clear TWINT bit in TWCR to start trnasmission of data
    while (!(TWCR & (1<<TWINT)));   //  Wait for TWINT flag set. This indicates that the data has been transmitted, and ACK/NACK has been received
    switch (TWSR & 0xF8)    //  Check the TWSR Status Code
    {
        case 0x18:
            status = 0x18;  //  Address has been transmitte; ACK has been received
            break;
        case 0x20:
            status = 0x20;  //  Address has been transmitte; NOT ACK has been received
            break;
        case 0x28:
            status = 0x28;  //  Data byte has been transmitte; ACK has been received
            break;
        case 0x30:
            status = 0x30;  //  Data byte has been transmitte; NOT ACK has been received
            break;
        case 0x38:
            status = 0x38;  //  Arbitration lost in address or data bytes
            break;
        default:
            status = 0x01;  //  Error when transmitting address or data bytes
            break;
    }
    return status;
}

void i2c_stop(void)
{
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN); //  Transmit STOP condition
    while ((TWCR & (1 << TWSTO)));  //  Wait until stop condition is transmitted
}

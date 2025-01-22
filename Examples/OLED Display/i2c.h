/* 
 * File:   i2c.h
 * Author: Luis Mora
 * 
 * TWI(I2C) Interface for Master Transmitter Mode
 * 
 * ATmega328p
 * I2C Standard Mode
 *
 * Created on January 5, 2025, 6:23 PM
 */
#ifndef I2C_H
#define I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#define F_I2C   100000UL    //  TWI Bus Frequency = 100 KHz (I2C Standartd Mode)
#define PRESC   1   //  Prescaler
#define F_CPU    16000000UL //  ATmega328 Frequency = 16 MHz (External Crystal Oscillator)
#if PRESC != 1 && PRESC != 4 && PRESC != 16 && PRESC != 64
    #error "WRONG PRESCALER"
#endif

#include <avr/io.h>

void i2c_init(void);
uint8_t i2c_start(void);
uint8_t i2c_write(uint8_t);
void i2c_stop(void);

#ifdef	__cplusplus
}
#endif

#endif  /* I2C_H */
#include <avr/io.h>
#include <util/delay.h>

void setupPWM() 
{
    DDRB |= (1 << PB1) | (1 << PB2) | (1 << PB3);

    TCCR1A |= (1 << WGM11) | (1 << COM1A1) | (1 << COM1B1); 
    TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11);
    ICR1 = 1999;

    TCCR2A |= (1 << WGM20) | (1 << WGM21) | (1 << COM2A1); 
    TCCR2B |= (1 << CS21);

    DDRD |= (1 << PD3) | (1 << PD5) | (1 << PD6);

    TCCR0A |= (1 << WGM00) | (1 << WGM01);
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
    TCCR0B |= (1 << CS01);
}

void setColorLED1(uint8_t red, uint8_t green, uint8_t blue) 
{
    OCR1A = (ICR1 * red) / 255;
    OCR1B = (ICR1 * green) / 255;
    OCR2A = (blue * 255) / 255;
}

void setColorLED2(uint8_t red, uint8_t green, uint8_t blue) 
{
    OCR2B = (red * 255) / 255;
    OCR0B = (green * 255) / 255;
    OCR0A = (blue * 255) / 255;
}

int main() 
{
    setupPWM();

    while (1) 
    {
            setColorLED1(255, 0, 0);
            setColorLED2(0, 0, 255);
            _delay_ms(4000);
            setColorLED1(127, 127, 0);
            setColorLED2(0, 127, 127);
            _delay_ms(4000);
            setColorLED1(0, 255, 0);
            setColorLED2(0, 255, 0);
            _delay_ms(4000);
            setColorLED1(0, 127, 127);
            setColorLED2(127, 127, 0);
            _delay_ms(4000);
            setColorLED1(0, 0, 255);
            setColorLED2(255, 0, 0);
            _delay_ms(4000);
            setColorLED1(127, 0, 127);
            setColorLED2(127, 0, 127);
            _delay_ms(4000);
    }
    return 0;
}



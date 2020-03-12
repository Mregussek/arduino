// Written by Mateusz Rzeczyca

#define F_CPU 1000000UL // 1 MHz - CPU frequency
 
#include <avr/io.h> // library, which defines ports, pins etc.
#include <util/delay.h> // adds _delay_ms()
 
 
int main(void)
{
    DDRB = 0xff; /* Data Direction Register B: configuring B ports as output */
     
    while (1) 
    {
        PORTB = 0b11111111; // launches all pins PORTB
        _delay_ms(1000); // wait
        PORTB = 0b00000000; // turns off all pins PORTB
        _delay_ms(1000); // wait
    }
     
    return 0;
}
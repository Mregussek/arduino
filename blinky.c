/*
 * pureClearning.c
 *
 * Created: 09.03.2020 21:12:57
 * Author : mateu
 */ 

#include <avr/io.h> /* Defines pins, ports, etc */
#include <util/delay.h> /* Functions to waste time */


int main(void) {
	// -------- Inits --------- //
	DDRB |= (1 << PB0); /* Data Direction Register B: writing a one to the bit and enables output. */
	
	// ------ Event loop ------ //
	while (1) {
		PORTB = 0b00000001; /* Turn on first LED bit/pin in PORTB */
		_delay_ms(1000); /* wait */
		PORTB = 0b00000000; /* Turn off all B pins, including LED */
		_delay_ms(1000); /* wait */
		} /* End event loop */
		return (0); /* This line is never reached */
}

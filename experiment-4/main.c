#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	// this will take input from PINB0
	unsigned char button;
	
	// Sets data direcion register with binary 1111 1111 as D ports have 8 I/O ports
	// DDRD is working as output
	DDRD = 0xFF;
	// Sets DDRB with 1111 1110 so DDRB0 will act as input
	DDRB &= (~(1 << 0));
	
	while (1) {
		// Sets PINB0 with 1111 1110
		button = PINB & (1 << 0);
		// if voltage is given to PINB0, LEDs in PORTD will light up,
		// otherwise not
		if (button) {
			PORTD = 0xFF;
		} else {
			PORTD = 0x00;
		}
	}
	return 0;
}

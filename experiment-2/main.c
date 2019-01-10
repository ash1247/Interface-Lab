#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DATA DDRB
#define PORT PORTB
#define PIN PINB
#define INT_DATA DDRD
#define INT_PIN PIND
#define DELAY 1000U

// these funtctions take two parameters, how many times the LED loop will
// run and delay in miliseconds
void up_to_down(int times, int delay);
void down_to_up(int times, int delay);

int main(void) {

	// this will take input from PIND2
	unsigned char button;
	
	// Sets data direcion register with binary 1111 1111 as D ports have 8 I/O ports
	// DDRB is working as output
	DATA = 0xFF;
	// Sets DDRD with 1111 1011 so DDRD2 will act as input
	INT_DATA &= (~(1 << 2));
	
	GICR |= 1<<INT0; // Enable INT0
	MCUCR = 0x02;	// Trigger INT0 on rising edge
	
	sei();
	
	while (1) {
		// Sets PIND2 with 1111 1011
		button = INT_PIN & (1 << 2);
		// if voltage is given to PIND2, LEDs will go from down to up,
		// otherwise up to down
		up_to_down(7, DELAY);
	}
	return 0;

}

void up_to_down(int times, int delay) {
	// LED will turn on and off PORTB0-PORTB7 after parameter delay time,
	// and loop will run on given parameter times.
	int count;
	for (count = 0; count <= times; count++) {
		PORT = 1 << count;
		_delay_ms(delay);
	}

}

void down_to_up(int times, int delay) {
	// LED will turn on and off PORTB7-PORTB0 after parameter delay time,
	// and loop will run on given parameter times.
	int count;
	for (count = times; count >= 0; count--) {
		PORT = 1 << count;
		_delay_ms(delay);
	}
}


// This function will be called when interrupt occurs
ISR(INT0_vect)
{
	down_to_up(7, DELAY);
}	

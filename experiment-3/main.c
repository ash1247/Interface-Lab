#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DATA DDRB
#define PORT PORTB
#define PIN PINB
#define INT_DATA DDRD
#define INT_PIN PIND
#define DELAY 300U

// these funtctions takes one parameter, delay in miliseconds
void up_to_down(int delay);
void down_to_up(int delay);

//	value of 7 segment display is sorted as dp, 'g' - 'a', first bit is 'dp', last bit is 'a';
// 	int array[10] = { 00111111, 00000110, 01011011, 01001111, 
//				01100110, 01101101, 01111101, 00000111, 
//				01111111, 01101111};
// All the values of 7 segment display from 0-9 is stored in index
// 0-9 in array as in decimal form.
static int array[10] = { 0x3f, 0x06, 0x5B, 0x4F, 0x66, 
				0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int main(void) {
	
	// this will take input from PIND2
	unsigned char button;
	
	// Sets data direcion register with binary 1111 1111 as D ports have 8 I/O ports
	// DATA is working as output
	DATA = 0xFF;
	int count = 0;
	
	// Sets INT_DATA with 1111 1011 so INT_DATA2 will act as input
	INT_DATA &= (~(1 << 2));
	
	GICR |= 1<<INT0; // Enable INT0
	MCUCR = 0x01;	// Trigger INT0 on falling edge
	
	sei();
	
	while (1) {
		// Sets PIND2 with 1111 1011
		button = INT_PIN & (1 << 2);
		//PORT will take value from array index for numbers. array acts
		// as a translation table
		down_to_up(DELAY);
	}
	return 0;
	
}

void up_to_down(int delay) {
	// will show output from 9 to 0 on 7 segment
	int count;
	for (count = 9; count != -1; count--) {
			PORT = array[count];
			_delay_ms(delay);
		}
}
void down_to_up(int delay) {
	// will show output from 0 to 9 on 7 segment
	int count;
	for (count = 0; count < 10; count++) {
			PORT = array[count];
			_delay_ms(delay);
		}
}

// This function will be called when interrupt occurs
ISR(INT0_vect)
{
	up_to_down(DELAY);
}	


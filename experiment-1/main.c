#include <avr/io.h>
#include <util/delay.h>

// these funtctions take two parameters, how many times the LED loop will
// run and delay in miliseconds
void up_to_down(int times, int delay);
void down_to_up(int times, int delay);
void on_off(int times, int delay);

int main(void) {

	int count = 0;
	// Setting data direcion register with binary 1111 1111 as D ports have 8 I/O ports
	// DDRD is working as output
	DDRD = 0xFF;
	while (1) {
		while (count != 2) {
			up_to_down(7, 100);
			down_to_up(7, 100);
			count++;
		}
		on_off(2, 200);
		count = 0;
	}
	return 0;
}

void on_off(int times, int delay) {
	// For turning off and on in PORTD data register
	int count = 0;
	while (count < times) {
		PORTD = 0xFF;
		_delay_ms(delay);
		PORTD = 0x00;
		_delay_ms(delay-100);
		count++;
	}
}

void up_to_down(int times, int delay) {
	// LED will turn on and off PORTD0-PORTD7 after parameter delay time,
	// and loop will run on given parameter times.
	int count;
	for (count = 0; count <= times; count++) {
		PORTD = 1 << count;
		_delay_ms(delay);
	}

}

void down_to_up(int times, int delay) {
	// LED will turn on and off PORTD7-PORTD0 after parameter delay time,
	// and loop will run on given parameter times.
	int count;
	for (count = times; count >= 0; count--) {
		PORTD = 1 << count;
		_delay_ms(delay);
	}
}

/*
	orb.c - Contains functions and interrupts necessary to run the orb
	author:  Tom Lauwers
*/


/* Interrupt takes roughly 65 us to run */

ISR(TIMER0_OVF_vect)
{
	int i;

	if(activity_state == 0) {
		/*if(activity_val < 132) {
			led_values_temp[10] = 0;
		}
		else {
			led_values_temp[10] = (activity_val-128)*2;
		}*/
		if(activity_val > 20) {
			led_values_temp[10] = activity_val;
		}
		else {
			led_values_temp[10] = 0;
		}
		if(activity_dir == 0) {
			activity_val+=5;
		}
		else {
			activity_val-=5;
		}
		if(activity_val >= 254) {
			activity_dir = 1;
		}
		else if(activity_val <= 2) {
			activity_dir = 0;
		}
	}
	else if(activity_state == 1){
		led_values_temp[10] = 255;
	}

	// Transfer set_orb values into this cycle's buffer
	for(i = 0; i < 11; i++) {
		led_values[i] = led_values_temp[i];
	}

	// Turn on all twelve elements unless their value is 0
	if(led_values[0] != 0)
		PORTD |= _BV(REDLED0);
	else {
		PORTD &= (0xFF - _BV(REDLED0));
		led_values[0] = 255;
	}

	if(led_values[1] != 0)
		PORTD |= _BV(GREENLED0);
	else {
		PORTD &= (0xFF - _BV(GREENLED0));
		led_values[1] = 255;
	}

	if(led_values[2] != 0)
		PORTD |= _BV(BLUELED0);
	else {
		PORTD &= (0xFF - _BV(BLUELED0));
		led_values[2] = 255;
	}
	if(led_values[3] != 0)
		PORTE |= _BV(REDLED1);
	else {
		PORTE &= (0xFF - _BV(REDLED1));
		led_values[3] = 255;
	}

	if(led_values[4] != 0)
		PORTE |= _BV(GREENLED1);
	else {
		PORTE &= (0xFF - _BV(GREENLED1));
		led_values[4] = 255;
	}

	if(led_values[5] != 0)
		PORTD |= _BV(BLUELED1);
	else {
		PORTD &= (0xFF - _BV(BLUELED1));
		led_values[5] = 255;
	}
	if(led_values[6] != 0)
		PORTB |= _BV(USERLED0);
	else {
		PORTB &= (0xFF - _BV(USERLED0));
		led_values[6] = 255;
	}

	if(led_values[7] != 0)
		PORTB |= _BV(USERLED1);
	else {
		PORTB &= (0xFF - _BV(USERLED1));
		led_values[7] = 255;
	}

	if(led_values[8] != 0)
		PORTC |= _BV(USERLED2);
	else {
		PORTC &= (0xFF - _BV(USERLED2));
		led_values[8] = 255;
	}

	if(led_values[9] != 0)
		PORTB |= _BV(USERLED3);
	else {
		PORTB &= (0xFF - _BV(USERLED3));
		led_values[9] = 255;
	}

	if(led_values[10] != 0)
		PORTC |= _BV(ACTIVITY);
	else {
		PORTC &= (0xFF - _BV(ACTIVITY));
		led_values[10] = 255;
	}
	// Find the smallest one of the twelve and set the next output compare to occur then
	// Set next_led_val to the smallest of the ten values
	for(i = 0; i < 11; i++) {
		if(led_values[i] < next_led_val) {
			next_led_val = led_values[i];
		}
	}
	OCR0A = next_led_val;

}


/*
	Output compare 0A interrupt:
	If the led value is 255, just exit the function -
	this means no pins need to be toggled.
	If not, check which LED(s) value is equal to the next led value
	and turn if off, then setting it's value to 255.
	Check which of the 12 values is smallest, and set the output
	compare to this value.

	Interrupt take 29 us, executes eleven or fewer times during a 65ms cycle
*/

// Currently going too slowly, so I should change this, make it so that I/O pins are toggled after OCRA is set

ISR(TIMER0_COMPA_vect)
{
	int i;
	// If output compare is 255, nothing needs to be done, so exit
	if(next_led_val == 255) {
		return;
	}

	// If an LED value equals the next led value, toggle the pin to off
	if(led_values[0] == next_led_val) {
		PORTD &= (0xFF - _BV(REDLED0));
		led_values[0] = 255;
	}

	if(led_values[1] == next_led_val) {
		PORTD &= (0xFF - _BV(GREENLED0));
		led_values[1] = 255;
	}

	if(led_values[2] == next_led_val) {
		PORTD &= (0xFF - _BV(BLUELED0));
		led_values[2] = 255;
	}
	if(led_values[3] == next_led_val) {
		PORTE &= (0xFF - _BV(REDLED1));
		led_values[3] = 255;
	}

	if(led_values[4] == next_led_val) {
		PORTE &= (0xFF - _BV(GREENLED1));
		led_values[4] = 255;
	}

	if(led_values[5] == next_led_val) {
		PORTD &= (0xFF - _BV(BLUELED1));
		led_values[5] = 255;
	}
	if(led_values[6] == next_led_val) {
		PORTB &= (0xFF - _BV(USERLED0));
		led_values[6] = 255;
	}

	if(led_values[7] == next_led_val) {
		PORTB &= (0xFF - _BV(USERLED1));
		led_values[7] = 255;
	}
	if(led_values[8] == next_led_val) {
		PORTC &= (0xFF - _BV(USERLED2));
		led_values[8] = 255;
	}

	if(led_values[9] == next_led_val) {
		PORTB &= (0xFF - _BV(USERLED3));
		led_values[9] = 255;
	}
	if(led_values[10] == next_led_val) {
		PORTC &= (0xFF - _BV(ACTIVITY));
		led_values[10] = 255;
	}

	// Set the next led value to the smallest of the twelve
	next_led_val = 255;
	for(i = 0; i < 11; i++) {
		if(led_values[i] < next_led_val) {
			next_led_val = led_values[i];
		}
	}
	OCR0A = next_led_val;
}

void init_orb()
{
	// Set registers for normal operation, counter prescalar of 256, so count at 31.25 KHz
	// Overflow occurs every ~64 ms
	TCCR0A = 0x00;
	TCCR0B = 0x04;

	// Turn on OCR0A and TOV interrupts
	TIMSK0 = 0x03;

	// Set all LEDs and vibration motors to outputs
	DDRB |= _BV(USERLED0) | _BV(USERLED1) | _BV(USERLED3);
	DDRC |= _BV(USERLED2) | _BV(ACTIVITY);
	DDRD |= _BV(REDLED0) | _BV(GREENLED0) | _BV(BLUELED0) | _BV(BLUELED1);
	DDRE |= _BV(REDLED1) | _BV(GREENLED1);


}

void set_orb(uint8_t whichOne, unsigned int red_led, unsigned int green_led, unsigned int blue_led)
{
	if(whichOne=='1') {
		set_orb1(red_led, green_led, blue_led);
	}
	else {
		set_orb0(red_led, green_led, blue_led);
	}
}

// Sets the red, green and blue elements of the first LED with 8-bit resolution
void set_orb0(unsigned int red_led, unsigned int green_led, unsigned int blue_led)
{
	led_values_temp[0] = red_led;
	led_values_temp[1] = green_led;
	led_values_temp[2] = blue_led;
}

// Sets the red, green and blue elements of the second LED with 8-bit resolution
void set_orb1(unsigned int red_led, unsigned int green_led, unsigned int blue_led)
{
	led_values_temp[3] = red_led;
	led_values_temp[4] = green_led;
	led_values_temp[5] = blue_led;
}

void set_led(uint8_t whichOne, unsigned int intensity)
{
	switch(whichOne) {
		case '0':
			set_led0(intensity);
			break;
		case '1':
			set_led1(intensity);
			break;
		case '2':
			set_led2(intensity);
			break;
		case '3':
			set_led3(intensity);
			break;
		default:
			break;
	}
}

void set_led0(unsigned int user)
{
	led_values_temp[6] = user;
}

void set_led1(unsigned int user)
{
	led_values_temp[7] = user;
}

void set_led2(unsigned int user)
{
	led_values_temp[8] = user;
}

void set_led3(unsigned int user)
{
	led_values_temp[9] = user;
}


// Turns off all LEDs and vibration motors
void turn_off_leds()
{

	// Turn pins off in case they're on
	set_orb0(0,0,0);
	set_orb1(0,0,0);
	set_led0(0);
	set_led1(0);
	set_led2(0);
	set_led3(0);
}




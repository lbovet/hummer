/*
	motor.c - Contains functions necessary for activating and driving the 
	H-bridge.  To add:  Over current protection with the sensor
	author:  Tom Lauwers
*/

/*  init_motor() - Initializes timer1 to generate phase-correct PWM
	at a frequency of 31.25 Khz
*/


// This method initializes the motor PWM ports and sets the direction pins to outputs
void init_motor() {

	// Configure counter such that we use fast
	// PWM with 8-bit resolution at a frequency of
	// 8000000/(1*255) = ~31 KHz
	
	TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
	TCCR1B = _BV(CS10) | _BV(WGM12);
	
	// Configure the four direction pins and two PWM as outputs and enable the H-bridge:
	DDRF |= _BV(PF6) | _BV(PF7); // direction pins
	DDRD |= _BV(PD4) | _BV(PD5);
	DDRB |= _BV(PB5) | _BV(PB6);  // PWM pins

	// Turn off the motors
	turn_off_motors();
}

// The following functions set the left & right motor direction and speed
void set_motor(uint8_t whichOne, uint8_t direction, uint8_t speed) {

	// Make sure no one sends out of bounds speed arguments
	if(speed > 255)
		speed = 255;
	
	if(speed < 0)
		speed = 0;
	
	
	if(whichOne == '0') {
		// Turn on D4, turn off D5 to go forward
		if(direction == 0) {
			PORTD &= ~_BV(PIN5);
			PORTD |= _BV(PIN4);
		}
		// Turn off D4, turn on D5 to go back
		else {
			PORTD |= _BV(PIN5);
			PORTD &= ~_BV(PIN4);
		}	
		// Set the timer to count up to speed, an 8-bit value
		OCR1A = speed;
		motor_vals[0] = direction+48;
		motor_vals[1] = speed;
	}
	else {
		// Turn on F6, turn off F7 to go forward
		if(direction == 0) {
			PORTF &= ~_BV(PIN7);
			PORTF |= _BV(PIN6);
		}
		// Turn off F6, turn on F7 to go back
		else {
			PORTF |= _BV(PIN7);
			PORTF &= ~_BV(PIN6);
		}	
		// Set the timer to count up to speed, an 8-bit value
		OCR1B = speed;
		motor_vals[2] = direction+48;
		motor_vals[3] = speed;
	}
	
}

// Just turns off the motors
void turn_off_motors() {
	OCR1A = 0x00;
	OCR1B = 0x00;
	motor_vals[0] = 0;
	motor_vals[1] = 0;
	motor_vals[2] = 0;
	motor_vals[3] = 0;
	
}


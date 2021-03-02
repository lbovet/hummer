/*  
	servo.c - Contains functions and interrupts necessary to activate servos
	author:  Tom Lauwers
*/

void disable_servos()
{
	transmitByteToTiny(0xFF);
}

void set_servo(uint8_t servo, uint8_t value)
{
	transmitByteToTiny(servo);
	_delay_us(500);
	transmitByteToTiny(value);	
	servo_values_temp[servo] = value;
}


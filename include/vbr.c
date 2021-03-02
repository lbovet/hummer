
void set_vibration_motor(uint8_t whichOne, uint8_t val) {
	whichOne -= 44; // Convert from ASCII 0,1 to numeric 4 or 5
	transmitByteToTiny(whichOne);
	_delay_us(500);
	transmitByteToTiny(val);
	
	vbr_values_temp[whichOne-4]=val;
}	

void disable_vibration_motors() {
	transmitByteToTiny(0xFE);
	vbr_values_temp[0] = 0;
	vbr_values_temp[1] = 0;
}


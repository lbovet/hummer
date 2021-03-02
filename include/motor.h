/*
	motor.h - Contains the function prototypes and global variables for controlling motors
	author:  Tom Lauwers
*/



int motorOffCount = 0;

uint8_t motor_vals[4] = {0,0,0,0};

// Function descriptions can be found in motor.c
void init_motor(void);
void set_motor(uint8_t whichOne, uint8_t direction, uint8_t speed);
void turn_off_motors(void);


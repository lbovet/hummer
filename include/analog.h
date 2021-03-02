/*  analog.h - Header file for Finch Analog inputs
	author:  Tom Lauwers
*/

#define SENSOR0   0b01100000
#define SENSOR1   0b01100001
#define SENSOR2   0b01100100
#define SENSOR3   0b01100101

// Function description can be found in analog.c
void init_analog(void);
unsigned int read_sensor(char sensor);

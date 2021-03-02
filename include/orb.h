/*  
	orb.h - Contains variables and function prototypes necessary to run the orb
	author:  Tom Lauwers
*/


// Defining pins used by the ORB and User LEDs
#define USERLED0  PB4
#define USERLED1  PB0
#define USERLED2  PC6
#define USERLED3  PB7
#define REDLED0   PD6
#define GREENLED0 PD1
#define BLUELED0  PD0
#define REDLED1   PE6
#define GREENLED1 PE2
#define BLUELED1  PD7
#define ACTIVITY  PC7

// orb_values_temp stores the red, green, blue values specified by calling set_orb

// orb_values reads orb_values_temp at the beginning of each interrupt cycle and
// so holds these values constant even if set_orb is called in the middle of an interrupt cycle
uint8_t led_values[11] = {0,0,0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t led_values_temp[11] = {0,0,0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t next_led_val = 0;
uint8_t  activity_state = 0;  // Stores the activity state - fading for idle, solid for connected, intermittent blink for no connection
uint8_t  activity_val = 0; // Activity intensity value
uint8_t  activity_dir = 0; // Direction of intensity value of activity LED - necessary for fading

// For function descriptions see orb.c 
void init_orb(void);
void set_orb(uint8_t whichOne, unsigned int red_led, unsigned int green_led, unsigned int blue_led);
void set_orb0(unsigned int red_led, unsigned int green_led, unsigned int blue_led); 
void set_orb1(unsigned int red_led, unsigned int green_led, unsigned int blue_led); 
void set_led(uint8_t whichOne, unsigned int intensity);
void set_led0(unsigned int user);
void set_led1(unsigned int user);
void set_led2(unsigned int user);
void set_led3(unsigned int user);
void turn_off_leds(void);



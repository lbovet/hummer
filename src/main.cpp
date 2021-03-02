#include "main.h"

int main(void)
{
  // Set up the motor power pin as an input
  DDRD &= (0xFF - _BV(PD3));

  sei();
  init_analog();
  init_motor();
  init_orb();
  init_tiny_comm();

  set_led(1, 128);

  while(1) {
    set_led(0, read_sensor(SENSOR0));
  }
}
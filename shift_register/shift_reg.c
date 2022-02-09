// Simple program using an 8-bit shift register (SN74HC595)
// to light up a set of 8 leds one at a time in a loop

#include <avr/io.h>
#include <util/delay.h>

#define DATA_PIN PD4
#define LATCH_PIN PD5
#define CLOCK_PIN PD6

int main() {
  // set the data, latch and clock pins to output
  DDRD |= (1 << DATA_PIN);
  DDRD |= (1 << LATCH_PIN);
  DDRD |= (1 << CLOCK_PIN);

  int led_lit = 0;

  while(1) {
    PORTD |= (1 << LATCH_PIN);
    // push in 8 bits of data
    for(int i = 0; i < 8; i++) {
      // set data pin to 1 if bit number matches led that should be on
      if(led_lit == i) {
        PORTD |= (1 << DATA_PIN);
      } else {
        PORTD &= ~(1 << DATA_PIN);
      }

      // tick the clock
      PORTD &= ~(1 << CLOCK_PIN);
      PORTD |= (1 << CLOCK_PIN);
    }

    // increment or reset the led counter
    if(led_lit == 7) {
      led_lit = 0;
    } else {
      led_lit++;
    }

    // flip latch to out
    PORTD &= ~(1 << LATCH_PIN);

    _delay_ms(500);
  }

  return 0;
}

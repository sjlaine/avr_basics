// code to control an 8x8 led matrix, with each of its 16 pins
// connected to a different avr pin (functions allow controlling single leds
// by row and column number)

#include <avr/io.h>
#include <util/delay.h>

// Rows
#define R1 PD2
#define R2 PD3
#define R3 PD4
#define R4 PD5
#define R5 PD6
#define R6 PD7
#define R7 PB0
#define R8 PB1

//Columns
#define C1 PB2
#define C2 PB3
#define C3 PB4
#define C4 PB5
#define C5 PC0
#define C6 PC1
#define C7 PC2
#define C8 PC3

void setRow(unsigned int row) {
   // set all rows to high
   PORTD = 0xff;
   PORTB |= (1 << R7);
   PORTB |= (1 << R8);

   switch(row) {
      case 1:
         PORTD &= ~(1 << R1);
         break;
      case 2:
         PORTD &= ~(1 << R2);
         break;
      case 3:
         PORTD &= ~(1 << R3);
         break;
      case 4:
         PORTD &= ~(1 << R4);
         break;
      case 5:
         PORTD &= ~(1 << R5);
         break;
      case 6:
         PORTD &= ~(1 << R6);
         break;
      case 7:
         PORTB &= ~(1 << R7);
         break;
      case 8:
         PORTB &= ~(1 << R8);
         break;
   }
}

// pin = magic_identifier & 0x7;
// port_id = magic_identifier >> 3;
// 0b00, 0b01, 0b10
// 0b111

void setColumn(unsigned int col) {
   // set all columns to low
   PORTB &= 0b00000011;
   PORTC &= 0;

   switch(col) {
      case 1:
         PORTB |= (1 << C1);
         break;
      case 2:
         PORTB |= (1 << C2);
         break;
      case 3:
         PORTB |= (1 << C3);
         break;
      case 4:
         PORTB |= (1 << C4);
         break;
      case 5:
         PORTB |= (1 << C6);
         break;
      case 6:
         PORTC |= (1 << C5);
         break;
      case 7:
         PORTC |= (1 << C7);
         break;
      case 8:
         PORTC |= (1 << C8);
         break;
   }
}

void main(void) {
   // set LED DDR to output
   DDRB = 0xff;
   DDRD = 0xff;

   // set all rows to high
   PORTD = 0xff;
   PORTB |= (1 << R7);
   PORTB |= (1 << R8);

   // broken rows: 2, 3, 5
   // rows are low, columns are high
   // PORTD &= ~(1 << R1); // make row 1 low

   int i = 1;

   while(1) {
      for(int i = 1; i < 9; i++) {
         for(int j = 1; j <= 8; j++) {
            setRow(i);
            setColumn(j);
            _delay_ms(500);
         }
      }
   }
}

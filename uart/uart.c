// simple code written with the help of the atmega328 datasheet
// code samples to transmit/receive data via uart

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#define BUTTON_PORT PORTD
#define BUTTON_PIN PIND
#define BUTTON PIND2

#define LED_PORT PORTB
#define LED_DDR DDRB
#define LED0 0 // port B pin 0

void USART_Init(unsigned int ubrr) {
  /*Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;

  UCSR0B = (1<<RXEN0)|(1<<TXEN0); // enable receiver and transmitter
  UCSR0C = (1<<USBS0)|(3<<UCSZ00); // Set frame format: 8data, 2stop bit
}

void USART_Transmit(unsigned char data) {
  /* Wait for empty transmit buffer */
  while (!(UCSR0A & (1<<UDRE0)));
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

unsigned char USART_Receive(void) {
  /* Wait for data to be received */
  while (!(UCSR0A & (1<<RXC0)));
  /* Get and return received data from buffer */
  return UDR0;
}

ISR(INT0_vect) {
  bool button_pressed = bit_is_clear(BUTTON_PIN, BUTTON); // when button high

  if(button_pressed) {
    USART_Transmit('a');
  }
}

void initInterrupt0(void) {
  EIMSK |= (1 << INT0); // enables the int0 interrupt
  EICRA |= (1 << ISC00); // makes interrupt trigger on any logical change (as opposed to just int low, etc.)
  sei(); // enable interrupts globally
}

void main(void) {
  USART_Init(MYUBRR); // init UART
  initInterrupt0(); // init button interrupt

  LED_DDR = 0xff; // set LED DDR to output
  BUTTON_PORT |= (1 << BUTTON); // enabling pull-up resistor for button

  while(1) {
    bool button_pressed = bit_is_clear(BUTTON_PIN, BUTTON); // when button high

    if(USART_Receive()) {
      LED_PORT ^= (1 << LED0);
    }
  }
}

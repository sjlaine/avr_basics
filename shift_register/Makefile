# compiler
CC=avr-gcc

# -Os tells compiler to optimize for size
# DF_CPU 16mHz tells clock how fast to run
# atmega328p is the platform
CFLAGS= -Os -DF_CPU=16000000UL -mmcu=atmega328p

all: shift_reg.out

USBPORT:=$(shell ls /dev/tty.usbmodem*)

%.out: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@

%.hex: %.out
	avr-objcopy -O ihex -R .eeprom $< $@

# Flash board
install.%: %.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P ${USBPORT} -b 115200 -U flash:w:$<

clean:
	rm -f *.hex *.out

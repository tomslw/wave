

#compiler
CC = avr-gcc
OBJCOPY = avr-objcopy

#my project
TARGET = wave
OBJECTS = wave.o adc.o wavemod.o

# is going to rebuild them if changed
HEADERS = adc.h uart.h wavemod.h

#the microcontroller and paramaters
MCU = atmega328p
F_CPU = 16000000LU
BAUD = 9600

TARGET_ARCH = -mmcu=$(MCU)

WERRORS = -Werror=int-conversion
#compiler/linker options
CFLAGS = -g -Wall $(WERRORS) -Os -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) $(TARGET_ARCH)

#targets
all: $(TARGET).elf ;

$(TARGET).elf: $(OBJECTS)
	$(CC) $(TARGET_ARCH) -o $@ $^

%.o: %.c Makefile $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

flash: $(TARGET).elf
	avrdude -c arduino -P /dev/ttyACM0 -p m328p -U flash:w:$<

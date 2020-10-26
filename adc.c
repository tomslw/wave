#include <avr/io.h>


uint16_t adc_convert(uint8_t pin)
{

  ADMUX &= 0xf0; // clears the selected pin
  ADMUX |= pin;   // selects the pin

  ADCSRA |= _BV(ADSC); //starts Conversion


  while ( (ADCSRA & _BV(ADSC)) ); //loops until done reading (checks the bit if is disabled in the ADMUX)

  return ADC;
}

void adc_init()
{
  ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);// sets the prescaler for the adc so that it works at its intended frequency
                                                // the adc for the atmega328p works best with 50khz-200khz, but can work with
                                                // more than 200khz at a lower resolution if needed
                                                // this knocks it down to 125khz


  ADCSRA |= (1<<ADEN);  // turns on the adc

  //ADMUX = (1<<REFS1)|(1<<REFS0); // sets reference voltage to 1.1v
  ADMUX |= (1<<REFS0);  // sets reference voltage to vcc
}

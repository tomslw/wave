#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>
#include "adc.h"
//#include "uart.h"

ISR(ADC_vect)
{
  // sets the new TOP value for the timer from analog (on differant mode)
  //OCR1A = ADC;


  // set the new compare value
  OCR1A = ADC;

  //printf("adc interrupt \n");
  //ADCSRA &= ~(1 << ADSC);

  // manualy clear the "overflow flag" because it dosent clear itself
  TIFR1 |= (1 << TOV1); // otherwise its allways on and the adc interrupt would run only once
}


ISR(TIMER1_OVF_vect) // currently disabled because there is no need for its existance
{
  OCR1A = (float)adc_convert(0) / 1023 * 0xFFFF;
  //PORTB ^= (1 << DDB5);  // swithes the port on and off (built in led)
}





int main(){

  sei(); // enable interrups
  adc_init();
  //uart_init();
  //stdout = &uart_output;



  //TCCR1B |= (1 << CS12) | (1 << CS10); // enables timer and sets the prescaler - 1024
  //TCCR1B |= (1 << CS12); // enables timer and sets the prescaler - 256
  //TCCR1B |= (1 << CS11) | (1 << CS10); // enables timer and sets the prescaler - 64
  //TCCR1B |= (1 << CS11); // enables timer and sets the prescaler - 8
  TCCR1B |= (1 << CS10); // to 1

  //TIMSK1 |= (1 << TOIE1);  // enables interrupt on each timer tick to update the TOP value

  //TCCR1A |= (1 << WGM10) | (1 << WGM11);
  //TCCR1B |= (1 << WGM13) | (1 << WGM12);  // sets up the Waveform Generation Mode to the nr15

  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12)|(1 << WGM13);  // fast PWM mode that looks at ICR1 for TOP

  ICR1 = 0xFFFF; // max

  // ADC =====================
  ADCSRB |= (1 << ADTS2) | (1 << ADTS1);  // configures the adc autotrigger to timer1 overflow
  //ADCSRB |= (1 << ADTS2) | (1 << ADTS0);  // configures the adc autotrigger to timer1 compare match b

  ADCSRA |= (1 << ADIE) | (1 << ADATE);                  // enables the adc conversion complete interrupt

  ADMUX &= 0xf0; // clears the selected pin
  ADMUX |= (uint8_t)0;   // selects the pin
  ADMUX |= (1 << ADLAR); // Left aligned the top value register for more optimized functionality (apart of the float removal)
  // =========================


  //DDRB |= (1 << DDB5);
  DDRB |= (1 << DDB1);  // configures port as output

  //PORTB ^= (1 << DDB5);

  TCCR1A |= (1 << COM1A0) | (1 << COM1A1); // make it turn on the pin on compare

  while(1) {}


}

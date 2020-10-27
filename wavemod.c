#include <avr/io.h>
#include <avr/interrupt.h>
#include "wavemod.h"

volatile int val;

volatile int *const timer_value = &val;

ISR(TIMER1_OVF_vect)
{
    OCR1A = val;
}

void TopSwitch()
{
    sei(); // turns on interrupts

    TCCR1A &= ~((1 << WGM11) | (1 << WGM10)); // clears the pins
    TCCR1B &= ~((1 << WGM12) | (1 << WGM13)); // aka clears the previous config

    TCCR1A |= (1 << WGM10) | (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12); // fast PWM mode that looks at OCR1A for TOP

    TIMSK1 |= (1 << TOIE1); // enables interrupt on each timer tick to update the TOP value

    DDRB |= (1 << DDB1); // sets the pin to output

    TCCR1A |= (1 << COM1A0) | (1 << COM1A1); // make it turn on the pin on compare
}

void CompareSwitch(int pin) // have to set the prescaler before this btw (only DDB1 and DDB2 pins are valid)
{  
    sei();  // turns on interrupts

    TCCR1A &= ~((1 << WGM11) | (1 << WGM10));   // clears the pins
    TCCR1B &= ~((1 << WGM12) | (1 << WGM13));   // aka clears the previous config

    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13); // fast PWM mode that looks at ICR1 for TOP

    ICR1 = 0xFFFF;  // max top value

    TIMSK1 |= (1 << TOIE1); // enables interrupt on each timer tick to update the TOP value

    DDRB |= (1 << pin);  // sets the pin to output

    if (pin == DDB1)
    {
        TCCR1A |= (1 << COM1A0) | (1 << COM1A1); // make it turn on the pin on compare
    }
    else if (pin == DDB2)
    {
        TCCR1A |= (1 << COM1B0) | (1 << COM1B1); // make it turn on the pin on compare
    }
}


void SetPrescaler(enum PrescalerValues val)
{
    // clears the prescaler pins for Timer1
    TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));

    // sets the prescaler for Timer1
    switch (val)
    {
    case V1:
        TCCR1B |= (1 << CS10);
        break;
    case V8:
        TCCR1B |= (1 << CS11);
        break;
    case V64:
        TCCR1B |= (1 << CS11) | (1 << CS10);
        break;
    case V256:
        TCCR1B |= (1 << CS12);
        break;
    case V1024:
        TCCR1B |= (1 << CS12) | (1 << CS10);
        break;
    }

}
#ifndef _WAVEMOD_H
#define _WAVEMOD_H

extern volatile int *const timer_value; // can be from 0x0000 to 0xFFFF

enum PrescalerValues{
    V1 = 1,
    V8 = 8,
    V64 = 64,
    V256 = 256,
    V1024 = 1024
};

void TopSwitch();   // works only on the DDB1 port

void CompareSwitch(int pin);    // have to set the prescaler before this btw (only DDB1 and DDB2 pins are valid)

void SetPrescaler(enum PrescalerValues val);

void ClockGen(long frequency); // overwrites the prescaler (no need to set the prescaler for this one)
// MIN frequency is 1hz
// The precision is lost over 80khz if you need unconventional frequencies.
// It can do MAX 4Mhz but the square wave looks more like a tooth than a square, it can do 2Mhz, 1Mhz and 800khz too, same applies.

#endif
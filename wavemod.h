#ifndef _WAVEMOD_H
#define _WAVEMOD_H

extern int * const timer_value;

enum PrescalerValues{
    V1 = 1,
    V8 = 8,
    V64 = 64,
    V256 = 256,
    V1024 = 1024
};

void TopSwitch();

void CompareSwitch(int pin); // have to set the prescaler before this btw (only DDB1 and DDB2 pins are valid)

void SetPrescaler(enum PrescalerValues val);

#endif
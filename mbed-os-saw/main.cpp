#include "mbed.h"

// main() runs in its own thread in the OS
#define wt (0.0001)


AnalogOut Aout(PA_4); //create an analog output on pin 18

int main()
{
    while (true) {

    // Aout=0.13;         // 0.25*3.3V = 0.825V
    // wait(0.0001);
    // Aout=0.26;          // 0.5*3.3V = 1.65V
    // wait(0.0001);
    // Aout=0.39;         // 0.75*3.3V = 2.475V
    // wait(0.0001);
    // Aout=0.52;         // 0.25*3.3V = 0.825V
    // wait(0.0001);
    // Aout=0.65;          // 0.5*3.3V = 1.65V
    // wait(0.0001);
    // Aout=0.78;         // 0.75*3.3V = 2.475V
    // wait(0.0001);
    // Aout=0.91;         // 0.75*3.3V = 2.475V
    // wait(0.0001);

    float i = 0;
    Aout = 0;

    for(i=0; i<10; i++) {

    Aout = (float)i * 0.1;         // 0.25*3.3V = 0.825V
    wait(wt);
    }

    }

}
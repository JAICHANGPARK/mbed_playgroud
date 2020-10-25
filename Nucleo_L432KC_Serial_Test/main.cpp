/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "stats_report.h"

DigitalOut led1(LED1);

#define SLEEP_TIME                  500 // (msec)
#define PRINT_AFTER_N_LOOPS         20
Serial pc(USBTX, USBRX); // tx, rx

// main() runs in its own thread in the OS
int main()
{
    SystemReport sys_state( SLEEP_TIME * PRINT_AFTER_N_LOOPS /* Loop delay time in ms */);
    pc.baud(9600);
    int count = 0;
    while (true) {
        pc.printf("hello");
        wait(1);
        
        ++count;
    }
}

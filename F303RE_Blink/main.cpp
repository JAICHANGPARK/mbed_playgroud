/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "stats_report.h"

#define TFT_WIDTH 320
#define TFT_HEIGHT 240
 
#define TFT_BLUE    0x1F00
#define TFT_RED     0x00F8
#define TFT_GREEN   0xE007


SPI spi(PA_7, PA_6, PA_5);


DigitalOut led1(LED1);

DigitalOut cs(PB_5);    // TFT chipselect pin
DigitalOut dc(PA_8);    // TFT data command select pin
DigitalOut rst(PA_10);  // TFT reset pin

#define SLEEP_TIME                  1000 // (msec)
#define PRINT_AFTER_N_LOOPS         20

// main() runs in its own thread in the OS
int main()
{
    SystemReport sys_state( SLEEP_TIME * PRINT_AFTER_N_LOOPS /* Loop delay time in ms */);

    int count = 0;
    while (true) {
        // Blink LED and wait 0.5 seconds
        led1 = !led1;
        wait_ms(SLEEP_TIME);

        if ((0 == count) || (PRINT_AFTER_N_LOOPS == count)) {
            // Following the main thread wait, report on the current system status
            sys_state.report_state();
            count = 0;
        }
        ++count;
    }
}

/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "./QEI/QEI.h"
#include "mbed.h"
#include "stats_report.h"

#define SLEEP_TIME 5000 // (msec)
#define PRINT_AFTER_N_LOOPS 20

Serial pc(USBTX, USBRX);

DigitalOut led1(LED1);
DigitalOut IO_12V_ON(PG_2);
DigitalOut IO_24V_ON(PG_3);
DigitalOut LH_DIO1(PG_0);
DigitalOut LH_DIO2(PG_1);
DigitalOut LH_DIO3(PD_1);
DigitalOut LK_DIO1(PF_9);
DigitalOut LK_DIO2(PD_0);
DigitalOut LK_DIO3(PF_7);

DigitalOut LH_ENABLE(PH_0);
DigitalOut LK_ENABLE(PH_1);

DigitalOut L_DAC_SYNC(PE_4);
DigitalOut L_DAC_DATA(PE_2);
DigitalOut L_DAC_CLK(PD_3);

QEI wheel(PE_5, PE_6, NC, 1440);
QEI wheel2(PF_8, PE_3, NC, 1440);
// main() runs in its own thread in the OS

void sendDigitalValue(uint16_t value);
uint32_t testValue = 0x00311fff;
int main() {
  SystemReport sys_state(SLEEP_TIME *
                         PRINT_AFTER_N_LOOPS /* Loop delay time in ms */);

  int count = 0;
  IO_12V_ON.write(0);
  IO_24V_ON.write(0);

  LH_ENABLE = 0;
  LK_ENABLE = 0;

  wait_ms(SLEEP_TIME);
  IO_12V_ON.write(1);
  IO_24V_ON.write(1);
  //   LH_DIO1.write(1);
  //   wait(10);
  //   LH_DIO1.write(0);
  //   wait(5);
  //   LH_DIO2.write(0);
  //   LH_DIO3.write(1);
  //   LH_DIO1.write(0);
  L_DAC_SYNC.write(1);
  L_DAC_DATA = 1;
  L_DAC_CLK = 1;
  while (true) {
    // sendDigitalValue(16);

    // wait(0.1);
    // pc.printf("wheel1 Pulses is: %i | ", wheel.getPulses());
    // pc.printf("getRevolutions is: %i | ", wheel.getRevolutions());
    // pc.printf("getCurrentState is: %i\n\r", wheel.getCurrentState());

    // pc.printf("wheel2 Pulses is: %i | ", wheel2.getPulses());
    // pc.printf("getRevolutions is: %i | ", wheel2.getRevolutions());
    // pc.printf("getCurrentState is: %i\n\r", wheel2.getCurrentState());

    // Blink LED and wait 0.5 seconds
    // led1 = !led1;
    // LH_DIO1.write(1);
    // wait(1);
    // LH_DIO1.write(0);

    // LH_DIO2.write(1);
    // wait(1);
    // LH_DIO2.write(0);
    // LH_DIO3.write(1);
    // wait(1);
    // LH_DIO3.write(0);
    // wait(1);
    // LH_ENABLE = 1;

    // LK_DIO1.write(1);
    // wait(1);
    // LK_DIO1.write(0);

    // LK_DIO2.write(1);
    // wait(1);
    // LK_DIO2.write(0);

    // LK_DIO3.write(1);
    // wait(1);
    // LK_DIO3.write(0);

    // LK_ENABLE = 1;

    // if ((0 == count) || (PRINT_AFTER_N_LOOPS == count)) {
    //   // Following the main thread wait, report on the current system status
    //   sys_state.report_state();
    //   count = 0;
    // }
    // ++count;

    for (int i = 0; i < 24; i++) {
        pc.printf("%d", i);
      pc.printf("wheel1 Pulses is: %d ", (testValue >> (24 - i)));
    }
    pc.printf("\n\r");
  }
}

void sendDigitalValue(uint16_t value) {
  L_DAC_SYNC.write(0);
  wait_ns(10);
  for (int i = 0; i < 24; i++) {
    L_DAC_CLK = 1;
    wait_ns(9);
    L_DAC_CLK = 0;
    L_DAC_DATA = (testValue >> (24 - i) | 0x01);
    wait_ns(9);
  }

  L_DAC_SYNC.write(1);
}
/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "platform/mbed_thread.h"

// Blinking rate in milliseconds
#define BLINKING_RATE_MS 500
Serial pc(USBTX, USBRX); // tx, rx
Serial uart(PB_3, PB_4); //tx, rx
bool echo_check = false;

int main() {
  // Initialise the digital pin LED1 as an output
  uint8_t buffer[20];
  uint8_t cnt = 0;
  pc.baud(115200);
  uart.baud(9600);
  DigitalOut led(LED1);

  uint8_t buff0[2] = {0x80, 0x80};

  uint8_t buff1[9] = {0x02, 0x08, 0x23, 0x00, 0x20, 0x00, 0xBD, 0x03};

  while (true) {
    led = !led;
    uint8_t temp = uart.getc();

    if (!echo_check && temp == 0x80) {
      pc.printf("Write buff0 \n");
      uart.write(buff0, 2, NULL);
      echo_check = true;
    } else {
      echo_check = false;
    }
    if (echo_check) {
      pc.printf("Write buff1 \n");
      for (int i = 0; i < sizeof(buff1); i++) {
        // device.write((unsigned char*)buff1[i], 1, NULL);
        uart.putc(buff1[i]);
      }
      //   device.write(buff1, 9, NULL);
    }

    // for(int i = 0; i < 2; i++){
    //     device.putc(buff[i]);
    // }
    thread_sleep_for(1000);
  }
}

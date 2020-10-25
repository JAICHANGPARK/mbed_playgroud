/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "stats_report.h"

#if !DEVICE_I2CSLAVE
  #error [NOT_SUPPORTED] I2C Slave is not supported
#endif

Serial pc(USBTX, USBRX); // tx, rx

I2CSlave slave(PB_7, PB_6); //Configure I2C slave
DigitalOut red_led(LED1); //red led
DigitalOut green_led(LED2); //green led1
const char message[] = "Slave!";
// main() runs in its own thread in the OS
int main()
{
    slave.address(0xA0);
    char buf[10];
    char msg[] = "Slave!";
    pc.baud(9600);
    pc.printf("I2C Testing");

  
    int cnt = 0x41;

    while (1) {
        int operation = slave.receive();
         int byte_read = 0;
         int status = 0;
        switch (operation) {
            case I2CSlave::ReadAddressed:
                status = slave.write(message, sizeof(message));
                if (status == 0) {
                    pc.printf("Written message: %s\n", message);
                } else {
                    pc.printf("Failed to write message.\n");
                }
                break;
            case I2CSlave::WriteGeneral:
                byte_read = slave.read(buf, 10);
                pc.printf("Read General: %c (%d)\n", byte_read, byte_read);
                break;
            case I2CSlave::WriteAddressed:
                byte_read = slave.read(buf, 10);
                pc.printf("Read Addressed: %s (%d)\n", buf, byte_read);
                break;
        }
       for(int i = 0; i < 10; i++) buf[i] = 0;    // Clear buffer
   }
}

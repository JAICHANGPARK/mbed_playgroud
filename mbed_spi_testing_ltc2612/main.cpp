#include "mbed.h"

// main() runs in its own thread in the OS
uint32_t data;
DigitalOut IO_12V_ON(PG_2);
DigitalOut IO_24V_ON(PG_3);

SPI spi(PC_3, NC, PD_3);
DigitalOut cs(PE_4);

DigitalOut L_DAC_SYNC(PE_4);
DigitalOut L_DAC_DATA(PC_3);
DigitalOut L_DAC_CLK(PD_3);

void sendDigitalValue(uint32_t value) {
  L_DAC_SYNC.write(0);
  wait_ns(10);
  for (int i = 0; i < 24; i++) {
    L_DAC_CLK = 0;
    L_DAC_DATA = (value >> (23 - i) & 0x01);
    wait_ns(10);
    L_DAC_CLK = 1;
    wait_ns(10);
  }
  L_DAC_SYNC.write(1);
  L_DAC_CLK = 1;
  L_DAC_DATA = 1;
}

int main() {
  data = 0x0031fffc;
  IO_12V_ON.write(0);
  IO_24V_ON.write(0);
  wait_ms(3000);
  IO_12V_ON.write(1);
  IO_24V_ON.write(1);
  L_DAC_SYNC = 1;
  L_DAC_CLK = 1;
  L_DAC_DATA = 1;
  //   cs = 1;
  //   spi.format(24, 1);
  //   spi.frequency(1000000);
  //   cs = 0;
  //   spi.write((data >> 16) & 0xFFFF); // MSB part first
  //   spi.write(data & 0xFFFF);         // LSB part
  //   cs = 1;

  sendDigitalValue(data);

  while (true) {
    sendDigitalValue(data);
    wait_ms(1);
    // cs = 1;
    // wait_ms(1);
    // cs = 0;
    // spi.write((data >> 16) & 0xFFFF); // MSB part first
    // spi.write(data & 0xFFFF);         // LSB part
    // cs = 1;
  }
}

/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "stats_report.h"

#define TFT_WIDTH 320
#define TFT_HEIGHT 240

#define TFT_BLUE 0x1F00
#define TFT_RED 0x00F8
#define TFT_GREEN 0xE007

SPI spi(PA_7, PA_6, PA_5);

DigitalOut led1(LED1);

DigitalOut cs(PB_5);   // TFT chipselect pin
DigitalOut dc(PA_8);   // TFT data command select pin
DigitalOut rst(PA_10); // TFT reset pin

#define SLEEP_TIME 1000 // (msec)
#define PRINT_AFTER_N_LOOPS 20

/*-------------------------------------------------------------------*/
/*  Write command                                                    */
/*-------------------------------------------------------------------*/
void write_cmd(uint8_t cmd) {
  dc = 0;
  spi.write(cmd);
}

/*-------------------------------------------------------------------*/
/*  Write data                                                       */
/*-------------------------------------------------------------------*/
void write_data(uint8_t data) {
  dc = 1;
  spi.write(data);
}

/*-------------------------------------------------------------------*/
/*  TFT reset                                                        */
/*-------------------------------------------------------------------*/
void tft_reset() {
  wait_ms(200);
  cs = 1;
  dc = 1;
  rst = 1;
  wait_ms(200);
  rst = 0;
  wait_us(10);
  rst = 1;
  wait_ms(120);
  cs = 0;
  wait_ms(10);

  write_cmd(0x3A);  // Pixel Format
  write_data(0x55); // 16bit Color

  write_cmd(0xB1); // Frame Control
  write_data(0);
  write_data(0x1f);

  write_cmd(0x36);  // Memory Access Control
  write_data(0xE8); // MY MX MV BGR

  write_cmd(0x11); // Sleep Out
  wait_ms(5);

  write_cmd(0x29); // Display On
}

/*-------------------------------------------------------------------*/
/*  Set the windows area and Start memory write.                     */
/*-------------------------------------------------------------------*/
void tft_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
  write_cmd(0x2A); // Column Address Set
  write_data(x0 >> 8);
  write_data(x0);
  write_data(x1 >> 8);
  write_data(x1);

  write_cmd(0x2B); // Page Address Set
  write_data(y0 >> 8);
  write_data(y0);
  write_data(y1 >> 8);
  write_data(y1);

  write_cmd(0x2C); // Memory Write

  wait_us(20);

  dc = 1;
}

/*-------------------------------------------------------------------*/
/*  Clear screen                                                     */
/*-------------------------------------------------------------------*/
void tft_clear(uint16_t color) {
  tft_set_window(0, 0, TFT_WIDTH, TFT_HEIGHT);

  for (int i = 0; i < TFT_WIDTH * TFT_HEIGHT; ++i) {
    spi.write(color & 0xff);
    spi.write(color >> 8);
  }
}

int main() {

  spi.format(8,3);
  spi.frequency(18000000);

  tft_reset();

  tft_clear(TFT_RED);

  wait(1);

  tft_clear(TFT_GREEN);

  wait(1);

  tft_clear(TFT_BLUE);

  while (1) {

    // tft_reset();
    wait_ms(500);
    tft_clear(TFT_RED);

    // wait(1);
    wait_ms(500);
    tft_clear(TFT_GREEN);

    // wait(1);
    wait_ms(500);

    tft_clear(TFT_BLUE);
  };
}

#include "Arial12x12.h"
#include "Arial24x23.h"
#include "Arial28x28.h"
#include "SPI_TFT_ILI9341.h"
#include "font_big.h"
#include "mbed.h"
#include "string"

// main() runs in its own thread in the OS
SPI_TFT_ILI9341 TFT(PA_7, PA_6, PA_5, PB_5, PA_10, PA_8,
                    "TFT"); // mosi, miso, sclk, cs, reset, dc

DigitalOut cs(PB_5);   // TFT chipselect pin
DigitalOut dc(PA_8);   // TFT data command select pin
DigitalOut rst(PA_10); // TFT reset pin

extern unsigned char p1[];       // the mbed logo
extern unsigned char IMG_woof[]; // the mbed logo

extern unsigned char IMG_purple[]; // the mbed logo
void drawGraphic() {

  TFT.cls();
  TFT.locate(100, 100);
  TFT.printf("Graphic");

  TFT.line(0, 0, 100, 0, Green);
  TFT.line(0, 0, 0, 200, Green);
  TFT.line(0, 0, 100, 200, Green);

  TFT.rect(100, 50, 150, 100, Red);
  TFT.fillrect(180, 25, 220, 70, Blue);

  TFT.circle(80, 150, 33, White);
  TFT.fillcircle(160, 190, 20, Yellow);

  double s;

  for (int i = 0; i < 320; i++) {
    s = 20 * sin((long double)i / 10);
    TFT.pixel(i, 100 + (int)s, Red);
  }
}
void biggerText() {
  // bigger text
  TFT.foreground(White);
  TFT.background(Blue);
  TFT.cls();
  TFT.locate(0, 0);
  TFT.printf("Different Fonts :");

  TFT.locate(0, 30);
  TFT.printf("Hello Mbed 1");
  TFT.locate(20, 80);
  TFT.printf("Hello Mbed 2");
  TFT.locate(35, 120);
  TFT.printf("Hello Mbed 3");
}

int main() {

  int i;
  // unsigned int y;
  TFT.claim(stdout); // send stdout to the TFT display
  // TFT.claim(stderr);      // send stderr to the TFT display
  // TFT.set_orientation(1);
  TFT.background(Black); // set background to black
  TFT.foreground(White); // set chars to white
  TFT.cls();             // clear the screen

  // y= 0;
  TFT.background(Black);
  TFT.cls();

  TFT.set_font((unsigned char *)Arial12x12);
  TFT.locate(0, 0);
  printf("  Hello Mbed ");

  ThisThread::sleep_for(5000);

  // draw some graphics
  TFT.cls();
  TFT.set_font((unsigned char *)Arial24x23);
  TFT.locate(100, 100);
  TFT.printf("Graphic");

  TFT.line(0, 0, 100, 0, Green);
  TFT.line(0, 0, 0, 200, Green);
  TFT.line(0, 0, 100, 200, Green);

  TFT.rect(100, 50, 150, 100, Red);
  TFT.fillrect(180, 25, 220, 70, Blue);

  TFT.circle(80, 150, 33, White);
  TFT.fillcircle(160, 190, 20, Yellow);

  double s;

  for (i = 0; i < 320; i++) {
    s = 20 * sin((long double)i / 10);
    TFT.pixel(i, 100 + (int)s, Red);
  }

  ThisThread::sleep_for(1000);

  // bigger text
  TFT.foreground(White);
  TFT.background(Blue);
  TFT.cls();
  TFT.set_font((unsigned char *)Arial24x23);
  TFT.locate(0, 0);
  TFT.printf("Different Fonts :");

  TFT.set_font((unsigned char *)Neu42x35);
  TFT.locate(0, 30);
  TFT.printf("Hello Mbed 1");
  TFT.set_font((unsigned char *)Arial24x23);
  TFT.locate(20, 80);
  TFT.printf("Hello Mbed 2");
  TFT.set_font((unsigned char *)Arial12x12);
  TFT.locate(35, 120);
  TFT.printf("Hello Mbed 3");
  ThisThread::sleep_for(3000);

  // mbed logo
  TFT.background(Black);
  TFT.cls();

  //   TFT.locate(10, 10);
  //   TFT.printf("Graphic from Flash");

  TFT.Bitmap(0, 0, 240, 320, IMG_woof);

  ThisThread::sleep_for(3000);
  TFT.cls();
  TFT.locate(10, 10);
  TFT.printf("Graphic from File System");
  TFT.locate(10, 20);
  TFT.printf("open test.bmp");
  int err = TFT.BMP_16(20, 50, "test.bmp");
  if (err != 1)
    TFT.printf(" - Err: %d", err);
  while (true) {

    // mbed logo
    TFT.background(Black);
    TFT.cls();

    //   TFT.locate(10, 10);
    //   TFT.printf("Graphic from Flash");

    TFT.Bitmap(0, 0, 240, 320, IMG_woof);

    ThisThread::sleep_for(3000);
    TFT.background(Black);
    TFT.cls();

    //   TFT.locate(10, 10);
    //   TFT.printf("Graphic from Flash");

    TFT.Bitmap(0, 0, 240, 320, IMG_purple);

    ThisThread::sleep_for(3000);
  }
  //   while (true) {
  //     TFT.cls(); // clear the screen
  //     drawGraphic();
  //     wait(1);
  //     TFT.cls(); // clear the screen
  //     biggerText();
  //     wait(1);
  //     TFT.background(Black);
  //     TFT.cls();

  //     TFT.locate(10, 10);
  //     TFT.printf("Graphic from Flash");

  //     TFT.Bitmap(90, 90, 172, 55, pokitto_icon);
  //   }
}

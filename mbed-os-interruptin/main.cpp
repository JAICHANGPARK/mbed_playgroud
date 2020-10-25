#include "mbed.h"

// main() runs in its own thread in the OS

InterruptIn     clockIOIn(PG_9);
DigitalOut      led(LED1);
DigitalOut      dataOut(PF_13);
DigitalOut      dataOutMinus(PE_9);
Serial          pc(USBTX, USBRX); // tx, rx
Timer           t;

uint16_t counter = 0;
uint16_t sendData = 0xABCD;

int interruptTime = 0;
double freq = 0.0;
int tempTime = 0;
bool flag = false;

bool getBit(uint16_t data);
bool getBitFromMSB(uint16_t data);

void flip() {

    // led = !led;
    // counter++;
    // tempTime = t.read_us() - interruptTime ;
    // freq =  1 / (tempTime / 1000000.0);  
    // interruptTime = t.read_us();
    // if(counter < 17){
    //     counter = 0;
    // }

    // if(sendData == 0x00){
    //     sendData = counter;
    // }

    // if(sendData == 0x0000){
    //     sendData = 0xABCD;
    // }

    flag = getBitFromMSB(sendData);
    sendData = sendData << 1;
    dataOut.write(flag);
    dataOutMinus.write(!flag);
    
    // counter++;

}

bool getBit(uint16_t data){
    return (data & 0x0001) == 0x0001;
}

bool getBitFromMSB(uint16_t data){
    return (data & 0x8000) == 0x8000;
}

int main()
{

    t.start();
    clockIOIn.fall(&flip);
    pc.printf("Hello World!\n\r");

    while (true) {
        //  pc.printf("%u, %dms %f hz \n\r", counter, tempTime, freq );
    }

}

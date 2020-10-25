#include "mbed.h"
#include "SDBlockDevice.h"
#include "FATFileSystem.h"
 
SDBlockDevice sd(PA_7, PA_6, PA_5, PB_5);
///SDBlockDevice sd(D11, D12, D13, D10);
FATFileSystem fs("sd");
Serial pc(SERIAL_TX, SERIAL_RX);
 
void testSDCard(){
    pc.printf("\nWait for new connection...\n");
    mkdir("/sd/mjm2016", 0777);
    FILE *fp = fopen("/sd/mjm2016/sdBlockDeviceTest.txt", "w");
    if(fp == NULL) {
        pc.printf("Could not open file for write\n");
        return  ;
    }
    fprintf(fp, "sdBlockDeviceTest System say \"Hello, have fun!\" ");
    pc.printf("Writing to your SD-CARD finished. BYE!!"); 
    fclose(fp);
    }
 
int main()
{
    sd.init();
    fs.mount(&sd);
    testSDCard();
    fs.unmount();
    sd.deinit();
}
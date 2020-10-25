#include "mbed.h"

// main() runs in its own thread in the OS

#define DLY 0.05

Thread lkMotorThread;
Thread lkJointThread;

// 모터 엔코더 Mock
DigitalOut aPlus(PF_13);
DigitalOut aMinus(PE_9);
DigitalOut bPlus(PE_11);
DigitalOut bMinus(PF_14);


DigitalOut JointPlus(PF_14);
DigitalOut JointMinus(PE_13);


InterruptIn button(PG_9);

void encoder(DigitalOut plus, DigitalOut minus);


void lkMotorIncreEncoderTread(){
    while(true){
       encoder(aPlus, aMinus);
    }
}

void lkJointIncreEncoderTread(){
    while(true){
        encoder(JointPlus, JointMinus);
    }
}

void encoder(DigitalOut plus, DigitalOut minus){
    for(int i = 0; i <= 20; i++){
            plus.write(1);
            wait(DLY);
            minus.write(1);
            wait(DLY);
            plus.write(0);
            wait(DLY);
            minus.write(0);
            wait(DLY);
        }

        wait(0.25);

        for(int i = 0; i <= 20; i++){
            minus.write(1);
            wait(DLY);
            plus.write(1);
            wait(DLY);

            minus.write(0);
            wait(DLY);
            plus.write(0);
            wait(DLY);
        }



}


int main()
{

    while(true){
        for(int i = 0; i<=20; i++){
            aPlus.write(1); aMinus.write(0);
            wait(DLY);
            bPlus.write(1); bMinus.write(0);
            wait(DLY);
  
            aPlus.write(0); aMinus.write(1);
            wait(DLY);
            bPlus.write(0); bMinus.write(1);
            wait(DLY);
        }

            for(int i = 0; i<=20; i++){
            aPlus.write(0); aMinus.write(1);
            wait(DLY);
            bPlus.write(0); bMinus.write(1);
            wait(DLY);

            aPlus.write(1); aMinus.write(0);
            wait(DLY);
            bPlus.write(1); bMinus.write(0);
            wait(DLY);
        }
        wait(0.3);
    }
//    lkMotorThread.start(lkMotorIncreEncoderTread);  
//    lkJointThread.start(lkJointIncreEncoderTread);  
    // while (true) {

        // encoder(aPlus, aMinus);
        //  encoder(JointPlus, JointMinus);
        // for(int i = 0; i <= 20; i++){
        //     aPlus.write(1);
        //     wait(DLY);
        //     aMinus.write(1);
        //     wait(DLY);
        //     aPlus.write(0);
        //     wait(DLY);
        //     aMinus.write(0);
        //     wait(DLY);

        //     // aPlus.write(1);
        //     // wait(DLY);
        //     // aMinus.write(1);
        //     // wait(DLY);
        //     // aPlus.write(0);
        //     // wait(DLY);
        //     // aMinus.write(0);
        //     // wait(DLY);
        // }

        // wait(0.5);

        // for(int i = 0; i <= 20; i++){
        //     aMinus.write(1);
        //     wait(DLY);
        //     aPlus.write(1);
        //     wait(DLY);

        //     aMinus.write(0);
        //     wait(DLY);
        //     aPlus.write(0);
        //     wait(DLY);

        //     // aMinus.write(1);
        //     // wait(DLY);
        //     // aPlus.write(1);
        //     // wait(DLY);

        //     // aMinus.write(0);
        //     // wait(DLY);
        //     // aPlus.write(0);
        //     // wait(DLY);
        // }
       
    
    // }
}

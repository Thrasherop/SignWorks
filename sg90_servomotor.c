/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== sg90_servomotor.c ========
 */
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>   //usleep()
/* Driver Header files */
#include <ti/drivers/PWM.h>

/* Driver configuration */
#include "ti_drivers_config.h"

// Declare motor driver functions
void set_motor(PWM_Handle handle, int percentage);
PWM_Handle* init_motor(int CONFIG_DEFINITION);
void init_fingers();
void move_joint(int finger, int joint, int percent);
void cycle_finger(int finger);

// High level movement functions
void close_hand();
void open_hand();
void c();
void l();
void f();
void x();
void s();
void b();
void i();
void w();
void y();
void o();

// Declare 2D array
PWM_Handle fingers[6][2];

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{

    /* Call driver init functions */
    PWM_init();

    init_fingers();



//    move_joint(4, 0, 90);
//    move_joint(2, 0, 90);

//    open_hand();

    int letter_gap = 2;
    int word_gap = 4;



    while(1){

//        close_hand();
//        sleep(1);
//        open_hand();
//        sleep(1);

//        c();
//        sleep(3);
//        open_hand();
//        sleep(2);

        // Billy
        b();
        sleep(letter_gap);
        open_hand();
        sleep(letter_gap);
        i();
        sleep(letter_gap);
        open_hand();
        sleep(letter_gap);
        l();
        sleep(letter_gap);
        open_hand();
        sleep(letter_gap);
        y();
        sleep(letter_gap);
        open_hand();
        sleep(letter_gap);
        s();
        sleep(letter_gap);
        open_hand();
        sleep(letter_gap);

        // cow
        sleep(word_gap); // sentence

        c();
        sleep(letter_gap);
        open_hand();
        sleep(letter_gap);
        o();
        sleep(letter_gap);
        open_hand();
        sleep(letter_gap);
        w();
        sleep(letter_gap);
        open_hand();
        sleep(letter_gap);

        // is
        sleep(word_gap); // word space


        i();
        sleep(letter_gap);
        open_hand();
        sleep(letter_gap);
        s();
        sleep(letter_gap);
        open_hand();
        sleep(letter_gap);

        // slow
        sleep(word_gap); // space

        s();
        sleep(letter_gap);
        open_hand();
        sleep(letter_gap);
        l();
        sleep(letter_gap);
        open_hand();
        sleep(letter_gap);
        o();
        sleep(letter_gap);
        open_hand();
        sleep(letter_gap);
        w();
        sleep(letter_gap);
        open_hand();
        sleep(letter_gap);



    }

}

void o(){
   // set fingers one by one
   move_joint(5, 0, 30);
   sleep(1);
   move_joint(1, 0, 25);
   move_joint(2, 0, 30);
   move_joint(4, 0, 30);
}

void y(){
    move_joint(2, 0, 25);
    move_joint(3, 0, 25);
}

void w(){
    move_joint(5, 0, 25);
    move_joint(1, 0, 25);
}

void i(){

    move_joint(2, 0, 25);
    move_joint(3, 0, 25);
    move_joint(1, 0, 25);

}

void b(){

    move_joint(1, 0, 25);

}

void s() {

    move_joint(5, 0, 25);
    sleep(1);
    move_joint(3, 0, 25);
    move_joint(2, 0, 25);
    sleep(1);
    move_joint(1, 0, 25);

}

void x(){

    move_joint(5, 0, 25);
    sleep(1);
    move_joint(3, 0, 25);
    move_joint(2, 0, 60);
    sleep(1);
    move_joint(1, 0, 25);

}

void f(){

    move_joint(1, 0, 25);
    move_joint(2, 0, 25);

}

void l(){

    move_joint(5,0,25);
    sleep(1);
    move_joint(4, 0, 25);
    sleep(1);

}

void c(){

    // set fingers one by one
    move_joint(5, 0, 50);
    sleep(1);
    move_joint(1, 0, 35);
    move_joint(2, 0, 40);
    move_joint(4, 0, 30);

}

void close_hand(){

    // Close fingers one by one
    move_joint(5, 0, 25);
    sleep(1);
    move_joint(1, 0, 25);
    move_joint(2, 0, 25);
    move_joint(4, 0, 25);

}

void open_hand(){

    // Close fingers one by one
    move_joint(1, 0, 90);
    move_joint(2, 0, 90);
    move_joint(4, 0, 90);
    sleep(1);
    move_joint(5, 0, 90);


}

void cycle_finger(int finger){
    move_joint(finger, 0, 25);
    sleep(1);
    move_joint(finger, 0, 80);
    sleep(1);
//    move_joint(finger, 0, 25);
//    sleep(1);
}


void move_joint(int finger, int joint, int percent){
    set_motor(fingers[finger][joint], percent);
}

void init_fingers(){

    // Create the first finger
    PWM_Handle finger1Handle = *(init_motor(FINGER_1));
    PWM_Handle finger2Handle = *(init_motor(FINGER_2));
    PWM_Handle finger34Handle = *(init_motor(FINGER_3_4));
    PWM_Handle finger5Handle = *(init_motor(FINGER_5));
    fingers[1][0] = finger1Handle;
    fingers[2][0] = finger2Handle;
    fingers[3][0] = finger34Handle;
    fingers[4][0] = finger34Handle;
    fingers[5][0] = finger5Handle;

    // Open all the fingers
    open_hand();

}

void set_motor(PWM_Handle handle, int percentage){

    int max = 2400;
    int thisDutyCycle = ((percentage * max) )/ 100;

    PWM_setDuty(handle, thisDutyCycle);

}

PWM_Handle* init_motor(int CONFIG_DEFINITION){


    uint32_t pwmPeriod = 20000;

    // Configure the motor
    PWM_Params pwmParams;
    PWM_Handle pwmHandle;
    PWM_Params_init(&pwmParams);
    pwmParams.dutyUnits = PWM_DUTY_US;
    pwmParams.dutyValue = 0;
    pwmParams.periodUnits = PWM_PERIOD_US;
    pwmParams.periodValue =pwmPeriod;
    pwmHandle = PWM_open(CONFIG_DEFINITION, &pwmParams);
    if(pwmHandle == NULL){
       while(1){}
    }

    // start the PWM
    PWM_start(pwmHandle);

    // return the handle
    return &pwmHandle;

}

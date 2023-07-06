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

    while(1){

//        move_joint(0, 0, 25);
//        sleep(1);
//        move_joint(0, 0, 99);
//        sleep(1);

//        cycle_finger(2);

        move_joint(5, 0, 25);
        sleep(2);
        move_joint(5, 0, 90);
        sleep(2);
//        move_joint(2, 0, 25);
//        sleep(2);
//        move_joint(3, 0, 25);
//        sleep(2);
//        move_joint(4, 0, 25);
//        sleep(2);
//        move_joint(5, 0, 25);
//        sleep(2);

    }

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

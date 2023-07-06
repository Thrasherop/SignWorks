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

// Declare 2D array
PWM_Handle fingers[5][2];

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{

    /* Call driver init functions */
    PWM_init();

    init_fingers();

    while(1){

        move_joint(0, 0, 25);
        sleep(1);
        move_joint(0, 0, 99);
        sleep(1);

    }

}

void move_joint(int finger, int joint, int percent){
    set_motor(fingers[finger][joint], percent);
}

void init_fingers(){

    // Create the first finger
    PWM_Handle pwmHandle1_1 = *(init_motor(CONFIG_PWM_1_1));
    PWM_Handle pwmHandle1_2 = *(init_motor(CONFIG_PWM_1_2));
    fingers[0][0] = pwmHandle1_1;
    fingers[0][1] = pwmHandle1_2;

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alt_interrupt.h"
#include "tie_ui_connection.h"

#define BUTTON_BASE 0xFF200004
#define BUTTON_SEC 0xFF200024

#define SEG_DISP1 0xFF200014
#define SEG_DISP2 0xFF200018
#define SEG_DISP3 0xFF20001C
#define SEG_DISP4 0xFF200020

#define TIMER_LOAD 0xFFFEC600
#define TIMER_CONTROL 0xFFFEC608
#define TIMER_INTERRUPT 0xFFFEC60C

uint32_t* button = (uint8_t*)BUTTON_BASE;
uint32_t* buttonW = BUTTON_SEC;

uint32_t* segDispVal4 = SEG_DISP1;
uint32_t* segDispVal3 = SEG_DISP2;
uint32_t* segDispVal2 = SEG_DISP3;
uint32_t* segDispVal1 = SEG_DISP4;

uint32_t* timerLoad = TIMER_LOAD;
uint32_t* timerControl = TIMER_CONTROL;
uint32_t* timerInterrupt = TIMER_INTERRUPT;

unsigned int n;
unsigned int score;
unsigned int lives;
int counter;
int inputCounter;
uint32_t lastFive[5];
bool Scored;
bool lighted;

unsigned int PERIPHBASE = 0;

void tie_periphbase_init(void){
    unsigned int base = 0;
    __asm("MRC p15, 4, %0, c15, c0, 0" : "=r" (base));
    PERIPHBASE = base;
    // For more info, you may see
    //  http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0068b/CIHEEIDJ.html
    // and
    //  http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0388i/CIHDHFBH.html
}

#define ISR_ID 29
#define ISR_TRIGGER_TO ALT_INT_TRIGGER_LEVEL

void isr_callback(uint32_t icciar, void* context){

    lighted = true;
    randomLight();
    if (lastFive[counter] != 25 && lastFive[counter] != 0) {
        --lives;
        if (lives <= 0) {
            gameOver();
        }
    }
    lastFive[counter] = *buttonW;
    ++counter;
    if (counter > 4) {
        updateSpeed();
        counter = 0;
    }
}
// <<<<

void initializeVariables() {
    n = 0;
    score = 0;
    lives = 5;
    counter = 0;
    inputCounter = 0;
    lastFive[5] = {25, 25, 25, 25, 25};
    Scored = false;
    lighted = false;
}

void gameOver() {
    *timerControl = 6;
    *buttonW = 15;
    updateDisplay(score);
}

void updateSpeed() {
    *timerLoad = *timerLoad * 0.80;
}

void randomLight() {
    unsigned int randNum = rand() % 4;
    // unsigned int current = *buttonW;
    switch (randNum) {
    case 0:
        randNum = 1;
        break;
    case 1:
    	randNum = 2;
        break;
    case 2:
    	randNum = 4;
        break;
    case 3:
    	randNum = 8;
        break;
    default:
        randomLight();
        printf("defaulted\n");
        break;
    }

    if (randNum == *buttonW) {
    	randomLight();
    } else {
    	*buttonW = randNum;
    }
}

uint32_t getButton() {
    uint32_t curr;
    while (*button != 0) {
        curr = *button;
    }
    return curr;
}

void checkButton() {
    if (getButton() == lastFive[inputCounter]) {
        ++score;
        updateDisplay(score);
    } else {
        --lives;
        if (lives <= 0) {
            gameOver();
        }
    }
    lastFive[inputCounter] = 0;
    ++inputCounter;
}

void buttonRelease() {
    while (*button != 0) {

    }
}

unsigned int dispNumSupp (unsigned int n, unsigned int order) {
    unsigned int output = 0;
    switch (order) {
    case 0:
        output = n % 10;
        break;
    case 1:
        output = ((n % 100) - (n % 10)) / 10;
        break;
    case 2:
        output = ((n % 1000) - (n % 100)) / 100;
        break;
    case 3:
        output = (n - (n % 1000)) / 1000;
        break;
    }
    return output;
}

uint32_t dispNum(unsigned int n) {
    uint32_t output = 63;
    switch (n) {
    case 0:
        output = 63;
        break;
    case 1:
        output = 6;
        break;
    case 2:
        output = 91;
        break;
    case 3:
        output = 79;
        break;
    case 4:
        output = 102;
        break;
    case 5:
        output = 109;
        break;
    case 6:
        output = 125;
        break;
    case 7:
        output = 7;
        break;
    case 8:
        output = 127;
        break;
    case 9:
        output = 111;
        break;
    }
    return output;
}

void updateDisplay (unsigned int n) {

    *segDispVal1 = dispNum (dispNumSupp (n, 0));
    *segDispVal2 = dispNum (dispNumSupp (n, 1));
    *segDispVal3 = dispNum (dispNumSupp (n, 2));
    *segDispVal4 = dispNum (dispNumSupp (n, 3));

}

int main(int argc, char** argv)
{

    // ------------------------------------------------------
    // STUDENTS NOTE: Do not touch on the following lines >>>
    alt_int_global_init();
    alt_int_cpu_init();
    alt_int_cpu_enable();
    alt_int_global_enable();
    tie_periphbase_init();
    tie_ui_connection_init();
    // <<<<
    // ------------------------------------------------------

    srand(time(NULL));

    // STUDENT NOTE: uncomment these, when you are ready to take interrupt in to use
    // >>>>
    alt_int_isr_register(ISR_ID, &isr_callback, 0);
    alt_int_dist_trigger_set(ISR_ID, ISR_TRIGGER_TO);
    alt_int_dist_target_set(ISR_ID, alt_int_util_cpu_current());
    alt_int_dist_enable(ISR_ID);
    // <<<<

    start:
    initializeVariables();
    updateDisplay(8888);
    *buttonW = 15;

    while (*button == 0) {

    }

    buttonRelease();

    *timerLoad = 125000000;	// approximately .5 to .6s
    *timerControl = 7;

    updateDisplay(0000);
    *buttonW = 0;

    // STUDENTS NOTE: build your code here
    for(;;) {

        if (checkButton() && !Scored && lighted) {
            Scored = true;
        }
    }
    return 0;
}

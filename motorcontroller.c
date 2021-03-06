/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Shem Cheng
* Student ID: 920768313
* Github ID: Jeshem
* Project: Assignment 3 - Start Your Engines
* 
* File: motorcontroller.c
*
* * Description: This file contains the method to set up wiringPi, wait for the button to be pressed, and run the motors
*
**************************************************************/

#include "motorcontroller.h"
#include <wiringPi.h>
#include <stdio.h>
#include <time.h>
#include <softPwm.h>


// Using Motor3 terminal
#define ENABLE 12 // pin 19 on motor shield
#define CONTROL1 13 // pin 21 on motor shield
#define CONTROL2 14 // pin 23 on motor shield
#define TRIGGER 7 // pin 11 on motor shield

#define LIGHT 24 // pin 33 on motor shield

#define HighSpeed 100
#define LowSpeed 15

void setupWiringPins() {
    wiringPiSetup();
    
    softPwmCreate(ENABLE, 100, 100);
    softPwmCreate(CONTROL1, 1, 100);
    softPwmCreate(CONTROL2, 1, 100);
    
    pinMode(TRIGGER, INPUT);
    pinMode(LIGHT, OUTPUT);
    
    digitalWrite(TRIGGER, LOW);
    
    delay(10);
}

void waitForButton() {
    while (digitalRead(TRIGGER) != 1){
    }
    printf("Button pressed");
}

void runMotors() {
    printf("\nrunning motors\n");
    
    //accelerate to full power in one direction
    digitalWrite(LIGHT, HIGH);
    digitalWrite(ENABLE, HIGH);
    forward();
    accelerate();
    
    
    //slow down over time to a stop
    brake();
    digitalWrite(LIGHT, LOW);
    

    //run in reverse direction
    digitalWrite(LIGHT, HIGH);
    reverse();
    accelerate();
    
    //slow down again over time to a stop
    brake();
    digitalWrite(LIGHT, LOW);
}

void forward(){
    softPwmWrite(CONTROL2, 0);
    softPwmWrite(CONTROL1, 100);
}

void reverse(){
    softPwmWrite(CONTROL1, 0);
    softPwmWrite(CONTROL2, 100);
}

void accelerate(){
    int power;
    for(power=LowSpeed; power<HighSpeed; power+=10){
        softPwmWrite(ENABLE, power);
        printf("Speeding up\n");
        fflush(stdout);
        delay(200);
    }
    delay(2000);
}

void brake(){
    int power;
    for (power=HighSpeed; power>LowSpeed; power-=10) {
        softPwmWrite(ENABLE, power);
        printf("Slowing down\n");
        fflush(stdout);
        delay(200);
    }
    delay(1000);
}

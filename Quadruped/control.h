#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class MOVEMENT{
  private:
    int bigmin = 140;          //minimum servo pulse
    int bigmax = 530;          //maximum servo pulse

    // Pin definition
    const int trigPin = 9;
    const int echoPin = 8;
    
    // Pre-defined constant
    float front =2; //step forward radius, its a semicircle equation
    float dist = front *2; //for step forward equation, CHANGE "FRONT"!
    float a= 10;    //unit in cm
    float b= 10;    //unit in cm
    float height= 10; //unit in cm
    float upper_tol =15;    //degree
    float lower_tol = 0;    //degree
    float speed_delay =50;    //unit in ms
    float turning_delay =50;  //unit in ms
    float speed =1;

    //Degree offset for legs                  Left lower| Left upper| Right upper| Right lower
    int M1_tol =10;   //right lower           M2          M3          M4           M1           |Front leg          
    int M2_tol =180;  //left lower            M2          M6          M5           M1           |Back leg
    int M3_tol =90;   //left upper
    int M4_tol =100;  //right upper
    int M5_tol =70;   //right back upper
    int M6_tol =110;  //left back upper

    float pi = 3.1415926535897932;
    Adafruit_PWMServoDriver leg = Adafruit_PWMServoDriver();
    // x, horizontal distance
    // y, vertical distance
    // h, hypothenus
        
    //#define bigservoMIN 140  //minimum pulse length out of 4096
    //#define bigservoMAX 530  //maximum pulse length out of 4096
  public:             
   void init();
   void forward();      //to move forward
   void left();         //to move left
   void right();        //to move right
   void STOP();         //to stop
   void reverse();      //to reverse
   void angle();        //to calibrate
   bool distance();     //to measure distance
   float formula_upfront(float);  //walking front for upper limb
   float formula_upback(float);   //walking back for upper limb
   float formula_dfront(float);   //walking front for lower limb
   float formula_dback(float);    //walking back for lower limb
  
};

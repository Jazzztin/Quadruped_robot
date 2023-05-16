#include "control.h"

//Adafruit_PWMServoDriver leg= Adafruit_PWMServoDriver();

// Pin declaration //
//int bigservoMIN = 140; //minimum pulse length out of 4096
//int bigservoMAX = 550;  //maximum pulse length out of 4096
#define fru 0     //front right uppper limb
#define frd 1     //front right down limb
#define flu 2     //front left up
#define fld 3     //front left down
#define bru 4     //back right up
#define brd 5    //back right down
#define blu 6    //back left up
#define bld 7    //back left down

// Class declaration //
MOVEMENT robot_move;

void setup() {
  //Serial.begin(115200);
  Serial3.begin(9600);
  robot_move.init();      //initialize PCA9685 PWM driver
  pinMode(2,INPUT);   //IR sensor left
  pinMode(3,INPUT);  //IR sensor right
}

void loop() {
  float x;
  bool distance = robot_move.distance();

  bool left =digitalRead(3);
  bool right = digitalRead(2);
  //Serial3.print(left);
  //Serial3.println(right);

  /*
  if(distance ==true)
  {
    if(right==true && left ==false)
    {
      robot_move.reverse();
      robot_move.left();
      Serial3.println("Mode: left");
    }

    else if(left==true && right ==false)
    {
      robot_move.reverse();
      robot_move.right();
      Serial3.println("Mode: right");
    }

    else
    {
      robot_move.forward();
      Serial3.println("Mode: front");
    }
  }

  else if(distance ==false)
  {
    robot_move.STOP();
    Serial3.println("Mode: stop");
  }
  */

//---------------------------------------------------------------------------------
// TESTING FUNCTION
//---------------------------------------------------------------------------------
  //robot_move.STOP();
  robot_move.forward();
  //robot_move.reverse();
  //robot_move.left();
  //robot_move.right();
  //delay(100);
  //robot_move.STOP();
  
}

#include "control.h"

// Front right //

#define fru 0     //f = front, b=back, r=right, l=left, u=upper, d=down
#define bru 1
#define flu 2
#define blu 3
#define frd 4
#define brd 5
#define fld 6
#define bld 7

//-----------------------------------------------------------//
// Claculation function
//-----------------------------------------------------------//
float MOVEMENT::formula_upfront(float x)
{
  float alpha, beta,theta,angle, pulse;
  float h,y;
  y = height - sqrt(pow(front,2)- pow(x-front,2));
  theta=(atan(x/y));
  h = y / cos(theta);
  alpha = acos((pow(h,2)+pow(a,2)- pow(b,2))/(2*a*h))*180/pi;
  angle=alpha+(theta*180/pi)-upper_tol;
  //Serial.print(angle);
  return angle;
}

float MOVEMENT::formula_upback(float x)
{
  float alpha, beta,theta,angle, pulse;
  float h,y;

  y = height;
  theta=(atan(x/y));
  h = y / cos(theta);
  alpha = acos((pow(h,2)+pow(a,2)- pow(b,2))/(2*a*h))*180/pi;
  angle=alpha+(theta*180/pi)-upper_tol; 
  //Serial.print(angle);
  return angle;
}

float MOVEMENT::formula_dfront(float x)
{
  float alpha, beta,theta,angle;
  float h,y;
  y = height - sqrt(pow(front,2)- pow(x-front,2));
  theta=(atan(x/y));
  h = y / cos(theta);
  beta = acos((pow(a,2)+pow(b,2)- pow(h,2))/(2*a*b))*180/pi;
  angle=beta+lower_tol;      //get the inner angle
  return angle;
}

float MOVEMENT::formula_dback(float x)
{
  float alpha, beta,theta,angle;
  float h,y;
  y = height;
  theta=(atan(x/y));
  h = y / cos(theta);
  beta = acos((pow(a,2)+pow(b,2)- pow(h,2))/(2*a*b))*180/pi;
  angle=beta+lower_tol;      //get the inner angle
  return angle;
}

//-----------------------------------------------------------//
// initialization
//-----------------------------------------------------------//
void MOVEMENT::init(){
  leg.begin(); 
  leg.setPWMFreq(60);  //frequency for PWM, defualt is set to 60Hz
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}


void MOVEMENT::STOP()
{
  float x,M1,M2,M3,M4,M5,M6,M11,M22,M33,M44,M55,M66;

  M1 = 10+formula_dfront(0); //right side lower
  M2 = 180-formula_dfront(0);
  M3 = 120+formula_upfront(0); //left side uppper
  M4 = 90-formula_upfront(0);

  M5 = 60-formula_upfront(0); //back right side
  M6 = 140+formula_upfront(0);  //back left upper

  M11 =map(M1, 0, 180, bigmin, bigmax);
  M22 =map(M2, 0, 180, bigmin, bigmax);
  M33 =map(M3, 0, 180, bigmin, bigmax);
  M44 =map(M4, 0, 180, bigmin, bigmax);

  M55 =map(M5, 0, 180, bigmin, bigmax);
  M66 =map(M6, 0, 180, bigmin, bigmax);

  leg.setPWM(fru, 0, M44);
  leg.setPWM(bru, 0, M55);
  leg.setPWM(flu, 0, M33);
  leg.setPWM(blu, 0, M66);
  leg.setPWM(frd, 0, M11);
  leg.setPWM(brd, 0, M11);
  leg.setPWM(fld, 0, M22);
  leg.setPWM(bld, 0, M22);
  //leg.setPWM(4, 0, pulse);
  delay(1000);
  
}

//-----------------------------------------------------------//
// Forward
//-----------------------------------------------------------//
void MOVEMENT::forward(){
  float x,M1,M2,M3,M4,M5,M6,M7,M8,M11,M22,M33,M44,M55,M66,M77,M88;

  //-------------------------------------------
  // move front right and back left legs first
  //place leg foward
  //--------------------------------------------
  float y=dist;
  for(x=0; x<=dist; x+=speed)
  {
  
  M1 = M1_tol+formula_dfront(y); //right side front lower
  M2 = M2_tol-formula_dback(x);  //left side front lower
  M3 = M3_tol+formula_upback(x); //left side front uppper
  M4 = M4_tol-formula_upfront(y); //right side front upper

  M5 = M5_tol-formula_upback(x); //right side back upper
  M6 = M6_tol+formula_upfront(y);  //left side back upper
  M7 = M2_tol-formula_dfront(y); //left side back lower
  M8 = M1_tol+formula_dback(x); //right side back lower

    M11 =map(M1, 0, 180, bigmin, bigmax);
    M22 =map(M2, 0, 180, bigmin, bigmax);
    M33 =map(M3, 0, 180, bigmin, bigmax);
    M44 =map(M4, 0, 180, bigmin, bigmax);

    M55 =map(M5, 0, 180, bigmin, bigmax);
    M66 =map(M6, 0, 180, bigmin, bigmax);
    M77 =map(M7, 0, 180, bigmin, bigmax);
    M88 =map(M8, 0, 180, bigmin, bigmax);    

    leg.setPWM(fru, 0, M44);
    leg.setPWM(bru, 0, M55);
    leg.setPWM(flu, 0, M33);
    leg.setPWM(blu, 0, M66);
    leg.setPWM(frd, 0, M11);
    leg.setPWM(brd, 0, M88);
    leg.setPWM(fld, 0, M22);
    leg.setPWM(bld, 0, M77);
    delay(speed_delay);
    //Serial.print(right_up_pulse);
    //Serial.print(", ");
    //Serial.println(x);
    y=y-1.5;

    if(y<=0)
    {
      y=0;
    }
  }

  y=dist;
  // place leg to backward
  for(x=0; x<=dist; x+=speed)
  {
    
  M1 = M1_tol+formula_dback(x); //right side front lower
  M2 = M2_tol-formula_dfront(y);  //left side front lower
  M3 = M3_tol+formula_upfront(y); //left side front uppper
  M4 = M4_tol-formula_upback(x); //right side front upper

  M5 = M5_tol-formula_upfront(y); //right side back upper
  M6 = M6_tol+formula_upback(x);  //left side back upper
  M7 = M2_tol-formula_dback(x); //left side back lower
  M8 = M1_tol+formula_dfront(y); //right side back lower

    M11 =map(M1, 0, 180, bigmin, bigmax);
    M22 =map(M2, 0, 180, bigmin, bigmax);
    M33 =map(M3, 0, 180, bigmin, bigmax);
    M44 =map(M4, 0, 180, bigmin, bigmax);

    M55 =map(M5, 0, 180, bigmin, bigmax);
    M66 =map(M6, 0, 180, bigmin, bigmax);
    M77 =map(M7, 0, 180, bigmin, bigmax);
    M88 =map(M8, 0, 180, bigmin, bigmax);    

    leg.setPWM(fru, 0, M44);
    leg.setPWM(bru, 0, M55);
    leg.setPWM(flu, 0, M33);
    leg.setPWM(blu, 0, M66);
    leg.setPWM(frd, 0, M11);
    leg.setPWM(brd, 0, M88);
    leg.setPWM(fld, 0, M22);
    leg.setPWM(bld, 0, M77);
    delay(speed_delay);

    y=y-1.5;

    if(y<=0)
    {
      y=0;
    }
  }
  
  //-------------------------------------------
  // move front left and back right legs first
  //place leg foward
  //--------------------------------------------

}

//-----------------------------------------------------------//
// Reverse
//-----------------------------------------------------------//

void MOVEMENT::reverse(){
  float x,M1,M2,M3,M4,M5,M6,M11,M22,M33,M44,M55,M66;
  //-------------------------------------------
  // move front right and back left legs first
  //place leg foward
  //--------------------------------------------

  for(x=0; x<=dist; x+=1.5)
  {

  M1 = M1_tol+formula_dfront(x); //right side lower
  M2 = M2_tol-formula_dfront(x);
  M3 = M3_tol+formula_upfront(x); //left side uppper
  M4 = M4_tol-formula_upfront(x);

  M5 = M5_tol-formula_upfront(x); //back right side
  M6 = M6_tol+formula_upfront(x);  //back left upper

    M11 =map(M1, 0, 180, bigmin, bigmax);
    M22 =map(M2, 0, 180, bigmin, bigmax);
    M33 =map(M3, 0, 180, bigmin, bigmax);
    M44 =map(M4, 0, 180, bigmin, bigmax);

    M55 =map(M5, 0, 180, bigmin, bigmax);
    M66 =map(M6, 0, 180, bigmin, bigmax);

    leg.setPWM(fru, 0, M44);
    //leg.setPWM(bru, 0, M55);
    //leg.setPWM(flu, 0, M33);
    leg.setPWM(blu, 0, M66);
    leg.setPWM(frd, 0, M11);
    //leg.setPWM(brd, 0, M11);
    //leg.setPWM(fld, 0, M22);
    leg.setPWM(bld, 0, M22);
    delay(speed_delay);
    //Serial.print(right_up_pulse);
    //Serial.print(", ");
    //Serial.println(x);
  }

  // place leg to backward
  for(x= dist; x>0; x-=0.5)
  {
    M1 = M1_tol+formula_dback(x); //right side lower
    M2 = M2_tol-formula_dback(x);
    M3 = M3_tol+formula_upback(x); //left side uppper
    M4 = M4_tol-formula_upback(x);

    M5 = M5_tol-formula_upback(x); //back right side
    M6 = M6_tol+formula_upback(x);  //back left upper

    M11 =map(M1, 0, 180, bigmin, bigmax);
    M22 =map(M2, 0, 180, bigmin, bigmax);
    M33 =map(M3, 0, 180, bigmin, bigmax);
    M44 =map(M4, 0, 180, bigmin, bigmax);

    M55 =map(M5, 0, 180, bigmin, bigmax);
    M66 =map(M6, 0, 180, bigmin, bigmax);

    leg.setPWM(fru, 0, M44);
    //leg.setPWM(bru, 0, M55);
    //leg.setPWM(flu, 0, M33);
    leg.setPWM(blu, 0, M66);
    leg.setPWM(frd, 0, M11);
    //leg.setPWM(brd, 0, M11);
    //leg.setPWM(fld, 0, M22);
    leg.setPWM(bld, 0, M22);
    delay(speed_delay);    
  }
  
  //-------------------------------------------
  // move front left and back right legs first
  //place leg foward
  //--------------------------------------------
    for(x=0; x<=dist; x+=1.5)
  {

    M1 = M1_tol+formula_dfront(x); //right side lower
    M2 = M2_tol-formula_dfront(x);
    M3 = M3_tol+formula_upfront(x); //left side uppper
    M4 = M4_tol-formula_upfront(x);

    M5 = M5_tol-formula_upfront(x); //back right side
    M6 = M6_tol+formula_upfront(x);  //back left upper

    M11 =map(M1, 0, 180, bigmin, bigmax);
    M22 =map(M2, 0, 180, bigmin, bigmax);
    M33 =map(M3, 0, 180, bigmin, bigmax);
    M44 =map(M4, 0, 180, bigmin, bigmax);

    M55 =map(M5, 0, 180, bigmin, bigmax);
    M66 =map(M6, 0, 180, bigmin, bigmax);

    //leg.setPWM(fru, 0, M44);
    leg.setPWM(bru, 0, M55);
    leg.setPWM(flu, 0, M33);
    //leg.setPWM(blu, 0, M66);
    //leg.setPWM(frd, 0, M11);
    leg.setPWM(brd, 0, M11);
    leg.setPWM(fld, 0, M22);
    //leg.setPWM(bld, 0, M22);
    delay(speed_delay);
    //Serial.print(right_up_pulse);
    //Serial.print(", ");
    //Serial.println(x);
  }

  // place leg to backward
  for(x= dist; x>0; x-=0.5)
  {
    M1 = M1_tol+formula_dback(x); //right side lower
    M2 = M2_tol-formula_dback(x);
    M3 = M3_tol+formula_upback(x); //left side uppper
    M4 = M4_tol-formula_upback(x);

    M5 = M5_tol-formula_upback(x); //back right side
    M6 = M6_tol+formula_upback(x);  //back left upper

    M11 =map(M1, 0, 180, bigmin, bigmax);
    M22 =map(M2, 0, 180, bigmin, bigmax);
    M33 =map(M3, 0, 180, bigmin, bigmax);
    M44 =map(M4, 0, 180, bigmin, bigmax);

    M55 =map(M5, 0, 180, bigmin, bigmax);
    M66 =map(M6, 0, 180, bigmin, bigmax);

    //leg.setPWM(fru, 0, M44);
    leg.setPWM(bru, 0, M55);
    leg.setPWM(flu, 0, M33);
    //leg.setPWM(blu, 0, M66);
    //leg.setPWM(frd, 0, M11);
    leg.setPWM(brd, 0, M11);
    leg.setPWM(fld, 0, M22);
    //leg.setPWM(bld, 0, M22);
    delay(speed_delay);   
  }

}

//-----------------------------------------------------------//
// Turn left
//-----------------------------------------------------------//
void MOVEMENT::left(){
  float x,M1,M2,M3,M4,M5,M6,M11,M22,M33,M44,M55,M66;
  //-------------------------------------------
  // move front right and back left legs first
  //place leg foward
  //--------------------------------------------

  for(x= dist; x>0; x-=0.5)
  {

    M1 = M1_tol+formula_dfront(x); //right side lower
    M2 = M2_tol-formula_dback(x); //left side lower
    M3 = M3_tol+formula_upback(x); //left side uppper
    M4 = M4_tol-formula_upfront(x); //right side upper

    M5 = M5_tol-formula_upfront(x); //back right upper
    M6 = M6_tol+formula_upback(x);  //back left upper

    M11 =map(M1, 0, 180, bigmin, bigmax);
    M22 =map(M2, 0, 180, bigmin, bigmax);
    M33 =map(M3, 0, 180, bigmin, bigmax);
    M44 =map(M4, 0, 180, bigmin, bigmax);

    M55 =map(M5, 0, 180, bigmin, bigmax);
    M66 =map(M6, 0, 180, bigmin, bigmax);

    leg.setPWM(fru, 0, M44);
    //leg.setPWM(bru, 0, M55);
    //leg.setPWM(flu, 0, M33);
    leg.setPWM(blu, 0, M66);
    leg.setPWM(frd, 0, M11);
    //leg.setPWM(brd, 0, M11);
    //leg.setPWM(fld, 0, M22);
    leg.setPWM(bld, 0, M22);
    delay(speed_delay);
    //Serial.print(right_up_pulse);
    //Serial.print(", ");
    //Serial.println(x);
  }

  // place leg to backward
  for(x=0; x<=dist; x+=0.5)
  {
    M1 = M1_tol+formula_dback(x); //right side lower
    M2 = M2_tol-formula_dfront(x);
    M3 = M3_tol+formula_upfront(x); //left side uppper
    M4 = M4_tol-formula_upback(x);

    M5 = M5_tol-formula_upback(x); //back right upper
    M6 = M6_tol+formula_upfront(x);  //back left upper

    M11 =map(M1, 0, 180, bigmin, bigmax);
    M22 =map(M2, 0, 180, bigmin, bigmax);
    M33 =map(M3, 0, 180, bigmin, bigmax);
    M44 =map(M4, 0, 180, bigmin, bigmax);

    M55 =map(M5, 0, 180, bigmin, bigmax);
    M66 =map(M6, 0, 180, bigmin, bigmax);

    leg.setPWM(fru, 0, M44);
    //leg.setPWM(bru, 0, M55);
    //leg.setPWM(flu, 0, M33);
    leg.setPWM(blu, 0, M66);
    leg.setPWM(frd, 0, M11);
    //leg.setPWM(brd, 0, M11);
    //leg.setPWM(fld, 0, M22);
    leg.setPWM(bld, 0, M22);
    delay(speed_delay);    
  }
  
  //-------------------------------------------
  // move front left and back right legs first
  //place leg foward
  //--------------------------------------------
  for(x= dist; x>0; x-=0.5)
  {

    M1 = M1_tol+formula_dfront(x); //right side lower
    M2 = M2_tol-formula_dback(x); //left side lower
    M3 = M3_tol+formula_upback(x); //left side uppper
    M4 = M4_tol-formula_upfront(x); //right side upper

    M5 = M5_tol-formula_upfront(x); //back right upper
    M6 = M6_tol+formula_upback(x);  //back left upper

    M11 =map(M1, 0, 180, bigmin, bigmax);
    M22 =map(M2, 0, 180, bigmin, bigmax);
    M33 =map(M3, 0, 180, bigmin, bigmax);
    M44 =map(M4, 0, 180, bigmin, bigmax);

    M55 =map(M5, 0, 180, bigmin, bigmax);
    M66 =map(M6, 0, 180, bigmin, bigmax);

    //leg.setPWM(fru, 0, M44);
    leg.setPWM(bru, 0, M55);
    leg.setPWM(flu, 0, M33);
    //leg.setPWM(blu, 0, M66);
    //leg.setPWM(frd, 0, M11);
    leg.setPWM(brd, 0, M11);
    leg.setPWM(fld, 0, M22);
    //leg.setPWM(bld, 0, M22);
    delay(speed_delay);
    //Serial.print(right_up_pulse);
    //Serial.print(", ");
    //Serial.println(x);
  }

  // place leg to backward
  for(x=0; x<=dist; x+=0.5)
  {
    M1 = M1_tol+formula_dback(x); //right side lower
    M2 = M2_tol-formula_dfront(x);
    M3 = M3_tol+formula_upfront(x); //left side uppper
    M4 = M4_tol-formula_upback(x);

    M5 = M5_tol-formula_upback(x); //back right upper
    M6 = M6_tol+formula_upfront(x);  //back left upper

    M11 =map(M1, 0, 180, bigmin, bigmax);
    M22 =map(M2, 0, 180, bigmin, bigmax);
    M33 =map(M3, 0, 180, bigmin, bigmax);
    M44 =map(M4, 0, 180, bigmin, bigmax);

    M55 =map(M5, 0, 180, bigmin, bigmax);
    M66 =map(M6, 0, 180, bigmin, bigmax);

    //leg.setPWM(fru, 0, M44);
    leg.setPWM(bru, 0, M55);
    leg.setPWM(flu, 0, M33);
    //leg.setPWM(blu, 0, M66);
    //leg.setPWM(frd, 0, M11);
    leg.setPWM(brd, 0, M11);
    leg.setPWM(fld, 0, M22);
    //leg.setPWM(bld, 0, M22);
    delay(speed_delay);   
  }

}

//-----------------------------------------------------------//
// Turn right
//-----------------------------------------------------------//
void MOVEMENT::right(){
 float x,M1,M2,M3,M4,M5,M6,M11,M22,M33,M44,M55,M66;
  //-------------------------------------------
  // move front right and back left legs first
  //place leg foward
  //--------------------------------------------

  for(x=0; x<=dist; x+=0.5)
  {

    M1 = M1_tol+formula_dfront(x); //right side lower
    M2 = M2_tol-formula_dback(x); //left side lower
    M3 = M3_tol+formula_upback(x); //left side uppper
    M4 = M4_tol-formula_upfront(x); //right side upper

    M5 = M5_tol-formula_upfront(x); //back right upper
    M6 = M6_tol+formula_upback(x);  //back left upper

    M11 =map(M1, 0, 180, bigmin, bigmax);
    M22 =map(M2, 0, 180, bigmin, bigmax);
    M33 =map(M3, 0, 180, bigmin, bigmax);
    M44 =map(M4, 0, 180, bigmin, bigmax);

    M55 =map(M5, 0, 180, bigmin, bigmax);
    M66 =map(M6, 0, 180, bigmin, bigmax);

    leg.setPWM(fru, 0, M44);
    //leg.setPWM(bru, 0, M55);
    //leg.setPWM(flu, 0, M33);
    leg.setPWM(blu, 0, M66);
    leg.setPWM(frd, 0, M11);
    //leg.setPWM(brd, 0, M11);
    //leg.setPWM(fld, 0, M22);
    leg.setPWM(bld, 0, M22);
    delay(speed_delay);
    //Serial.print(right_up_pulse);
    //Serial.print(", ");
    //Serial.println(x);
  }

  // place leg to backward
  for(x= dist; x>0; x-=0.5)
  {
    M1 = M1_tol+formula_dback(x); //right side lower
    M2 = M2_tol-formula_dfront(x);
    M3 = M3_tol+formula_upfront(x); //left side uppper
    M4 = M4_tol-formula_upback(x);

    M5 = M5_tol-formula_upback(x); //back right upper
    M6 = M6_tol+formula_upfront(x);  //back left upper

    M11 =map(M1, 0, 180, bigmin, bigmax);
    M22 =map(M2, 0, 180, bigmin, bigmax);
    M33 =map(M3, 0, 180, bigmin, bigmax);
    M44 =map(M4, 0, 180, bigmin, bigmax);

    M55 =map(M5, 0, 180, bigmin, bigmax);
    M66 =map(M6, 0, 180, bigmin, bigmax);

    leg.setPWM(fru, 0, M44);
    //leg.setPWM(bru, 0, M55);
    //leg.setPWM(flu, 0, M33);
    leg.setPWM(blu, 0, M66);
    leg.setPWM(frd, 0, M11);
    //leg.setPWM(brd, 0, M11);
    //leg.setPWM(fld, 0, M22);
    leg.setPWM(bld, 0, M22);
    delay(speed_delay);    
  }
  
  //-------------------------------------------
  // move front left and back right legs first
  //place leg foward
  //--------------------------------------------
  for(x=0; x<=dist; x+=0.5)
  {

    M1 = M1_tol+formula_dfront(x); //right side lower
    M2 = M2_tol-formula_dback(x); //left side lower
    M3 = M3_tol+formula_upback(x); //left side uppper
    M4 = M4_tol-formula_upfront(x); //right side upper

    M5 = M5_tol-formula_upfront(x); //back right upper
    M6 = M6_tol+formula_upback(x);  //back left upper

    M11 =map(M1, 0, 180, bigmin, bigmax);
    M22 =map(M2, 0, 180, bigmin, bigmax);
    M33 =map(M3, 0, 180, bigmin, bigmax);
    M44 =map(M4, 0, 180, bigmin, bigmax);

    M55 =map(M5, 0, 180, bigmin, bigmax);
    M66 =map(M6, 0, 180, bigmin, bigmax);

    //leg.setPWM(fru, 0, M44);
    leg.setPWM(bru, 0, M55);
    leg.setPWM(flu, 0, M33);
    //leg.setPWM(blu, 0, M66);
    //leg.setPWM(frd, 0, M11);
    leg.setPWM(brd, 0, M11);
    leg.setPWM(fld, 0, M22);
    //leg.setPWM(bld, 0, M22);
    delay(speed_delay);
    //Serial.print(right_up_pulse);
    //Serial.print(", ");
    //Serial.println(x);
  }

  // place leg to backward
  for(x= dist; x>0; x-=0.5)
  {
    M1 = M1_tol+formula_dback(x); //right side lower
    M2 = M2_tol-formula_dfront(x);
    M3 = M3_tol+formula_upfront(x); //left side uppper
    M4 = M4_tol-formula_upback(x);

    M5 = M5_tol-formula_upback(x); //back right upper
    M6 = M6_tol+formula_upfront(x);  //back left upper

    M11 =map(M1, 0, 180, bigmin, bigmax);
    M22 =map(M2, 0, 180, bigmin, bigmax);
    M33 =map(M3, 0, 180, bigmin, bigmax);
    M44 =map(M4, 0, 180, bigmin, bigmax);

    M55 =map(M5, 0, 180, bigmin, bigmax);
    M66 =map(M6, 0, 180, bigmin, bigmax);

    //leg.setPWM(fru, 0, M44);
    leg.setPWM(bru, 0, M55);
    leg.setPWM(flu, 0, M33);
    //leg.setPWM(blu, 0, M66);
    //leg.setPWM(frd, 0, M11);
    leg.setPWM(brd, 0, M11);
    leg.setPWM(fld, 0, M22);
    //leg.setPWM(bld, 0, M22);
    delay(speed_delay);   
  }  
}

bool MOVEMENT::distance(){

  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial3.print("Distance: ");
  Serial3.println(distance);
  //Serial3.print(", Mode: ");

  if(distance >20)
  {
    return true;
  }

  else
  {
    return false;
  }
}

  
#include <MyEspInclude.h>

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

}

void loop() 
{
  Display Display;
  myValues myValues;
  Motor m;
  Generator g;
  PID *pid;
  myPID myPID;
  MyTime t;

delay(150);

  float mDuty =0;
  float SpeedSet = 2000;
  float SpeedLive;
  float kp = 0.000280;
  float ki = 0.00000;
  float kd = 0;

  float gDuty =0.75;
  float CurrentSet = 0.200;
  float CurrentLive =0;
  float kp2 = 0.0004;
  float ki2 = 0;
  float kd2 = 0;

  int  actualtime;
  int  previoustime =0;
//m.setDuty(0.5);

  int Delay = 10;
  char ch;
  char id;
  char buffer[20] = {0};
  char k= 0;
  
  while(1)
  {

    
    delay(Delay);
    SpeedLive = m.readSpeed();
    CurrentLive = g.readCurrent();
    mDuty = myPID.updateMotor(kp,ki,kd,3500,SpeedLive,SpeedSet,Delay,mDuty);
    gDuty = myPID.updateGenerator(kp2,ki2,kd2,1.0f,CurrentLive, CurrentSet,Delay,gDuty);
    m.setDuty(mDuty);

    actualtime = millis();
    if((actualtime-previoustime)>250)
    {
    Serial.print('1');
    Serial.print(m.readSpeed(), 0);
    Serial.print('\0');
    Serial.print('2');
    Serial.print(g.readSpeed(), 0);
    Serial.print('\0');
    previoustime = millis();
    }
    
    if(t.Time > t.DisplayTime)
    {
      t.DisplayTime = t.Time + 1000;
      Display.Update(0,&myValues);
      myValues.update();
    }
  }
}



#include <MyEspInclude.h>

void setup() {
  // put your setup code here, to run once:

  Serial.begin(921600);

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
Serial.println("Started");
  float mDuty =0;
  float SpeedSet = 2000;
  float SpeedLive;
  float kp = 0.000280;
  float ki = 0.00000;
  float kd = 0;

  float gDuty =0.75;
  float VoltageSet = 6;
  float VoltageLive =0;
  float kp2 = 0.022;
  float ki2 = 0;
  float kd2 = 0;




  int Delay = 10;
  char ch;
  //pid = new PID(0.1, MAX_SPEED, MIN_SPEED, kp, ki, kd);
  while(1)
  {
    //m.calibrateSpeed();
    //g.calibrateCurrent(); 
    //mDuty = (pid->calculate(Speed, m.readSpeed())/MAX_SPEED)*100;
    
    delay(Delay);
    SpeedLive = m.readSpeed();
    VoltageLive = g.readVout();
    mDuty = myPID.updateMotor(kp,ki,kd,3500,SpeedLive,SpeedSet,Delay,mDuty);
    gDuty = myPID.updateGenerator(kp2,ki2,kd2,24,VoltageLive,VoltageSet,Delay,gDuty);
    m.setDuty(mDuty);
    g.setDuty(gDuty);
    Serial.print("\rDuty:");
    Serial.print(gDuty);
    Serial.print("\tVolt:");
    Serial.print(VoltageLive);


    

    ch = Serial.read();
    if(ch != -1)
    {
      Serial.print('\t');

      if(ch=='1')
      {
        kp2-=0.00001;
        Serial.print("KP2=");
        Serial.print(kp2,5);
      }
      else if(ch=='2')
      {
        kp2+=0.00001;
        Serial.print("KP2=");
        Serial.print(kp2,5);
      }
      else if(ch=='3')
      {
        VoltageSet+=1;
        Serial.print("VoltageSet=");
        Serial.print(VoltageSet,5);
      }
      else if(ch=='4')
      {
        VoltageSet-=1;
        Serial.print("VoltageSet=");
        Serial.print(VoltageSet,5);
      }
      else if(ch=='5')
      {
        kd+=0.1;
        Serial.print("KD=");
        Serial.print(kd);
      }
      else if(ch=='6')
      {
        kd+=0.1;
        Serial.print("KD=");
        Serial.print(kd);
      }
      else if(ch=='q')
      {
        kp2-=0.001;
        Serial.print("KP2=");
        Serial.print(kp2,5);
      }
      else if(ch=='w')
      {
        kp2+=0.001;
        Serial.print("KP2=");
        Serial.print(kp2,5);
      }
      else if(ch=='a')
      {
        kp2-=0.1;
        Serial.print("KP2=");
        Serial.print(kp2,5);
      }
      else if(ch=='s')
      {
        kp2+=0.1;
        Serial.print("KP2=");
        Serial.print(kp2,5);
      }
    
      
      //pid = new PID(0.1, MAX_SPEED, MIN_SPEED, kp, ki, kd);
    }


    if(t.Time > t.DisplayTime)
    {
      t.DisplayTime = t.Time + 1000;
      Display.Update(0,&myValues);
      myValues.update();
      //j.SerialSend(myValues);
      //j.SerialTest(myValues);
    }
  }
}

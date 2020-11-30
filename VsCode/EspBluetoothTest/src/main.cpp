#include <MyEspInclude.h>

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

}

void loop() 
{
  Display Display;
  Motor m;
  Generator g;
  PID *pid;

  float Duty;
  float Speed = 1500;

  int kp = 10;
  int ki = 0;
  int kd = 0;

  char ch;

  pid = new PID(0.1, MAX_SPEED, MIN_SPEED, kp, ki, kd);

  while(1)
  {
    //m.calibrateSpeed();
   //g.calibrateCurrent(); 
    
    delay(100);
    Duty = (pid->calculate(Speed, m.readSpeed())/MAX_SPEED)*100;
    m.setDuty(Duty);
    Serial.print('\r');
    Serial.print(Duty);
    Serial.print('\t');
    Serial.print(m.readSpeed());

    ch = Serial.read()
    if(ch != -1)
    {
      delete pid;
      Serial.print('\t');

      if(ch=='1')
      {
        kp-=0.1;
        Serial.print("KP=");
        Serial.print(kp);
      }
      else if(ch=='2')
      {
        kp+=0.1;
        Serial.print("KP=");
        Serial.print(kp);
      }

      pid = new PID(0.1, MAX_SPEED, MIN_SPEED, kp, ki, kd);
    if(t.Time > t.DisplayTime)
    {
      t.DisplayTime = t.Time + 1000;
      Display.Update(0,&myValues);
      myValues.update();
      //j.SerialSend(myValues);
      j.SerialTest(myValues);
    }

  }
}

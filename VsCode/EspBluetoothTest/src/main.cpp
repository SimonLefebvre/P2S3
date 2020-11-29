#include <MyEspInclude.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() 
{
  MyTime t;
  myValues myValues;
  myValues.update();
  Json j;
  Display Display;
  Motor m;
  Generator g;


  while(1)
  {
    t.update();

    myValues.update();
    if(t.Time > t.PidTime)
    {
      t.PidTime = t.Time + 10; 
      m.calibrateSpeed();
      g.calibrateCurrent();
    }


    if(t.Time > t.DisplayTime)
    {
      Display.Update(0,&myValues);
    }


    

  }
}

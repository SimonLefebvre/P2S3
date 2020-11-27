#include <MyEspInclude.h>

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  Motor m;
  Generator g;

}

void loop() 
{
  Display Display;
  Motor m;
  Generator g;

  while(1)
  {
    m.calibrateSpeed();
    g.calibrateCurrent();
    delay(10);

  }
}

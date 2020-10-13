#include <MyEspInclude.h>

BluetoothSerial BT;
void setup() {
  // put your setup code here, to run once:
  BT.begin("Myesp32");
  Serial.begin(9600);
  Serial.println("Bt started");

  SSD1306 display(0x3c,5,4);
  //display.init();
  //display.setFont(ArialMT_Plain_10);
  //display.setTextAlignment(TEXT_ALIGN_LEFT);
  //display.drawStringMaxWidth(0, 0, 128,
  //    "ma name a jeff" );
  Serial.println("Display started");
}

void loop() {
  // put your main code here, to run repeatedly:
  static bool test = false;
  if(BT.available())
  {
    Serial.println("Data is available");
    Serial.println(BT.read());
  }

  

  if(test ==false && BT.hasClient())
  {
    Serial.println("New Client has been connected");
    test = true;
  }
}
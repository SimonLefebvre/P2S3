#include <MyEspInclude.h>

BluetoothSerial BT;
SSD1306 display(0x3c,5,4);
void setup() {
  // put your setup code here, to run once:
  BT.begin("Myesp32");
  Serial.begin(9600);
  Serial.println("Bt started");
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  //display.setLogBuffer(5, 30);
  display.drawStringMaxWidth(0, 0, 128,
      "U Moteur 24V" );
  display.drawStringMaxWidth(0, 16, 128,
  "U Gene 80V" );
  display.display();
  display.drawStringMaxWidth(0, 32, 128,
  "T Moteur 20\248C" );
  display.display();
  display.drawStringMaxWidth(0, 48, 128,
  "T Gene 80\248C" );
  display.display();
  Serial.println("Display started");

  pinMode(0,OUTPUT);
  ledcAttachPin(16,0);//ledcAttachPin(gpio, channel)
  //ledcSetup(0,1000000,10);//ledcSetup(channel, frequency, resolution)
  //ledcWrite(0,0.25*1024);//ledcWrite(channel, dutycycle)
  Serial.println("PWM started");
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
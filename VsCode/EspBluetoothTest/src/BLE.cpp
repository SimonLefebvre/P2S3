#include <MyEspInclude.h>


//note, when tested with nRF connection, unbond was very important for uuid Changes

#define SERVICE_UUID         "00000004-0000-1000-8000-00805F9B34FB"
#define CHARACTERISTIC_UUID1 "00000001-0000-1000-8000-00805F9B34FB"
#define CHARACTERISTIC_UUID2 "00000002-0000-1000-8000-00805F9B34FB"
#define CHARACTERISTIC_UUID3 "00000003-0000-1000-8000-00805F9B34FB"

myBLE::myBLE()
{
  BLEDevice::init("SalePedal");
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);

  pCharacteristic_info = pService->createCharacteristic(
      CHARACTERISTIC_UUID1,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE |
      BLECharacteristic::PROPERTY_NOTIFY
                                       );
  pCharacteristic_ADC = pService->createCharacteristic(
      CHARACTERISTIC_UUID2,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE |
      BLECharacteristic::PROPERTY_NOTIFY
                                       );
  pCharacteristic_PWM = pService->createCharacteristic(
      CHARACTERISTIC_UUID3,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE |
      BLECharacteristic::PROPERTY_NOTIFY
                                       );  


  cJSON* JsonInfo = cJSON_CreateObject();
  cJSON* JsonADC = cJSON_CreateObject();
  cJSON* JsonPWM = cJSON_CreateObject();

  cJSON_AddNumberToObject(JsonInfo,"Mode Ecran",0);
  cJSON_AddNumberToObject(JsonInfo,"Status",0);

  cJSON_AddNumberToObject(JsonADC,"Temp Moteur",0);
  cJSON_AddNumberToObject(JsonADC,"Temp Generateur",0);
  cJSON_AddNumberToObject(JsonADC,"Vitesse Moteur",0);
  cJSON_AddNumberToObject(JsonADC,"Vitesse Generateur",0);
  cJSON_AddNumberToObject(JsonADC,"Tension Moteur",0);
  cJSON_AddNumberToObject(JsonADC,"Tension Generateur",0);

  cJSON_AddNumberToObject(JsonPWM,"Freq Moteur",0);
  cJSON_AddNumberToObject(JsonPWM,"Freq Generateur",0);
  cJSON_AddNumberToObject(JsonPWM,"PWM Moteur",0);
  cJSON_AddNumberToObject(JsonPWM,"PWM Generateur",0);

  pCharacteristic_info->setValue(cJSON_Print(JsonInfo));
  pCharacteristic_ADC->setValue(cJSON_Print(JsonADC));
  pCharacteristic_PWM->setValue(cJSON_Print(JsonPWM));
  Serial.println(cJSON_Print(JsonADC));
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->setScanResponse(true);
  pAdvertising->addServiceUUID(SERVICE_UUID);
  BLEDevice::startAdvertising();                        
}


void myBLE::Update(myValues* Values)
{
  cJSON* JsonInfo = cJSON_CreateObject();
  cJSON* JsonADC = cJSON_CreateObject();
  cJSON* JsonPWM = cJSON_CreateObject();

  cJSON_AddNumberToObject(JsonInfo,"Mode Ecran",Values->ModeEcran);
  cJSON_AddNumberToObject(JsonInfo,"Status",Values->Status);

  cJSON_AddNumberToObject(JsonADC,"Temp Moteur",Values->TempMoteur);
  cJSON_AddNumberToObject(JsonADC,"Temp Generateur",Values->TempGenerateur);
  cJSON_AddNumberToObject(JsonADC,"Vitesse Moteur",Values->TensionMoteur);
  cJSON_AddNumberToObject(JsonADC,"Vitesse Generateur",Values->VitesseGenerateur);
  cJSON_AddNumberToObject(JsonADC,"Tension Moteur",Values->TensionGenerateur);
  cJSON_AddNumberToObject(JsonADC,"Tension Generateur",Values->TensionGenerateur);

  cJSON_AddNumberToObject(JsonPWM,"Freq Moteur",Values->FreqMoteur);
  cJSON_AddNumberToObject(JsonPWM,"Freq Generateur",Values->FreqGenerateur);
  cJSON_AddNumberToObject(JsonPWM,"PWM Moteur",Values->PWMMoteur);
  cJSON_AddNumberToObject(JsonPWM,"PWM Generateur",Values->PWMGenerateur);
  pCharacteristic_info->setValue(cJSON_Print(JsonInfo));
  pCharacteristic_ADC->setValue(cJSON_Print(JsonADC));
  pCharacteristic_PWM->setValue(cJSON_Print(JsonPWM));
  

}

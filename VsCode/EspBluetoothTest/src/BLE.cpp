#include <MyEspInclude.h>

#define SERVICE_UUID        "00000003-0000-1000-8000-00805F9B34FB"
#define CHARACTERISTIC_UUID "00000001-0000-1000-8000-00805F9B34FB"

void BLE_init(void)
{
    
  
  BLEUUID BLEUUID1((uint16_t)0x0003);
  BLEUUID BLEUUID2((uint16_t)0x0001);
  BLEDevice::init("Simon'sESP");


  BLEServer *pServer = BLEDevice::createServer();
  //BLEService *pService = pServer->createService(BLEUUID1);
  BLEService *pService = pServer->createService(SERVICE_UUID);


  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         BLEUUID1,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       );


  BLECharacteristic *pCharacteristic2 = pService->createCharacteristic(
                                         BLEUUID2,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       );
  pCharacteristic->setValue("YO, mon nom c'est simon pi je test comment peux etre le long le string de data dun esp BLE protocol pour le characteristique dun appareil pour savoir si je peux me faire un protocol dans le protocol ou non. Merci");
  pCharacteristic2->setValue("POGO");
  pService->start();
   BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
   //pAdvertising->start();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
BLEDevice::startAdvertising();
/*
BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
  
  
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(BLEUUID1);
  pAdvertising->setScanResponse(true);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");

*/

/*

  BLEUUID BLEUUID((uint16_t) 0x0010);
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  //pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  BLEAdvertisementData advertisementData;
  advertisementData.setName("MyEsp32");
  advertisementData.setPartialServices(BLEUUID);
  pAdvertising->setAdvertisementData(advertisementData);
  BLEDevice::startAdvertising();
*/
}
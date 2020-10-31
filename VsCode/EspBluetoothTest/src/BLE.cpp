#include <MyEspInclude.h>


//note, when tested with nRF connection, unbond was very important for uuid Changes

#define SERVICE_UUID        "00000004-0000-1000-8000-00805F9B34FB"
#define CHARACTERISTIC_UUID1 "00000001-0000-1000-8000-00805F9B34FB"
#define CHARACTERISTIC_UUID2 "00000002-0000-1000-8000-00805F9B34FB"
#define CHARACTERISTIC_UUID3 "00000003-0000-1000-8000-00805F9B34FB"

void BLE_init1(void)
{
    
  BLEUUID BLEserviceid((uint16_t)0x0004);
  BLEUUID BLEserviceid2((uint16_t)0x0005);
  BLEUUID BLEUUID1((uint16_t)0x0005);
  BLEUUID BLEUUID2((uint16_t)0x0006);
  BLEUUID BLEUUID3((uint16_t)0x0007);
  BLEDevice::init("Simon'sESP1");

  BLEServer *pServer = BLEDevice::createServer();


  BLEService *pService = pServer->createService(BLEserviceid,15,15);
  BLEService *pService2 = pServer->createService(BLEserviceid2);
  



  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
      BLEUUID1,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE |
      BLECharacteristic::PROPERTY_NOTIFY
                                       );


  BLECharacteristic *pCharacteristic2 = pService->createCharacteristic(
      BLEUUID2,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE |
      BLECharacteristic::PROPERTY_NOTIFY
                                       );
  BLECharacteristic *pCharacteristic3 = pService2->createCharacteristic(
      BLEUUID3,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE |
      BLECharacteristic::PROPERTY_NOTIFY
  );
  pCharacteristic->setValue("YO, mon nom c'est simon pi je test comment peux etre le long le string de data dun esp BLE protocol pour le characteristique dun appareil pour savoir si je peux me faire un protocol dans le protocol ou non. Merci");
  pCharacteristic2->setValue("POGOes goes badies");
  pCharacteristic3->setValue("Piickles");
  pService->start();
  pService2->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
   pAdvertising->start();
/*

  pAdvertising->setScanResponse(true);
  // pAdvertising->addServiceUUID(BLEserviceid);
  // BLEDevice::startAdvertising();
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


void BLE_init2(void)
{
  BLEDevice::init("Simon'sESP2");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

BLECharacteristic *pCharacteristic1 = pService->createCharacteristic(
      CHARACTERISTIC_UUID1,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE |
      BLECharacteristic::PROPERTY_NOTIFY
                                       );

BLECharacteristic *pCharacteristic2 = pService->createCharacteristic(
      CHARACTERISTIC_UUID2,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE |
      BLECharacteristic::PROPERTY_NOTIFY
                                       );

BLECharacteristic *pCharacteristic3 = pService->createCharacteristic(
  CHARACTERISTIC_UUID3,
  BLECharacteristic::PROPERTY_READ |
  BLECharacteristic::PROPERTY_WRITE |
  BLECharacteristic::PROPERTY_NOTIFY
);

  pCharacteristic1->setValue("This will be my first attempt");
  pCharacteristic2->setValue("Should you call me mister");
  pCharacteristic3->setValue("or will it be master");
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->setScanResponse(true);
  pAdvertising->addServiceUUID(SERVICE_UUID);
  BLEDevice::startAdvertising();
}
#ifndef MYESPINCLUDE_H
#define MYESPINCLUDE_H

#include <Arduino.h>
#include "SSD1306.h"
#include "BluetoothSerial.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <cJSON.h>
#include <string.h>


class myValues
{
    public:
    myValues(void);
    myValues(int* info, int* ADC, int* PWM);
    int ModeEcran;
    int Status;
    int TempMoteur;
    int TempGenerateur;
    int VitesseMoteur;
    int VitesseGenerateur;
    int TensionMoteur;
    int TensionGenerateur;
    int FreqMoteur;
    int FreqGenerateur;
    int PWMMoteur;
    int PWMGenerateur;
    int Current;
};

class myBLE
{
    private:
    BLEServer *pServer;
    BLEService *pService;
    BLECharacteristic *pCharacteristic_info;
    BLECharacteristic *pCharacteristic_ADC;
    BLECharacteristic *pCharacteristic_PWM;
    public:
    myBLE();
    void Update(myValues* Values);
};

class Display
{
    private:
    int currentmode;
    public:
    Display(void);
    void Update(int mode, myValues* Values);
};
#endif
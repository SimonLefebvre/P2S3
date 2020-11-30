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


#include "Motor.h"
#include "Generator.h"


class myValues
{
    public:
    myValues(void);
    void update(void);

    int ModeEcran;
    int Status;
    float TempMoteur;
    float TempGenerateur;
    float VitesseMoteur;
    float VitesseGenerateur;
    float TensionMoteur;
    float TensionGenerateur;
    float Current;
    int FreqMoteur;
    int FreqGenerateur;
    int PWMMoteur;
    int PWMGenerateur;
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


class Json
{
    private:

    public:

    Json();
    void SerialCheck(void);
    void SerialSend(myValues myValues);
    void SerialTest(myValues myValues);
};

class MyTime
{
    private:
    public:
    uint32_t Time;
    uint32_t PidTime;
    uint32_t DisplayTime;
    MyTime(void);
    void update(void);


};
#endif
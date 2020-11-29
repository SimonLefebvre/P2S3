#include <MyEspInclude.h>


    Json::Json()
    {

    }

    void Json::SerialCheck(void)
    {
        String ReadStr = Serial.readString();
        if(ReadStr[0] == '{')
        {
            cJSON *root = cJSON_Parse(ReadStr.c_str());

            if(root != NULL)
            {
                if(cJSON_HasObjectItem(root,"JsonInfo"))
                {
                    cJSON *JsonInfo = cJSON_GetObjectItem(root,"JsonInfo");

                }

                if(cJSON_HasObjectItem(root,"JsonInfo"))
                {
                    cJSON *JsonADC = cJSON_GetObjectItem(root,"JsonADC");
                }

                if(cJSON_HasObjectItem(root,"JsonInfo"))
                {
                    cJSON *JsonPWM = cJSON_GetObjectItem(root,"JsonPWM");
                }
            }
        }

    }


    void Json::SerialSend(myValues myValues)
    {
        cJSON *root = cJSON_CreateObject();
        cJSON *JsonInfo = cJSON_CreateObject();
        cJSON *JsonADC = cJSON_CreateObject();
        cJSON *JsonPWM = cJSON_CreateObject();
        cJSON_AddItemToObject(root,"JsonInfo",JsonInfo);
        cJSON_AddItemToObject(root,"JsonInfo",JsonADC);
        cJSON_AddItemToObject(root,"JsonInfo",JsonPWM);

        cJSON_AddNumberToObject(JsonInfo,0,"Mode Ecran");
        cJSON_AddNumberToObject(JsonInfo,0,"Status");

        cJSON_AddNumberToObject(JsonADC,myValues.TempMoteur,"Temp Moteur");
        cJSON_AddNumberToObject(JsonADC,myValues.TempGenerateur,"Temp Generateur");
        cJSON_AddNumberToObject(JsonADC,myValues.VitesseMoteur,"Vitesse Moteur");
        cJSON_AddNumberToObject(JsonADC,myValues.VitesseGenerateur,"Vitesse Generateur");
        cJSON_AddNumberToObject(JsonADC,myValues.TensionMoteur,"Tension Moteur");
        cJSON_AddNumberToObject(JsonADC,myValues.TensionGenerateur,"Tension Generateur");
        cJSON_AddNumberToObject(JsonADC,myValues.Current,"Courant Generateur");

        cJSON_AddNumberToObject(JsonPWM,myValues.FreqMoteur,"Freq Moteur");
        cJSON_AddNumberToObject(JsonPWM,myValues.FreqGenerateur,"Freq Generateur");
        cJSON_AddNumberToObject(JsonPWM,myValues.PWMMoteur,"PWM Moteur");
        cJSON_AddNumberToObject(JsonPWM,myValues.PWMGenerateur,"PWM Generateur");

        Serial.print(cJSON_Print(root));
        cJSON_Delete(root);
    }
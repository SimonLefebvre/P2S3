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

        cJSON_AddNumberToObject(JsonInfo,"Mode Ecran",0);
        cJSON_AddNumberToObject(JsonInfo,"Status",0);

        cJSON_AddNumberToObject(JsonADC,"Temp Moteur",myValues.TempMoteur);
        cJSON_AddNumberToObject(JsonADC,"Temp Generateur",myValues.TempGenerateur);
        cJSON_AddNumberToObject(JsonADC,"Vitesse Moteur",myValues.VitesseMoteur);
        cJSON_AddNumberToObject(JsonADC,"Vitesse Generateur",myValues.VitesseGenerateur);
        cJSON_AddNumberToObject(JsonADC,"Tension Moteur",myValues.TensionMoteur);
        cJSON_AddNumberToObject(JsonADC,"Tension Generateur",myValues.TensionGenerateur);
        cJSON_AddNumberToObject(JsonADC,"Courant Generateur",myValues.Current);

        cJSON_AddNumberToObject(JsonPWM,"Freq Moteur",myValues.FreqMoteur);
        cJSON_AddNumberToObject(JsonPWM,"Freq Generateur",myValues.FreqGenerateur);
        cJSON_AddNumberToObject(JsonPWM,"PWM Moteur",myValues.PWMMoteur);
        cJSON_AddNumberToObject(JsonPWM,"PWM Generateur",myValues.PWMGenerateur);

        cJSON_AddItemToObject(root,"JsonInfo",JsonInfo);
        cJSON_AddItemToObject(root,"JsonADC",JsonADC);
        cJSON_AddItemToObject(root,"JsonPWM",JsonPWM);
        Serial.print(cJSON_Print(root));
        Serial.print('\0');
        cJSON_Delete(root);
    }

    void Json::SerialTest(myValues myValues)
    {
        cJSON *JsonADC = cJSON_CreateObject();
        cJSON_AddNumberToObject(JsonADC,"Temp Moteur",myValues.TempMoteur);
        cJSON_AddNumberToObject(JsonADC,"Temp Generateur",myValues.TempGenerateur);
        cJSON_AddNumberToObject(JsonADC,"Vitesse Moteur",myValues.VitesseMoteur);
        cJSON_AddNumberToObject(JsonADC,"Vitesse Generateur",myValues.VitesseGenerateur);
        cJSON_AddNumberToObject(JsonADC,"Tension Moteur",myValues.TensionMoteur);
        cJSON_AddNumberToObject(JsonADC,"Tension Generateur",myValues.TensionGenerateur);
        cJSON_AddNumberToObject(JsonADC,"Courant Generateur",myValues.Current);
        
        Serial.print(cJSON_Print(JsonADC));
        Serial.print('\0');
        cJSON_Delete(JsonADC);

    }
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


    void Json::SerialSend(void)
    {

        
    }
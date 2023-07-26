#ifndef FILE_HAND
#define FILE_HAND

void readDomeConfig(){
    const size_t capacity = JSON_OBJECT_SIZE(100);
    DynamicJsonDocument doc(capacity);
    File file = SPIFFS.open("/domeconfig.txt", FILE_READ);
    if (!file) {
        Serial.println("Reading Dome config error");
        return;
    }
    DeserializationError error = deserializeJson(doc, file);

    if(error){
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
    } else {
        setting.dome.pinStart = doc["pinstart"];
        setting.dome.pinHalt = doc["pinhalt"];
        setting.dome.pinOpen = doc["pinopen"];
        setting.dome.pinClose = doc["pinclose"];
        setting.dome.movingTimeOut = doc["tout"];
        setting.dome.enAutoClose = doc["enautoclose"];
        setting.dome.autoCloseTimeOut = doc["autoclose"];
    }
    Serial.println(setting.dome.pinStart);
    Serial.println(setting.dome.pinHalt);
    Serial.println(setting.dome.pinOpen);
    Serial.println(setting.dome.pinClose);
    file.close();
}


void saveDomeConfig(){
    const size_t capacity = JSON_OBJECT_SIZE(120);
    String datasetup;
    DynamicJsonDocument doc(capacity);
    doc["pinstart"] = setting.dome.pinStart;
    doc["pinhalt"] = setting.dome.pinHalt;
    doc["pinopen"] = setting.dome.pinOpen;
    doc["pinclose"] = setting.dome.pinClose;    
    doc["tout"] = setting.dome.movingTimeOut;
    doc["enautoclose"] = setting.dome.enAutoClose;
    doc["autoclose"] = setting.dome.autoCloseTimeOut;
    serializeJson(doc, datasetup);
    File file = SPIFFS.open("/domeconfig.txt", FILE_WRITE);
    file.print(datasetup);
    file.close();
}


void fileLoop(){

    if(FileHandler.saveDomeSetting){
        FileHandler.saveDomeSetting = false;
        saveDomeConfig();
        Serial.println("richiesta salvataggio dati dome");
    }

    if(FileHandler.saveSwitchSetting){
        FileHandler.saveSwitchSetting = false;
        Serial.println("richiesta salvataggio dati switch");
    }
}
#endif
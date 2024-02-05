#ifndef FILE_HAND
#define FILE_HAND

void readDomeConfig(){
    JsonDocument doc;
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
    file.close();
}


void saveDomeConfig(){
    String datasetup;
    JsonDocument doc;
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

void readCoverCalibConfig(){
    JsonDocument doc;
    File file = SPIFFS.open("/ccalibconfig.txt", FILE_READ);
    if (!file) {
        Serial.println("Reading Cover Calibrator config error");
        return;
    }
    DeserializationError error = deserializeJson(doc, file);

    if(error){
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
    } else {
        setting.coverCalibration.pin = doc["pin"];
    }
    file.close();
}

void saveCoverCalibConfig(){
    String datasetup;
    JsonDocument doc;
    doc["pin"] = setting.coverCalibration.pin;
    serializeJson(doc, datasetup);
    File file = SPIFFS.open("/ccalibconfig.txt", FILE_WRITE);
    file.print(datasetup);
    file.close();
}

void readSwitchConfig(){
    JsonDocument doc;
    File file = SPIFFS.open("/switchconfig.txt", FILE_READ);
    if (!file) {
        Serial.println(F("Reading Switch config error"));
        return;
    }
    DeserializationError error = deserializeJson(doc, file);

    if(error){
        Serial.print(F("deserialize switch setting failed: "));
        Serial.println(error.c_str());
    } 

    int i=0;
    int type = 0;
    int pin = 0;
    for (JsonObject elem : doc.as<JsonArray>()) {
        type = elem["type"].as<unsigned int>();
        pin = elem["pin"].as<unsigned int>();
        if(type != 0 && (pin != 0 || pin != 99)){
            Switch[i].Name = elem["name"].as<String>();
            Switch[i].Description = elem["desc"].as<String>();
            Switch[i].type = type;
            Switch[i].CanSet = false;
            Switch[i].analog = false;
            Switch[i].pin = pin;
            Switch[i].minValue = 0;
            Switch[i].maxValue = 1;
            switch(type){
                case 1: //Digital Output
                        Switch[i].CanSet = true;
                        Switch[i].pin = pin;

                        break;
                case 2: //Digital Input
                        Switch[i].pin = pin;
                        break;
                case 3: //PWM Output
                        Switch[i].CanSet = true;
                        Switch[i].analog = true;
                        Switch[i].pin = pin;
                        break;
                case 4: //Analog Input
                        Switch[i].CanSet = false;
                        Switch[i].analog = true;
                        Switch[i].pin = pin;
                        break;
                
                default:
                    break;
            }
        } else {
            setting.switches.maxSwitch = i;
            break;
        }
        i++;
    }
    doc.clear();
    file.close();
}

void saveSwitchConfig(){
    int i = 0;
    File file = SPIFFS.open("/switchconfig.txt", FILE_WRITE);
    file.print("[");
    for(i=0;i<_MAX_SWITCH_ID_;i++){
        file.print("{\"name\":\"");
        file.print(Switch[i].Name.substring(0,32));
        file.print("\",\"desc\":\"");
        file.print(Switch[i].Description.substring(0,32));
        file.print("\",\"type\":");
        file.print(Switch[i].type);
        file.print(",\"pin\":");
        file.print(Switch[i].pin);
        file.print("}");
        if(i != _MAX_SWITCH_ID_ - 1){
            file.print(",");
        }
    }
    file.print("]");
    file.close();
}

void fileLoop(){

    if(FileHandler.saveDomeSetting){
        FileHandler.saveDomeSetting = false;
        saveDomeConfig();
        Serial.println("richiesta salvataggio dati dome");
        if(FileHandler.restartNeeded){ESP.restart();}
    }

    if(FileHandler.saveSwitchSetting){
        FileHandler.saveSwitchSetting = false;
        saveSwitchConfig();
        Serial.println("richiesta salvataggio dati switch");
        if(FileHandler.restartNeeded){ESP.restart();}
    }
    
    if(FileHandler.saveCoverCalibratorSetting){
        FileHandler.saveCoverCalibratorSetting = false;
        saveCoverCalibConfig();
        Serial.println("richiesta salvataggio CoverCalibrator");
        if(FileHandler.restartNeeded){ESP.restart();}
    }
}
#endif
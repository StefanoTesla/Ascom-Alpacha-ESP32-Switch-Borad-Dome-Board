#ifndef BROWSER_WEB
#define BROWSER_WEB

void notFound(AsyncWebServerRequest *request) {
  request->send(400, "text/plain", "Not found");
  Serial.println("400");
  Serial.println(request->url());
}


void browserServer(){

    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send(SPIFFS, "/index.html", "text/html");
    });

    server.on("/setup", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send(SPIFFS, "/setup.html", "text/html");
    });

    server.on("/setup.txt", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send(SPIFFS, "/setup.txt", "text/plain");
    });

    server.on("/domecmd",               HTTP_PUT, [](AsyncWebServerRequest *request) {
        if (request->hasParam("cmd")){
            int cmd;
            cmd = request->getParam("cmd")->value().toInt();
            switch (cmd) {
                case 1:
                    if(Dome.ShutterState != ShOpen){
                    Dome.ShutterCommand = CmdOpen;
                    request->send(200, "application/json", "{\"error\":0}");
                    } else { request->send(200, "application/json", "{\"error\":1}"); }
                    break;

                case 2:
                    if(Dome.ShutterState != ShClose){
                        Dome.ShutterCommand = CmdClose;
                        request->send(200, "application/json", "{\"error\":0}");
                    } else { request->send(200, "application/json", "{\"error\":2}"); }
                    break;

                case 3:
                    Dome.ShutterCommand = CmdHalt;
                    Dome.Cycle = 100;
                    request->send(200, "application/json", "{\"error\":0}");
                    break;
                default:
                    request->send(200, "application/json", "{\"error\":3}");
                    break;
            }
        } else {
            request->send(200, "application/json", "{\"error\":3}");
        }
    });

    server.on("/switchcmd",             HTTP_PUT, [](AsyncWebServerRequest *request) {
        int id = -1;
        int value = -1;
        if (request->hasParam("id")){
             id = request->getParam("id")->value().toInt();
        } else { 
            request->send(200, "application/json", "{\"error\" : \"Missing ID\"}");
            return;
        }
        if (request->hasParam("value")){ 
            value = request->getParam("value")->value().toInt();
        } else {
            request->send(200, "application/json", "{\"error\" : \"Missing Value\"}");
            return;
        }
        if (id >= setting.switches.maxSwitch){ 
            request->send(200, "application/json", "{\"error\" : \"ID Out of Range\"}"); return;
        }
        if (!Switch[id].CanSet){ 
            request->send(200, "application/json", "{\"error\" : \"Switch cannot be setted\"}"); 
            return;
        }
        if (value < Switch[id].minValue || value > Switch[id].maxValue){
            request->send(200, "application/json", "{\"error\" : \"Value outside limits\"}");
            return;
        }

        switch (Switch[id].type)
        {
        case 1:
            value == 1 ? digitalWrite(Switch[id].pin, HIGH) : digitalWrite(Switch[id].pin, LOW);
            break;
        
        case 3: 
            ledcWrite(Switch[id].pwmChannel,value);
            Serial.println(value);
            break;
        default:
            break;  
        }
        request->send(200, "text/html", "{\"done\" : 1}");
    
    });

    server.on("/status",                HTTP_GET, [](AsyncWebServerRequest *request) {
        int i;
        AsyncResponseStream *response = request->beginResponseStream("application/json");

        response->printf("{\"dome\":{ \"actualState\":");
            response->print(Dome.ShutterState);
            response->print(",\"lastCommand\":");
            response->print(Dome.LastDomeCommand);
        response->print("},");

        response->print("\"switches\": [");
        for (i=0;i<setting.switches.maxSwitch;i++){
            response->print("{\"id\":");
            response->print(i);
            response->print(",\"name\":\"");
            response->print(Switch[i].Name);
            response->print("\",\"description\":\"");
            response->print(Switch[i].Description);
            response->print("\",\"canBeHandle\":");
            response->print(Switch[i].CanSet);
            response->print(",\"type\":");
            response->print(Switch[i].analog);
            response->print(",\"actualValue\":");
            switch (Switch[i].type)
            {
                case 1:
                case 2:
                    response->print(digitalRead(Switch[i].pin));
                    break;
                case 3:
                    response->print(ledcRead(Switch[i].pwmChannel));
                    break;
                case 4:
                    response->print(analogRead(Switch[i].pin));
                    break;
                default:
                    break;
            }
            response->print(",\"min\":");
            response->print(Switch[i].minValue);
            response->print(",\"max\":");
            response->print(Switch[i].maxValue);
            response->print(",\"step\":");
            response->print(Switch[i].Step);
            response->print("}");
            if(i != setting.switches.maxSwitch - 1 ){
                response->printf(",");
            }
        }
        response->printf("],\"free\":");
        response->print(ESP.getFreeHeap());
        response->print("}");
        request->send(response);
    });

    AsyncCallbackJsonWebHandler *domecfg = new AsyncCallbackJsonWebHandler("/domeconfig", [](AsyncWebServerRequest * request, JsonVariant & json) {
        const size_t capacity = JSON_OBJECT_SIZE(200);
        DynamicJsonDocument doc(capacity);
        doc = json.as<JsonObject>();
        setting.dome.pinStart = doc["pinstart"];
        setting.dome.pinHalt = doc["pinhalt"];
        setting.dome.pinOpen = doc["pinopen"];
        setting.dome.pinClose = doc["pinclose"];
        setting.dome.movingTimeOut = doc["tout"];
        setting.dome.enAutoClose = doc["enautoclose"];
        setting.dome.autoCloseTimeOut = doc["autoclose"];
        FileHandler.saveDomeSetting = true;
        request->send(200, "application/json", "{\"accept\": \"ok\"}");
    });
    server.addHandler(domecfg);


    AsyncCallbackJsonWebHandler *switchConfig = new AsyncCallbackJsonWebHandler("/switchconfig", [](AsyncWebServerRequest * request, JsonVariant & json) {
        const size_t capacity = JSON_OBJECT_SIZE(5000);
        DynamicJsonDocument doc(capacity);
        int i=0;
        int x=0;
        int type = 0;
        int pin = 0;
        bool err = false;
        bool reboot = false;

        for (JsonObject elem : json.as<JsonArray>()) {
            type = elem["type"].as<unsigned int>();
            pin = elem["pin"].as<unsigned int>();
            if(type != 0 && pin != 0 && pin !=99){
                switch(type){

                    case 1: //Digital Output
                            if(Switch[i].CanSet != true){ reboot = true; }
                            if(Switch[i].pin != pin){ reboot = true; }
                            Switch[i].CanSet = true;
                            Switch[i].analog = false;
                            Switch[i].pin = pin;
                            Switch[i].minValue = 0;
                            Switch[i].maxValue = 1;
                            break;

                    case 2: //Digital Input
                            if(Switch[i].CanSet != false){ reboot = true; }
                            if(Switch[i].pin != pin){ reboot = true; }
                            Switch[i].CanSet = false;
                            Switch[i].analog = false;
                            Switch[i].pin = pin;
                            Switch[i].minValue = 0;
                            Switch[i].maxValue = 1;
                            break;
                    case 3: //PWM Output
                            if(Switch[i].CanSet != true){ reboot = true; }
                            if(Switch[i].pin != pin){ reboot = true; }
                            Switch[i].CanSet = true;
                            Switch[i].analog = true;
                            Switch[i].pin = pin;
                            Switch[i].minValue = elem["min"].as<unsigned int>();
                            Switch[i].maxValue = elem["max"].as<unsigned int>();
                            break;

                    case 4: //Analog Input
                            if(Switch[i].CanSet != false){ reboot = true; }
                            if(Switch[i].pin != pin){ reboot = true; }
                            Switch[i].CanSet = false;
                            Switch[i].analog = true;
                            Switch[i].pin = pin;
                            Switch[i].minValue = elem["min"].as<unsigned int>();
                            Switch[i].maxValue = elem["max"].as<unsigned int>();
                            break;
                    
                    default:
                        Serial.println("/switchconfig wrong pin type");
                        err = true;
                        break;
                }
                Switch[i].type = type;
                Switch[i].Name = elem["name"].as<String>();
                Switch[i].Description = elem["desc"].as<String>();
            } else {
                Serial.print("male");
                err = true;
                return;
            }
            i++;
        }
        if(err){
            request->send(200, "application/json", "{\"error\": \"some type or input are wrong\"}");
            return;
        } 
        for(x=i;x<_MAX_SWITCH_ID_;x++){
            Switch[x].Name = "";
            Switch[x].Description = "";
            Switch[x].pin = 99;
            Switch[x].type = 0;
            Switch[x].minValue = 0;
            Switch[x].maxValue = 1;
        }
        if (reboot){
            request->send(200, "application/json", "{\"reboot\": \"1\"}");
            FileHandler.saveSwitchSetting = true;
        } else {
            request->send(200, "application/json", "{\"accept\": \"ok\"}");
            FileHandler.saveSwitchSetting = true;
        }

    });
    server.addHandler(switchConfig);

    server.on("/config",                HTTP_GET, [](AsyncWebServerRequest *request) {
        int i;
        AsyncResponseStream *response = request->beginResponseStream("application/json");
        response->print("{\"dome\":{ \"pinstart\":");
        response->print(setting.dome.pinStart);
        response->print(",\"pinhalt\":");
        response->print(setting.dome.pinHalt);
        response->print(",\"pinopen\":");
        response->print(setting.dome.pinOpen);
        response->print(",\"pinclose\":");
        response->print(setting.dome.pinClose);
        response->print(",\"tout\":");
        response->print(setting.dome.movingTimeOut);
        response->print(",\"enautoclose\":");
        setting.dome.enAutoClose ? response->print("true") : response->print("false");
        response->print(",\"autoclose\":");
        response->print(setting.dome.autoCloseTimeOut);
        response->print("},");
        response->print("\"switches\":[");
        for(i=0;i<setting.switches.maxSwitch;i++){
            response->print("{\"name\":\"");
            response->print(Switch[i].Name);
            response->print("\",\"desc\":\"");
            response->print(Switch[i].Description);
            response->print("\",\"type\":");
            response->print(Switch[i].type);
            response->print(",\"pin\":");
            response->print(Switch[i].pin);
            response->print(",\"min\":");
            response->print(Switch[i].minValue);
            response->print(",\"max\":");
            response->print(Switch[i].maxValue);
            response->print("}");
            if (i != setting.switches.maxSwitch - 1 ){
                response->print(",");
            }
        }    
        response->print("]}");
        request->send(response);
    });

    server.serveStatic("/domeconfig.txt", SPIFFS, "/domeconfig.txt");
    server.serveStatic("/switchconfig.txt", SPIFFS, "/switchconfig.txt");
    server.serveStatic("/favicon.ico", SPIFFS, "/favicon.ico").setCacheControl("max-age=31536000");
    server.serveStatic("/assets/", SPIFFS, "/assets/").setCacheControl("max-age=31536000");

    server.onNotFound(notFound);
}

#endif
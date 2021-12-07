#ifndef SWITCH_HAND
#define SWITCH_HAND

void switchsetup() {
  int i=0;

  
  Switch[0].Name = "Switch 1";
  Switch[0].Description = "Switch 1";
  Switch[0].pin = 2;
  Switch[0].minValue = 0;
  Switch[0].maxValue = 1;
  Switch[0].CanSet = true;
  Switch[0].Step = 1;
  Switch[0].analog = false;

  Switch[1].Name = "Switch 2";
  Switch[1].Description = "Switch 2";
  Switch[1].pin = 4;
  Switch[1].minValue = 0;
  Switch[1].maxValue = 1;
  Switch[1].CanSet = true;
  Switch[1].Step = 1;
  Switch[1].analog = false;

  Switch[2].Name = "Switch 3";
  Switch[2].Description = "Switch 3";
  Switch[2].pin = 16;
  Switch[2].minValue = 0;
  Switch[2].maxValue = 1;
  Switch[2].CanSet = true;
  Switch[2].Step = 1;
  Switch[2].analog = false;

  Switch[3].Name = "Switch 4";
  Switch[3].Description = "Switch 4";
  Switch[3].pin = 17;
  Switch[3].minValue = 0;
  Switch[3].maxValue = 1;
  Switch[3].CanSet = true;
  Switch[3].Step = 1;
  Switch[3].analog = false;

  Switch[4].Name = "Switch 5";
  Switch[4].Description = "Switch 5";
  Switch[4].pin = 18;
  Switch[4].minValue = 0;
  Switch[4].maxValue = 1;
  Switch[4].CanSet = true;
  Switch[4].Step = 1;
  Switch[4].analog = false;

  Switch[5].Name = "Switch 6";
  Switch[5].Description = "Switch 6";
  Switch[5].pin = 18;
  Switch[5].minValue = 0;
  Switch[5].maxValue = 1;
  Switch[5].CanSet = true;
  Switch[5].Step = 1;
  Switch[5].analog = false;

  for (i=0;i<_MAX_SWTICH_ID_;i++){
    if (Switch[i].CanSet == true){
      if (Switch[i].analog == false){
        pinMode(Switch[i].pin, OUTPUT);
      }
    } else {
      pinMode(Switch[i].pin, INPUT);
    }
  }
}

void SwtSWName(AsyncWebServerRequest *request) {
  const size_t capacity = JSON_OBJECT_SIZE(1024);
  String JSwitchAnsw;
  DynamicJsonDocument doc(capacity);
  JsonArray Switchjs = doc.createNestedArray("Switch");

  JsonObject Switchjs_0 = Switchjs.createNestedObject();
  Switchjs_0["name"] = Switch[0].Name;
  Switchjs_0["description"] = Switch[0].Description;

  JsonObject Switchjs_1 = Switchjs.createNestedObject();
  Switchjs_1["name"] = Switch[1].Name;
  Switchjs_1["description"] = Switch[1].Description;

  JsonObject Switchjs_2 = Switchjs.createNestedObject();
  Switchjs_2["name"] = Switch[2].Name;
  Switchjs_2["description"] = Switch[2].Description;

  JsonObject Switchjs_3 = Switchjs.createNestedObject();
  Switchjs_3["name"] = Switch[3].Name;
  Switchjs_3["description"] = Switch[3].Description;

  JsonObject Switchjs_4 = Switchjs.createNestedObject();
  Switchjs_4["name"] = Switch[4].Name;
  Switchjs_4["description"] = Switch[4].Description;

  JsonObject Switchjs_5 = Switchjs.createNestedObject();
  Switchjs_5["name"] = Switch[5].Name;
  Switchjs_5["description"] = Switch[5].Description;

  JSwitchAnsw="";
  serializeJson(doc, JSwitchAnsw);
  request->send(200, "application/json", JSwitchAnsw);
}


void SwtSWState(AsyncWebServerRequest *request) {

;
 
}


#endif

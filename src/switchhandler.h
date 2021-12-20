#ifndef SWITCH_HAND
#define SWITCH_HAND




void switchsetup() {
  int i=0;

  
/* Switch Setup */

/* Default Switch setting

  pin -> Choose the GPIO where switch is plugged on!
  minValue -> Min Value the switch can have (default is 0 and is set to 0 if Switch is Output)
  maxValue -> Max Value the switch can have (default is 1 and is forced to 1 if Switch is Output)
  CanSet -> Default: true, if true is output or pwm, if false is an input
  Step -> Choose the step for change the value of Switch (default 1 and forced to 1 if is output)
  analog -> Default is false, if true this switch is PWM
  pwmChannel -> Default -1, the value can be 0..15 according to esp32 pwm channels

*/

// Input Example
  Switch[0].pin = 5;
  Switch[0].CanSet = false;

// Output Example
  Switch[1].pin = 4;

  Switch[2].pin = 16;

  Switch[3].pin = 17;

  Switch[4].pin = 18;

// PWM Output Example
  Switch[5].pin = 2;
  Switch[5].analog = true;


/* automatic setup for Switch */

  for (i=0;i<_MAX_SWTICH_ID_;i++){
    if (Switch[i].CanSet == false){
      pinMode(Switch[i].pin, INPUT);
    } else {
      if (Switch[i].analog == false){
        pinMode(Switch[i].pin, OUTPUT);
        Switch[i].Step = 1;
        Switch[i].maxValue = 1;
      }  else {
          ledcSetup(pwmchannles, 5000, 10);
          ledcAttachPin(Switch[i].pin, pwmchannles);
          Switch[i].pwmChannel = pwmchannles;
          Switch[i].minValue = 0;
          Switch[i].maxValue = 1024;
          pwmchannles++;
      }  
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
  Switchjs_0["min"] = Switch[0].minValue;
  Switchjs_0["max"] = Switch[0].maxValue;

  JsonObject Switchjs_1 = Switchjs.createNestedObject();
  Switchjs_1["name"] = Switch[1].Name;
  Switchjs_1["description"] = Switch[1].Description;
  Switchjs_1["min"] = Switch[1].minValue;
  Switchjs_1["max"] = Switch[1].maxValue;

  JsonObject Switchjs_2 = Switchjs.createNestedObject();
  Switchjs_2["name"] = Switch[2].Name;
  Switchjs_2["description"] = Switch[2].Description;
  Switchjs_2["min"] = Switch[2].minValue;
  Switchjs_2["max"] = Switch[2].maxValue;

  JsonObject Switchjs_3 = Switchjs.createNestedObject();
  Switchjs_3["name"] = Switch[3].Name;
  Switchjs_3["description"] = Switch[3].Description;
  Switchjs_3["min"] = Switch[3].minValue;
  Switchjs_3["max"] = Switch[3].maxValue;


  JsonObject Switchjs_4 = Switchjs.createNestedObject();
  Switchjs_4["name"] = Switch[4].Name;
  Switchjs_4["description"] = Switch[4].Description;
  Switchjs_4["min"] = Switch[4].minValue;
  Switchjs_4["max"] = Switch[4].maxValue;

  JsonObject Switchjs_5 = Switchjs.createNestedObject();
  Switchjs_5["name"] = Switch[5].Name;
  Switchjs_5["description"] = Switch[5].Description;
  Switchjs_5["min"] = Switch[5].minValue;
  Switchjs_5["max"] = Switch[5].maxValue;

  JSwitchAnsw="";
  serializeJson(doc, JSwitchAnsw);
  request->send(200, "application/json", JSwitchAnsw);
}


#endif

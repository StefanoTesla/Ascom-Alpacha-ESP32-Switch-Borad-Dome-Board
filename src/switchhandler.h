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

Please refer to this page to understand wich output/input you can use without problems:
https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
*/


/* automatic setup for Switch */

  for (i=0;i<_MAX_SWTICH_ID_;i++){
    if((Switch[i].pin == 0 || Switch[i].pin == 99) || Switch[i].type == 0 ){
      Serial.print(i);
      Serial.print(" ");
      Serial.print(Switch[i].pin);
      Serial.print(" ");
      Serial.print(Switch[i].type);
      Serial.println("fine switch setup");
      setting.switches.maxSwitch = i;
      break;
    }
    Serial.println("");
    Serial.print("Pin: ");
    Serial.print(Switch[i].pin);
    Serial.print(" ");
    if (Switch[i].CanSet == true){
      if (Switch[i].analog == false){
        //Uscita Digitale
        pinMode(Switch[i].pin, OUTPUT);
        Serial.print("Uscita Digitale ");
        Switch[i].Step = 1;
        Switch[i].minValue = 0;
        Switch[i].maxValue = 1;
      } else {
          //Uscita PWM
          Serial.print("Uscita PWM ");
          ledcSetup(pwmchannles, 5000, 10);
          ledcAttachPin(Switch[i].pin, pwmchannles);
          Switch[i].pwmChannel = pwmchannles;
          Switch[i].minValue = 0;
          Switch[i].maxValue = 1024;
          pwmchannles++;
      }
    } else {
      if (Switch[i].analog == false){
        //Ingresso Digitale
        Serial.print("Ingresso Digitale ");
        pinMode(Switch[i].pin, INPUT);
        Switch[i].Step = 1;
        Switch[i].minValue = 0;
        Switch[i].maxValue = 1;
      } else {
        //Ingresso Analogico
        Serial.print("Ingresso Analogico ");
        Switch[i].minValue = 0;
        Switch[i].maxValue = 4095;
      }  
    }
  Serial.println("");
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

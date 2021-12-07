#ifndef SWITCH_FUNC
#define SWITCH_FUNC

#include "switchhandler.h"


DynamicJsonDocument  JSwitch(200);
String JSwitchAnsw;

void JsonSwitchCostructor(int error, String errormessage ) {
  JSwitch["ClientTransactionID"] = ClientTransactionID;
  JSwitch["ServerTransactionID"] = AlpServerID;
  JSwitch["ErrorNumber"] = (uint32_t)error;
  JSwitch["ErrorMessage"] = errormessage;
  JSwitchAnsw = "";
  serializeJson(JSwitch, JSwitchAnsw);
  JSwitch.clear();
}

/*------------------------*/
/* COMANDI COMUNI */

//api/v1/switch/0/action
void SwtAlpCmdAction(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JsonSwitchCostructor(1036, "No actions defined");
  request->send(200, "application/json", JSwitchAnsw);
}


//GET api/v1/switch/0/connected
void SwtAlpConnected(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JSwitch["Value"] = true;
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);

}

//PUT api/v1/switch/0/connected
void SwtAlpConnectedPut(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}

//api/v1/switch/0/description
void SwtAlpDescription(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JSwitch["Value"] = "Tesla Switch first implementation";
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}

//api/v1/switch/0/driverinfo
void SwtAlpDriverInfo(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JSwitch["Value"] = "First implementation with id and json handler";
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}

//api/v1/switch/0/driverversion
void SwtAlpDriverVer(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JSwitch["Value"] = "1.0";
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}


//api/v1/switch/0/interfaceversion
void SwtAlpIntVer(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JSwitch["Value"] = 1;
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}

void SwtAlpName(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JSwitch["Value"] = "Tesla Switch";
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}

/* FINE COMANDI COMUNI */


void SwtAlpMaxSwitch(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  //must be implemented int result
  JSwitch["Value"] = _MAX_SWTICH_ID_;
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}


void SwtAlpCanWrite(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  if (Switch[Int_ID].CanSet == true) {
    JSwitch["Value"] = true;
  } else {
    JSwitch["Value"] = false;
  }
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}

void SwtAlpGetSwitch(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JSwitch["Value"] = digitalRead(Switch[Int_ID].pin);
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}

void SwtAlpSwtDesc(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JSwitch["Value"] = Switch[Int_ID].Description;
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}

void SwtAlpSwtName(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JSwitch["Value"] = Switch[Int_ID].Name;
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}

void SwtAlpGetSwtValue(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  if (Switch[Int_ID].analog == false) {
    JSwitch["Value"] = digitalRead(Switch[Int_ID].pin);
  } else {
    JSwitch["Value"] = Switch[Int_ID].anaValue;
  }
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);

}

void SwtAlpMinSwtValue(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JSwitch["Value"] = Switch[Int_ID].minValue;
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}

void SwtAlpMaxSwtValue(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JSwitch["Value"] = Switch[Int_ID].maxValue;
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}

void SwtAlpSetSwt(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JSwitch["Value"] = false;
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}

void SwtAlpSetSwtName(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JSwitch["Value"] = true;
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}

void SwtAlpSetSwtValue(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  if (Switch[Int_ID].analog == true) {
    Switch[Int_ID].anaValue = Int_Value;
    ledcWrite(Switch[Int_ID].pwmChannel, Switch[Int_ID].anaValue);
  } else {
    if (Int_Value == 1) {
      digitalWrite(Switch[Int_ID].pin, HIGH);
    } else {
      digitalWrite(Switch[Int_ID].pin, LOW);
    }
  }
  JSwitch["Value"] = true;
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}

void SwtAlpSwtStep(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JSwitch["Value"] = Switch[Int_ID].Step;
  JsonSwitchCostructor(0, "");
  request->send(200, "application/json", JSwitchAnsw);
}


#endif

#ifndef DOME_FUNC
#define DOME_FUNC

#include "domehandler.h"



DynamicJsonDocument  JDome(200);
String JDomeAnsw;


void JsonDomeCostructor(int error, String errormessage ) {
  JDome["ClientTransactionID"] = ClientTransactionID;
  JDome["ServerTransactionID"] = AlpServerID;
  JDome["ErrorNumber"] = (uint32_t)error;
  JDome["ErrorMessage"] = errormessage;
  JDomeAnsw = "";
  serializeJson(JDome, JDomeAnsw);
  JDome.clear();
}
/*------------------------*/
/* COMANDI COMUNI */


//GET api/v1/dome/0/connected
void DomAlpConnected(AsyncWebServerRequest *request) {

  JDome["Value"] = true;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);

}

//PUT api/v1/dome/0/connected
void DomAlpConnectedPut(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}

//api/v1/dome/0/description
void DomAlpDescription(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = "Tesla Dome first implementation";
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}

//api/v1/dome/0/driverinfo
void DomAlpDriverInfo(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = "First implementation with id and json handler";
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}

//api/v1/dome/0/driverversion
void DomAlpDriverVer(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = "1.0";
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}


//api/v1/dome/0/interfaceversion
void DomAlpIntVer(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = 1;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}

void DomAlpName(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = "Tesla Dome";
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}


/* FINE COMANDI COMUNI */

void DomAlpCanSetShutter(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = true;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}


void DomAlpShutterState(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = ShutterState;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}


void DomAlpSlewing(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  if (ShutterCommand == Idle) {
    JDome["Value"] = false;
  } else {
    JDome["Value"] = true;
  }
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}

void DomAlpAbortSlew(AsyncWebServerRequest *request) {
  //no amswer needed only costum data client server error ecc...
  ShCyIndex =100;
  GetAlpArguments(request);
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}

void DomAlpCloseShutter(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  if (ShutterCommand == Idle && ShutterState != ShClose ){
    JsonDomeCostructor(0, "");
    request->send(200, "application/json", JDomeAnsw);
    ShutterCommand = CmdClose;
  } else {
  JsonDomeCostructor(1035, "Shutter already closed or moving");
  request->send(200, "application/json", JDomeAnsw);
  } 

}

void DomAlpOpenShutter(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  if (ShutterCommand == Idle && ShutterState != ShOpen ){
    JsonDomeCostructor(0, "");
    request->send(200, "application/json", JDomeAnsw);
    ShutterCommand = CmdOpen;
  } else {
  JsonDomeCostructor(1035, "Shutter already opened or moving");
  request->send(200, "application/json", JDomeAnsw);
  }
}


/** NOT USED BUT NECESSARY FUNCTION **/

//api/v1/dome/0/action
void DomAlpCmdAction(AsyncWebServerRequest *request) {
  JsonDomeCostructor(1036, "No actions defined");
  request->send(200, "application/json", JDomeAnsw);
}

void DomAlpCanFindHome(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}


void DomAlpCanPark(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);

}

void DomAlpCanSetAlt(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}


void DomAlpSlaved(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}

void DomAlpSlavedPut(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}

void DomAlpCanSetAzi(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}

void DomAlpCanSetPark(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}

void DomAlpCanSlave(AsyncWebServerRequest *request) {
  //must be implemented bool result
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}

void DomAlpCanSyncAzi(AsyncWebServerRequest *request) {
  //must be implemented bool result
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
}


void DomWSState (AsyncWebServerRequest *request) {
  const size_t capacity = JSON_OBJECT_SIZE(800);
  String domestatus;
  DynamicJsonDocument doc(capacity);
  doc["domepos"]   = ShutterState;
  doc["domelstcmd"]  = "nietca";
  doc["dometimeout"] = MovingTimeOut;
 
  serializeJson(doc, domestatus);
  request->send(200, "application/json", domestatus);
}

void DomWSSetup (AsyncWebServerRequest *request) {
  const size_t capacity = JSON_OBJECT_SIZE(16);
  String domesetup;
  DynamicJsonDocument doc(capacity);
  doc["dometmout"]   = MovingTimeOut;
  serializeJson(doc, domesetup);
  Serial.println(domesetup);
  request->send(200, "application/json", domesetup);
}
#endif

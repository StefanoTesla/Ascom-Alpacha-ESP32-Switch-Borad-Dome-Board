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


void AlpacaDome(){ 


Alpserver.on("/api/v1/dome/0/shutterstatus",                                            HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = ShutterState;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
});

Alpserver.on("/api/v1/dome/0/closeshutter",                                             HTTP_PUT, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  if (ShutterCommand == Idle && ShutterState != ShOpen ){
    JsonDomeCostructor(0, "");
    request->send(200, "application/json", JDomeAnsw);
    ShutterCommand = CmdClose;
  } else {
  JsonDomeCostructor(1035, "Shutter already opened or moving");
  request->send(200, "application/json", JDomeAnsw);
  }
});

Alpserver.on("/api/v1/dome/0/openshutter",                                              HTTP_PUT, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  if (ShutterCommand == Idle && ShutterState != ShOpen ){
    JsonDomeCostructor(0, "");
    request->send(200, "application/json", JDomeAnsw);
    ShutterCommand = CmdOpen;
  } else {
  JsonDomeCostructor(1035, "Shutter already opened or moving");
  request->send(200, "application/json", JDomeAnsw);
  }
});

Alpserver.on("/api/v1/dome/0/abortslew",                                                HTTP_PUT, [](AsyncWebServerRequest *request) {
  ShCyIndex =100;
  GetAlpArguments(request);
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
});

Alpserver.on("/api/v1/dome/0/connected",                                                HTTP_GET, [](AsyncWebServerRequest *request){

  JDome["Value"] = true;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);

});

Alpserver.on("/api/v1/dome/0/connected",                                                HTTP_PUT, [](AsyncWebServerRequest *request){

  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);

});

Alpserver.on("/api/v1/dome/0/description",                                              HTTP_GET, [](AsyncWebServerRequest *request) {

  GetAlpArguments(request);
  JDome["Value"] = "Tesla Dome first implementation";
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);

});

Alpserver.on("/api/v1/dome/0/driverinfo",                                               HTTP_GET, [](AsyncWebServerRequest *request) {

  GetAlpArguments(request);
  JDome["Value"] = "First implementation with id and json handler";
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);

});

Alpserver.on("/api/v1/dome/0/driverversion",                                            HTTP_GET, [](AsyncWebServerRequest *request) {

  GetAlpArguments(request);
  JDome["Value"] = "1.0";
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);

});

Alpserver.on("/api/v1/dome/0/interfaceversion",                                         HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = 1;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
});

Alpserver.on("/api/v1/dome/0/name",                                                     HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = "Tesla Dome";
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
});

Alpserver.on("/api/v1/dome/0/canfindhome",                                              HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
});

Alpserver.on("/api/v1/dome/0/canpark",                                                  HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw); 
});

Alpserver.on("/api/v1/dome/0/cansetaltitude",                                           HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
});

Alpserver.on("/api/v1/dome/0/cansetazimuth",                                            HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
});

Alpserver.on("/api/v1/dome/0/cansetpark",                                               HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
});

Alpserver.on("/api/v1/dome/0/cansetshutter",                                            HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = true;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
});

Alpserver.on("/api/v1/dome/0/canslave",                                                 HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
});

Alpserver.on("/api/v1/dome/0/cansyncazimuth",                                           HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
});

Alpserver.on("/api/v1/dome/0/slaved",                                                   HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  JDome["Value"] = false;
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
});

Alpserver.on("/api/v1/dome/0/slewing",                                                  HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  if (ShutterCommand == Idle) {
    JDome["Value"] = false;
  } else {
    JDome["Value"] = true;
  }
  JsonDomeCostructor(0, "");
  request->send(200, "application/json", JDomeAnsw);
});

Alpserver.on("/api/v1/dome/0/altitude",                                                 HTTP_GET, AscomPropertyNotImplemented);
Alpserver.on("/api/v1/dome/0/athome",                                                   HTTP_GET, AscomPropertyNotImplemented);
Alpserver.on("/api/v1/dome/0/atpark",                                                   HTTP_GET, AscomPropertyNotImplemented);
Alpserver.on("/api/v1/dome/0/azimuth",                                                  HTTP_GET, AscomPropertyNotImplemented);
Alpserver.on("/api/v1/dome/0/slaved",                                                   HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("/api/v1/dome/0/findhome",                                                 HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("/api/v1/dome/0/park",                                                     HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("/api/v1/dome/0/setpark",                                                  HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("/api/v1/dome/0/slewtoaltitude",                                           HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("/api/v1/dome/0/slewtoazimuth",                                            HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("/api/v1/dome/0/synctoazimuth",                                            HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("api/v1/dome/0/commandblind",                                              HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("api/v1/dome/0/commandbool",                                               HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("api/v1/dome/0/commandstring",                                             HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("/api/v1/dome/0/supportedactions",                                         HTTP_GET, AscomMethodNotImplemented);
Alpserver.on("api/v1/dome/0/action",                                                    HTTP_PUT, [](AsyncWebServerRequest *request) {
  JsonDomeCostructor(1036, "No actions defined");
  request->send(200, "application/json", JDomeAnsw);
});

}

void DomWSState (AsyncWebServerRequest *request) {
  const size_t capacity = JSON_OBJECT_SIZE(800);
  String domestatus;
  DynamicJsonDocument doc(capacity);
  doc["domepos"]   = ShutterState;
  doc["domelstcmd"]  = LastDomeCommand;
  doc["dometimeout"] = MovingTimeOut;
 
  serializeJson(doc, domestatus);
  request->send(200, "application/json", domestatus);
}

#endif

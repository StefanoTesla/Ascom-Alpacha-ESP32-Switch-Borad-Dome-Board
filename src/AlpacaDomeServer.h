#ifndef DOME_FUNC
#define DOME_FUNC

#include "domehandler.h"

void domeFalseValueAnswer(AsyncWebServerRequest *request){
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  AlpacaHeaderSchema(response,AlpacaData);
  AlpacaNoErrorSchema(response);
  response->printf("%sfalse}",Alp_Value);
  request->send(response);
}
void DomeAlpaca(){ 


Alpserver.on("/api/v1/dome/0/shutterstatus",                                            HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  AlpacaHeaderSchema(response,AlpacaData);
  AlpacaNoErrorSchema(response);
  response->printf("%s%d}",Alp_Value,Dome.ShutterState);
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/closeshutter",                                             HTTP_PUT, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  AlpacaHeaderSchema(response,AlpacaData);
  if (Dome.ShutterCommand == Idle && Dome.ShutterState != ShClose ){
    AlpacaNoErrorSchema(response,false); 
    Dome.ShutterCommand = CmdClose;
  } else {
    response->printf("%s1035,%s\"Shutter already closed or moving\"",Alp_ErrN,Alp_ErrM); 
  }
  response->print(F("}"));
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/openshutter",                                              HTTP_PUT, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  AlpacaHeaderSchema(response,AlpacaData);
  if (Dome.ShutterCommand == Idle && Dome.ShutterState != ShOpen ){
    AlpacaNoErrorSchema(response,false);
    Dome.ShutterCommand = CmdOpen; 
  } else {
    response->printf("%s1035,%s\"Shutter already opened or moving\"",Alp_ErrN,Alp_ErrM); 
  }
  response->print(F("}"));
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/abortslew",                                                HTTP_PUT, [](AsyncWebServerRequest *request) {
  Dome.Cycle =100;
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  AlpacaHeaderSchema(response,AlpacaData);
  AlpacaNoErrorSchema(response,false);
  response->print(F("}"));
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/connected",                                                HTTP_GET, [](AsyncWebServerRequest *request){
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  AlpacaHeaderSchema(response,AlpacaData);
  AlpacaNoErrorSchema(response);
  response->printf("%strue}",Alp_Value);
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/connected",                                                HTTP_PUT, [](AsyncWebServerRequest *request){
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  AlpacaHeaderSchema(response,AlpacaData);
  AlpacaNoErrorSchema(response,false);
  response->printf("}");
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/description",                                              HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  AlpacaHeaderSchema(response,AlpacaData);
  AlpacaNoErrorSchema(response);
  response->printf("%s\"StefanoTesla Dome\"}",Alp_Value);
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/driverinfo",                                               HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  AlpacaHeaderSchema(response,AlpacaData);
  AlpacaNoErrorSchema(response);
  response->printf("%s\"StefanoTesla Dome response on the fly\"}",Alp_Value);
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/driverversion",                                            HTTP_GET, [](AsyncWebServerRequest *request) {

  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  AlpacaHeaderSchema(response,AlpacaData);
  AlpacaNoErrorSchema(response);
  response->printf("%s\"2.0.0\"}",Alp_Value);
  request->send(response);

});

Alpserver.on("/api/v1/dome/0/interfaceversion",                                         HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  AlpacaHeaderSchema(response,AlpacaData);
  AlpacaNoErrorSchema(response);
  response->printf("%s1}",Alp_Value);
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/name",                                                     HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  AlpacaHeaderSchema(response,AlpacaData);
  AlpacaNoErrorSchema(response);
  response->printf("%s\"StefanoTeslaDome\"}",Alp_Value);
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/cansetshutter",                                            HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  AlpacaHeaderSchema(response,AlpacaData);
  AlpacaNoErrorSchema(response);
  response->printf("%strue}",Alp_Value);
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/slewing",                                                  HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  AlpacaHeaderSchema(response,AlpacaData);
  AlpacaNoErrorSchema(response);
  Dome.ShutterCommand == Idle ? response->printf("%sfalse}",Alp_Value) : response->printf("%strue}",Alp_Value);
  request->send(response);  
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
Alpserver.on("/api/v1/dome/0/commandblind",                                             HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("/api/v1/dome/0/commandbool",                                              HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("/api/v1/dome/0/commandstring",                                            HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("/api/v1/dome/0/supportedactions",                                         HTTP_GET, AscomNoActions);
Alpserver.on("/api/v1/dome/0/action",                                                    HTTP_PUT, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  AlpacaHeaderSchema(response,AlpacaData);
  response->print(F("\"ErrorNumber\":1036,\"ErrorMessage\":\"No actions defined\"}"));
  request->send(response);
});


Alpserver.on("/api/v1/dome/0/canfindhome",                                              HTTP_GET, domeFalseValueAnswer);
Alpserver.on("/api/v1/dome/0/canpark",                                                  HTTP_GET, domeFalseValueAnswer);
Alpserver.on("/api/v1/dome/0/cansetaltitude",                                           HTTP_GET, domeFalseValueAnswer);
Alpserver.on("/api/v1/dome/0/cansetazimuth",                                            HTTP_GET, domeFalseValueAnswer);
Alpserver.on("/api/v1/dome/0/cansetpark",                                               HTTP_GET, domeFalseValueAnswer);
Alpserver.on("/api/v1/dome/0/canslave",                                                 HTTP_GET, domeFalseValueAnswer);
Alpserver.on("/api/v1/dome/0/cansyncazimuth",                                           HTTP_GET, domeFalseValueAnswer);
Alpserver.on("/api/v1/dome/0/slaved",                                                   HTTP_GET, domeFalseValueAnswer);

}

#endif

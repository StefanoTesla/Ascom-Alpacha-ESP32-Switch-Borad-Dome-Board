#ifndef DOME_FUNC
#define DOME_FUNC

#include "domehandler.h"

void domeFalseValueAnswer(AsyncWebServerRequest *request){
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print(F("{\"Value\": false,\"ClientTransactionID\":"));
  response->print(AlpacaData.clientTransactionID);
  response->print(F(",\"ServerTransactionID\":"));
  response->print(AlpacaData.serverTransactionID);
  response->print(F(",\"ErrorNumber\":0,\"ErrorMessage\":\"\""));
  response->print(F("}"));
  request->send(response);
}
void DomeAlpaca(){ 


Alpserver.on("/api/v1/dome/0/shutterstatus",                                            HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->printf("{%s%d,%s%d,%s%d,%s}",
                                  Alp_Value,Dome.ShutterState,
                                  Alp_CliTraId,AlpacaData.clientTransactionID,
                                  Alp_SerTraId,AlpacaData.serverTransactionID,
                                  Alp_NoErrors
                                  );
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/closeshutter",                                             HTTP_PUT, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->printf("{%s%d,%s%d,",
                              Alp_CliTraId,AlpacaData.clientTransactionID,
                              Alp_SerTraId,AlpacaData.serverTransactionID
                              );
  if (Dome.ShutterCommand == Idle && Dome.ShutterState != ShClose ){
    response->print(Alp_NoErrors);  
  } else {
    response->printf("%s1035,%s\"Shutter already closed or moving\"",Alp_ErrN,Alp_ErrM); 
  }
  response->print(F("}"));
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/openshutter",                                              HTTP_PUT, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->printf("{%s%d,%s%d,",Alp_CliTraId,AlpacaData.clientTransactionID,Alp_SerTraId,AlpacaData.serverTransactionID);
  if (Dome.ShutterCommand == Idle && Dome.ShutterState != ShOpen ){
    response->print(Alp_NoErrors);  
  } else {
    response->printf("%s:1035,%s:\"Shutter already opened or moving\"",Alp_ErrN,Alp_ErrM); 
  }
  response->print(F("}"));
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/abortslew",                                                HTTP_PUT, [](AsyncWebServerRequest *request) {
  Dome.Cycle =100;
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->printf("{%s%d,%s%d,%s}",Alp_CliTraId,AlpacaData.clientTransactionID,Alp_SerTraId,AlpacaData.serverTransactionID,Alp_NoErrors);
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/connected",                                                HTTP_GET, [](AsyncWebServerRequest *request){
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->printf("{%strue,%s%d,%s%d,%s}",
                                  Alp_Value,
                                  Alp_CliTraId,AlpacaData.clientTransactionID,
                                  Alp_SerTraId,AlpacaData.serverTransactionID,
                                  Alp_NoErrors
                                  );
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/connected",                                                HTTP_PUT, [](AsyncWebServerRequest *request){
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->printf("{%strue,%s%d,%s%d,%s}",
                                  Alp_Value,
                                  Alp_CliTraId,AlpacaData.clientTransactionID,
                                  Alp_SerTraId,AlpacaData.serverTransactionID,
                                  Alp_NoErrors
                                  );
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/description",                                              HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->printf("{%s\"StefanoTesla Dome\",%s%d,%s%d,%s}",
                                  Alp_Value,
                                  Alp_CliTraId,AlpacaData.clientTransactionID,
                                  Alp_SerTraId,AlpacaData.serverTransactionID,
                                  Alp_NoErrors
                                  );
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/driverinfo",                                               HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->printf("{%s\"StefanoTesla Dome response on the fly\",%s%d,%s%d,%s}",
                                  Alp_Value,
                                  Alp_CliTraId,AlpacaData.clientTransactionID,
                                  Alp_SerTraId,AlpacaData.serverTransactionID,
                                  Alp_NoErrors
                                  );
  request->send(response);
});

Alpserver.on("/api/v1/dome/0/driverversion",                                            HTTP_GET, [](AsyncWebServerRequest *request) {

  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->printf("{%s\"2.0.0\",%s%d,%s%d,%s}",
                                  Alp_Value,
                                  Alp_CliTraId,AlpacaData.clientTransactionID,
                                  Alp_SerTraId,AlpacaData.serverTransactionID,
                                  Alp_NoErrors
                                  );
  request->send(response);

});

Alpserver.on("/api/v1/dome/0/interfaceversion",                                         HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->printf("{%s1,%s%d,%s%d,%s}",
                                  Alp_Value,
                                  Alp_CliTraId,AlpacaData.clientTransactionID,
                                  Alp_SerTraId,AlpacaData.serverTransactionID,
                                  Alp_NoErrors
                                  );
  request->send(response);
  });


Alpserver.on("/api/v1/dome/0/name",                                                     HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->printf("{%s\"StefanoTeslaDome\",%s%d,%s%d,%s}",
                                  Alp_Value,
                                  Alp_CliTraId,AlpacaData.clientTransactionID,
                                  Alp_SerTraId,AlpacaData.serverTransactionID,
                                  Alp_NoErrors
                                  );
  request->send(response);
  });


Alpserver.on("/api/v1/dome/0/cansetshutter",                                            HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->printf("{%strue,%s%d,%s%d,%s}",
                                  Alp_Value,
                                  Alp_CliTraId,AlpacaData.clientTransactionID,
                                  Alp_SerTraId,AlpacaData.serverTransactionID,
                                  Alp_NoErrors
                                  );
  request->send(response);
});



Alpserver.on("/api/v1/dome/0/slewing",                                                  HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->printf("{%s",Alp_Value);
  Dome.ShutterCommand == Idle ? response->print("false,") : response->print("true,");
  response->printf("%s%d,%s%d,%s}",
                                  Alp_CliTraId,AlpacaData.clientTransactionID,
                                  Alp_SerTraId,AlpacaData.serverTransactionID,
                                  Alp_NoErrors
                                  );
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
    response->print(F("{\"ClientTransactionID\":"));
    response->print(AlpacaData.clientTransactionID);
    response->print(F(",\"ServerTransactionID\":"));
    response->print(AlpacaData.serverTransactionID);
    response->print(F(",\"ErrorNumber\":1036,\"ErrorMessage\":\"No actions defined\"}"));
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

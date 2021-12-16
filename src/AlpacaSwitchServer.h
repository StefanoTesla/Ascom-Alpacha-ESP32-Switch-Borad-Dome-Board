#ifndef SWITCH_FUNC
#define SWITCH_FUNC

#include "switchhandler.h"


const char Alp_Value[] = "\"Value\": ";
const char Alp_CliTraId[] = "\"ClientTransactionID\": ";
const char Alp_SerTraId[] = "\"ServerTransactionID\": ";
const char Alp_ErrN[] = "\"ErrorNumber\": ";
const char Alp_ErrM[] = "\"ErrorMessage\": ";
const char Alp_NoErrors[] = "\"ErrorNumber\": 0, \"ErrorMessage\": \"\"";


void SwitchAlpaca(){

Alpserver.on("/api/v1/switch/0/setswitchvalue",                                         HTTP_PUT, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);

  if(Alp_idcheck){
    if(Alp_value_ex){
      if(Alp_Int_Value >= Switch[Alp_Int_ID].minValue && Alp_Int_Value <= Switch[Alp_Int_ID].maxValue) {
        if (Switch[Alp_Int_ID].analog == true) {
          Switch[Alp_Int_ID].anaValue = Alp_Int_Value;
          ledcWrite(Switch[Alp_Int_ID].pwmChannel, Switch[Alp_Int_ID].anaValue);
        } else {
          Alp_Int_Value == 1 ? digitalWrite(Switch[Alp_Int_ID].pin, HIGH) : digitalWrite(Switch[Alp_Int_ID].pin, LOW);
        }
        response->print(Alp_NoErrors);
      } else {
        response->printf("%s1025,%s \"The Value %d is out of range MIN: %d MAX: %d\"", Alp_ErrN, Alp_ErrM, Alp_Int_Value,Switch[Alp_Int_ID].minValue,Switch[Alp_Int_ID].maxValue);
      }
    } else {
      response->printf("%s1025, %s\"The Value was not provided from ASCOM\"", Alp_ErrN, Alp_ErrM);
    }
  } else {
    response->printf("%s 1025, %s \"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, Alp_Int_ID);
  }
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/maxswitch",                                              HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->print(Alp_Value);
  response->printf("%d, ",_MAX_SWTICH_ID_);
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/canwrite",                                               HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(Alp_idcheck){
    response->print(Alp_Value);
    Switch[Alp_Int_ID].CanSet ? response->print("true, ") : response->print("false, ");
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  Alp_idcheck ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, Alp_Int_ID); 
  response->print(" }");
  request->send(response);

});

Alpserver.on("/api/v1/switch/0/getswitch",                                              HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(Alp_idcheck){
    response->print(Alp_Value);
    response->printf("%d, ",digitalRead(Switch[Alp_Int_ID].pin));
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  Alp_idcheck ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, Alp_Int_ID); 
  response->print(" }");
  request->send(response);

});

Alpserver.on("/api/v1/switch/0/getswitchdescription",                                   HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);

  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(Alp_idcheck){
    response->print(Alp_Value);
    response->printf("\"%s\", ",Switch[Alp_Int_ID].Description.c_str());
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  Alp_idcheck ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, Alp_Int_ID); 
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/getswitchname",                                          HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);

  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(Alp_idcheck){
    response->print(Alp_Value);
    response->printf("\"%s\", ",Switch[Alp_Int_ID].Name.c_str());
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  Alp_idcheck ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, Alp_Int_ID); 
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/minswitchvalue",                                         HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);

  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(Alp_idcheck){
    response->print(Alp_Value);
    response->printf("%d, ",Switch[Alp_Int_ID].minValue);
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  Alp_idcheck ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, Alp_Int_ID); 
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/maxswitchvalue",                                         HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);

  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(Alp_idcheck){
    response->print(Alp_Value);
    response->printf("%d, ",Switch[Alp_Int_ID].maxValue);
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  Alp_idcheck ? response->print(Alp_NoErrors) : response->printf("%s 1025, %s \"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, Alp_Int_ID); 
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/switchstep",                                             HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);

  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(Alp_idcheck){
    response->print(Alp_Value);
    response->printf("%d, ",Switch[Alp_Int_ID].Step);
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  Alp_idcheck ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, Alp_Int_ID); 
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/getswitchvalue",                                         HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);

  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(Alp_idcheck){
    response->print(Alp_Value);
    Switch[Alp_Int_ID].analog ? response->printf("%d, ",Switch[Alp_Int_ID].anaValue) : response->printf("%d, ",digitalRead(Switch[Alp_Int_ID].pin)); 
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  Alp_idcheck ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, Alp_Int_ID); 
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/name",                                                   HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->printf("%s\"Tesla Switch\", ",Alp_Value);
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/description",                                            HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->printf("%s\"Tesla Switch board with esp32 and Ascom Alpaca Protocol\", ",Alp_Value);
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/driverinfo",                                             HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->printf("%s\"Removed Json handler to better error message handling\", ",Alp_Value);
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/driverversion",                                          HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->printf("%s\"1.2\", ",Alp_Value);
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/interfaceversion",                                       HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->printf("%s1, ",Alp_Value);
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/connected",                                              HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->printf("%strue, ",Alp_Value);
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);

});

Alpserver.on("/api/v1/switch/0/connected",                                              HTTP_PUT, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);
});


Alpserver.on("/api/v1/switch/0/setswitchname",                                          HTTP_PUT, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(Alp_idcheck){
    Switch[Alp_Int_ID].Name = Alp_Name;
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  Alp_idcheck ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, Alp_Int_ID);
  response->print(" }");
  request->send(response);
});


Alpserver.on("/api/v1/switch/0/commandblind",                                           HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("/api/v1/switch/0/commandbool",                                            HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("/api/v1/switch/0/commandstring",                                          HTTP_PUT, AscomMethodNotImplemented);
Alpserver.on("/api/v1/switch/0/supportedactions",                                       HTTP_GET, AscomMethodNotImplemented);
Alpserver.on("/api/v1/switch/0/action",                                                 HTTP_PUT, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  response->printf("%s1036, %s\"No actions defined\"", Alp_ErrN, Alp_ErrM); 
  response->print(" }");
  request->send(response);

});


Alpserver.on("/api/v1/switch/0/setswitch",                                              HTTP_PUT, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(Alp_idcheck){
    if (Switch[Alp_Int_ID].analog){
      Switch[Alp_Int_ID].anaValue = Switch[Alp_Int_ID].maxValue;
      ledcWrite(Switch[Alp_Int_ID].pwmChannel, Switch[Alp_Int_ID].maxValue);
    } else {
      digitalWrite(Switch[Alp_Int_ID].pin, Alp_state);
    }
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, ClientTransactionID, Alp_SerTraId, AlpServerID);
  if(Alp_idcheck){
    if(Alp_state == 0 || Alp_state == 1){
      response->print(Alp_NoErrors);
    } else {
      response->printf("%s1025, %s\"The Switch State is outside range\"", Alp_ErrN, Alp_ErrM);
    }
    response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, Alp_Int_ID); 
  }
  response->print(" }");
  request->send(response);
});


}





#endif

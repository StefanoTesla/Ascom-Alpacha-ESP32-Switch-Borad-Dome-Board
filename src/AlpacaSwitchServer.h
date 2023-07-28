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
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);

  if(AlpacaData.SwitchIdInRange){
    if(AlpacaData.SwitchValueInRange){
      if(AlpacaData.SwitchIntValue >= Switch[AlpacaData.SwitchId].minValue && AlpacaData.SwitchIntValue <= Switch[AlpacaData.SwitchId].maxValue) {
        if (Switch[AlpacaData.SwitchId].analog == true) {
          Switch[AlpacaData.SwitchId].anaValue = AlpacaData.SwitchIntValue;
          ledcWrite(Switch[AlpacaData.SwitchId].pwmChannel, Switch[AlpacaData.SwitchId].anaValue);
        } else {
          AlpacaData.SwitchIntValue == 1 ? digitalWrite(Switch[AlpacaData.SwitchId].pin, HIGH) : digitalWrite(Switch[AlpacaData.SwitchId].pin, LOW);
        }
        response->print(Alp_NoErrors);
      } else {
        response->printf("%s1025,%s \"The Value %d is out of range MIN: %d MAX: %d\"", Alp_ErrN, Alp_ErrM, AlpacaData.SwitchIntValue,Switch[AlpacaData.SwitchId].minValue,Switch[AlpacaData.SwitchId].maxValue);
      }
    } else {
      response->printf("%s1025, %s\"The Value was not provided from ASCOM\"", Alp_ErrN, Alp_ErrM);
    }
  } else {
    response->printf("%s 1025, %s \"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, AlpacaData.SwitchId);
  }
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/maxswitch",                                              HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->print(Alp_Value);
  response->printf("%d, ",setting.switches.maxSwitch);
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/canwrite",                                               HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(AlpacaData.SwitchIdInRange){
    response->print(Alp_Value);
    Switch[AlpacaData.SwitchId].CanSet ? response->print("true, ") : response->print("false, ");
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  AlpacaData.SwitchIdInRange ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, AlpacaData.SwitchId); 
  response->print(" }");
  request->send(response);

});

Alpserver.on("/api/v1/switch/0/getswitch",                                              HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(AlpacaData.SwitchIdInRange){
    response->print(Alp_Value);
    response->printf("%d, ",digitalRead(Switch[AlpacaData.SwitchId].pin));
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  AlpacaData.SwitchIdInRange ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, AlpacaData.SwitchId); 
  response->print(" }");
  request->send(response);

});

Alpserver.on("/api/v1/switch/0/getswitchdescription",                                   HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);

  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(AlpacaData.SwitchIdInRange){
    response->print(Alp_Value);
    response->printf("\"%s\", ",Switch[AlpacaData.SwitchId].Description.c_str());
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  AlpacaData.SwitchIdInRange ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, AlpacaData.SwitchId); 
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/getswitchname",                                          HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);

  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(AlpacaData.SwitchIdInRange){
    response->print(Alp_Value);
    response->printf("\"%s\", ",Switch[AlpacaData.SwitchId].Name.c_str());
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  AlpacaData.SwitchIdInRange ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, AlpacaData.SwitchId); 
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/minswitchvalue",                                         HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);

  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(AlpacaData.SwitchIdInRange){
    response->print(Alp_Value);
    response->printf("%d, ",Switch[AlpacaData.SwitchId].minValue);
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  AlpacaData.SwitchIdInRange ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, AlpacaData.SwitchId); 
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/maxswitchvalue",                                         HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);

  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(AlpacaData.SwitchIdInRange){
    response->print(Alp_Value);
    response->printf("%d, ",Switch[AlpacaData.SwitchId].maxValue);
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  AlpacaData.SwitchIdInRange ? response->print(Alp_NoErrors) : response->printf("%s 1025, %s \"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, AlpacaData.SwitchId); 
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/switchstep",                                             HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);

  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(AlpacaData.SwitchIdInRange){
    response->print(Alp_Value);
    response->printf("%d, ",Switch[AlpacaData.SwitchId].Step);
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  AlpacaData.SwitchIdInRange ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, AlpacaData.SwitchId); 
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/getswitchvalue",                                         HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);

  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(AlpacaData.SwitchIdInRange){
    response->print(Alp_Value);
    Switch[AlpacaData.SwitchId].analog ? response->printf("%d, ",Switch[AlpacaData.SwitchId].anaValue) : response->printf("%d, ",digitalRead(Switch[AlpacaData.SwitchId].pin)); 
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  AlpacaData.SwitchIdInRange ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, AlpacaData.SwitchId); 
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/name",                                                   HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->printf("%s\"Tesla Switch\", ",Alp_Value);
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/description",                                            HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->printf("%s\"Tesla Switch board with esp32 and Ascom Alpaca Protocol\", ",Alp_Value);
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/driverinfo",                                             HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->printf("%s\"Removed Json handler to better error message handling\", ",Alp_Value);
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/driverversion",                                          HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->printf("%s\"1.2\", ",Alp_Value);
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/interfaceversion",                                       HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->printf("%s1, ",Alp_Value);
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);
});

Alpserver.on("/api/v1/switch/0/connected",                                              HTTP_GET, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->printf("%strue, ",Alp_Value);
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);

});

Alpserver.on("/api/v1/switch/0/connected",                                              HTTP_PUT, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->print("{ ");
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  response->print(Alp_NoErrors);
  response->print(" }");
  request->send(response);
});


Alpserver.on("/api/v1/switch/0/setswitchname",                                          HTTP_PUT, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(AlpacaData.SwitchIdInRange){
    Switch[AlpacaData.SwitchId].Name = AlpacaData.SwitchString;
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  AlpacaData.SwitchIdInRange ? response->print(Alp_NoErrors) : response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, AlpacaData.SwitchId);
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
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  response->printf("%s1036, %s\"No actions defined\"", Alp_ErrN, Alp_ErrM); 
  response->print(" }");
  request->send(response);

});


Alpserver.on("/api/v1/switch/0/setswitch",                                              HTTP_PUT, [](AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");

  response->print("{ ");
  if(AlpacaData.SwitchIdInRange){
    if (Switch[AlpacaData.SwitchId].analog){
      Switch[AlpacaData.SwitchId].anaValue = Switch[AlpacaData.SwitchId].maxValue;
      ledcWrite(Switch[AlpacaData.SwitchId].pwmChannel, Switch[AlpacaData.SwitchId].maxValue);
    } else {
      digitalWrite(Switch[AlpacaData.SwitchId].pin, AlpacaData.SwitchValue);
    }
  }
  response->printf("%s%d, %s%d, ",Alp_CliTraId, AlpacaData.ClientTransactionID, Alp_SerTraId, AlpacaData.AlpServerID);
  if(AlpacaData.SwitchIdInRange){
    if(AlpacaData.SwitchValue == 0 || AlpacaData.SwitchValue == 1){
      response->print(Alp_NoErrors);
    } else {
      response->printf("%s1025, %s\"The Switch State is outside range\"", Alp_ErrN, Alp_ErrM);
    }
    response->printf("%s1025, %s\"The Switch %d doesn't exist\"", Alp_ErrN, Alp_ErrM, AlpacaData.SwitchId); 
  }
  response->print(" }");
  request->send(response);
});


}





#endif

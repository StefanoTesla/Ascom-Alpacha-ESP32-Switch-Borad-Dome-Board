#ifndef SWITCH_FUNC
#define SWITCH_FUNC

#include "switchhandler.h"

void SwitchAlpaca(){

  Alpserver.on("/api/v1/switch/0/name",                                                     HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->printf("%s\"StefanoTeslaSwitch\"}",Alp_Value);
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/connected",                                                HTTP_PUT, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response,false);
    response->printf("}");
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/description",                                              HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->printf("%s\"StefanoTesla Switch\"}",Alp_Value);
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/driverinfo",                                               HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->printf("%s\"StefanoTesla Dome response on the fly\"}",Alp_Value);
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/driverversion",                                            HTTP_GET, [](AsyncWebServerRequest *request) {

    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->printf("%s\"2.0.0\"}",Alp_Value);
    request->send(response);

  });

  Alpserver.on("/api/v1/switch/0/interfaceversion",                                         HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->printf("%s1}",Alp_Value);
    request->send(response);
  });

  Alpserver.on("/api/v1/dome/0/action",                                                    HTTP_PUT, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    response->print(F("\"ErrorNumber\":1036,\"ErrorMessage\":\"No actions defined\"}"));
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/maxswitch",                                            HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->printf("%s%d}",Alp_Value,setting.switches.maxSwitch);
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/connected",                                             HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->printf("%sTrue}",Alp_Value,Dome.ShutterState);
    request->send(response);
  });

 
  Alpserver.on("/api/v1/switch/0/getswitchname",                                            HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id > setting.switches.maxSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
      AlpacaNoErrorSchema(response);
      response->printf("%s\"%s\"}",Alp_Value,Switch[AlpacaData.switches.id].Name);
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/getswitchdescription",                                     HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id > setting.switches.maxSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
      AlpacaNoErrorSchema(response);
      response->printf("%s\"%s\"}",Alp_Value,Switch[AlpacaData.switches.id].Description);
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/minswitchvalue",                                           HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id > setting.switches.maxSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
      AlpacaNoErrorSchema(response);
      response->printf("%s%d}",Alp_Value,Switch[AlpacaData.switches.id].minValue);
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/maxswitchvalue",                                           HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id > setting.switches.maxSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
      AlpacaNoErrorSchema(response);
      response->printf("%s%d}",Alp_Value,Switch[AlpacaData.switches.id].maxValue);
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/switchstep",                                               HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id > setting.switches.maxSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
      AlpacaNoErrorSchema(response);
      response->printf("%s%d}",Alp_Value,Switch[AlpacaData.switches.id].Step);
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/canwrite",                                                 HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id > setting.switches.maxSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
      AlpacaNoErrorSchema(response);
      response->printf("%s%d}",Alp_Value,Switch[AlpacaData.switches.id].CanSet);
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/getswitchvalue",                                           HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id > setting.switches.maxSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
        AlpacaNoErrorSchema(response);
        response->printf("%s",Alp_Value);
        switch (Switch[AlpacaData.switches.id].type)
        {
        case 1 ... 2:
          response->print(digitalRead(Switch[AlpacaData.switches.id].pin));
          break;
        case 3:
          response->print(ledcRead(Switch[AlpacaData.switches.id].pwmChannel));
          break;
        case 4:
          response->print(analogRead(Switch[AlpacaData.switches.id].pin));
          break;
        }
        response->print(F("}"));
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/getswitch",                                                HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id > setting.switches.maxSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
        AlpacaNoErrorSchema(response);
        response->printf("%s",Alp_Value);
        switch (Switch[AlpacaData.switches.id].type)
        {
        case 1 ... 2:
          digitalRead(Switch[AlpacaData.switches.id].pin) ? response->printf("true") : response->printf("false");
          break;
        case 3:
          if(ledcRead(Switch[AlpacaData.switches.id].pwmChannel) == 0){
            response->printf("false");
          } else {
            response->printf("true");
          }
          break;
        case 4:
          if(analogRead(Switch[AlpacaData.switches.id].pin) == 0){
            response->printf("false");
          } else {
            response->printf("true");
          }
          break;
        }
        response->print(F("}"));
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/getswitchvalue",                                            HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id > setting.switches.maxSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
        AlpacaNoErrorSchema(response);
        response->printf("%s",Alp_Value);
        switch (Switch[AlpacaData.switches.id].type)
        {
        case 1 ... 2:
          response->print(digitalRead(Switch[AlpacaData.switches.id].pin));
          break;
        case 3:
          response->print(ledcRead(Switch[AlpacaData.switches.id].pwmChannel));
          break;
        case 4:
          response->print(analogRead(Switch[AlpacaData.switches.id].pin));
          break;
        }
        response->print(F("}"));
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/setswitch",                                                 HTTP_PUT, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id > setting.switches.maxSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else if(!AlpacaData.switches.stateExist || AlpacaData.switches.state < 0 || AlpacaData.switches.state > 1){
      response->printf("%s1025,%s\"State value not valid MIN:false MAX:true, %d given\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.state);
    } else if( Switch[AlpacaData.switches.id].CanSet == false){
      response->printf("%s1025,%s\"Switch %d cannot be set\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else if( Switch[AlpacaData.switches.id].type == 2 || Switch[AlpacaData.switches.id].type == 4){
      response->printf("%s1025,%s\"Switch %d is an input, cannot be set\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
        AlpacaNoErrorSchema(response,false);
        switch (Switch[AlpacaData.switches.id].type){
        case 1:
          digitalWrite(Switch[AlpacaData.switches.id].pin, AlpacaData.switches.state);
          break;
        case 3:
          AlpacaData.switches.state ? ledcWrite(Switch[AlpacaData.switches.id].pwmChannel,Switch[AlpacaData.switches.id].maxValue) : ledcWrite(Switch[AlpacaData.switches.id].pwmChannel,Switch[AlpacaData.switches.id].minValue);            
          break;
        }
        response->printf("}");
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/setswitchvalue",                                            HTTP_PUT, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id > setting.switches.maxSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else if(!AlpacaData.switches.intValueExist || AlpacaData.switches.intValue < Switch[AlpacaData.switches.id].minValue || AlpacaData.switches.intValue > Switch[AlpacaData.switches.id].maxValue){
      response->printf("%s1025,%s\"State value not valid MIN:%d MAX:%d, %d given\"}",Alp_ErrN,Alp_ErrM,Switch[AlpacaData.switches.id].minValue,Switch[AlpacaData.switches.id].maxValue,AlpacaData.switches.intValue);
    } else if( Switch[AlpacaData.switches.id].CanSet == false){
      response->printf("%s1025,%s\"Switch %d cannot be set\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else if( Switch[AlpacaData.switches.id].type == 2 || Switch[AlpacaData.switches.id].type == 4){
      response->printf("%s1025,%s\"Switch %d is an input, cannot be set\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
        AlpacaNoErrorSchema(response,false);
        switch (Switch[AlpacaData.switches.id].type){
        case 1:
          digitalWrite(Switch[AlpacaData.switches.id].pin, AlpacaData.switches.intValue);
          break;
        case 3:
          ledcWrite(Switch[AlpacaData.switches.id].pwmChannel,AlpacaData.switches.intValue);            
          break;
        }
        response->printf("}");
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/commandblind",                                           HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/switch/0/commandbool",                                            HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/switch/0/commandstring",                                          HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/switch/0/supportedactions",                                       HTTP_GET, AscomNoActions);

}

#endif

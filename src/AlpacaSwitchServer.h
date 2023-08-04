#ifndef SWITCH_FUNC
#define SWITCH_FUNC

#include "switchhandler.h"

String urlDecoding;
unsigned int prova;
char* command[30];

void ascomSwitchHandler(AsyncWebServerRequest *request){
  int errId = 0;
  int errValue = 0;
  GetAlpArguments(request);
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  urlDecoding = request->url();
  urlDecoding.remove(0,17);

  response->printf("{%s%d,%s%d,",Alp_CliTraId,AlpacaData.clientTransactionID,Alp_SerTraId,AlpacaData.serverTransactionID);

  if (urlDecoding == F("name")) {
    response->print(Alp_NoErrors);
    response->print(F(",\"Value\":\"Tesla Swtich Board\"}"));
    request->send(response);
  } else if (urlDecoding == F("description")) {
    response->print(Alp_NoErrors);
    response->print(F(",\"Value\":\"Tesla Switch Board 2.0.0 ascom alpacha\"}"));
    request->send(response);
  } else if(urlDecoding == F("driverinfo")){
    response->print(Alp_NoErrors);
    response->print(F(",\"Value\":\"One Handler switch implementation\"}"));
    request->send(response);
  } else if (urlDecoding == F("driverversion")) {
    response->print(Alp_NoErrors);
    response->print(F(",\"Value\":\"2.0.0\"}"));
    request->send(response);
  } else if (urlDecoding == F("interfaceversion")) {
    response->print(Alp_NoErrors);
    response->print(F(",\"Value\":1}"));
    request->send(response);
  } else if (urlDecoding == F("connected")) {
    response->print(Alp_NoErrors);
    if(request->method() == HTTP_GET){
      response->print(F(",\"Value\":True}"));
    } else {
      response->print(F("}"));
    }
    request->send(response);
  } else if (urlDecoding == F("action")) {
    response->print(F("\"ErrorNo\":1036,\"ErrorMessage\": \"No actions defined\"}")); 
    request->send(response);
  } else if (urlDecoding == F("maxswitch")) {
    response->print(Alp_NoErrors);
    response->print(F(",\"Value\":"));
    response->print(setting.switches.maxSwitch);
    response->print(F("}"));
    request->send(response);
  } else {
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id > setting.switches.maxSwitch){
      
      response->printf("\"ErrorNumber\":1025,\"ErrorMessage\":\"The Switch %d doesn't exist\"}",AlpacaData.switches.id);
      request->send(response);
    } else {
      if (urlDecoding == F("getswitchname")){
        response->print(Alp_NoErrors);
        response->print(F(",\"Value\":\""));
        response->print(Switch[AlpacaData.switches.id].Name);
        response->print(F("\"}"));
        request->send(response);
      } else if (urlDecoding == F("getswitchdescription")){
        response->print(Alp_NoErrors);
        response->print(F(",\"Value\":\""));
        response->print(Switch[AlpacaData.switches.id].Description);
        response->print(F("\"}"));
        request->send(response);
      } else if (urlDecoding == F("minswitchvalue")){
        response->print(Alp_NoErrors);
        response->print(F(",\"Value\":"));
        response->print(Switch[AlpacaData.switches.id].minValue);
        response->print(F("}"));
        request->send(response);
      } else if (urlDecoding == F("maxswitchvalue")){
        response->print(Alp_NoErrors);
        response->print(F(",\"Value\":"));
        response->print(Switch[AlpacaData.switches.id].maxValue);
        response->print(F("}"));
        request->send(response);
      } else if (urlDecoding == F("switchstep")){
        response->print(Alp_NoErrors);
        response->print(F(",\"Value\":"));
        response->print(Switch[AlpacaData.switches.id].Step);
        response->print(F("}"));
        request->send(response);
      } else if (urlDecoding == F("canwrite")){
        response->print(Alp_NoErrors);
        response->print(F(",\"Value\":"));
        Switch[AlpacaData.switches.id].CanSet ? response->print("true") : response->print("false");
        response->print(F("}"));
        request->send(response);
      } else if (urlDecoding == F("getswitchvalue")){
        response->print(Alp_NoErrors);
        response->print(F(",\"Value\":"));
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
        request->send(response);

      } else if (urlDecoding == F("getswitch")){
        response->print(Alp_NoErrors);
        response->print(F(",\"Value\":"));
        if(Switch[AlpacaData.switches.id].analog == false){
          response->print(digitalRead(Switch[AlpacaData.switches.id].pin));
        }
        response->print(F("}"));
        request->send(response);
      } else if (urlDecoding == F("setswitch")){
        if(AlpacaData.switches.stateExist && Switch[AlpacaData.switches.id].analog == false && (AlpacaData.switches.state == 0 || AlpacaData.switches.state == 1)){
          digitalWrite(Switch[AlpacaData.switches.id].pin,AlpacaData.switches.state);
          response->print(Alp_NoErrors);
          response->print(F("}"));
          request->send(response);
        } else {
          response->printf("\"ErrorNumber\":1025,\"ErrorMessage\":\"Value Outside Range True or False\"}",AlpacaData.switches.id);
          request->send(response);
        }
      } else if (urlDecoding == F("setswitchvalue")){
        if(AlpacaData.switches.intValueExist && AlpacaData.switches.intValue >= Switch[AlpacaData.switches.id].minValue && AlpacaData.switches.intValue <= Switch[AlpacaData.switches.id].maxValue ){
          switch (Switch[AlpacaData.switches.id].type)
          {
          case 1 ... 2:
            digitalWrite(Switch[AlpacaData.switches.id].pin,AlpacaData.switches.intValue);
            break;
          case 3:
            ledcWrite(Switch[AlpacaData.switches.id].pwmChannel,AlpacaData.switches.intValue);
            break;
          }
          response->print(Alp_NoErrors);
          response->print(F("}"));
          request->send(response);
        } else {
          response->printf("\"ErrorNumber\":1025,\"ErrorMessage\":\"Value Outside Range MIN: %d or MAX: %d\"}",Switch[AlpacaData.switches.id].minValue,Switch[AlpacaData.switches.id].maxValue);
          request->send(response);
        }
      }
    }

  }
}


void SwitchAlpaca(){

  Alpserver.on("/api/v1/switch/0/name",                                                   HTTP_GET, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/description",                                            HTTP_GET, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/driverinfo",                                             HTTP_GET, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/driverversion",                                          HTTP_GET, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/interfaceversion",                                       HTTP_GET, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/connected",                                              HTTP_GET, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/connected",                                              HTTP_PUT, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/action",                                                 HTTP_PUT, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/maxswitch",                                              HTTP_GET, ascomSwitchHandler);

  Alpserver.on("/api/v1/switch/0/getswitchname",                                          HTTP_GET, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/getswitchdescription",                                   HTTP_GET, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/minswitchvalue",                                         HTTP_GET, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/maxswitchvalue",                                         HTTP_GET, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/switchstep",                                             HTTP_GET, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/getswitchvalue",                                         HTTP_GET, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/canwrite",                                               HTTP_GET, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/getswitch",                                              HTTP_GET, ascomSwitchHandler);

  Alpserver.on("/api/v1/switch/0/setswitch",                                              HTTP_PUT, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/setswitchvalue",                                         HTTP_PUT, ascomSwitchHandler);
  Alpserver.on("/api/v1/switch/0/setswitchname",                                          HTTP_PUT, ascomSwitchHandler);

  Alpserver.on("/api/v1/switch/0/commandblind",                                           HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/switch/0/commandbool",                                            HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/switch/0/commandstring",                                          HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/switch/0/supportedactions",                                       HTTP_GET, AscomNoActions);

}

#endif

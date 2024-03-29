#ifndef COVER_CALIB
#define COVER_CALIB

void CoverCalibratorSetup()
{
  ledcSetup(0, 5000, 13);
  if(setting.coverCalibration.pin){  ledcAttachPin(setting.coverCalibration.pin, 0); }
  Serial.println(setting.coverCalibration.pin);
}

void CoverCalibratorServer()
{

  Alpserver.on("/api/v1/covercalibrator/0/brightness", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":"));
    response->print(ledcRead(0));
    response->print(F("}"));
    request->send(response);
  });

  Alpserver.on("/api/v1/covercalibrator/0/calibratorstate", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":3}"));
    request->send(response); 
  });

  Alpserver.on("/api/v1/covercalibrator/0/coverstate", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":3}"));
    request->send(response); 
  });

  Alpserver.on("/api/v1/covercalibrator/0/maxbrightness", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":8192}"));
    request->send(response);
  });

  Alpserver.on("/api/v1/covercalibrator/0/calibratoroff", HTTP_PUT, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    ledcWrite(0,0);
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response,false);
    response->print(F("}"));
    request->send(response); 
  });

  Alpserver.on("/api/v1/covercalibrator/0/calibratoron", HTTP_PUT, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(AlpacaData.coverCalibrator.brightness < 0 || AlpacaData.coverCalibrator.brightness > 8192){
      response->printf("%s1025,%s\"Brightness value exced limit. %d given, MIN:0 MAX:8192\"",Alp_ErrN,Alp_ErrM,AlpacaData.coverCalibrator.brightness);
    } else {
      ledcWrite(0,AlpacaData.coverCalibrator.brightness);
      AlpacaNoErrorSchema(response,false);
    }
    response->print(F("}"));
    request->send(response); 
  });
  
  Alpserver.on("/api/v1/covercalibrator/0/connected", HTTP_GET, [](AsyncWebServerRequest *request){
      GetAlpArguments(request);
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      AlpacaHeaderSchema(response,AlpacaData);
      AlpacaNoErrorSchema(response);
      response->print(F("\"Value\":true}"));
      request->send(response); 
  });

  Alpserver.on("/api/v1/covercalibrator/0/connected", HTTP_PUT, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response,false);
    response->print(F("}"));
    request->send(response);
  });

  Alpserver.on("/api/v1/covercalibrator/0/description", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":\"StefanoTesla CoverCalibrator\"}"));
    request->send(response); 
  });

  Alpserver.on("/api/v1/covercalibrator/0/driverinfo", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":\"StefanoTesla CoverCalibrator response on the fly\"}"));
    request->send(response);
  });

  Alpserver.on("/api/v1/covercalibrator/0/driverversion", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":\"2.0.0\"}"));
    request->send(response);
  });

  Alpserver.on("/api/v1/covercalibrator/0/interfaceversion", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":1}"));
    request->send(response); 
  });

  Alpserver.on("/api/v1/covercalibrator/0/name", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":\"StefanoTesla Cover Calibrator\"}"));
    request->send(response);
  });

  Alpserver.on("/api/v1/covercalibrator/0/action", HTTP_PUT, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    response->printf("%s1036,%s\"No Actions defined\"}",Alp_ErrN,Alp_ErrM);
    request->send(response);
  });

  Alpserver.on("/api/v1/covercalibrator/0/closecover", HTTP_PUT, AscomPropertyNotImplemented);
  Alpserver.on("/api/v1/covercalibrator/0/haltcover", HTTP_PUT, AscomPropertyNotImplemented);
  Alpserver.on("/api/v1/covercalibrator/0/opencover", HTTP_PUT, AscomPropertyNotImplemented);
  Alpserver.on("/api/v1/covercalibrator/0/commandblind", HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/covercalibrator/0/commandbool", HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/covercalibrator/0/commandstring", HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/covercalibrator/0/supportedactions", HTTP_GET, AscomNoActions);
}

#endif

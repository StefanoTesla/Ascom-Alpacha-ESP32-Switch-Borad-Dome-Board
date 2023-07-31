#ifndef MANAGE_FUNC
#define MANAGE_FUNC
unsigned int ManClientTransactionID;
String JManAnsw;
StaticJsonDocument<128> AplacaError;


void GetAlpArguments(AsyncWebServerRequest *request ) {
  AlpacaData.switches.idExist = false;
  AlpacaData.switches.intValueExist = false;
  AlpacaData.switches.nameExist = false;
  AlpacaData.switches.stateExist = false;
  AlpacaData.switches.intValueExist = false;
  AlpacaData.switches.nameExist = false;
  AlpacaData.switches.stateExist = false;
  AlpacaData.clientID = 0;
  AlpacaData.clientTransactionID = 0;
  AlpacaData.boConnect = false;
  AlpacaData.switches.id = -1;
  AlpacaData.switches.state = false;
  AlpacaData.switches.intValue = -1;
  int paramsNr = request->params();
  String parameter;
  AlpacaData.serverTransitionID++;
  for (int i = 0; i < paramsNr; i++) {
    AsyncWebParameter* p = request->getParam(i);
    parameter = p->name();
    parameter.toLowerCase();
    if (parameter == "clientid") {
      AlpacaData.clientID = p->value().toInt();
    }
    if (parameter == "clienttransactionid") {
      AlpacaData.clientTransactionID = p->value().toInt();
    }
    if (parameter == "connected") {
      String aa;
      aa = p->value();
      aa.toLowerCase();      
      if ( aa == "true"){
        AlpacaData.boConnect = true;
      } else {
        AlpacaData.boConnect = false;
      }
    }
    if (parameter == "id") {
      AlpacaData.switches.idExist = true;
      AlpacaData.switches.id = p->value().toInt();
    }
    if (parameter == "value") {
      AlpacaData.switches.intValueExist = true;
      AlpacaData.switches.intValue = p->value().toInt();
    }
    if (parameter == "name") {
      AlpacaData.switches.nameExist = true;
      AlpacaData.switches.name = p->value();
    }
    if (parameter == "state") {
      AlpacaData.switches.stateExist = true;
      AlpacaData.switches.state = p->value().toInt();
    }    
    
  }
}


void ManApiversion(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(3);
  DynamicJsonDocument JMan(capacity);
  JsonArray Value = JMan.createNestedArray("Value");
  Value.add(1);
  JMan["ClientTransactionID"] = AlpacaData.clientTransactionID;
  JMan["ServerTransactionID"] = AlpacaData.serverTransitionID;
  JManAnsw = "";
  serializeJson(JMan, JManAnsw);
  request->send(200, "application/json" , JManAnsw);
  Serial.println("valore api");
  JMan.clear();
}

void ManDescription(AsyncWebServerRequest *request) {
  const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4);
  DynamicJsonDocument JMan(capacity);

  JsonObject Value = JMan.createNestedObject("Value");
  Value["ServerName"] = "Tesla Alpaca Device";
  Value["Manufacturer"] = "The Big Tesla Company";
  Value["ManufacturerVersion"] = "v2.0.0-alpha";
  Value["Location"] = "Cerreto Guidi, IT";
  if (request->hasParam("ClientTransactionID"))    {
    ManClientTransactionID = request->getParam("ClientTransactionID")->value().toInt();
    JMan["ClientTransactionID"] = ManClientTransactionID;
  }
  JMan["ServerTransactionID"] = AlpacaData.serverTransitionID;
  JManAnsw = "";
  serializeJson(JMan, JManAnsw);
  request->send(200, "application/json" , JManAnsw);
  JMan.clear();
}

void ManConfigureDev(AsyncWebServerRequest *request) {
  const size_t capacity = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3) + 2 * JSON_OBJECT_SIZE(4);
  DynamicJsonDocument doc(capacity);
  GetAlpArguments(request);
  
  JsonArray Value = doc.createNestedArray("Value");

  JsonObject Dome = Value.createNestedObject();
  Dome["DeviceName"] = "Tesla Dome";
  Dome["DeviceType"] = "Dome";
  Dome["DeviceNumber"] = 0;
  Dome["UniqueID"] = "277C652F-2AA9-4E86-A6A6-9230C42876FA";

  JsonObject Switch = Value.createNestedObject();
  Switch["DeviceName"] = "Tesla Switch";
  Switch["DeviceType"] = "Switch";
  Switch["DeviceNumber"] = 0;
  Switch["UniqueID"] = "69D8C73A-AEC8-4B21-8332-F1497A90100A";
  doc["ClientTransactionID"] = AlpacaData.clientTransactionID;
  doc["ServerTransactionID"] = AlpacaData.serverTransitionID;
  JManAnsw="";
  serializeJson(doc, JManAnsw);
  request->send(200, "application/json", JManAnsw);
}

void AscomMethodNotImplemented(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AplacaError["ClientTransactionID"] = AlpacaData.clientTransactionID;
  AplacaError["ServerTransactionID"] = AlpacaData.serverTransitionID;
  AplacaError["ErrorNumber"] = 1024;
  AplacaError["ErrorMessage"] = "Method not implemented";
  JManAnsw="";
  serializeJson(AplacaError, JManAnsw);
  AplacaError.clear();
  request->send(200, "application/json", JManAnsw);
}

void AscomPropertyNotImplemented(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AplacaError["ClientTransactionID"] = AlpacaData.clientTransactionID;
  AplacaError["ServerTransactionID"] = AlpacaData.serverTransitionID;
  AplacaError["ErrorNumber"] = 1024;
  AplacaError["ErrorMessage"] = "Property not implemented";
  JManAnsw="";
  serializeJson(AplacaError, JManAnsw);
  AplacaError.clear();
  request->send(200, "application/json", JManAnsw);
}

#endif

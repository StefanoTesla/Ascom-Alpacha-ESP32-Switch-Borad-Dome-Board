#ifndef MANAGE_FUNC
#define MANAGE_FUNC
unsigned int ManClientTransactionID;
String JManAnsw;
StaticJsonDocument<128> AplacaError;


void GetAlpArguments(AsyncWebServerRequest *request ) {
  Serial.println(request->url());
  ClientID = 0;
  ClientTransactionID = 0;
  boConnect = false;
  Alp_Int_Value = 0;
  Alp_Int_ID = -1;
  Alp_idcheck = false;
  Alp_value_ex = true;
  int paramsNr = request->params();
  String parameter;
  AlpServerID++;
  for (int i = 0; i < paramsNr; i++) {
    AsyncWebParameter* p = request->getParam(i);
    parameter = p->name();
    parameter.toLowerCase();
    if (parameter == "clientid") {
      ClientID = p->value().toInt();
    }
    if (parameter == "clienttransactionid") {
      ClientTransactionID = p->value().toInt();
    }
    if (parameter == "connected") {
      String aa;
      aa = p->value();
      aa.toLowerCase();      
      if ( aa == "true"){
        boConnect = true;
      } else {
        boConnect = false;
      }
    }
    if (parameter == "id") {
      Alp_Int_ID = p->value().toInt();
      Alp_Int_ID >= 0 && Alp_Int_ID < _MAX_SWTICH_ID_ ? Alp_idcheck = true : Alp_idcheck = false;
    }
    if (parameter == "value") {
      Alp_Int_Value = p->value().toInt();
      Alp_value_ex = true;
    }
    if (parameter == "name") {
      Alp_Name = p->value();
    }
    if (parameter == "state") {
      Alp_state = p->value().toInt();
    }    
    
  }
}


void ManApiversion(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(3);
  DynamicJsonDocument JMan(capacity);
  JsonArray Value = JMan.createNestedArray("Value");
  Value.add(1);
  JMan["ClientTransactionID"] = ClientTransactionID;
  JMan["ServerTransactionID"] = AlpServerID;
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
  Value["ManufacturerVersion"] = "v1.2.2";
  Value["Location"] = "Cerreto Guidi, IT";
  if (request->hasParam("ClientTransactionID"))    {
    ManClientTransactionID = request->getParam("ClientTransactionID")->value().toInt();
    JMan["ClientTransactionID"] = ManClientTransactionID;
  }
  JMan["ServerTransactionID"] = AlpServerID;
  JManAnsw = "";
  serializeJson(JMan, JManAnsw);
  request->send(200, "application/json" , JManAnsw);
  JMan.clear();
  Serial.println("descrizione");
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
  doc["ClientTransactionID"] = ClientTransactionID;
  AlpServerID++;
  doc["ServerTransactionID"] = AlpServerID;
  JManAnsw="";
  serializeJson(doc, JManAnsw);
  request->send(200, "application/json", JManAnsw);
}

void AscomMethodNotImplemented(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AplacaError["ClientTransactionID"] = ClientTransactionID;
  AplacaError["ServerTransactionID"] = AlpServerID;
  AplacaError["ErrorNumber"] = 1024;
  AplacaError["ErrorMessage"] = "Method not implemented";
  JManAnsw="";
  serializeJson(AplacaError, JManAnsw);
  AplacaError.clear();
  request->send(200, "application/json", JManAnsw);
}

void AscomPropertyNotImplemented(AsyncWebServerRequest *request) {
  GetAlpArguments(request);
  AplacaError["ClientTransactionID"] = ClientTransactionID;
  AplacaError["ServerTransactionID"] = AlpServerID;
  AplacaError["ErrorNumber"] = 1024;
  AplacaError["ErrorMessage"] = "Property not implemented";
  JManAnsw="";
  serializeJson(AplacaError, JManAnsw);
  AplacaError.clear();
  request->send(200, "application/json", JManAnsw);
}

#endif

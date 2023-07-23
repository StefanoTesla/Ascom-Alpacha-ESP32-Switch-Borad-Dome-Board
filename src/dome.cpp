#include <ArduinoJson.h>
#include <WiFi.h>
#include "AsyncJson.h"
#include "AsyncUDP.h"
#include "HTTPClient.h"
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <stdint.h>
#include "SPIFFS.h"
#include "header.h"
#include "alpacamanagefunction.h"
#include <AsyncElegantOTA.h>

AsyncWebServer server(80);
AsyncWebServer Alpserver(4567);
#include "AlpacaDomeServer.h"
#include "AlpacaSwitchServer.h"
unsigned long previousMillis = 0;
unsigned long interval = 30000;
DNSServer dns;
///////enter your sensitive data in the Secret tab/arduino_secrets.h

unsigned const int localPort = 32227;  //The Alpaca Discovery test port
unsigned const int alpacaPort = 4567;  //The (fake) port that the Alpaca API would be available on


AsyncUDP udp;

void notFound(AsyncWebServerRequest *request) {
  request->send(400, "text/plain", "Not found");
  Serial.println("400");
  Serial.println(request->url());
}

void ServerNotFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
  Serial.println("404");
  Serial.println(request->url());
}

void setup()
{
  Serial.begin(115200);
  AlpServerID = 0;
  pinMode(2, OUTPUT);
/* reading configuration from file */
  if (!SPIFFS.begin()) { Serial.println("An Error has occurred while mounting SPIFFS"); return; }
  if (!SPIFFS.exists("/setup.txt")) { StoreDataFileSPIFFS(); } else { ReadDataFileSPIFFS(); }
 
  switchsetup();
  domehandlersetup();
  
  JDomeAnsw.reserve(300);
  Serial.println("Listening for discovery requests...");
  AsyncWiFiManager wifiManager(&server,&dns);
  wifiManager.autoConnect("TeslaBoard");
  Serial.print("Connect with IP Address: ");
  Serial.println(WiFi.localIP());


  if (udp.listen(32227))
  {
    Serial.println("Listening for discovery requests...");
    udp.onPacket([](AsyncUDPPacket packet) {
      if (packet.length() < 16)
      {
        return;
      }
      //Compare packet to Alpaca Discovery string
      if (strncmp("alpacadiscovery1", (char *)packet.data(), 16) != 0)
      {
        return;
      }
      packet.printf("{\"alpacaport\": %d}", alpacaPort);
    });
  }

  Alpserver.onNotFound(notFound);
  /*** MANAGE AREA ***/
  Alpserver.on("/management/apiversions",                                                 HTTP_GET, ManApiversion);
  Alpserver.on("/management/v1/description",                                              HTTP_GET, ManDescription);
  Alpserver.on("/management/v1/configureddevices",                                        HTTP_GET, ManConfigureDev);

  AlpacaDome();
  SwitchAlpaca();


  server.onNotFound(notFound);

  server.on("/getdomestate",              HTTP_GET, DomWSState);
  server.on("/getswitchname",             HTTP_GET, SwtSWName);
  server.on("/getswitchstate",            HTTP_GET, [](AsyncWebServerRequest *request) {
    int i;
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    response->print("{ \"State\": [");

    for (i=0;i<_MAX_SWTICH_ID_;i++){
        Switch[i].analog ? response->printf("%d",Switch[i].anaValue) : response->printf("%d",digitalRead(Switch[i].pin));
        if (i != _MAX_SWTICH_ID_ -1){
          response->printf(", ");
        }
    }
    response->print("]}");
    request->send(response);
});

  server.on("/domecmd",              HTTP_POST, [](AsyncWebServerRequest *request) {
    int cmd = -1;
    if (request->hasParam("cmd")){
      cmd = request->getParam("cmd")->value().toInt();
    }
    if (cmd <1){
      ShutterCommand = CmdHalt;
      ShCyIndex = 100;
      request->send(200, "text/html", "HALT");

    } else {

    if (ShutterCommand == Idle){
      if (cmd ==1){
          if(ShutterState != ShOpen){
            ShutterCommand = CmdOpen;
            request->send(200, "text/html", "ok");
          } else { request->send(200, "text/html", "Shutter is Already Open"); }
      } else if (cmd == 2){
          if(ShutterState != ShClose){
            ShutterCommand = CmdClose;
            request->send(200, "text/html", "ok");
          } else { request->send(200, "text/html", "Shutter is Already Closed"); }}
    } else { request->send(200, "text/html", "Shutter is already moving"); }
    
    }
});

  server.on("/setsw",              HTTP_POST, [](AsyncWebServerRequest *request) {
    int sw = -1;
    int value = -1;
    if (request->hasParam("sw")){ sw = request->getParam("sw")->value().toInt();
    } else { request->send(200, "text/html", "No switch selected");
      return;
    }
    if (request->hasParam("value")){ value = request->getParam("value")->value().toInt();
    } else { request->send(200, "text/html", "No value passed");
      return;
    }
    if (sw >= _MAX_SWTICH_ID_){ request->send(200, "text/html", "Switch ID Out of range"); return;}
    if (!Switch[sw].CanSet){ request->send(200, "text/html", "Switch cannot be setted"); return;}
    if (value < Switch[sw].minValue || value > Switch[sw].maxValue){ request->send(200, "text/html", "Value outside limits"); return;}

    if (Switch[sw].analog){
      Switch[sw].anaValue = value;
      ledcWrite(Switch[sw].pwmChannel, Switch[sw].anaValue);
    } else {
          value == 1 ? digitalWrite(Switch[sw].pin, HIGH) : digitalWrite(Switch[sw].pin, LOW);
    }
    request->send(200, "text/html", "ok");
   
});

  AsyncCallbackJsonWebHandler *domehandler = new AsyncCallbackJsonWebHandler("/storedomedata", [](AsyncWebServerRequest * request, JsonVariant & json) {
    const size_t capacity = JSON_OBJECT_SIZE(200);
    DynamicJsonDocument doc(capacity);
    if (json.is<JsonArray>())
    {
      doc = json.as<JsonArray>();
    }
    else if (json.is<JsonObject>())
    {
      doc = json.as<JsonObject>();
    }
    MovingTimeOut = doc["dometmout"];

    request->send(200);
    StoreData = true;
  });
  server.addHandler(domehandler);


 AsyncCallbackJsonWebHandler *switchhandler = new AsyncCallbackJsonWebHandler("/storeswdata", [](AsyncWebServerRequest * request, JsonVariant & json) {
  StaticJsonDocument<1000> data;
  int i=0;
  if (json.is<JsonArray>())
  {
    data = json.as<JsonArray>();
  }
  else if (json.is<JsonObject>())
  {
    data = json.as<JsonObject>();
  }

  for (JsonObject elem : data["Switch"][0].as<JsonArray>()) {

  const char* name = elem["name"]; // "Switch 1", "Switch 2", "Switch 3", "Switch 4", "Switch 5", "Switch ...
  const char* description = elem["description"]; // "Switch 1", "Switch 2", "Switch 3", "Switch 4", ...
  Switch[i].Name = name;
  Switch[i].Description = description;
  i++;
  }

  request->send(200);
  StoreData = true;
  });
  server.addHandler(switchhandler);

  /** END COMMON OPERATION **/
  server.onNotFound(notFound);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/dome", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/dome.html", "text/html");
  });

  server.on("/switch", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/switch.html", "text/html");
  });

  server.on("/swsetup", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/switchsetup.html", "text/html");
  });


  server.on("/setup.txt", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/setup.txt", "text/plain");
  });

  server.serveStatic("/assets/", SPIFFS, "/assets/").setCacheControl("max-age=31536000");

  /** END SWITCH SPECIFIC METHODS **/
  Alpserver.begin();
  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
}

void loop()
{
  domehandlerloop();
  if (StoreData == true) {
    StoreDataFileSPIFFS();
  }

  unsigned long currentMillis = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }

  if(WiFi.status() == WL_CONNECTED ){
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }
}

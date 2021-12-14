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


AsyncWebServer server(80);
AsyncWebServer Alpserver(4567);
#include "AlpacaDomeServer.h"
#include "AlpacaSwitchServer.h"

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

void setup()
{
  Serial.begin(115200);
  AlpServerID = 0;

/* reading configuration from file */
  if (!SPIFFS.begin()) { Serial.println("An Error has occurred while mounting SPIFFS"); return; }
  if (!SPIFFS.exists("/setup.txt")) { StoreDataFileSPIFFS(); } else { ReadDataFileSPIFFS(); }
 
  domehandlersetup();
  switchsetup();

  JDomeAnsw.reserve(300);
  
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

  /** END COMMON OPERATION **/
  server.serveStatic("/", SPIFFS, "/").setCacheControl("max-age=31536000");
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

  server.on("/getdomestate",              HTTP_GET, DomWSState);
  server.on("/getswitchname",             HTTP_GET, SwtSWName);
  server.on("/getswitchstate",            HTTP_GET, SwtSWState);  

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

  /** END SWITCH SPECIFIC METHODS **/
  Alpserver.begin();
  server.begin();
}

void loop()
{
  domehandlerloop();
  if (StoreData == true) {
    StoreDataFileSPIFFS();
  }

}

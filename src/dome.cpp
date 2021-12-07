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
#include "alpacadomefunction.h"
#include "alpacaswitchfunction.h"


AsyncWebServer server(80);
AsyncWebServer Alpserver(4567);
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

  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  if (!SPIFFS.exists("/setup.txt")) {
    StoreDataFileSPIFFS();
  } else {
    ReadDataFileSPIFFS();
  }
 
  domehandlersetup();
  switchsetup();

  AsyncWiFiManager wifiManager(&server,&dns);
  wifiManager.autoConnect("DomeBoard");
  Serial.print("Connect with IP Address: ");
  Serial.println(WiFi.localIP());


  if (udp.listen(32227))
  {
    Serial.println("Listening for discovery requests...");
    udp.onPacket([](AsyncUDPPacket packet) {
      Serial.print("Received UDP Packet of Type: ");
      Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
      Serial.print(", From: ");
      Serial.print(packet.remoteIP());
      Serial.print(":");
      Serial.print(packet.remotePort());
      Serial.print(", To: ");
      Serial.print(packet.localIP());
      Serial.print(":");
      Serial.print(packet.localPort());
      Serial.print(", Length: ");
      Serial.print(packet.length());
      Serial.print(", Data: ");
      Serial.write(packet.data(), packet.length());
      Serial.println();
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
  /** END MANGED AREA **/

  /** END COMMON OPERATION **/

  /** DOME SPECIFIC METHODS **/

  Alpserver.on("/api/v1/dome/0/canfindhome",                                              HTTP_GET, DomAlpCanFindHome);
  Alpserver.on("/api/v1/dome/0/canpark",                                                  HTTP_GET, DomAlpCanPark);
  Alpserver.on("/api/v1/dome/0/cansetaltitude",                                           HTTP_GET, DomAlpCanSetAlt);
  Alpserver.on("/api/v1/dome/0/cansetazimuth",                                            HTTP_GET, DomAlpCanSetAzi);
  Alpserver.on("/api/v1/dome/0/cansetpark",                                               HTTP_GET, DomAlpCanSetPark);
  Alpserver.on("/api/v1/dome/0/cansetshutter",                                            HTTP_GET, DomAlpCanSetShutter);
  Alpserver.on("/api/v1/dome/0/canslave",                                                 HTTP_GET, DomAlpCanSlave);
  Alpserver.on("/api/v1/dome/0/cansyncazimuth",                                           HTTP_GET, DomAlpCanSyncAzi);
  Alpserver.on("/api/v1/dome/0/shutterstatus",                                            HTTP_GET, DomAlpShutterState);
  Alpserver.on("/api/v1/dome/0/slaved",                                                   HTTP_GET, DomAlpSlaved);
  Alpserver.on("/api/v1/dome/0/slaved",                                                   HTTP_PUT, DomAlpSlavedPut);
  Alpserver.on("/api/v1/dome/0/slewing",                                                  HTTP_GET, DomAlpSlewing);
  Alpserver.on("/api/v1/dome/0/abortslew",                                                HTTP_PUT, DomAlpAbortSlew);
  Alpserver.on("/api/v1/dome/0/closeshutter",                                             HTTP_PUT, DomAlpCloseShutter);
  Alpserver.on("/api/v1/dome/0/openshutter",                                              HTTP_PUT, DomAlpOpenShutter);
  
  /** NOT HANDLED OPERATIONS **/
  Alpserver.on("/api/v1/dome/0/altitude",                                                 HTTP_GET, AscomPropertyNotImplemented);
  Alpserver.on("/api/v1/dome/0/athome",                                                   HTTP_GET, AscomPropertyNotImplemented);
  Alpserver.on("/api/v1/dome/0/atpark",                                                   HTTP_GET, AscomPropertyNotImplemented);
  Alpserver.on("/api/v1/dome/0/azimuth",                                                  HTTP_GET, AscomPropertyNotImplemented);
  Alpserver.on("/api/v1/dome/0/findhome",                                                 HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/dome/0/park",                                                     HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/dome/0/setpark",                                                  HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/dome/0/slewtoaltitude",                                           HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/dome/0/slewtoazimuth",                                            HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/dome/0/synctoazimuth",                                            HTTP_PUT, AscomMethodNotImplemented);
  /** END DOME SPECIFIC METHODS **/



  /** SWITCH SPECIFIC METHODS **/

  Alpserver.on("/api/v1/switch/0/maxswitch",                                              HTTP_GET, SwtAlpMaxSwitch);
  Alpserver.on("/api/v1/switch/0/canwrite",                                               HTTP_GET, SwtAlpCanWrite);
  Alpserver.on("/api/v1/switch/0/getswitch",                                              HTTP_GET, SwtAlpGetSwitch);
  Alpserver.on("/api/v1/switch/0/getswitchdescription",                                   HTTP_GET, SwtAlpSwtDesc);
  Alpserver.on("/api/v1/switch/0/getswitchname",                                          HTTP_GET, SwtAlpSwtName);
  Alpserver.on("/api/v1/switch/0/getswitchvalue",                                         HTTP_GET, SwtAlpGetSwtValue);
  Alpserver.on("/api/v1/switch/0/minswitchvalue",                                         HTTP_GET, SwtAlpMinSwtValue);
  Alpserver.on("/api/v1/switch/0/maxswitchvalue",                                         HTTP_GET, SwtAlpMaxSwtValue);
  Alpserver.on("/api/v1/switch/0/setswitch",                                              HTTP_PUT, SwtAlpSetSwt);
  Alpserver.on("/api/v1/switch/0/setswitchname",                                          HTTP_PUT, SwtAlpSetSwtName);
  Alpserver.on("/api/v1/switch/0/setswitchvalue",                                         HTTP_PUT, SwtAlpSetSwtValue);
  Alpserver.on("/api/v1/switch/0/switchstep",                                             HTTP_GET, SwtAlpSwtStep);


  /** COMMON OPERATION **/

  Alpserver.on("api/v1/dome/0/action",                                                    HTTP_PUT, DomAlpCmdAction);
  Alpserver.on("api/v1/dome/0/commandblind",                                              HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("api/v1/dome/0/commandbool",                                               HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("api/v1/dome/0/commandstring",                                             HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/dome/0/connected",                                                HTTP_GET, DomAlpConnected);
  Alpserver.on("/api/v1/dome/0/connected",                                                HTTP_PUT, DomAlpConnectedPut);
  Alpserver.on("/api/v1/dome/0/description",                                              HTTP_GET, DomAlpDescription);
  Alpserver.on("/api/v1/dome/0/driverinfo",                                               HTTP_GET, DomAlpDriverInfo);
  Alpserver.on("/api/v1/dome/0/driverversion",                                            HTTP_GET, DomAlpDriverVer);
  Alpserver.on("/api/v1/dome/0/interfaceversion",                                         HTTP_GET, DomAlpIntVer);
  Alpserver.on("/api/v1/dome/0/name",                                                     HTTP_GET, DomAlpName);
  Alpserver.on("/api/v1/dome/0/supportedactions",                                         HTTP_GET, AscomMethodNotImplemented);
  
  Alpserver.on("/api/v1/switch/0/action",                                                 HTTP_PUT, SwtAlpCmdAction);
  Alpserver.on("/api/v1/switch/0/commandblind",                                           HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/switch/0/commandbool",                                            HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/switch/0/commandstring",                                          HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/switch/0/connected",                                              HTTP_GET, SwtAlpConnected);
  Alpserver.on("/api/v1/switch/0/connected",                                              HTTP_PUT, SwtAlpConnectedPut);
  Alpserver.on("/api/v1/switch/0/description",                                            HTTP_GET, SwtAlpDescription);
  Alpserver.on("/api/v1/switch/0/driverinfo",                                             HTTP_GET, SwtAlpDriverInfo);
  Alpserver.on("/api/v1/switch/0/driverversion",                                          HTTP_GET, SwtAlpDriverVer);
  Alpserver.on("/api/v1/switch/0/interfaceversion",                                       HTTP_GET, SwtAlpIntVer);
  Alpserver.on("/api/v1/switch/0/name",                                                   HTTP_GET, SwtAlpName);
  Alpserver.on("/api/v1/switch/0/supportedactions",                                       HTTP_GET, AscomMethodNotImplemented);

  /** END COMMON OPERATION **/

  server.serveStatic("/", SPIFFS, "/").setCacheControl("max-age=31536000");
  server.onNotFound(notFound);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/setup", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/setup.html", "text/html");
  });

  server.on("/getdomestate",              HTTP_GET, DomWSState);
  server.on("/getswitchname",             HTTP_GET, SwtSWName);
  server.on("/getswitchstate",            HTTP_GET, SwtSWState);
  server.on("/getdomesetup",              HTTP_GET, DomWSSetup);  

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

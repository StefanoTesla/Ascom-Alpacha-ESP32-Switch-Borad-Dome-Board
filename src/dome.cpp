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
#include "browserServer.h"
#include "fileHandler.h"

unsigned long previousMillis = 0;
unsigned long interval = 30000;
DNSServer dns;
///////enter your sensitive data in the Secret tab/arduino_secrets.h

unsigned const int localPort = 32227;  //The Alpaca Discovery test port
unsigned const int alpacaPort = 4567;  //The (fake) port that the Alpaca API would be available on


AsyncUDP udp;



void ServerNotFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
  Serial.println("404");
  Serial.println(request->url());
}

void setup()
{
  Serial.begin(115200);
  AlpacaData.AlpServerID = 0;
  pinMode(2, OUTPUT);
/* reading configuration from file */
  if (!SPIFFS.begin()) { Serial.println("An Error has occurred while mounting SPIFFS"); return; }
  readDomeConfig();
  readSwitchConfig();
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
  browserServer();

  /** END SWITCH SPECIFIC METHODS **/
  Alpserver.begin();
  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
}

void loop()
{
  fileLoop();
  domehandlerloop();
  if (StoreData == true) {
    StoreDataFileSPIFFS();
  }

  unsigned long currentMillis = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
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

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
#include <AsyncElegantOTA.h>

AsyncWebServer server(80);
AsyncWebServer Alpserver(4567);

unsigned long previousWifiMillis = 0;
unsigned long previousUpTimeWifi = 0;
unsigned long previousUpTimeESP32 = 0;
unsigned long upTimeInterval = 60000;
unsigned long wifiInterval = 30000;
unsigned long upTimeWiFi = 0;
unsigned long upTimeESP32 = 0;

#include "AlpacaManageFunction.h"
#include "AlpacaDomeServer.h"
#include "AlpacaSwitchServer.h"
#include "AlpacaCoverCalibratorServer.h"
#include "browserServer.h"
#include "fileHandler.h"
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
  AlpacaData.serverTransactionID = 0;
/* reading configuration from file */
  if (!SPIFFS.begin()) { Serial.println("An Error has occurred while mounting SPIFFS"); return; }
  readDomeConfig();
  domeSetup();
  readCoverCalibConfig();
  CoverCalibratorSetup();
  readSwitchConfig();
  switchSetup();
 
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


  AlpacaManager();
  DomeAlpaca();
  SwitchAlpaca();
  CoverCalibratorServer();
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


  unsigned long currentMillis = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousWifiMillis >=wifiInterval)) {
    WiFi.disconnect();
    WiFi.reconnect();
    previousWifiMillis = currentMillis;
    upTimeWiFi = 0;
  }



  //one minute clock
  if (currentMillis - previousUpTimeESP32 > upTimeInterval){
    upTimeESP32 +=1;
    if(WiFi.status() == WL_CONNECTED ){
      upTimeWiFi +=1;
    }
    previousUpTimeESP32 = currentMillis;
  } 
  
}

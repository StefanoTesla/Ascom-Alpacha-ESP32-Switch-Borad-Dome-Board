bool StoreData;

/* ALPACA COMMON DATA */
uint32_t ClientTransactionID;
uint32_t AlpServerID = 0;
uint32_t ClientID;
int Alp_Int_ID;               /* used for switch ID */
bool Alp_state;               /* used for setswitch */
int Alp_Int_Value;            /* used for setswitchvalue */
String Alp_Name;              /* used for set switch name */
bool Alp_idcheck;
bool Alp_value_ex;
bool boConnect;
/*END ALPACA COMMON DATA */

/**DOME DATA**/
unsigned int LastDomeCommand =0;
enum ShInEnum {
  ShInNoOne,
  ShOnlyClose,
  ShOnlyOpen,
  ShInAll,
};
enum ShStEnum {
  ShOpen,
  ShClose,
  ShOpening,
  ShClosing,
  ShError
};
enum ShCmdEnum {
  Idle,
  CmdOpen,
  CmdClose,
  CmdHalt
};

ShCmdEnum ShutterCommand;
ShStEnum ShutterState;
ShInEnum ShutterInputState;
unsigned long MovingTimeOut = 20;
/** END DOME DATA **/


struct SwtichStruct
{
  String Name;
  String Description;
  int pin;
  int minValue = 0;
  int maxValue = 1;
  bool CanSet = true;
  int Step = 1;
  bool analog = false;
  int anaValue = 0;
  int pwmChannel = -1;
};

#define _MAX_SWTICH_ID_ 17

SwtichStruct Switch[_MAX_SWTICH_ID_];

unsigned int pwmchannles = 0;



void StoreDataFileSPIFFS() {

  const size_t capacity = JSON_OBJECT_SIZE(1024);
  String datasetup;
  DynamicJsonDocument doc(capacity);
  doc["dometime"]   = MovingTimeOut;
  JsonArray Switchjs = doc.createNestedArray("Switch");

    JsonObject Switchjs_0 = Switchjs.createNestedObject();
    Switchjs_0["name"] = Switch[0].Name;
    Switchjs_0["description"] = Switch[0].Description;

    JsonObject Switchjs_1 = Switchjs.createNestedObject();
    Switchjs_1["name"] = Switch[1].Name;
    Switchjs_1["description"] = Switch[1].Description;

    JsonObject Switchjs_2 = Switchjs.createNestedObject();
    Switchjs_2["name"] = Switch[2].Name;
    Switchjs_2["description"] = Switch[2].Description;

    JsonObject Switchjs_3 = Switchjs.createNestedObject();
    Switchjs_3["name"] = Switch[3].Name;
    Switchjs_3["description"] = Switch[3].Description;

    JsonObject Switchjs_4 = Switchjs.createNestedObject();
    Switchjs_4["name"] = Switch[4].Name;
    Switchjs_4["description"] = Switch[4].Description;

    JsonObject Switchjs_5 = Switchjs.createNestedObject();
    Switchjs_5["name"] = Switch[5].Name;
    Switchjs_5["description"] = Switch[5].Description;

  serializeJson(doc, datasetup);

Serial.println(datasetup);

  File file = SPIFFS.open("/setup.txt", FILE_WRITE);
  if (!file) {
    Serial.println("Error writing file");
    return;
  } else {
    file.close();
    SPIFFS.remove("/setup.txt");
  }
  file = SPIFFS.open("/setup.txt", FILE_WRITE);
  
  if (!file) {
    Serial.println("Error writing file");
  }

  int bytesWritten = file.print(datasetup);
 
if (bytesWritten == 0) {
    Serial.println("File write failed");
    return;
} else {
Serial.println("tuttoookkk");

}
 
file.close();

  StoreData = false;
}


void ReadDataFileSPIFFS() {
  const size_t capacity = JSON_OBJECT_SIZE(20) + 500;
  int i=0;
  DynamicJsonDocument doc(capacity);

  File file = SPIFFS.open("/setup.txt", FILE_READ);
  if (!file) {
    Serial.println("ReadDataFileSPIFFS Error reading file");
    return;
  }

  DeserializationError error = deserializeJson(doc, file);
  
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
  } else {
    MovingTimeOut  = doc["dometime"];
    for (JsonObject elem : doc["Switch"].as<JsonArray>()) {

    Switch[i].Name = elem["name"].as<String>(); 
    Switch[i].Description = elem["description"].as<String>();
    Serial.println(Switch[i].Name);
    Serial.println(Switch[i].Description);
    i++;
}


  }
  file.close();
}

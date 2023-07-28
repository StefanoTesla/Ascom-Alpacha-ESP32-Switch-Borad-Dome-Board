struct FileStruct{
  bool saveSwitchSetting;
  bool saveDomeSetting;
  bool restartNeeded;
};

FileStruct FileHandler;

bool StoreData;

/* ALPACA COMMON DATA */
struct AlpacaCommonData{
  uint32_t ClientTransactionID;
  uint32_t AlpServerID = 0;
  uint32_t ClientID;
  int SwitchId;               /* used for switch ID */
  bool SwitchValue;               /* used for setswitch */
  int SwitchIntValue;            /* used for setswitchvalue */
  String SwitchString;              /* used for set switch name */
  bool SwitchIdInRange;
  bool SwitchValueInRange;
  bool boConnect;
};

AlpacaCommonData AlpacaData;

/*END ALPACA COMMON DATA */

/**DOME DATA**/
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

struct DomeStruct{
  ShCmdEnum ShutterCommand;
  ShStEnum ShutterState;
  ShInEnum ShutterInputState;
  int Cycle;
  bool MoveRetry;
  unsigned int LastDomeCommand =0;
  unsigned long LastServerRequest;
};

DomeStruct Dome;

/** END DOME DATA **/

/** SWITCH STRUCT **/
struct SwtichStruct
{
  String Name;
  String Description;
  uint8_t pin = 99;
  int minValue = 0;
  int maxValue = 1;
  bool CanSet = false;
  int Step = 1;
  bool analog = false;
  int anaValue = 0;
  int pwmChannel = -1;
  int type;
};

#define _MAX_SWTICH_ID_ 16

SwtichStruct Switch[_MAX_SWTICH_ID_];

unsigned int pwmchannles = 0;


typedef struct{
  uint8_t pinStart;
  uint8_t pinHalt;
  uint8_t pinOpen;
  uint8_t pinClose;
  unsigned long movingTimeOut = 20;
  bool enAutoClose;
  unsigned long autoCloseTimeOut = 20;
} domeSetting;

typedef struct{
  unsigned int maxSwitch;
} switchSetting;

typedef struct {
  domeSetting dome;
  switchSetting switches;
}boardSetting;

boardSetting setting;


void StoreDataFileSPIFFS() {

  const size_t capacity = JSON_OBJECT_SIZE(1024);
  String datasetup;
  DynamicJsonDocument doc(capacity);
  doc["dometime"]   = setting.dome.movingTimeOut;
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
    setting.dome.movingTimeOut = doc["dometime"];
    for (JsonObject elem : doc["Switch"].as<JsonArray>()) {

    Switch[i].Name = elem["name"].as<String>();
    Switch[i].Description = elem["description"].as<String>();
    i++;
  }

  }
  file.close();
}


struct FileStruct{
  bool saveSwitchSetting = false;
  bool saveDomeSetting = false;
  bool saveCoverCalibratorSetting = false;
  bool restartNeeded = false;
};

FileStruct FileHandler;

typedef struct{
  bool idExist;
  int id;               /* used for switch ID */
  bool stateExist;
  bool state;               /* used for setswitch */
  bool intValueExist;
  int intValue;            /* used for setswitchvalue */
  bool nameExist;
  String name;              /* used for set switch name */
} switchAlpacaParameters;

typedef struct{
  unsigned int brightness;
} coverCalibratorAlpacaParameters;


/* ALPACA COMMON DATA */
struct AlpacaCommonData{
  uint32_t clientTransactionID;
  uint32_t serverTransactionID = 0;
  uint32_t clientID;
  bool boConnect;
  switchAlpacaParameters switches;
  coverCalibratorAlpacaParameters coverCalibrator;
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
  uint8_t pin = 0;
  int minValue = 0;
  int maxValue = 1;
  bool CanSet = false;
  int Step = 1;
  bool analog = false;
  int anaValue = 0;
  int pwmChannel = -1;
  int type;
};

#define _MAX_SWITCH_ID_ 16

SwtichStruct Switch[_MAX_SWITCH_ID_];
/** END SWITCH STRUCT **/
unsigned int pwmchannles = 1;
//channel 0 is reserved to coverCalibrator

/** SETTING STRUCT **/
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

typedef struct{
  unsigned int pin = 0;
} coverCalibrationSetting;


typedef struct {
  domeSetting dome;
  switchSetting switches;
  coverCalibrationSetting coverCalibration;
}boardSetting;

boardSetting setting;
/**END SETTING STRUCT **/


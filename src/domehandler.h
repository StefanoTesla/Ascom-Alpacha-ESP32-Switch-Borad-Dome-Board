#ifndef DOME_HAND
#define DOME_HAND

#define SHUTTER_OPEN_INPUT    13
#define SHUTTER_CLOSE_INPUT   12
#define SHUTTER_CMD_OUTPUT    2
#define SHUTTER_HALT_OUTPUT   5

unsigned long onesecack;
unsigned long ShMoveTimeOut;
unsigned long ShMoveTimeOutAck;
int ShCyIndex = 0;
bool MoveRetry;
bool onesecclock;
int OldShCyIndex;
void domehandlersetup() {
  pinMode(SHUTTER_CMD_OUTPUT, OUTPUT);
  pinMode(SHUTTER_HALT_OUTPUT, OUTPUT);
  pinMode(SHUTTER_OPEN_INPUT, INPUT);
  pinMode(SHUTTER_CLOSE_INPUT, INPUT);
}


void domeInputState(){

    // I used enum for input state for making the cycle code more clean
    if (digitalRead(SHUTTER_CLOSE_INPUT) == HIGH && digitalRead(SHUTTER_OPEN_INPUT) == LOW) {
      ShutterInputState = ShOnlyClose;
    }
    if ( digitalRead(SHUTTER_CLOSE_INPUT) == LOW && digitalRead(SHUTTER_OPEN_INPUT) == HIGH) {
      ShutterInputState = ShOnlyOpen;
    }
    if ( digitalRead(SHUTTER_OPEN_INPUT) == HIGH && digitalRead(SHUTTER_CLOSE_INPUT) == HIGH) {
      ShutterInputState = ShInAll;
    }
    if ( digitalRead(SHUTTER_OPEN_INPUT) == LOW && digitalRead(SHUTTER_CLOSE_INPUT) == LOW) {
      ShutterInputState = ShInNoOne;
    }
}


void domehandlerloop() {
  ShMoveTimeOut = MovingTimeOut *1000;
  domeInputState();

if (ShCyIndex != OldShCyIndex){
  Serial.println(ShCyIndex);
  OldShCyIndex=ShCyIndex;
}
  
  //Ciclo apertura/chiusura shutter

  // TIMEOUT MOVIMENTAZIONE
  if (ShCyIndex >= 11 && ShCyIndex <= 12) {
    if ((millis() - ShMoveTimeOutAck) > ShMoveTimeOut) { //input error I wait 10 sec. before done command
      ShCyIndex = 100;  //Timeout, HALT
    }
  }

  switch (ShCyIndex)
  {
    case 0:
            MoveRetry = false;
            
            if (ShutterInputState == ShOnlyClose) {       ShutterState = ShClose;
            } else if (ShutterInputState == ShOnlyOpen) { ShutterState = ShOpen;
            } else {                                      ShutterState = ShError; }
            
            if (ShutterCommand == CmdOpen) {
              if (ShutterInputState != ShOnlyOpen) {
                ShutterState = ShOpening;
                ShCyIndex = 10;
              } else {
                ShutterState = ShOpen;
                ShutterCommand = Idle;
              }
            }

            if (ShutterCommand == CmdClose) {
              if (ShutterInputState != ShOnlyClose) {
                ShCyIndex = 10;
                ShutterState = ShClosing;
              } else {
                ShutterCommand = Idle;
                ShutterState = ShClose;
              }
            }
            if (ShutterCommand == CmdHalt) {
              ShCyIndex = 100;
            }
            break;

    /* NO OPENING COMMAND IF ROOF IS OPEN SHULD ARRIVE, AND VICE VERSA FOR CLOSING COMMAND, BUT ARE ACCEPTED IF NO/EACH TWO INPUT IS IN (safety first) */
    case 10:
            //Open and close cycle are identical, I just hope to reach the right
            //Pulse to start to the motor, ack millis for time out and
            ShMoveTimeOutAck = millis();
            digitalWrite(SHUTTER_CMD_OUTPUT, HIGH);
            ShCyIndex++;
            break;

    case 11:  //Take signal end to loose signal
            if ((millis() - ShMoveTimeOutAck) > 1000) { //Wait 1second anyway
              if (ShutterInputState == ShInAll || ShutterInputState == ShInNoOne) {
                digitalWrite(SHUTTER_CMD_OUTPUT, LOW);
                ShMoveTimeOutAck = millis();
                ShCyIndex++;
              }
            }
            break;

    case 12:  //Sensor Reached
            // INIZIO CHECK APERTUA
            if (ShutterCommand == CmdOpen) {
                if (ShutterInputState == ShOnlyOpen) { //As aspected direction!
                ShutterState = ShOpen;
                ShCyIndex++;
                break;
              }
              if (ShutterInputState == ShOnlyClose) { //OMG wrong direction!
                if (MoveRetry == false) {
                  MoveRetry = true; // just one retry
                  ShCyIndex = 20;
                } else {
                  ShCyIndex = 100;  //no ping pong all day, HALT
                }
              } 

            }

            // FINE CHECK APERTUA


            //INIZIO CHECK CHIUSURA
            if (ShutterCommand == CmdClose) { //OMG wrong direction!
              if (ShutterInputState == ShOnlyOpen) {
                if (MoveRetry == false) {
                  MoveRetry = true; // just one retry
                  ShCyIndex = 20;
                } else {
                  ShCyIndex = 100;  //no ping pong all day, HALT
                }
              }
              if (ShutterInputState == ShOnlyClose) { //As aspected direction!
                ShutterState = ShClose;
                ShCyIndex++;
              }
            }
            // FINE CHECK CHIUSURA

            break;

    case 13:
            MoveRetry = false;
            ShutterCommand = Idle;
            ShCyIndex = 0;
            break;


//PING PONG - HALT ASPETTO E RIBADISCO LO START
    case 20:ShMoveTimeOutAck = millis();
            digitalWrite(SHUTTER_HALT_OUTPUT, HIGH);   //I need just a pulse for start roof motor
            digitalWrite(SHUTTER_CMD_OUTPUT, LOW);
            ShCyIndex++;
            break;

    case 21:
            if ((millis() - ShMoveTimeOutAck) > 1000) { //Wait a second
              digitalWrite(SHUTTER_HALT_OUTPUT, LOW);   
              digitalWrite(SHUTTER_CMD_OUTPUT, LOW);
              ShCyIndex++;
              ShMoveTimeOutAck = millis();
            }        
            break;

    case 22:
            if ((millis() - ShMoveTimeOutAck) > 5000) { //Wait 5 seconds and restart movement
              ShCyIndex = 10;
            }        
            break;


    /* HALT CYCLE */
    case 100: //halt command for 1sec
            ShMoveTimeOutAck = millis();
            digitalWrite(SHUTTER_HALT_OUTPUT, HIGH);   //I need just a pulse for start roof motor
            digitalWrite(SHUTTER_CMD_OUTPUT, LOW);
            ShCyIndex++;
            break;

    case 101: //halt command for 1sec
            if ((millis() - ShMoveTimeOutAck) > 1000) { //Setting Open Output for?
              digitalWrite(SHUTTER_HALT_OUTPUT, LOW);   //I need just a pulse for start roof motor
              digitalWrite(SHUTTER_CMD_OUTPUT, LOW);
              ShCyIndex++;
            }
            break;

    case 102: 
            ShutterCommand = Idle;
            ShutterState = ShError;
            ShCyIndex = 0;
            MoveRetry = false;
            break;


    default:
            Serial.println("unknown state");
            break;
  }


}


#endif

#ifndef DOME_HAND
#define DOME_HAND

#define SHUTTER_OPEN_INPUT    34
#define SHUTTER_CLOSE_INPUT   35

unsigned long ShMoveTimeOut;
unsigned long ShMoveTimeOutAck;

void domehandlersetup() {
  pinMode(setting.dome.pinStart, OUTPUT);
  pinMode(setting.dome.pinHalt, OUTPUT);
  pinMode(SHUTTER_OPEN_INPUT, INPUT);
  pinMode(SHUTTER_CLOSE_INPUT, INPUT);
}


void domeInputState(){

    // I used enum for input state for making the cycle code more clean
    if (digitalRead(SHUTTER_CLOSE_INPUT) == HIGH && digitalRead(SHUTTER_OPEN_INPUT) == LOW) {
      Dome.ShutterInputState = ShOnlyClose;
    }
    if ( digitalRead(SHUTTER_CLOSE_INPUT) == LOW && digitalRead(SHUTTER_OPEN_INPUT) == HIGH) {
      Dome.ShutterInputState = ShOnlyOpen;
    }
    if ( digitalRead(SHUTTER_OPEN_INPUT) == HIGH && digitalRead(SHUTTER_CLOSE_INPUT) == HIGH) {
      Dome.ShutterInputState = ShInAll;
    }
    if ( digitalRead(SHUTTER_OPEN_INPUT) == LOW && digitalRead(SHUTTER_CLOSE_INPUT) == LOW) {
      Dome.ShutterInputState = ShInNoOne;
    }
}
void LastDomeCommandExe(){
  if (Dome.ShutterCommand != Idle) {
    Dome.LastDomeCommand = Dome.ShutterCommand;
  }
}

void domehandlerloop() {
  ShMoveTimeOut = setting.dome.movingTimeOut *1000;
  domeInputState();
  LastDomeCommandExe();

  // TIMEOUT MOVIMENTAZIONE
  if (Dome.Cycle >= 11 && Dome.Cycle <= 12) {
    if ((millis() - ShMoveTimeOutAck) > ShMoveTimeOut) { //input error I wait 10 sec. before done command
      Dome.Cycle = 100;  //Timeout, HALT
    }
  }

  switch (Dome.Cycle)
  {
    case 0:
            Dome.MoveRetry = false;
            
            if (Dome.ShutterInputState == ShOnlyClose) {       Dome.ShutterState = ShClose;
            } else if (Dome.ShutterInputState == ShOnlyOpen) { Dome.ShutterState = ShOpen;
            } else {                                      Dome.ShutterState = ShError; }
            
            if (Dome.ShutterCommand == CmdOpen) {
              if (Dome.ShutterInputState != ShOnlyOpen) {
                Dome.ShutterState = ShOpening;
                Dome.Cycle = 10;
              } else {
                Dome.ShutterState = ShOpen;
                Dome.ShutterCommand = Idle;
              }
            }

            if (Dome.ShutterCommand == CmdClose) {
              if (Dome.ShutterInputState != ShOnlyClose) {
                Dome.Cycle = 10;
                Dome.ShutterState = ShClosing;
              } else {
                Dome.ShutterCommand = Idle;
                Dome.ShutterState = ShClose;
              }
            }
            if (Dome.ShutterCommand == CmdHalt) {
              Dome.Cycle = 100;
            }
            break;

    /* NO OPENING COMMAND IF ROOF IS OPEN SHULD ARRIVE, AND VICE VERSA FOR CLOSING COMMAND, BUT ARE ACCEPTED IF NO/EACH TWO INPUT IS IN (safety first) */
    case 10:
            //Open and close cycle are identical, I just hope to reach the right
            //Pulse to start to the motor, ack millis for time out and
            ShMoveTimeOutAck = millis();
            digitalWrite(setting.dome.pinStart, HIGH);
            Dome.Cycle++;
            break;

    case 11:  //Take signal end to loose signal
            if ((millis() - ShMoveTimeOutAck) > 1000) { //Wait 1second anyway
              if (Dome.ShutterInputState == ShInAll || Dome.ShutterInputState == ShInNoOne) {
                digitalWrite(setting.dome.pinStart, LOW);
                ShMoveTimeOutAck = millis();
                Dome.Cycle++;
              }
            }
            break;

    case 12:  //Sensor Reached
            // INIZIO CHECK APERTUA
            if (Dome.ShutterCommand == CmdOpen) {
                if (Dome.ShutterInputState == ShOnlyOpen) { //As aspected direction!
                Dome.ShutterState = ShOpen;
                Dome.Cycle++;
                break;
              }
              if (Dome.ShutterInputState == ShOnlyClose) { //OMG wrong direction!
                if (Dome.MoveRetry == false) {
                  Dome.MoveRetry = true; // just one retry
                  Dome.Cycle = 20;
                } else {
                  Dome.Cycle = 100;  //no ping pong all day, HALT
                }
              } 

            }

            // FINE CHECK APERTUA


            //INIZIO CHECK CHIUSURA
            if (Dome.ShutterCommand == CmdClose) { //OMG wrong direction!
              if (Dome.ShutterInputState == ShOnlyOpen) {
                if (Dome.MoveRetry == false) {
                  Dome.MoveRetry = true; // just one retry
                  Dome.Cycle = 20;
                } else {
                  Dome.Cycle = 100;  //no ping pong all day, HALT
                }
              }
              if (Dome.ShutterInputState == ShOnlyClose) { //As aspected direction!
                Dome.ShutterState = ShClose;
                Dome.Cycle++;
              }
            }
            // FINE CHECK CHIUSURA

            break;

    case 13:
            Dome.MoveRetry = false;
            Dome.ShutterCommand = Idle;
            Dome.Cycle = 0;
            break;


//PING PONG - HALT ASPETTO E RIBADISCO LO START
    case 20:ShMoveTimeOutAck = millis();
            digitalWrite(setting.dome.pinHalt, HIGH);   //I need just a pulse for start roof motor
            digitalWrite(setting.dome.pinStart, LOW);
            Dome.Cycle++;
            break;

    case 21:
            if ((millis() - ShMoveTimeOutAck) > 1000) { //Wait a second
              digitalWrite(setting.dome.pinHalt, LOW);   
              digitalWrite(setting.dome.pinStart, LOW);
              Dome.Cycle++;
              ShMoveTimeOutAck = millis();
            }        
            break;

    case 22:
            if ((millis() - ShMoveTimeOutAck) > 5000) { //Wait 5 seconds and restart movement
              Dome.Cycle = 10;
            }        
            break;


    /* HALT CYCLE */
    case 100: //halt command for 1sec
            ShMoveTimeOutAck = millis();
            Dome.ShutterState = ShError;
            digitalWrite(setting.dome.pinHalt, HIGH);
            digitalWrite(setting.dome.pinStart, LOW);
            Dome.Cycle++;
            break;

    case 101: //halt command for 1sec
            if ((millis() - ShMoveTimeOutAck) > 1000) { //Setting Output for 1sec
              digitalWrite(setting.dome.pinHalt, LOW);   
              digitalWrite(setting.dome.pinStart, LOW);
              Dome.Cycle++;
            }
            break;

    case 102: 
            Dome.ShutterCommand = Idle;
            Dome.Cycle = 0;
            Dome.MoveRetry = false;
            break;


    default:
            Serial.println("unknown state");
            break;
  }


}


#endif

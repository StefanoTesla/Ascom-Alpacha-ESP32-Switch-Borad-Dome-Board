#ifndef SWITCH_HAND
#define SWITCH_HAND




void switchsetup() {
  int i=0;
/* Switch Setup */

/* Default Switch setting

  pin -> Choose the GPIO where switch is plugged on!
  minValue -> Min Value the switch can have (default is 0 and is set to 0 if Switch is Output)
  maxValue -> Max Value the switch can have (default is 1 and is forced to 1 if Switch is Output)
  CanSet -> Default: true, if true is output or pwm, if false is an input
  Step -> Choose the step for change the value of Switch (default 1 and forced to 1 if is output)
  analog -> Default is false, if true this switch is PWM
  pwmChannel -> Default -1, the value can be 0..15 according to esp32 pwm channels

Please refer to this page to understand wich output/input you can use without problems:
https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
*/


/* automatic setup for Switch */

  for (i=0;i<_MAX_SWTICH_ID_;i++){
    if((Switch[i].pin == 0 || Switch[i].pin == 99) || Switch[i].type == 0 ){
        Switch[i].Name ="";
        Switch[i].Description ="";
    }
    Serial.print(Switch[i].pin);
    Serial.print(" ");
    if (Switch[i].CanSet == true){
      if (Switch[i].analog == false){
        //Uscita Digitale
        pinMode(Switch[i].pin, OUTPUT);
        Switch[i].Step = 1;
        Switch[i].minValue = 0;
        Switch[i].maxValue = 1;
      } else {
          //Uscita PWM
          ledcAttachPin(Switch[i].pin, pwmchannles);
          ledcSetup(pwmchannles, 5000, 13);
          Switch[i].pwmChannel = pwmchannles;
          Switch[i].minValue = 0;
          Switch[i].maxValue = 8192;
          pwmchannles++;
      }
    } else {
      if (Switch[i].analog == false){
        //Ingresso Digitale
        pinMode(Switch[i].pin, INPUT);
        Switch[i].Step = 1;
        Switch[i].minValue = 0;
        Switch[i].maxValue = 1;
      } else {
        //Ingresso Analogico
        Switch[i].minValue = 0;
        Switch[i].maxValue = 4095;
      }  
    }
  Serial.println("");
  }
}

#endif

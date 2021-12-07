# Ascom Alpacha Switch and Dome Board


Hello everyone, I use this firmware to open and close my Dome roof and is used olso for handle 6 switch.

Each two devices are recognized form ascom aplacha, no usb connectio or driver are needed to work, only http api comunication.

The switch are already tested with N.I.N.A!
Dome is already tested with Ascom device hub

It's a work in progess, but it's already tested with great stability!

WiFi Manager for first connection or connection to WiFi fail, automatic reconnection in case of disconnection (hoping for a router restart)

## Dome

My dome is R.O.R rolling roof, I used a gate motor, so I use just two output and two input:

-Start
-Halt
-Open Input
-Close Input

The start signal is HIGH just for one second

-If everything work as expected roof will open/close correcty
-In case of Worng direction (you want open but it going to close) the board send another Start signal (only one time avoiding ping pong), this can happen in case of shoutdown during roof is moving
-A timer look for a moviment timeout, if timeout occurred HALT signal is HIGH for 3 second.

## Switch

6 Switch can be configurated as output or input, in near future I will implement olso pwm signal.

### History

The software was made with Arduino IDE and ported subsequently to Platformio for better management

#### Changelog

1.0.0 First GitHub deploy :grinning:


### ToDo List:

- Automatic setup of pwm output
- Better alpacha error messages
- Make Switch OOP
- Webbrowser Switch setup at the moment can only change Name and Description, can be useful change olso input/output/pwm with min and max selection?? idk..

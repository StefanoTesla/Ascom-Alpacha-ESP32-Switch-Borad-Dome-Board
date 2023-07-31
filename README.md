# Ascom Alpacha Switch and Dome Board ESP32


Hello everyone, with this board you can use Ascom Switch and Ascom Dome via Wifi!

Each two devices are recognized form ascom aplacha, no usb connectio or driver are needed to work!

Switch can be ON/OFF or PWM!!!!

The switch are already tested with N.I.N.A!
Dome is already tested with Ascom device hub, Nina and Starkeepper Voyager Software

It's a work in progess, but it's already tested with great stability!

WiFi Manager for first connection.
Automatic reconnection in case of disconnection (hoping for a router restart)
Ota Update to update the firmware without any cables.

## Dome
Actually Ascom Dome function is tested with:

- Starkeepper Voyager Software
- Ascom Device Hub

My dome is R.O.R rolling roof, I used a gate motor, so I use just two output and two input:

- Start
- Halt
- Open Input
- Close Input

The start signal is HIGH until I will not lost the acutal position sensor.
- If everything work as expected roof will open/close correcty
- In case of Worng direction (you want open but it going to close) the board send another Start signal (only one time avoiding ping pong), this can happen in case of shoutdown during roof is moving
- A timer look for a moviment timeout, if timeout occurred HALT signal is HIGH for 3 second.

## Switch

Actually Ascom Switch function is tested with:

- N.I.N.A.

16 Switch can be configurated as output or input, pwm signal or analog input.

Error sended to ascom alpaca:

- "The Switch x doesn't exist", where x is the switch number, if x= -1 the parameters was not in the ascom alpaca request
- "The Value X is out of range MIN: Y MAX: Z" is coming if we are setting a value X outside the min and max value of that switch (ex. value 2 to a digital output)
- "The Value was not provided from ASCOM" in the coming request is missing value parameter

### History
The software was made with Arduino IDE and ported subsequently to Platformio for better management
Version 1.2 requred I/O config form the firmware, with version 2.0 you need to download the firmware only the first time!

#### Changelog

💥 2.0.0 - BREACKING NEWS! Now all the board can be setupped by the browser. Dome I/O and Switch setting is now editable from the browser and you can save the confi files.
Before update write in a memo all your setting.

What's new in version 2.0.0?

Web pages run now alpine.js and all the js under the hood is rewrited in a modern way.
Now Dome and switch are in the same page, olso settings now are in the same page!
New dome function: Auto Close if anyone is talking with the board (browser or ascom alpacha driver) [IS UNDER DEVELOPMENT], you can enable or disable this featur by browser setup page.


### ToDo List:

- Make Switch OOP
- Webrowser have some bugs

Knowed browser bugs:
- :white_check_mark: Missing Validation info on setup page [2.0.0]

## html_pages directory

This folder contain a vite project with web browser pages, in this way I can have a clean and powerfull css by Taliwind 3.

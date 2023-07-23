# Ascom Alpacha Switch and Dome Board ESP32


Hello everyone, I use this firmware to open and close my Dome roof and is used olso for handle 6 switch.

Each two devices are recognized form ascom aplacha, no usb connectio or driver are needed to work, only http api comunication.

The switch are already tested with N.I.N.A!
Dome is already tested with Ascom device hub

It's a work in progess, but it's already tested with great stability!

WiFi Manager for first connection or connection to WiFi fail, automatic reconnection in case of disconnection (hoping for a router restart)

## Dome
Actually Ascom Dome function is tested with:

- Starkeepper Voyager Software
- Ascom Device Hub

My dome is R.O.R rolling roof, I used a gate motor, so I use just two output and two input:

- Start
- Halt
- Open Input
- Close Input

The start signal is HIGH just for one second

- If everything work as expected roof will open/close correcty
- In case of Worng direction (you want open but it going to close) the board send another Start signal (only one time avoiding ping pong), this can happen in case of shoutdown during roof is moving
- A timer look for a moviment timeout, if timeout occurred HALT signal is HIGH for 3 second.

## Switch

Actually Ascom Switch function is tested with:

- N.I.N.A.

6 Switch can be configurated as output or input, in near future I will implement olso pwm signal.

Error sended to ascom alpaca:

- "The Switch x doesn't exist", where x is the switch number, if x= -1 the parameters was not in the ascom alpaca request
- "The Value X is out of range MIN: Y MAX: Z" is coming if we are setting a value X outside the min and max value of that switch (ex. value 2 to a digital output)
- "The Value was not provided from ASCOM" in the coming request is missing value parameter

### History
The software was made with Arduino IDE and ported subsequently to Platformio for better management

#### Changelog

1.2.4 Added wifi automatic reconnection, added OTA firmware uploader

1.2.3 Switch web page should be ok now 💥

1.2.2 Dome web page should be ok now 💥

1.2.1 Solved bug that cause a slow response from api server port 80

1.1.0 Switch Error have a better expletation of the problem

1.0.0 First GitHub deploy :grinning:


### ToDo List:

- Make Switch OOP
- Webrowser have some bugs

Knowed browser bugs:

- :white_check_mark: Updating switch actual value [1.2.1]
- :white_check_mark: Show last command to the dome, at the moment is "nietca" an Italian words meaning "nothing" [1.2.1]
- :white_check_mark: Saving Switch Name and Descriptions [1.1.0]
- :white_check_mark: Actual time-out setting time is not showed in Dome page [1.2.2]
- :white_check_mark: From WebServer we cannot change switch Value [1.2.3]
- :white_check_mark: Actually Dome time-out is multiplied * 1000 from webbrowser before store it [1.2.2]
- :white_check_mark: Actually Dome Open Close Halt buttom from browser do nothing, need to add olso error message. [1.2.2]


## html_pages directory

This folder contain a vite project with web browser pages, in this way I can have a clean and powerfull css by Taliwind 3.

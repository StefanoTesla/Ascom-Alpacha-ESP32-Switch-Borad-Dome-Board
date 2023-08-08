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


# How to use

## First time board installation

First of all we need to install Visual Studio Code and add Platformio extension.


Download Visual Studio Code from: https://code.visualstudio.com/

Install it.

One installation is finish, Go to Extension and search Platformio, then install it.

![platformio](https://github.com/StefanoTesla/Ascom-Alpacha-ES32-Switch-Borad-Dome-Board/assets/92517402/d98877fb-aad2-4a95-8ed2-27ca3c7f2d11)

And wait until restart vs code is needed:

![restartvscode](https://github.com/StefanoTesla/Ascom-Alpacha-ES32-Switch-Borad-Dome-Board/assets/92517402/cba04a24-7c34-466e-bf7c-61187920322d)

At this point, download the software from this page, go up click on Code and click on Download Zip

![image](https://github.com/StefanoTesla/Ascom-Alpacha-ES32-Switch-Borad-Dome-Board/assets/92517402/3221a252-7aa6-4844-860c-6ff7f2ea973d)

Extact the folder where you want, BE CAREFUL, don't extract the files inside the folder! extract directly the folder!

Go to VsCode and click on the Platformio Icon, click on Pick a Folder and select the extracted folder

![image](https://github.com/StefanoTesla/Ascom-Alpacha-ES32-Switch-Borad-Dome-Board/assets/92517402/c3af02f5-2c4d-4720-97f1-36f7b6ec2528)

At this point wait platformio will download all the necessary things needed to make the board work:

![image](https://github.com/StefanoTesla/Ascom-Alpacha-ES32-Switch-Borad-Dome-Board/assets/92517402/eaaf9c67-e40a-4d33-ac0d-ffbdfacbf22f)

Once is finish on the right you will have this menu:

![image](https://github.com/StefanoTesla/Ascom-Alpacha-ES32-Switch-Borad-Dome-Board/assets/92517402/9bd040e0-7b05-466a-8a48-5ec8335a7ceb)

Click build and wait until you will not have this message:

![image](https://github.com/StefanoTesla/Ascom-Alpacha-ES32-Switch-Borad-Dome-Board/assets/92517402/5eb184d7-bb6e-44c9-9231-a6a07f06b311)

Now we are ready to upload the firmware!

If it is your first time connecting an esp32 to the pc you need to install serial driver depending on your bard serial chip:

CH340 driver: https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all (download at the buttom of the page)
CP210x driver: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads

(check the video on the CH340 page to see wich COM port is used by your device)

Connect your esp32 board to a usb port 
On the menu we seen before we need to click:

Upload Filesystem Image

![image](https://github.com/StefanoTesla/Ascom-Alpacha-ES32-Switch-Borad-Dome-Board/assets/92517402/58f7db3d-f677-45a6-93cd-fa3bf2e5c8f1)

After some while the board will rebot.

Now we need to click on Upload

![image](https://github.com/StefanoTesla/Ascom-Alpacha-ES32-Switch-Borad-Dome-Board/assets/92517402/8e8e496e-f380-4362-937a-61dd0c350b40)

Wait for success printed out.

### Connect the board to your own wifi

If is your first time setup, you need to connct the board to your wifi, don't check into the code, the board will manage everything for you!
Open your WiFi and you will have TeslaBoard wifi, connect to him

![image](https://github.com/StefanoTesla/Ascom-Alpacha-ES32-Switch-Borad-Dome-Board/assets/92517402/f0096d68-8f93-4f54-b429-013b7b53d3f6)

Click your WiFi, type the password and click on save

![image](https://github.com/StefanoTesla/Ascom-Alpacha-ES32-Switch-Borad-Dome-Board/assets/92517402/df91e6dc-8caf-4447-b116-007b4646f0c4)

In few seconds the board will be up and running, go to your route setting and check the board IP.

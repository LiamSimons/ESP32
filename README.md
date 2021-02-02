# FreeRTOSDemo

Created by Espressif Systems, the ESP32 is a low-cost, low-power system on a chip (SoC) series with Wi-Fi & dual-mode Bluetooth capabilities!  
The chip can run FreeRTOS, which is a Realtime Operating System for microcontrollers.  

## Installation of ESP-IDF

ESP-IDF = Espressif IoT Development Framework  
Download esp-idf (https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html#step-1-install-prerequisites) and install.  
Configure IDF_PATH = ~/esp/esp-idf  
ESP-IDF uses a modified version of openocd    
Configure OPENOCD_PATH (see below)

## Steps to create this project

### Setup environment

```commandline
export PATH=$PATH:~/.espressif/tools/xtensa-esp32-elf/esp-2020r3-8.4.0/xtensa-esp32-elf/bin
export OPENOCD_PATH="~/.espressif/tools/openocd-esp32/v0.10.0-esp32-20200709/openocd-esp32"
cd $IDF_PATH
. ./export.sh
```

### Create project

Checkout the demo project
```commandline
git clone https://gitlab.groept.be/ee5/freertosdemo.git
```

Or create your own new project in a separate git repository on gitlab.groept.be
```commandline
cd ~/projects/esp32
idf.py create-project freertosdemo
git init
git remote add origin git@gitlab.groept.be:ee5/team_xx.git
git add .
git commit -m "Initial commit"
git push -u origin master
```

### Configure target and menuconfig

```commandline
idf.py set-target esp32
idf.py menuconfig
```
Change parameters in FreeRTOSDemo Configuration (WiFi SSID/Password)

### Configure CLion

Install CLion, best is to do this via the JetBrains Toolbox (https://www.jetbrains.com/toolbox-app/)  
Open Clion  
Open project...  
Select freertosdemo directory  
Install plugin ESP32 via settings/plugins (Ctrl-Alt-S)
(https://github.com/paoloach/ESP32)

Go to Settings... / CMake / Change debug profile    
Change:  
```
CMake Options: -DCMAKE_TOOLCHAIN_FILE=CrossCompiler.cmake  
Add environment: IDF_PATH=~/esp/esp-idf;PATH=~/.espressif/tools/xtensa-esp32-elf/esp-2020r3-8.4.0/xtensa-esp32-elf/bin:/usr/bin:/sbin:/bin:/opt/bin  
```
Add Run Configuration...  
```
ESP32 Flash  
Name : Flash  
Configuration : Debug  
Select serial port  
Baud rate: 115200  
```

## Beyond this project

### CMake

ESP-IDF uses CMake to compile projects, this has a specific syntax you will need to learn.  
Adding C-files requires you to add the source to one of the CMakeLists.txt files.  
Look in that file for an example.

### Kconfig

ESP-IDF uses Kconfig files to specify configurable constants.  
These can be configured using idf.py menuconfig.  
Using them in your source code is done through defines.  
Look in this example to see how to do this.  

### Adding a component

When you start developing your project, use components.

```commandline
idf.py create-component mycomponent -C components/mycomponent
```
### More information

ESP32 : http://esp32.net/  
ESP-IDF : https://docs.espressif.com/projects/esp-idf/en/latest/esp32/index.html  
FreeRTOS : https://freertos.org/  
ESP32 Huzzah : https://www.adafruit.com/product/3619  
Technical information : https://www.espressif.com/en/products/socs/esp32  
Book : https://leanpub.com/kolban-ESP32  
TRM : https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf  
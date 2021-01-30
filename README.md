# Installation of ESP-IDF

Download esp-idf and install.

Configure IDF_PATH

Install openocd

Configure OPENOCD_PATH


# Steps to create this project

Create git repository on gitlab.groept.be

## Setup environment

```
export OPENOCD_PATH="~/.espressif/tools/openocd-esp32/v0.10.0-esp32-20200709/openocd-esp32"
cd $IDF_PATH
(~/esp/esp-idf)
. ./export.sh
```

## Create project

```
cd ~/projects/esp32
idf.py create-project freertosdemo
git init
git remote add origin git@gitlab.groept.be:ee5/freertosdemo.git
git add .
git commit -m "Initial commit"
git push -u origin master
```

## Configure target

```
idf.py set-target esp32
idf.py menuconfig
```
## Configure CLion

Install CLion

Open Clion

Open project...

Select freertosdemo directory

Install plugin ESP32 via settings/plugins
(https://github.com/paoloach/ESP32)

Settings.../CMake/Change debug profile
CMake Options: -DCMAKE_TOOLCHAIN_FILE=CrossCompiler.cmake
Add environment: IDF_PATH=~/esp/esp-idf;PATH=~/.espressif/tools/xtensa-esp32-elf/esp-2020r3-8.4.0/xtensa-esp32-elf/bin:/usr/bin:/sbin:/bin:/opt/bin

Add Run Configuration...

ESP32 Flash

Name : Flash

Configuration : Debug

Select serial port

Baud rate: 115200

## Configure ESP32

```
idf.py menuconfig
```
Change parameters in FreeRTOSDemo Configuration

## Adding a component

```
idf.py create-component mycomponent -C components/mycomponent
```

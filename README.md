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

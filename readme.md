# TeaTimer
Simple Qt5 application to measure a steep time of a tea.

![alt tag](https://raw.githubusercontent.com/tomasxvavra/TeaTimer/master/screen/screen_app.jpg)

# Features

* Minimalistic and very easy to use.
* Countdown starts automatically after start. Restart button may be used for delayed start.
* Change desired time whenever you desire.
* Timer does not stop after timeout - you can change your mind and increase steep time. If you forget about your tea, you will still know how long it was steeped.
* Stays always on top, so you will not forget about it :)
* Visual alarm after timeout.
* Select desired time manually or from from a drop down menu.

## Tested platforms

* Linux Mint 18.1 Serena
* TODO

# Building

    git clone https://github.com/tomasxvavra/TeaTimer.git
    cd TeaTimer && mkdir build && cd build
    qmake ../src/TeaTimer.pro
    make

# TODO

* Implement settings
    * Last used duration.
    * Stay on top behavior.
* Nicer visual alarm.
* Test on more platforms.

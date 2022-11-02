# 433Screen-SignalHacker
Full duplex 433 MHz Signal jammer, recorder, decoder and hacking multitool device based on ESP32 microcontroller and RFM69HW radios. This version of the device provides an OLED screen and simple UI to navigate menus and different hacks/modes/settings.

Hardware Features:
- ESP32 Node MCU board, USB can be used to power the device;
- 2x RFM69HW radio boards, in order to provide full duplex signal hacking
- SSD1306 128x64 px OLED display
- SD card module for signal storage
- 4 navigation buttons

Software features and modes (currently in development):
- Custom library for RFM69HW register configurations
- Custom functions for UI creation in OLED screen
- Signal jamming and blocking mode, with various types of "pollution"
- Simple signal recorder, for both OOK and FSK signals
- Rolljam attack signal recorder and sender, for hacking keyless entry systems
- Signal file explorer for recorded signals, using custom file format
- Button mapping signal sender, providng and easy way to send different signals using different buttons

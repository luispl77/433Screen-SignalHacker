# 433Screen-SignalHacker
Full duplex 433 MHz Signal jammer, recorder, decoder and hacking multitool device based on ESP32 microcontroller and RFM69HW radios. This version of the device provides an OLED screen and simple UI to navigate menus and different hacks/modes/settings.

Hardware Features:
- ESP32 Node MCU board, USB can be used to power the device;
- 2x RFM69HW radio boards, in order to provide full duplex signal hacking;
- SSD1306 128x64 px OLED display;
- SD card module for signal storage;
- 4 navigation buttons;

Software features and modes (currently in development):
- Custom library for RFM69HW register configurations (https://github.com/luispl77/RFM69LPL);
- Custom library for UI creation in OLED screen (https://github.com/luispl77/UI1306LPL);
- Signal jamming and blocking mode, with various modes of "pollution";
- Simple signal recorder mode, for OOK/FSK signals;
- Rolljam attack signal recorder and sender, for hacking cars with rolling codes;
- Signal file explorer for recorded signals, using custom file format;
- Button mapping signal sender, providng an easy way to send different signals using different buttons;
- Graphic signal receiver mode, allowing to see onscreen the OOK/FSK demodulated waveform in realtime (may require using second core of esp32);

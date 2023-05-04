# 433Screen-SignalHacker
(not finished, needs to be updated to the new RFM69LPL library version)
Full duplex 433 MHz Signal jammer, recorder, decoder and hacking multitool device based on ESP32 microcontroller and RFM69HW radios. This version of the device provides an OLED screen and simple UI to navigate menus and different hacks/modes/settings.

Hardware Features (Done):
- ESP32 Devkit V1 board, USB can be used to power the device;
- 2x RFM69HW radio boards, in order to provide full duplex signal hacking;
- SSD1306 128x64 px OLED display;
- SD card module for signal storage (Support for 2 different modules);
- 4 navigation buttons.

Firmware features and modes (currently in development):
- Custom library for RFM69HW register configurations (https://github.com/luispl77/RFM69LPL) (Done);
- Custom library for UI creation in OLED screen (https://github.com/luispl77/UI1306LPL) (Done);
- Signal jamming and blocking mode, with various modes of "pollution" (Under development);
- Simple signal recorder mode, for OOK/FSK signals (Under development);
- Rolljam attack signal recorder and sender, for hacking cars with rolling codes (Under development);
- Signal file explorer for recorded signals, using custom file format (Under development);
- Button mapping signal sender, providng an easy way to send different signals using different buttons (Under development);
- Graphic signal receiver mode, allowing to see onscreen the OOK/FSK demodulated waveform in realtime (may require using second core of esp32) (Under development);
- Spectrum analyser mode: sweeps 415-510Mhz and finds frequency with strongest RSSI (Under development).

## Hardware
EasyEDA schematic and layout: https://oshwlab.com/maarnotto/lpl_esp32signalhacker
![image](https://user-images.githubusercontent.com/81360502/236343828-5eb571a6-c591-4fb2-bbef-8b55d704c261.png)
![image](https://user-images.githubusercontent.com/81360502/236343848-cd96bbe8-c5c1-4bd1-ad73-7ae4cd8e46e6.png)





![WhatsApp Image 2023-05-05 at 00 24 34](https://user-images.githubusercontent.com/81360502/236350820-bab8f90a-2e23-47e5-a12c-8dca480eee96.jpeg)

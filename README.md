# 433Screen-SignalHacker
(not finished, needs to be updated to the new RFM69LPL library version)
Full duplex 433 MHz Signal jammer, recorder, decoder and hacking multitool device based on ESP32 microcontroller and RFM69HW radios. This version of the device provides an OLED screen and simple UI to navigate menus and different hacks/modes/settings.

Hardware Features:
- ESP32 Devkit V1 board, USB can be used to power the device;
- 2x RFM69HW radio boards, in order to provide full duplex signal hacking;
- SSD1306 128x64 px OLED display;
- SD card module for signal storage;
- 4 navigation buttons.

Software features and modes (currently in development):
- Custom library for RFM69HW register configurations (https://github.com/luispl77/RFM69LPL);
- Custom library for UI creation in OLED screen (https://github.com/luispl77/UI1306LPL);
- Signal jamming and blocking mode, with various modes of "pollution";
- Simple signal recorder mode, for OOK/FSK signals;
- Rolljam attack signal recorder and sender, for hacking cars with rolling codes;
- Signal file explorer for recorded signals, using custom file format;
- Button mapping signal sender, providng an easy way to send different signals using different buttons;
- Graphic signal receiver mode, allowing to see onscreen the OOK/FSK demodulated waveform in realtime (may require using second core of esp32);
- Spectrum analyser mode: sweeps 415-510Mhz and finds frequency with strongest RSSI.

## Hardware
EasyEDA schematic and layout: https://oshwlab.com/maarnotto/lpl_esp32signalhacker
<img width="270" alt="top" src="https://user-images.githubusercontent.com/81360502/200019548-0850a8f0-5479-41c4-92ea-47d86335f9c2.png">
<img width="268" alt="bottom" src="https://user-images.githubusercontent.com/81360502/200019563-1e905f63-8e2c-447e-a91d-a367f3701991.png">


Resources:
https://github.com/UberGuidoZ/Flipper/tree/main/Sub-GHz/Vehicles/Tesla/BEST_PORT_OPENER
https://www.reddit.com/r/flipperzero/comments/thglag/am250_am650_unlocks_teslas_charging_ports_credit/

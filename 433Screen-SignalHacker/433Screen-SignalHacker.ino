#include <RFM69LPL.h>
#include <SPI.h>
#include <RFM69LPLregisters.h>
#include <EEPROM.h>

#include <UI1306LPL.h>

#define DIO2_T 15
#define DIO2_R 16

#define R_CS 4
#define T_CS 5
#define SD_CS 13

#define BUILTIN_LED 2

float frequency_ISM = 433.92;
uint8_t buttonA = 27;
uint8_t buttonB = 26;     //buttons pins. these work on ESP32, but add whichever ones you like. 
uint8_t buttonUP = 25;    //on intializeDisplay(), they're all set to pinMode(x, INPUT_PULLUP).
uint8_t buttonDOWN = 33;


//custom modes//////////
UI1306LPL read_battery(&readBattery, MODE_FUNCTION);
UI1306LPL tesla_door(&sendTesla, MODE_FUNCTION);
UI1306LPL custom_modes(NULL, MODE_MENU, "Tesla door", &tesla_door, "Battery voltage", &read_battery);
///////////////

RFM69LPL radio_R(R_CS, DIO2_R); 
RFM69LPL radio_T(T_CS, DIO2_T);


UI1306LPL spc_analyser(&spectrumAnalyser, MODE_FUNCTION);
UI1306LPL gx_analyser(&graphicAnalyser, MODE_FUNCTION);
UI1306LPL rec_rep(&recordReplay, MODE_FUNCTION);
UI1306LPL r_config(&receiverConfig, MODE_FUNCTION);
UI1306LPL receive_replay(NULL, MODE_MENU, "Receiver Config", &r_config, "Record/Replay", &rec_rep, "Graphic Analyser", &gx_analyser, "Spectrum Analyser", &spc_analyser);

UI1306LPL send_cst(&sendConstantWave, MODE_FUNCTION);
UI1306LPL send_sqr(&sendSquareWave, MODE_FUNCTION);
UI1306LPL t_config(&transmitterConfig, MODE_FUNCTION);
UI1306LPL signal_jammer(NULL, MODE_MENU, "Send Constant Wave", &send_cst, "Send Square Wave", &send_sqr, "Transmitter Config", &t_config);

UI1306LPL main_menu(NULL, MODE_MENU, "Signal Jammer", &signal_jammer, "Receive/Replay", &receive_replay, "Custom Modes", &custom_modes);


void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  unselect_SD();

  radio_T.unselect(); // avoid SPI interference between radios
  radio_R.init();
  radio_T.init();
  
  initEEPROM();
  
  radio_T.readAllRegs(); 
  radio_R.readAllRegs(); printEEPROMSettings();
  radio_R.readAllSettings(); //reads registers and translates into readable form
  radio_T.readAllSettings(); //reads registers and translates into readable form
  
  main_menu.initializeDisplay(SHOW_BOOT_SCREEN);
}

void loop() {
  main_menu.runMenu();
}

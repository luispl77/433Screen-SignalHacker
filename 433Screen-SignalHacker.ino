#include <RFM69LPL.h>
#include <SPI.h>
#include <RFM69LPLregisters.h>

#include <UI1306LPL.h>

#define DIO2_T 15
#define DIO2_R 16

#define R_CS 4
#define T_CS 5
#define SD_CS 13

#define BUILTIN_LED 2

uint8_t buttonA = 27;
uint8_t buttonB = 26;     //buttons pins. these work on ESP32, but add whichever ones you like. 
uint8_t buttonUP = 25;    //on intializeDisplay(), they're all set to pinMode(x, INPUT_PULLUP).
uint8_t buttonDOWN = 33;

RFM69LPL radio_R(R_CS, DIO2_R, true);
RFM69LPL radio_T(T_CS, DIO2_T, true);


UI1306LPL spc_analyser(&spectrumAnalyser, MODE_FUNCTION);
UI1306LPL send_cst(&sendConstantWave, MODE_FUNCTION);
UI1306LPL signal_jammer(NULL, MODE_MENU, "Send Constant Wave", &send_cst);
UI1306LPL main_menu(NULL, MODE_MENU, "Signal Jammer", &signal_jammer, "Spectrum Analyser", &spc_analyser);


void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  radio_R.initialize();
  //radio_T.initializeTransmit(10, PA_MODE_PA1_PA2);
  //radio_T.send(1);
  main_menu.initializeDisplay(SHOW_BOOT_SCREEN);
}

void loop() {
  main_menu.runMenu();
}

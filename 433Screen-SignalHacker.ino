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
float frequency_ISM = 433.92;
uint8_t buttonA = 27;
uint8_t buttonB = 26;     //buttons pins. these work on ESP32, but add whichever ones you like. 
uint8_t buttonUP = 25;    //on intializeDisplay(), they're all set to pinMode(x, INPUT_PULLUP).
uint8_t buttonDOWN = 33;


//car mode//////////
UI1306LPL speed_60(&speed60, MODE_FUNCTION);
UI1306LPL speed_70(&speed70, MODE_FUNCTION);
UI1306LPL speed_80(&speed80, MODE_FUNCTION);
UI1306LPL speed_90(&speed90, MODE_FUNCTION);
UI1306LPL speed_100(&speed100, MODE_FUNCTION);

UI1306LPL speed_config(NULL, MODE_MENU, "PWM: 190", &speed_60, "PWM: 200", &speed_70, "PWM: 210", &speed_80, "PWM: 230", &speed_90, "PWM: 255", &speed_100);

UI1306LPL car_mode(&carMode, MODE_FUNCTION);
UI1306LPL rc_car(NULL, MODE_MENU, "Car Mode", &car_mode, "Speed Config", &speed_config);
///////////////

RFM69LPL radio_R(R_CS, DIO2_R, true);
RFM69LPL radio_T(T_CS, DIO2_T, true);

UI1306LPL spc_analyser(&spectrumAnalyser, MODE_FUNCTION);
UI1306LPL gx_analyser(&graphicAnalyser, MODE_FUNCTION);
UI1306LPL sig_analyser(NULL, MODE_MENU, "Graphic Analyser", &gx_analyser, "Spectrum Analyser", &spc_analyser);

UI1306LPL send_cst(&sendConstantWave, MODE_FUNCTION);
UI1306LPL signal_jammer(NULL, MODE_MENU, "Send Constant Wave", &send_cst);

UI1306LPL t_config(&transmitterConfig, MODE_FUNCTION);
UI1306LPL r_config(&receiverConfig, MODE_FUNCTION);
UI1306LPL replay_attacks(NULL, MODE_MENU, "Receiver Config", &r_config, "Transmitter Config", &t_config);

UI1306LPL main_menu(NULL, MODE_MENU, "Signal Jammer", &signal_jammer, "Signal Analyser", &sig_analyser, "RC Car", &rc_car, "Replay Attacks", &replay_attacks);





void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  radio_R.initialize();
  radio_T.initialize();
  radio_R.setMode(RF69OOK_MODE_STANDBY);
  radio_T.setMode(RF69OOK_MODE_STANDBY);
  //radio_T.initializeTransmit(10, PA_MODE_PA1_PA2);
  //radio_T.send(1);
  main_menu.initializeDisplay(SHOW_BOOT_SCREEN);
}

void loop() {
  main_menu.runMenu();
}

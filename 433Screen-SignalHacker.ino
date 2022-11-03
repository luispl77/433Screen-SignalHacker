#include <RFM69LPL.h>
#include <SPI.h>
#include <RFM69LPLregisters.h>

#define DIO2_T 15
#define DIO2_R 16

#define R_CS 4
#define T_CS 5
#define SD_CS 13

#define BUILTIN_LED 2

#define buttonA 27
#define buttonB 26
#define buttonUP 25
#define buttonDOWN 33

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define INVERS 1 //inverser text
#define NORMAL 0 //normal text
#define BLAC 2 //black text

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RFM69LPL radio_R(R_CS, DIO2_R, true);
RFM69LPL radio_T(T_CS, DIO2_T, true);

void setup() {
  initializeTransmit_R();
  initializeTransmit_T();
  radio_R.setModulationType(MOD_OOK);
  radio_R.setModulationType(MOD_OOK);
  radio_R.send(0);
  radio_T.send(0);
  initializeDisplay();
}

void loop() {
  
}

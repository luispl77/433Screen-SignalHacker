//send tesla charging door signal at max power (+20dbm)
int tesla_signal[236] = {400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 1200, 400, 400, 400, 400, 800, 800, 400, 400, 800, 800, 800, 800, 400, 400, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 400, 400, 800, 400, 400, 800, 800, 400, 400, 800, 400, 400, 800, 400, 400, 400, 400, 800, 400, 400, 400, 400, 800, 400, 400, 800, 800, 400, 400, 800, 800, 800, 400, 400, 400, 400, 400, 400, 800, 400, 400, 800, 400, 400, 800, 1200, 400, 400, 400, 400, 800, 800, 400, 400, 800, 800, 800, 800, 400, 400, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 400, 400, 800, 400, 400, 800, 800, 400, 400, 800, 400, 400, 800, 400, 400, 400, 400, 800, 400, 400, 400, 400, 800, 400, 400, 800, 800, 400, 400, 800, 800, 800, 400, 400, 400, 400, 400, 400, 800, 400, 400, 800, 400, 400, 800, 1200, 400, 400, 400, 400, 800, 800, 400, 400, 800, 800, 800, 800, 400, 400, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 400, 400, 800, 400, 400, 800, 800, 400, 400, 800, 400, 400, 800, 400, 400, 400, 400, 800, 400, 400, 400, 400, 800, 400, 400, 800, 800, 400, 400, 800, 800, 800, 400, 400, 400, 400, 400, 400, 800, 400, 400, 800, 400, 400, 400, 100};
void sendTesla(){
  int i = 0;
  radio_R.setTransmitPower(20, PA_MODE_PA1_PA2_20dbm, OCP_OFF); //max power
  radio_R.txBegin();
  UI.drawText("TESLA", 0, 0, 2, NORMAL);
  UI.drawText("UP: send", 0, 45, 1, NORMAL);
  UI.drawText("B: exit", 0, 55, 1, NORMAL);
  UI.drawText(String(radio_R._frequency), 75, 55, 1, NORMAL);
  delay(400);
  while(1){
    if(UI.clickA()){
      delay(10);
    }
    if(UI.clickUP()){
      ledOn();
      for(int i = 0; i < 236; i += 2){
        radio_R.send(1);
        delayMicroseconds(tesla_signal[i]);
        radio_R.send(0);
        delayMicroseconds(tesla_signal[i+1]);
      }
      ledOff();
      delay(24); //24 ms in between codes
    }
    if(UI.clickDOWN()){
      delay(10);
    }
    if(UI.clickB()){
      radio_R.standby();
      break;
    }
  }
}

//connect 3.7V battery with half voltage divider to pin 35 to get a voltage reading at boot
void readBattery(){ 
  float reading = analogRead(35);
  pinMode(35, INPUT);
  Serial.print("analog: ");
  Serial.println(reading);
  Serial.print("corresponding voltage: ");
  Serial.println((reading/4096)*6.6, 3);
  Serial.print("offset: 3.6-3.25 = 0.35  ");
  Serial.println((reading/4096)*6.6 + 0.35, 3); //offset 0.35, actually its more like 0.49
  UI.drawText("bat: ", 0, 0, 1, NORMAL);
  UI.drawText(String((reading/4096)*6.6 + 0.49, 2), 30, 0, 2, NORMAL);
  UI.drawText("V", 80, 0, 2, NORMAL);
  UI.drawText("connect to pin 35", 0, 30, 1, NORMAL);
  UI.drawText("b: exit", 0, 50, 1, NORMAL);
  while(1){
    if(UI.clickA()){
      delay(300);
    }
    if(UI.clickUP()){
      delay(200);
    }
    if(UI.clickDOWN()){
      delay(200);
    }
    if(UI.clickB()){
      break; 
    }
  }
}


void unselect_SD(){
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);
}

void ledOn(){
  digitalWrite(BUILTIN_LED, HIGH);
}

void ledOff(){
  digitalWrite(BUILTIN_LED, LOW);
}

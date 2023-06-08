 int ram = 10000;
 unsigned long readings[10000];
 int i = 0; int j = 0;
 unsigned long previous_micros;
 
void IRAM_ATTR isr() {
    readings[i] = micros() - previous_micros;
    previous_micros = micros();
    i++;
}

void recordReplay(){
  int nr_samples = 0;
  clear_ram();
  UI.drawText("PULSES:", 0, 0, 1, NORMAL);
  UI.drawText("A: record", 60, 35, 1, NORMAL);
  UI.drawText("UP: replay", 60, 45, 1, NORMAL);
  UI.drawText("DOWN: clear", 60, 55, 1, NORMAL);
  delay(500);
  
  while(1){
    if(UI.clickA() && i < ram){
      radio_R.rxBegin(); UI.updateText("REC..", 0, 40, 1, NORMAL, 8);
      ledOn(); i = 0;
      Serial.println("begin recording");
      while(digitalRead(DIO2_R) == LOW); 
      previous_micros = micros();
      attachInterrupt(DIO2_R, isr, CHANGE);
      while(UI.clickA());
      detachInterrupt(DIO2_R); 
      UI.updateText(String(i), 45, 0, 1, NORMAL, 8); //update pulses
      delay(100);
      ledOff();
      dump_ram();
      radio_R.standby();
      radio_R.setTransmitPower(20, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
      radio_R.txBegin();
      UI.updateText("      ", 0, 40, 1, NORMAL, 8);
    }

    
    if(UI.clickUP()){
      j = 0; UI.updateText("REP...", 0, 40, 1, NORMAL, 8);
      ledOn();
      while(UI.clickUP()){
        radio_R.send(1);
        delay_us(readings[j]); //ets_delay_us(10);
        radio_R.send(0);
        delay_us(readings[j+1]); //delayMicroseconds
        j += 2; 
        if(j >= i) j = 0; //start from begining of recorded signal
      }
      UI.updateText("      ", 0, 40, 1, NORMAL, 8);
      delay(100);
      ledOff();
      
    }
    
    if(UI.clickDOWN()){
      ledOn();
      clear_ram();
      i = 0;
      UI.updateText(String(i), 45, 0, 1, NORMAL, 8); //update pulses
      delay(200);
      ledOff();

    }
    
    if(UI.clickB()){
      radio_R.standby();
      break;
    }
  }
}



void delay_us(unsigned long micro){
  unsigned long prev_micros = micros();
  while((micros() - prev_micros) < micro);
}

void clear_ram(){
  for(int j = 0; j < ram; j++)readings[j] = 0;
}

void dump_ram() {
  for(int j = 0; j < i; j++){
    Serial.print(readings[j]);
    Serial.print(' ');
  }
  Serial.println(); 
}

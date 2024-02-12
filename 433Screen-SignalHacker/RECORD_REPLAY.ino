 int ram = 10000;
 unsigned long readings[10000];
 int index_ram = 0; int j = 0;
 unsigned long previous_micros;
 int i;
 
void IRAM_ATTR isr() {
    readings[i] = micros() - previous_micros;
    previous_micros = micros();
    i++;
}

void recordReplay(){
  int nr_samples = 0; long timeout = 0;
  clear_ram();
  UI.drawText("PULSES:", 0, 0, 1, NORMAL);
  UI.drawText("A: record", 60, 35, 1, NORMAL);
  UI.drawText("UP: replay", 60, 45, 1, NORMAL);
  UI.drawText("DOWN: clear", 60, 55, 1, NORMAL);
  delay(500);
  
  while(1){
    if(UI.clickA()){
      recordRAM();
      delay(200);
    }

    if(UI.clickUP()){
      while(UI.clickUP()){
        UI.updateText("REP...", 0, 40, 1, NORMAL, 8);
        sendSignal(readings);
        UI.updateText("      ", 0, 40, 1, NORMAL, 8);
      }
    }
    
    if(UI.clickDOWN()){
      clear_ram();
      index_ram = 0;
      UI.updateText(String(readings[0]), 45, 0, 1, NORMAL, 8); //update pulses
      delay(200);

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

void sendSignal(unsigned long * arr){
  radio_R.txBegin();
  j = 1; UI.updateText("SEND...", 0, 24, 1, NORMAL, 19);
  while(j < arr[0]){
     radio_R.send(1);
     delayMicroseconds(arr[j]); 
     radio_R.send(0);
     delayMicroseconds(arr[j+1]);
     j += 2; 
  }
  UI.updateText("      ", 0, 24, 1, NORMAL, 10);
  delay(200);
}

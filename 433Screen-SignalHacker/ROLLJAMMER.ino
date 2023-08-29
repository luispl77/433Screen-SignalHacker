#define TIMEOUT_US 5000

int index_isr;

void IRAM_ATTR isr_rolljam() {
    readings[index_isr] = micros() - previous_micros;
    previous_micros = micros();
    index_isr++;
}

void rollJammer(){
  unsigned long replay_buffer[1000];
  clear_ram();
  UI.drawText("PULSES:", 0, 0, 1, NORMAL);
  UI.drawText("DOWN: replay", 0, 35, 1, NORMAL);
  UI.drawText("A: rec 1st", 0, 45, 1, NORMAL);
  UI.drawText("UP: rec 2nd/send 1st", 0, 55, 1, NORMAL);
  radio_R.setTransmitPower(20, PA_MODE_PA1_PA2_20dbm, OCP_OFF); //always replay at max power
  delay(400);
  while(1){
    if(UI.clickA()){
      activateJammer();
      recordRAM(); //record first
      transferRAMtoBuffer(replay_buffer);
    }
    if(UI.clickUP()){
      activateJammer();
      recordRAM(); //record second
      deactivateJammer();
      sendSignal(replay_buffer); //replay first, now RAM has a valid signal stored
    }
    if(UI.clickDOWN()){
      sendSignal(readings);
    }
    if(UI.clickB()){
      radio_R.standby();
      break;
    }
  }
}

void activateJammer(){
  ledOn();
  radio_T.send(1);
}

void deactivateJammer(){
  radio_T.send(0);
  ledOff();
}

void recordRAM(){
  unsigned long previous_millis;
  radio_R.rxBegin(); UI.updateText("Waiting signal..", 0, 24, 1, NORMAL, 12);
  index_isr = 1; //leave index 0 for storing i value (nr of pulses)

  previous_millis = millis();
  previous_micros = micros();
  attachInterrupt(DIO2_R, isr_rolljam, CHANGE);
  while(1){ 
    if((millis() - previous_millis > 2000) && (index_isr < 100)){ //two seconds of timeout waiting for a signal, less than 100 pulses show up
      UI.updateText("No signal.", 0, 24, 1, NORMAL, 19);
      break;
    }
    if((index_isr > 100) && (micros() - previous_micros < 1000000)){ //signal was caught, stay in ISR for the rest of the signal, with a timout of 1 second of no signal presense
      UI.updateText("SIGNAL FOUND", 0, 24, 1, NORMAL, 19);
      break;
    }
  }
  detachInterrupt(DIO2_R); 
  readings[0] = index_isr; //write the number of pulses to the first element
  
  UI.updateText(String(index_isr), 45, 0, 1, NORMAL, 8); //update pulses count
  
}

void transferRAMtoBuffer(unsigned long * arr){
  for(int j = 1; j < readings[0]+1; j++){
    arr[j] = readings[j];
  }
}

void dump_arr(unsigned long * arr){
  for(int j = 1; j < arr[0]+1; j++){
    Serial.print(arr[j]);
    Serial.print(", ");
  }
  Serial.println();  
}

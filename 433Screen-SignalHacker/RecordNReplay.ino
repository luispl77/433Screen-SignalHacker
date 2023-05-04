 int ram = 10000;
 unsigned long readings[10000];
 
void recordReplay(){
  unsigned long previous_micros;
  int i = 0; int j = 0;
  int nr_samples = 0;
  rec_rep.drawText("PULSES:", 0, 0, 1, NORMAL);
  rec_rep.drawText("A: record", 60, 35, 1, NORMAL);
  rec_rep.drawText("UP: replay", 60, 45, 1, NORMAL);
  rec_rep.drawText("DOWN: clear", 60, 55, 1, NORMAL);
  delay(500);
  
  while(1){
    if(rec_rep.clickA() && i < ram){
      radio_R.rxBegin(); rec_rep.updateText("REC..", 0, 40, 1, NORMAL, 8);
      ledOn(); i = 0;
      while(rec_rep.clickA() && i < ram){
        if(digitalRead(DIO2_R) == HIGH){
          previous_micros = micros();
          while(digitalRead(DIO2_R) == HIGH);
          readings[i] = micros() - previous_micros;
          previous_micros = micros();
          while(digitalRead(DIO2_R) == LOW && (micros() - previous_micros) < 1000000);//one second of zeros
          readings[i+1] = micros() - previous_micros;
          i += 2;
        }       
      }
      rec_rep.updateText(String(i), 45, 0, 1, NORMAL, 8); //update pulses
      delay(100);
      ledOff();
      i = 0;
      radio_R.standby();
      radio_R.setTransmitPower(15, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
      radio_R.txBegin();
      rec_rep.updateText("      ", 0, 40, 1, NORMAL, 8);
    }

    
    if(rec_rep.clickUP()){
      j = 0; rec_rep.updateText("REP...", 0, 40, 1, NORMAL, 8);
      ledOn();
      while(rec_rep.clickUP()){
        radio_R.send(1);
        smartdelay(readings[j]);
        radio_R.send(0);
        smartdelay(readings[j+1]);
        j += 2; 
        if(j >= i) j = 0; //start from begining of recorded signal
      }
      rec_rep.updateText("      ", 0, 40, 1, NORMAL, 8);
      delay(100);
      ledOff();
      
    }
    
    if(rec_rep.clickDOWN()){
      ledOn();
      clear_ram();
      i = 0;
      rec_rep.updateText(String(i), 45, 0, 1, NORMAL, 8); //update pulses
      delay(200);
      ledOff();

    }
    
    if(rec_rep.clickB()){
      radio_R.standby();
      break;
    }
  }
}



void smartdelay(unsigned long micro){
  delay(micro/1000);
  delayMicroseconds(micro%1000);
}

void clear_ram(){
  for(int j = 0; j < ram; j++)readings[j] = 0;
}

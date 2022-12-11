 int ram = 10000;
 unsigned long readings[10000];
void recordReplay(){
  unsigned long previous_micros;
  int i = 0;
  int nr_samples = 0;
  unselect_T();
  unselect_SD();
  radio_R.receiveBegin();
  radio_R.initializeReceive();
  unselect_R();
  radio_T.setModulationType(MOD_OOK);
  radio_T.setFrequencyMHz(433.92); 
  radio_T.initializeTransmit(15, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
  rec_rep.drawText("SPL:", 0, 0, 1, NORMAL);
  delay(500);
  for(int j = 0; j < ram; j++)readings[j] = 0;
  while(1){
    if(rec_rep.clickA() && i < ram){
      ledOn(); i = 0;
      while(rec_rep.clickA()){
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
      rec_rep.updateText(String(i), 40, 0, 1, NORMAL, 8);
      delay(300);
      ledOff();
    }

    
    if(rec_rep.clickUP()){
      i = 0;
      ledOn();
      while(rec_rep.clickUP() && i < ram){
        radio_T.send(1);
        smartdelay(readings[i]);
        radio_T.send(0);
        smartdelay(readings[i+1]);
        i += 2; 
      }
      
      delay(200);
      ledOff();
    }
    
    if(rec_rep.clickDOWN()){
      
      delay(200);

    }
    
    if(rec_rep.clickB()){

      break;
    }
  }
}

bool high(){
  if(digitalRead(DIO2_R) == HIGH){
    return true;
  }
  else{
    return false;
  }
}

bool low(){
  if(digitalRead(DIO2_R) == LOW){
    return true;
  }
  else{
    return false;
  }
}

void smartdelay(unsigned long micro){
  delay(micro/1000);
  delayMicroseconds(micro%1000);
}

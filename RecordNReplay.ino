void recordReplay(){
  long readings[5000];
  long previous_micros;
  int i;
  int nr_samples = 0;
  unselect_T();
  unselect_SD();
  radio_R.receiveBegin();
  radio_R.initializeReceive();
  unselect_R();
  radio_T.setModulationType(MOD_OOK);
  radio_T.setFrequencyMHz(433.92); 
  radio_T.initializeTransmit(15, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
  delay(500);
  for(int j = 0; j < 5000; j++)readings[j] = 0;
  while(1){
    if(rec_rep.clickA()){
      ledOn(); i = 0;
      while(rec_rep.clickA()){
        if(digitalRead(DIO2_R) == HIGH){
          previous_micros = micros();
          while(digitalRead(DIO2_R) == HIGH);
          readings[i] = micros() - previous_micros;
          while(digitalRead(DIO2_R) == LOW && (micros() - readings[i]) < 10000000);//one second of zeros
          readings[i+1] = micros() - readings[i];
          //Serial.print(readings[i]); Serial.print(" "); Serial.println(readings[i+1]);
          i += 2;
        }       
      }
      rec_rep.updateText(String(i), 40, 20, 1, NORMAL, 8);
      Serial.println(String(readings[0]));

      delay(300);
      ledOff();
    }

    
    if(rec_rep.clickUP()){
      i = 0;
      ledOn();
      while(rec_rep.clickUP() && i < 5000){
        /*radio_T.send(1);
        Serial.print(readings[i]);//smartdelay(readings[i]);  Serial.print(readings[i]);
        //radio_T.send(0);
        Serial.print(" ");
        Serial.println(readings[i+1]);//smartdelay(readings[i+1]);  
        i += 2; */ 
      }
      ledOff();
      delay(200);
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

void smartdelay(int micro){
  delay(micro/1000);
  delay(micro%1000);
}

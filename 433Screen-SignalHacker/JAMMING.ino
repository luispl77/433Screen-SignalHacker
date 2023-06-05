void sendJammingSignal(){
  int dbm = radio_T._dbm;
  int scw_cursor = 0;
  float frequency = radio_T._frequency;
  bool onOff = false;
  send_jam.drawText("frequency:", 0, 20, 1, INVERS); send_jam.drawText(String(frequency, 3), 63, 20, 1, NORMAL);
  send_jam.drawText("dbm: ", 0, 40, 1, NORMAL); send_jam.drawText(String(dbm), 27, 40, 1, NORMAL);
  send_jam.drawText("SEND", 80, 50, 1, NORMAL);
  radio_T.setTransmitPower(dbm, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
  radio_T.txBegin();
  delay(200);
  while(1){
    if(send_jam.clickA()){
      rotate(&scw_cursor);
      delay(300);
    }
    if(send_jam.clickUP()){
      increase_dbm_frequency(&scw_cursor, &frequency, &dbm);
      delay(200);
    }
    if(send_jam.clickDOWN()){
      decrease_dbm_frequency(&scw_cursor, &frequency, &dbm);
      delay(200);
    }
    if(send_jam.clickB()){
      pushEEPROMSettings(); //save changes
      break; 
    }
  }
}

void increase_dbm_frequency(int * scw_cursor, float *frequency, int* dbm){
  if(*scw_cursor == 0){
    (*frequency) = (*frequency) + 0.001; radio_T.setFrequencyMHz(*frequency);
    Serial.println(*frequency); send_jam.updateText(String(*frequency, 3), 63, 20, 1, NORMAL, 8);
  }
  if(*dbm < 20 && *scw_cursor == 1){
    (*dbm)++; radio_T.setTransmitPower(*dbm, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
    Serial.println(*dbm); send_jam.updateText(String(*dbm), 27, 40, 1, NORMAL, 2);
  }
  if(*scw_cursor == 2){
    ledOn();
    radio_T.send(1);
  }
}

void decrease_dbm_frequency(int * scw_cursor, float *frequency, int* dbm){
  if(*scw_cursor == 0){
    (*frequency) = (*frequency) - 0.001; radio_T.setFrequencyMHz(*frequency);
    Serial.println(*frequency); send_jam.updateText(String(*frequency, 3), 63, 20, 1, NORMAL, 8);
  }
  if(*dbm > 5 && *scw_cursor == 1){
    (*dbm)--; radio_T.setTransmitPower(*dbm, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
    Serial.println(*dbm); send_jam.updateText(String(*dbm), 27, 40, 1, NORMAL, 2);
  }
  if(*scw_cursor == 2){
    ledOff();
    radio_T.send(0);
  }
}

void rotate(int * scw_cursor){
  (*scw_cursor)++;
  if(*scw_cursor == 3) *scw_cursor = 0;
      if(*scw_cursor == 0){
        send_jam.updateText("frequency:", 0, 20, 1, INVERS, 9); //Serial.println("updated freq");      
        send_jam.updateText("SEND", 80, 50, 1, NORMAL, 5);
      }
      if(*scw_cursor == 1){
        send_jam.updateText("dbm:", 0, 40, 1, INVERS, 3);//Serial.println("updated dbm"); //update current 
        send_jam.updateText("frequency:", 0, 20, 1, NORMAL, 12); //normalize previous
        
      }
      if(*scw_cursor == 2){
        send_jam.updateText("SEND", 80, 50, 1, INVERS, 5); //Serial.println("updated SEND");
        send_jam.updateText("dbm:", 0, 40, 1, NORMAL, 5);
      }
}

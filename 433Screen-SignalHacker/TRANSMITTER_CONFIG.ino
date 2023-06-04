
void transmitterConfig(){
  int mod_cursor_T = radio_T._modulation;
  int _frequency_dev = radio_T.getFrequencyDev();
  int cursor = 0;
  int max_cursor = 3;
  float _frequency = radio_T._frequency;
  int dbm = radio_T._dbm;
  t_config.drawText("A: scroll", 72, 50, 1, NORMAL);
  t_config.drawText(String(_frequency, 3), 0, 0, 1, NORMAL);
  t_config.drawText(String(dbm), 0, 10, 1, NORMAL);
  t_config.drawText(mod[mod_cursor_T], 0, 20, 1, NORMAL);
  t_config.drawText(String(_frequency_dev), 0, 30, 1, NORMAL);
  t_config.drawText("<", 50, 10*_cursor, 1, NORMAL);
  while(1){
    if(t_config.clickA()){
      cursor++; if(cursor == max_cursor + 1) cursor = 0;
      t_config.updateText(" ", 50, (cursor == 0) ? max_cursor*10 : (cursor * 10  - 10), 1, NORMAL, 1);
      t_config.drawText("<", 50, 10*cursor, 1, NORMAL);
      //Serial.print("cursor "); Serial.println(cursor);
      delay(300);
    }
    if(t_config.clickUP()){
      while(t_config.clickUP()){
        triggerIncrease_T(&dbm, &mod_cursor_T, &_frequency_dev, &cursor);
        speedDelay();
      }
      speed_cnt = 0; //slow back down
      ms = 200;
      increment = 0.001;
      delay(200);
    }
    if(t_config.clickDOWN()){
      while(t_config.clickDOWN()){
        triggerDecrease_T(&dbm, &mod_cursor_T, &_frequency_dev, &cursor);
        speedDelay();
      }
      speed_cnt = 0; //slow back down
      ms = 200;
      increment = 0.001;
      delay(200);
    }
    if(t_config.clickB()){
      pushEEPROMSettings();
      printEEPROMSettings();
      //radio_T.standby();
      break;
    }
  }
}

void triggerIncrease_T(int * _dbm, int * _mod_cursor, int * _frequency_dev, int * _cursor){
  if(*_cursor == 0){
    radio_T.setFrequencyMHz(radio_T._frequency + increment); 
    t_config.updateText(String(radio_T._frequency, 3), 0, 0, 1, NORMAL, 8);
  }
  else if(*_cursor == 1){
    if(*_dbm < 20){(*_dbm)++;} radio_T.setTransmitPower(*_dbm, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
    t_config.updateText(String(*_dbm), 0, 10, 1, NORMAL, 8);
  }
  else if(*_cursor == 2){
    (*_mod_cursor)++; if(*_mod_cursor > 1) {
      (*_mod_cursor) = 0;
    }
    radio_T.setModulationType(modulation[*_mod_cursor]);
    t_config.updateText(mod[(*_mod_cursor)], 0, 20, 1, NORMAL, 8);
  }
  if(*_cursor == 3){
    if(*_frequency_dev < 300000) {
      (*_frequency_dev) += 61;
    }
    radio_T.setFrequencyDev(*_frequency_dev);
    t_config.updateText(String(*_frequency_dev), 0, 30, 1, NORMAL, 8);
  }
}

void triggerDecrease_T(int * _dbm, int * _mod_cursor, int * _frequency_dev, int * _cursor){
  if(*_cursor == 0){
    radio_T.setFrequencyMHz(radio_T._frequency - increment);
    t_config.updateText(String(radio_T._frequency, 3), 0, 0, 1, NORMAL, 8);
  }
  else if(*_cursor == 1){
    if(*_dbm > 0){(*_dbm)--;} radio_T.setTransmitPower(*_dbm, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
    t_config.updateText(String(*_dbm), 0, 10, 1, NORMAL, 8);
  }
  else if(*_cursor == 2){
    (*_mod_cursor)--; if(*_mod_cursor < 0) {
      (*_mod_cursor) = 1;
    }
    radio_T.setModulationType(modulation[*_mod_cursor]);
    t_config.updateText(mod[(*_mod_cursor)], 0, 20, 1, NORMAL, 8);
  }
  if(*_cursor == 3){
    if(*_frequency_dev > 0) {
      (*_frequency_dev) -= 61;
    }
    radio_T.setFrequencyDev(*_frequency_dev);
    t_config.updateText(String(*_frequency_dev), 0, 30, 1, NORMAL, 8);
  }
}

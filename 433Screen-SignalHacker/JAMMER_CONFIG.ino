/*
 * Three different jamming modes: continous wave, square wave and 
 * sweep mode, which sweeps a selectable frequency range repeatedly, 
 * to jam a range of frequencies.
 */

#define CONT_MODE 0  //three different jamming modes
#define SQR_MODE 1
#define SWEEP_MODE 2
int _mode = CONT_MODE;
String modes[3] = {"CONT", "SQUARE", "SWEEP"};
void jammerConfig(){
  int mod_cursor_T = radio_T._modulation;
  int _frequency_dev = radio_T.getFrequencyDev();
  int cursor = 0;
  int max_cursor = 4;
  float _frequency = radio_T._frequency;
  int dbm = radio_T._dbm;
  j_config.drawText("A: scroll", 72, 50, 1, NORMAL);
  j_config.drawText(String(_frequency, 3), 0, 0, 1, NORMAL);
  j_config.drawText(String(dbm), 0, 10, 1, NORMAL);
  j_config.drawText(mod[mod_cursor_T], 0, 20, 1, NORMAL);
  j_config.drawText(String(_frequency_dev), 0, 30, 1, NORMAL);
  j_config.drawText(String(modes[_mode]), 0, 40, 1, NORMAL);
  j_config.drawText("<", 50, 10*cursor, 1, NORMAL);
  while(1){
    if(j_config.clickA()){
      cursor++; if(cursor == max_cursor + 1) cursor = 0;
      j_config.updateText(" ", 50, (cursor == 0) ? max_cursor*10 : (cursor * 10  - 10), 1, NORMAL, 1);
      j_config.drawText("<", 50, 10*cursor, 1, NORMAL);
      delay(300);
    }
    if(j_config.clickUP()){
      while(j_config.clickUP()){
        triggerIncrease_T(&dbm, &mod_cursor_T, &_frequency_dev, &cursor);
        speedDelay();
      }
      speed_cnt = 0; //slow back down
      ms = 200;
      increment = 0.001;
      delay(200);
    }
    if(j_config.clickDOWN()){
      while(j_config.clickDOWN()){
        triggerDecrease_T(&dbm, &mod_cursor_T, &_frequency_dev, &cursor);
        speedDelay();
      }
      speed_cnt = 0; //slow back down
      ms = 200;
      increment = 0.001;
      delay(200);
    }
    if(j_config.clickB()){
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
    j_config.updateText(String(radio_T._frequency, 3), 0, 0, 1, NORMAL, 8);
  }
  else if(*_cursor == 1){
    if(*_dbm < 20){(*_dbm)++;} radio_T.setTransmitPower(*_dbm, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
    j_config.updateText(String(*_dbm), 0, 10, 1, NORMAL, 8);
  }
  else if(*_cursor == 2){
    (*_mod_cursor)++; if(*_mod_cursor > 1) {
      (*_mod_cursor) = 0;
    }
    radio_T.setModulationType(modulation[*_mod_cursor]);
    j_config.updateText(mod[(*_mod_cursor)], 0, 20, 1, NORMAL, 8);
  }
  if(*_cursor == 3){
    if(*_frequency_dev < 300000) {
      (*_frequency_dev) += 61;
    }
    radio_T.setFrequencyDev(*_frequency_dev);
    j_config.updateText(String(*_frequency_dev), 0, 30, 1, NORMAL, 8);
  }
  if(*_cursor == 4){
    if(_mode < 2)
      _mode++;
    else
      _mode = 0;
    j_config.updateText(modes[_mode], 0, 40, 1, NORMAL, 11);
  }
}

void triggerDecrease_T(int * _dbm, int * _mod_cursor, int * _frequency_dev, int * _cursor){
  if(*_cursor == 0){
    radio_T.setFrequencyMHz(radio_T._frequency - increment);
    j_config.updateText(String(radio_T._frequency, 3), 0, 0, 1, NORMAL, 8);
  }
  else if(*_cursor == 1){
    if(*_dbm > 0){(*_dbm)--;} radio_T.setTransmitPower(*_dbm, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
    j_config.updateText(String(*_dbm), 0, 10, 1, NORMAL, 8);
  }
  else if(*_cursor == 2){
    (*_mod_cursor)--; if(*_mod_cursor < 0) {
      (*_mod_cursor) = 1;
    }
    radio_T.setModulationType(modulation[*_mod_cursor]);
    j_config.updateText(mod[(*_mod_cursor)], 0, 20, 1, NORMAL, 8);
  }
  if(*_cursor == 3){
    if(*_frequency_dev > 0) {
      (*_frequency_dev) -= 61;
    }
    radio_T.setFrequencyDev(*_frequency_dev);
    j_config.updateText(String(*_frequency_dev), 0, 30, 1, NORMAL, 8);
  }
  if(*_cursor == 4){
    if(_mode > 0)
      _mode--;
    else
      _mode = 2;
    j_config.updateText(modes[_mode], 0, 40, 1, NORMAL, 11);
  }
}

  byte bandwidth[24] = {OOK_BW_1_3, OOK_BW_1_6, OOK_BW_2_0, OOK_BW_2_6, OOK_BW_3_9, OOK_BW_5_2, OOK_BW_6_3,  OOK_BW_7_8, OOK_BW_10_4, OOK_BW_12_5, OOK_BW_15_6, 
                        OOK_BW_20_8, OOK_BW_25_0, OOK_BW_31_3, OOK_BW_41_7, OOK_BW_50_0, OOK_BW_62_5, OOK_BW_83_3, OOK_BW_100_0, OOK_BW_125_0,
                        OOK_BW_166_7, OOK_BW_200_0, OOK_BW_250_0};
  float bw[24] = {1.3, 1.6, 2.0, 2.6, 3.1, 3.9, 5.2, 6.3, 7.8, 10.4, 12.5, 15.6, 20.8, 25.0, 31.3, 41.7, 50.0, 62.5, 83.3, 100.0, 125.0, 166.7, 200.0, 250.0};

  byte lna_gain[7] = {RF_LNA_GAINSELECT_AUTO, RF_LNA_GAINSELECT_MAX, RF_LNA_GAINSELECT_MAXMINUS6, RF_LNA_GAINSELECT_MAXMINUS12, RF_LNA_GAINSELECT_MAXMINUS24,
                      RF_LNA_GAINSELECT_MAXMINUS36, RF_LNA_GAINSELECT_MAXMINUS48};
  String lg[7] = {"AUTO", "MAX", "MAX-6", "MAX-12", "MAX-24", "MAX-36", "MAX-48"};
  
  byte modulation[2] = {MOD_FSK, MOD_OOK};
  String mod[2] = {"FSK", "OOK"};
  
  
  int lna_cursor;
  int mod_cursor;
  float frequency_dev;
  int bw_cursor;
  int _cursor = 0; //making this global means the cursor remembers where it left off after leaving r_config
  int max_cursor = 5;
  int fixedThreshold;
  float frequency;
  int speed_cnt = 0;
  int ms = 200;
  float increment = 0.001;
void receiverConfig(){
  lna_cursor = radio_R._lna_gain;
  mod_cursor = radio_R._modulation;
  frequency_dev = radio_R.getFrequencyDev();
  bw_cursor = radio_R.getBandwidthIndex();
  frequency = radio_R._frequency;
  fixedThreshold = radio_R._fixed_threshold;
  r_config.drawText("A: scroll", 72, 50, 1, NORMAL);
  r_config.drawText(String(frequency, 3), 0, 0, 1, NORMAL);
  r_config.drawText(String(fixedThreshold), 0, 10, 1, NORMAL);
  r_config.drawText(String(bw[bw_cursor]), 0, 20, 1, NORMAL);
  r_config.drawText(lg[lna_cursor], 0, 30, 1, NORMAL);
  r_config.drawText(mod[mod_cursor], 0, 40, 1, NORMAL);
  r_config.drawText(String(frequency_dev, 0), 0, 50, 1, NORMAL);
  r_config.drawText("<", 50, 10*_cursor, 1, NORMAL);
  while(1){
    if(r_config.clickA()){
      changeCursor();
      delay(200);
    }
    if(r_config.clickUP()){
      while(r_config.clickUP()){
        triggerIncrease();
        speedDelay();
      }
      speed_cnt = 0; //slow back down
      ms = 200;
      increment = 0.001;
    }
    if(r_config.clickDOWN()){
      while(r_config.clickDOWN()){
        triggerDecrease();
        speedDelay();
      }
      speed_cnt = 0; //slow back down
      ms = 200;
      increment = 0.001;
    }
    if(r_config.clickB()){
      radio_R.standby();
      pushEEPROMSettings(); //save changes
      break;
    }
  }
}

void changeCursor(){
  _cursor++; if(_cursor == max_cursor + 1) _cursor = 0;
  r_config.updateText(" ", 50, (_cursor == 0) ? max_cursor*10 : (_cursor * 10  - 10), 1, NORMAL, 1);
  r_config.drawText("<", 50, 10*_cursor, 1, NORMAL);
}

void triggerIncrease(){
  if(_cursor == 0){
    radio_R.setFrequencyMHz(radio_R._frequency + increment); 
    r_config.updateText(String(radio_R._frequency, 3), 0, 0, 1, NORMAL, 8);
  }
  else if(_cursor == 1){
    radio_R.setFixedThreshold(radio_R._fixed_threshold + 1);
    r_config.updateText(String(radio_R._fixed_threshold), 0, 10, 1, NORMAL, 8);
  }
  else if(_cursor == 2){
    bw_cursor++; if(bw_cursor > 22) bw_cursor = 0;
    radio_R.setBandwidth(bandwidth[bw_cursor]);
    r_config.updateText(String(bw[bw_cursor]), 0, 20, 1, NORMAL, 8);
  }
  else if(_cursor == 3){
    lna_cursor++; if(lna_cursor > 6) lna_cursor = 0;
    radio_R.setLNAGain(lna_gain[lna_cursor]);
    r_config.updateText(lg[lna_cursor], 0, 30, 1, NORMAL, 8);
  }
  else if(_cursor == 4){
    mod_cursor++; if(mod_cursor > 1) mod_cursor = 0;
    radio_R.setModulationType(modulation[mod_cursor]);
    r_config.updateText(mod[mod_cursor], 0, 40, 1, NORMAL, 8);
  }
  if(_cursor == 5){
    if(frequency_dev < 300000) frequency_dev += 61;
    radio_R.setFrequencyDev(frequency_dev);
    r_config.updateText(String(frequency_dev, 0), 0, 50, 1, NORMAL, 8);
  }
}

void triggerDecrease(){
  if(_cursor == 0){
    radio_R.setFrequencyMHz(radio_R._frequency - increment);
    r_config.updateText(String(radio_R._frequency, 3), 0, 0, 1, NORMAL, 8);
  }
  else if(_cursor == 1){
    radio_R.setFixedThreshold(radio_R._fixed_threshold - 1); 
    r_config.updateText(String(radio_R._fixed_threshold), 0, 10, 1, NORMAL, 8);
  }
  else if(_cursor == 2){
    bw_cursor--; if(bw_cursor < 0) bw_cursor = 22;
    radio_R.setBandwidth(bandwidth[bw_cursor]);
    r_config.updateText(String(bw[bw_cursor]), 0, 20, 1, NORMAL, 8);
  }
  else if(_cursor == 3){
    lna_cursor--; if(lna_cursor < 0) lna_cursor = 6;
    radio_R.setLNAGain(lna_gain[lna_cursor]);
    r_config.updateText(lg[lna_cursor], 0, 30, 1, NORMAL, 8);
  }
  else if(_cursor == 4){
    mod_cursor--; if(mod_cursor < 0) mod_cursor = 1;
    radio_R.setModulationType(modulation[mod_cursor]);
    r_config.updateText(mod[mod_cursor], 0, 40, 1, NORMAL, 8);
  }
  if(_cursor == 5){
    if(frequency_dev > 0) frequency_dev -= 61;
    radio_R.setFrequencyDev(frequency_dev);
    r_config.updateText(String(frequency_dev, 0), 0, 50, 1, NORMAL, 8);
  }
}

void speedDelay(){
  speed_cnt++;
  if(speed_cnt == 4)
    ms = 150;
  else if(speed_cnt == 8){
    ms = 75;
  }
  else if(speed_cnt == 16){
    increment = 0.01;
  }
  else if(speed_cnt == 50){
    increment = 0.1;
  }
  else if(speed_cnt == 85){
    increment = 1;
    ms = 30;
  }
  delay(ms);
}

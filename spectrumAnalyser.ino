void spectrumAnalyser(){ //sweep 425-450MHz and find highest frequency.
  unselect_T();
  unselect_SD();
  radio_R.initializeReceive();
  unselect_R(); unselect_SD(); 
  delay(200);
  float current_frequency = 425.000; //starting frequency
  byte highest_rssi = 255;
  byte rssi_reading;
  while(1){
    //spc_analyser.updateText(String(digitalRead(DIO2_R)), 40, 0, 1, NORMAL, 1);
    //spc_analyser.updateText(String(radio_R.readReg(REG_RSSIVALUE)), 0, 0, 1, NORMAL, 4);
    
    radio_R.setFrequencyMHz(current_frequency);
    rssi_reading = radio_R.readReg(REG_RSSIVALUE);
    Serial.print(current_frequency); Serial.print(" "); Serial.println(rssi_reading);
    if(rssi_reading < highest_rssi){
      highest_rssi = rssi_reading;
      spc_analyser.updateText(String(current_frequency), 40, 20, 1, NORMAL, 7);
    }
    
    current_frequency += 0.01;
    if(current_frequency >= 450) current_frequency = 425.000;
    
    if(spc_analyser.clickB()){

      break;
    }
  }
}

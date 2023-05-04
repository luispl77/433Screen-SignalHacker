void spectrumAnalyser(){ //sweep 425-450MHz and find highest frequency.
  unselect_SD();
  radio_R.rxBegin();
  delay(200);
  float current_frequency = 425.000; //starting frequency
  float lower_limit = 425.000;
  float upper_limit = 450.000;
  float gap = upper_limit - lower_limit;
  int inc_index = 0;
  float increments[5] = {0.250, 0.200, 0.100, 0.50, 0.0208};
  byte bandwidths[5] = {OOK_BW_250_0, OOK_BW_200_0, OOK_BW_100_0, OOK_BW_50_0, OOK_BW_20_8};
  float increment = 0.250; //start with highest bandwidth 250 - 200 - 100 - 50 - 20.8
  float best_frequency = (upper_limit + lower_limit)/2; //center frequency of the search
  byte highest_rssi = 200;
  byte rssi_reading;
  int division = 10;
  bool found = false;
  while(1){
    //highest_rssi = 200;
    current_frequency = best_frequency - (gap/2);
    for(int i = 0; i < gap/increment; i++){
      current_frequency += increment;
      radio_R.setFrequencyMHz(current_frequency);
      rssi_reading = read_rssi();
      Serial.print(current_frequency, 3); Serial.print(" "); Serial.print(rssi_reading); Serial.print(" "); Serial.println(gap);
      if(rssi_reading < highest_rssi){
        highest_rssi = rssi_reading;
        best_frequency = current_frequency;
        found = true;
      }
    }
    spc_analyser.updateText(String(best_frequency, 3), 40, 20, 1, NORMAL, 8);
    if (increment >= 0.0208 && found){ //shorten the search but increase precision
      if(inc_index < 4)inc_index++; //go down in step, increasing precision
      gap /= (increment/increments[inc_index]); //find ratio to find new shorter gap
      increment = increments[inc_index]; //update new increment
      radio_R.setBandwidth(bandwidths[inc_index]);
    } 
    
    
    
    
    if(spc_analyser.clickB()){

      break;
    }
  }
}

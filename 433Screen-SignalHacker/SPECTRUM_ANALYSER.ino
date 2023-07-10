/* sweep frequency and evaluate energy to determine the center frequency
 * (in works)
 * Frequency Hop time on the RFM69HW: 200KHz - 20us; 25 MHz - 80 us.
 * To cover a 25 MHz range, should take about (25/0.2)*20 = 2500 us,
 * This would be in 200KHZ steps, but that is too high,
 * So for 40 KHZ steps, it could take ~12-20 ms
 */
void spectrumAnalyser(){ //sweep 425-450MHz and find highest frequency.
  float current_frequency = 425.000; //starting frequency
  float lower_limit = 425.000;
  float upper_limit = 450.000;
  int inc_index = 0;
  byte bandwidths[5] = {OOK_BW_250_0, OOK_BW_200_0, OOK_BW_100_0, OOK_BW_50_0, OOK_BW_20_8};
  float freq_step = 0.020; //start with highest bandwidth 250 - 200 - 100 - 50 - 20.8
  float best_frequency; //center frequency of the search
  byte lowest_rssi = 200;
  byte rssi_reading;
  int division = 10;
  bool found = false;
  radio_R.rxBegin();
  radio_R.setBandwidth(OOK_BW_1_3); //for 40 khz steps
  radio_R.setLNAGain(RF_LNA_GAINSELECT_AUTO);
  radio_R.setModulationType(MOD_OOK);
  while(1){
      while(current_frequency < upper_limit){
        current_frequency += freq_step; 
        radio_R.setFrequencyMHz(current_frequency);
        delayMicroseconds(80); //wait for pll lock time
        rssi_reading = read_rssi();
        if(rssi_reading < lowest_rssi){
          lowest_rssi = rssi_reading;
          best_frequency = current_frequency;
        }
      }
      
      current_frequency = lower_limit;
      UI.updateText(String(best_frequency, 3), 40, 20, 1, NORMAL, 8);
      UI.updateText(String(lowest_rssi), 40, 30, 1, NORMAL, 8);
    
    if(UI.clickB()){
      radio_R.standby();
      break;
    }
  }
}

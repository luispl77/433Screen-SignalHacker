void spectrumAnalyser(){
  unselect_T();
  unselect_SD();
  radio_R.initializeReceive();
  unselect_R(); unselect_SD(); 
  delay(200);
  while(1){
    spc_analyser.updateText(String(digitalRead(DIO2_R)), 40, 0, 1, NORMAL, 1);
    spc_analyser.updateText(String(radio_R.readReg(REG_RSSIVALUE)), 0, 0, 1, NORMAL, 4);
    if(spc_analyser.clickB()){

      break;
    }
  }
}

void spectrumAnalyser(){
  send_cst.drawText("frequency:", 0, 20, 1, INVERS); send_cst.drawText(String(frequency, 3), 63, 20, 1, NORMAL);
  send_cst.drawText("dbm: ", 0, 40, 1, NORMAL); send_cst.drawText(String(dbm), 27, 40, 1, NORMAL);
  send_cst.drawText("SEND", 80, 50, 1, NORMAL);
  unselect_R(); unselect_SD(); //avoid SPI interference for transmitter
  radio_T.initialize(); Serial.println("initialization done.");
  radio_T.setModulationType(MOD_OOK);
  radio_T.setFrequencyMHz(frequency); Serial.println("frequency set.");
  radio_T.initializeTransmit(dbm, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
  delay(200);
  while(1){
    if(send_cst.clickA()){
      delay(300);
    }
    if(send_cst.clickUP()){
      delay(200);
    }
    if(send_cst.clickDOWN()){
      delay(200);
    }
    if(send_cst.clickB()){

      break;
    }
  }
}

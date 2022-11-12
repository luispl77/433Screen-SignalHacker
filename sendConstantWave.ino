void sendConstantWave(){
  int dbm = 10;
  unselect_R(); unselect_SD(); //avoid SPI interference for transmitter
  radio_T.initialize(); Serial.println("initialization done.");
  radio_T.setModulationType(MOD_OOK);
  radio_T.setFrequencyMHz(420.000); Serial.println("frequency set.");
  radio_T.initializeTransmit(dbm, PA_MODE_PA0);
  delay(200);
  while(1){
    if(send_cst.clickA()){
      ledOn();
      radio_T.send(1);
    }
    if(send_cst.clickUP()){
      if(dbm < 13)dbm++; radio_T.initializeTransmit(dbm, PA_MODE_PA0);
      Serial.println(dbm);
      delay(400);
    }
    if(send_cst.clickDOWN()){
      if(dbm > -18) dbm--; radio_T.initializeTransmit(dbm, PA_MODE_PA0);
      Serial.println(dbm);
      delay(400);
    }
    if(send_cst.clickB()){
      
      break;
    }
    if(!send_cst.clickA()){
      ledOff();
      radio_T.send(0);
    }
  }
}

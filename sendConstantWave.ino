void sendConstantWave(){
  int dbm = 10;
  send_cst.drawText("frequency: ", 0, 20, 1, NORMAL); send_cst.drawText("433.920", 60, 20, 1, NORMAL);
  send_cst.drawText("dbm: ", 0, 40, 1, NORMAL); send_cst.drawText(String(dbm), 25, 40, 1, NORMAL);
  unselect_R(); unselect_SD(); //avoid SPI interference for transmitter
  radio_T.initialize(); Serial.println("initialization done.");
  radio_T.setModulationType(MOD_OOK);
  radio_T.setFrequencyMHz(433.920); Serial.println("frequency set.");
  radio_T.initializeTransmit(dbm, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
  delay(200);
  while(1){
    if(send_cst.clickA()){
      ledOn();
      radio_T.send(1);
    }
    if(send_cst.clickUP()){
      if(dbm < 20)dbm++; radio_T.initializeTransmit(dbm, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
      Serial.println(dbm); send_cst.updateText(String(dbm), 25, 40, 1, NORMAL, 2);
      delay(300);
    }
    if(send_cst.clickDOWN()){
      if(dbm > 5) dbm--; radio_T.initializeTransmit(dbm, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
      Serial.println(dbm); send_cst.updateText(String(dbm), 25, 40, 1, NORMAL, 2);
      delay(300);
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

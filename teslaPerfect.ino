int am270prfct[236] = {400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 1200, 400, 400, 400, 400, 800, 800, 400, 400, 800, 800, 800, 800, 400, 400, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 400, 400, 800, 400, 400, 800, 800, 400, 400, 800, 400, 400, 800, 400, 400, 400, 400, 800, 400, 400, 400, 400, 800, 400, 400, 800, 800, 400, 400, 800, 800, 800, 400, 400, 400, 400, 400, 400, 800, 400, 400, 800, 400, 400, 800, 1200, 400, 400, 400, 400, 800, 800, 400, 400, 800, 800, 800, 800, 400, 400, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 400, 400, 800, 400, 400, 800, 800, 400, 400, 800, 400, 400, 800, 400, 400, 400, 400, 800, 400, 400, 400, 400, 800, 400, 400, 800, 800, 400, 400, 800, 800, 800, 400, 400, 400, 400, 400, 400, 800, 400, 400, 800, 400, 400, 800, 1200, 400, 400, 400, 400, 800, 800, 400, 400, 800, 800, 800, 800, 400, 400, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 400, 400, 800, 400, 400, 800, 800, 400, 400, 800, 400, 400, 800, 400, 400, 400, 400, 800, 400, 400, 400, 400, 800, 400, 400, 800, 800, 400, 400, 800, 800, 800, 400, 400, 400, 400, 400, 400, 800, 400, 400, 800, 400, 400, 400, 100};
void teslaPerfect(){
  int i = 0;
  radio_T.setTransmitPower(20, PA_MODE_PA1_PA2_20dbm, OCP_OFF); //max power
  radio_T.initializeTransmit();
  tesla.drawText("UP: prfct AM270", 30, 45, 1, NORMAL);
  tesla.drawText("DOWN: prfct AM650", 30, 55, 1, NORMAL);
  delay(400);
  while(1){
    if(tesla.clickA()){
      
    }
    if(tesla.clickUP()){
      i = 0; ledOn();
      while(tsla.clickUP() && i <= 234){ //total of 236 numbers, minus 2
        radio_T.send(1);
        delayMicroseconds(am270prfct[i]);
        radio_T.send(0);
        delayMicroseconds(am270prfct[i+1]);
        i += 2;
      }
      ledOff();
      delay(24);
    }
    if(tsla.clickDOWN()){
      delay(100);
    }
    if(tsla.clickB()){
      radio_T.standby();
      break;
    }
  }
}

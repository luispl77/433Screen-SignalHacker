void carMode(){
  unselect_R(); unselect_SD();
  radio_T.initialize();
  radio_T.setMode(RF69OOK_MODE_STANDBY);
  radio_T.setModulationType(MOD_OOK);
  radio_T.setFrequencyMHz(frequency_ISM);
  radio_T.initializeTransmit(21, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
  
  car_mode.drawText("A: right", 0, 0, 1, NORMAL);
  car_mode.drawText("B: left", 0, 10, 1, NORMAL);
  car_mode.drawText("UP: forward", 0, 20, 1, NORMAL);
  car_mode.drawText("DOWN: backward", 0, 30, 1, NORMAL);
  
  car_mode.drawText("EN: reboot/exit", 0, 50, 1, NORMAL);
  
  while(1){
    if(car_mode.clickA()){
     pulse(900);
    }
    if(!car_mode.clickA() && !car_mode.clickB()){
      pulse(1100); 
    }
    if(car_mode.clickB()){
      pulse(1300); 
    }
    
    
    
    if(car_mode.clickUP()){
      pulse(1500); 
    }
    if(!car_mode.clickUP() && !car_mode.clickDOWN()){
     pulse(1700); 
    }
    if(car_mode.clickDOWN()){
     pulse(1900); 
    }
     
  }
}




void speed50(){
  for(int i = 0; i < 20; i++) pulse(2750);
}

void speed60(){
  for(int i = 0; i < 20; i++) pulse(3250);
}

void speed70(){
  for(int i = 0; i < 20; i++) pulse(3750);
}

void speed80(){
  for(int i = 0; i < 20; i++) pulse(4250);
}

void speed90(){
  for(int i = 0; i < 20; i++) pulse(4750);
}

void speed100(){
  for(int i = 0; i < 20; i++) pulse(5250);
}

void pulse(int duration) {
  digitalWrite(DIO2_T, HIGH);
  delayMicroseconds(duration);
  digitalWrite(DIO2_T, LOW);
  delayMicroseconds(duration/10);
}

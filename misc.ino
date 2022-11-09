void initializeTransmit_R(){
  Serial.println("Transmit R initialization:");
  unselect_T();
  unselect_SD();
  radio_R.initialize(); Serial.println("initialization done.");
  radio_R.transmitBegin(); Serial.println("transmission begin.");
  radio_R.setFrequencyMHz(430.000); Serial.println("frequency set.");
  radio_R.setPowerLevel(35); Serial.println("power level set.");
  radio_R.writeReg(REG_TESTPA1, 0x5D); 
  radio_R.writeReg(REG_TESTPA2, 0x7C); Serial.println("high power regs set.");
  radio_R.setHighPower(1); Serial.println("PA stages set.");
  Serial.print("frequency: ");Serial.println(radio_R.getFrequency());
  radio_R.readAllRegs();
}

void initializeTransmit_T(){
  Serial.println("Transmit T initialization:");
  unselect_R();
  unselect_SD();
  radio_T.initialize(); Serial.println("initialization done.");
  radio_T.transmitBegin(); Serial.println("transmission begin.");
  radio_T.setFrequencyMHz(450.000); Serial.println("frequency set.");
  radio_T.setPowerLevel(35); Serial.println("power level set.");
  radio_T.writeReg(REG_TESTPA1, 0x5D); 
  radio_T.writeReg(REG_TESTPA2, 0x7C); Serial.println("high power regs set.");  
  radio_T.setHighPower(1); Serial.println("PA stages set."); 
  Serial.print("frequency: ");Serial.println(radio_T.getFrequency());
  radio_T.readAllRegs();
}

void unselect_R(){
  pinMode(R_CS, OUTPUT);
  digitalWrite(R_CS, HIGH);
}

void unselect_T(){
  pinMode(T_CS, OUTPUT);
  digitalWrite(T_CS, HIGH);
}

void unselect_SD(){
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);
}

void ledOn(){
  digitalWrite(BUILTIN_LED, HIGH);
}

void ledOff(){
  digitalWrite(BUILTIN_LED, LOW);
}

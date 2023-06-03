/* This is code for pushing the registers to the eeprom, and pulling from the 
 * eeprom and writing to the register.
 * 13 registers are saved. 
 * Furthremore, the class variables are also updated using updatedVariables()
 * which reads the registers and updates the varibles from their default 
 * state after power up.
 */
#define EEPROM_SIZE 13
#define EEPROM_SIZE_T 8

byte addr[EEPROM_SIZE] = {
    REG_PALEVEL,
    REG_OOKPEAK,
    REG_RXBW,
    REG_FRFMSB,
    REG_FRFMID,
    REG_FRFLSB,
    REG_OOKFIX,
    REG_LNA,
    REG_OCP,
    REG_DATAMODUL,
    REG_TESTLNA,
    REG_FDEVMSB,
    REG_FDEVLSB
  };

byte addr_T[EEPROM_SIZE_T] = {
    REG_PALEVEL,
    REG_FRFMSB,
    REG_FRFMID,
    REG_FRFLSB,
    REG_OCP,
    REG_DATAMODUL,
    REG_FDEVMSB,
    REG_FDEVLSB
  };
  
void printEEPROMSettings() {
  for(int i = 0; i < EEPROM_SIZE; i++){
    Serial.print(EEPROM.read(i));
    Serial.print(' ');
  }
  Serial.println();
  for(int i = EEPROM_SIZE; i < (EEPROM_SIZE_T + EEPROM_SIZE); i++){
    Serial.print(EEPROM.read(i));
    Serial.print(' ');
  }
  Serial.println();
}

void pullEEPROMSettings() {
  for(int i = 0; i < EEPROM_SIZE; i++){
    radio_R.writeReg(addr[i], EEPROM.read(i));
  }
  for(int i = EEPROM_SIZE; i < (EEPROM_SIZE_T + EEPROM_SIZE); i++){
    radio_T.writeReg(addr_T[i-EEPROM_SIZE], EEPROM.read(i));
  }
}

void pushEEPROMSettings() {
  for(int i = 0; i < EEPROM_SIZE; i++){
    if(EEPROM.read(i) != radio_R.readReg(addr[i])){ //write only if there are changes
      EEPROM.write(i, radio_R.readReg(addr[i]));    //(save cycles)
      EEPROM.commit();
      Serial.println("wrote to eeprom");
    }
  }
  for(int i = EEPROM_SIZE; i < (EEPROM_SIZE_T + EEPROM_SIZE); i++){
    if(EEPROM.read(i) != radio_T.readReg(addr_T[i - EEPROM_SIZE])){ //write only if there are changes
      EEPROM.write(i, radio_T.readReg(addr_T[i - EEPROM_SIZE]));    //(save cycles)
      EEPROM.commit();
      Serial.println("wrote to eeprom (T)");
    }
  }
}

void initEEPROM() {
  if (!EEPROM.begin(EEPROM_SIZE+EEPROM_SIZE_T)){
    Serial.println("failed to initialise EEPROM");
    delay(1000000);
  }
}

void updateVariables(){
  radio_R._dbm = radio_R.readReg(REG_PALEVEL) & 0x1F - 11;
  radio_R._thresh_type_fixed = !(radio_R.readReg(REG_OOKPEAK) & 0x40);
  radio_R._bandwidth = radio_R.readReg(REG_RXBW);
  radio_R._frequency = radio_R.getFrequency();
  radio_R._fixed_threshold = radio_R.readReg(REG_OOKFIX);
  radio_R._lna_gain = radio_R.readReg(REG_LNA) & 0x03;
  radio_R._ocp = radio_R.readReg(REG_OCP) & 0x10;
  radio_R._modulation = (radio_R.readReg(REG_DATAMODUL) >> 3) & 0x01;
  radio_R._sensitivity_boost = (radio_R.readReg(REG_DATAMODUL) == 0x2D) ? 1 : 0; //0x2D: sensitivity 
  radio_R._deviation = radio_R.getFrequencyDev();   
  
  radio_T._dbm = radio_T.readReg(REG_PALEVEL) & 0x1F - 11;
  radio_T._frequency = radio_T.getFrequency();
  radio_T._ocp = radio_T.readReg(REG_OCP) & 0x10;
  radio_T._modulation = (radio_T.readReg(REG_DATAMODUL) >> 3) & 0x01;
  radio_T._deviation = radio_T.getFrequencyDev();  //boost on
}

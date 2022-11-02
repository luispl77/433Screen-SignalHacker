#include <RFM69LPL.h>
#include <RFM69LPLregisters.h>
#include <SPI.h>

volatile byte RFM69LPL::_mode;  // current transceiver state
volatile int RFM69LPL::RSSI; 	// most accurate RSSI during reception (closest to the reception)
RFM69LPL* RFM69LPL::selfPointer;

bool RFM69LPL::initialize(){
  const byte CONFIG[][2] =
  {
    /* 0x01 */ { REG_OPMODE, RF_OPMODE_SEQUENCER_OFF | RF_OPMODE_LISTEN_OFF | RF_OPMODE_STANDBY },
    /* 0x02 */ { REG_DATAMODUL, RF_DATAMODUL_DATAMODE_CONTINUOUSNOBSYNC | RF_DATAMODUL_MODULATIONTYPE_FSK | RF_DATAMODUL_MODULATIONSHAPING_00 }, // no shaping
    /* 0x03 */ { REG_BITRATEMSB, 0x03}, // bitrate: 32768 Hz
    /* 0x04 */ { REG_BITRATELSB, 0xD1},
    /* 0x19 */ { REG_RXBW, RF_RXBW_DCCFREQ_010 | RF_RXBW_MANT_24 | RF_RXBW_EXP_4}, // BW: 10.4 kHz
    /* 0x1B */ { REG_OOKPEAK, RF_OOKPEAK_THRESHTYPE_PEAK | RF_OOKPEAK_PEAKTHRESHSTEP_000 | RF_OOKPEAK_PEAKTHRESHDEC_000 },
    /* 0x1D */ { REG_OOKFIX, 6 }, // Fixed threshold value (in dB) in the OOK demodulator
    /* 0x29 */ { REG_RSSITHRESH, 140 }, // RSSI threshold in dBm = -(REG_RSSITHRESH / 2)
    /* 0x6F */ { REG_TESTDAGC, RF_DAGC_IMPROVED_LOWBETA0 }, // run DAGC continuously in RX mode, recommended default for AfcLowBetaOn=0
    {255, 0}
  };

  pinMode(_slaveSelectPin, OUTPUT);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);

  Serial.begin(115200); Serial.println();

  for (byte i = 0; CONFIG[i][0] != 255; i++) //write initial regs
    writeReg(CONFIG[i][0], CONFIG[i][1]);

  setHighPower(1);

  setMode(RF69OOK_MODE_STANDBY);
  Serial.print("Waiting for flag MODE_READY...");
  while ((readReg(REG_IRQFLAGS1) & RF_IRQFLAGS1_MODEREADY) == 0x00); // Wait for ModeReady
  Serial.println(" ready."); 

  selfPointer = this;
  return true;
}


bool RFM69LPL::poll(){
  // Poll for OOK signal
  return digitalRead(_interruptPin);
}

void RFM69LPL::send(bool signal){
  // Send a 1 or 0 signal in OOK mode
  digitalWrite(_interruptPin, signal);
}

void RFM69LPL::transmitBegin(){
  // Turn the radio into transmission mode
  setMode(RF69OOK_MODE_TX);
  pinMode(_interruptPin, OUTPUT);
}

void RFM69LPL::transmitEnd(){
  // Turn the radio back to standby
  pinMode(_interruptPin, INPUT);
  setMode(RF69OOK_MODE_STANDBY);
}

void RFM69LPL::receiveBegin(){
  // Turn the radio into OOK listening mode
  pinMode(_interruptPin, INPUT);
  setMode(RF69OOK_MODE_RX);
}

void RFM69LPL::receiveEnd(){
  // Turn the radio back to standby
  setMode(RF69OOK_MODE_STANDBY);
}

uint32_t RFM69LPL::getFrequency(){ 
  // return the frequency (in Hz) by transforming to uint32_t and shifting the 3 bytes accordingly
  return RF69OOK_FSTEP * (((uint32_t)readReg(REG_FRFMSB)<<16) + ((uint16_t)readReg(REG_FRFMID)<<8) + readReg(REG_FRFLSB)); 
}

void RFM69LPL::setFrequencyMHz(float f){
  // Set literal frequency using floating point MHz value
  setFrequency(f * 1000000);
}

void RFM69LPL::setFrequency(uint32_t freqHz){
  // set the frequency (in Hz)
  // TODO: p38 hopping sequence may need to be followed in some cases
  freqHz /= RF69OOK_FSTEP; // divide down by FSTEP to get FRF
  writeReg(REG_FRFMSB, freqHz >> 16);
  writeReg(REG_FRFMID, freqHz >> 8);
  writeReg(REG_FRFLSB, freqHz);
}

void RFM69LPL::setBitrate(uint32_t bitrate){
  // Set bitrate
  bitrate = 32000000 / bitrate; // 32M = XCO freq.
  writeReg(REG_BITRATEMSB, bitrate >> 8);
  writeReg(REG_BITRATELSB, bitrate);
}


void RFM69LPL::setBandwidth(uint8_t bw){
  // set OOK/FSK bandwidth
  writeReg(REG_RXBW, readReg(REG_RXBW) & 0xE0 | bw);
}

void RFM69LPL::setRSSIThreshold(int8_t rssi){
  // set RSSI threshold
  writeReg(REG_RSSITHRESH, (-rssi << 1));
}

void RFM69LPL::setFixedThreshold(uint8_t threshold){
  // set OOK fixed threshold
  writeReg(REG_OOKFIX, threshold);
}

void RFM69LPL::setSensitivityBoost(uint8_t value){
  // set sensitivity boost in REG_TESTLNA
  // see: http://www.sevenwatt.com/main/rfm69-ook-dagc-sensitivity-boost-and-modulation-index
  writeReg(REG_TESTLNA, value);
}

void RFM69LPL::setMode(byte newMode){
    if (newMode == _mode) return;

    switch (newMode) {
        case RF69OOK_MODE_TX:
            writeReg(REG_OPMODE, (readReg(REG_OPMODE) & 0xE3) | RF_OPMODE_TRANSMITTER);
      if (_isRFM69HW) setHighPowerRegs(true);
            break;
        case RF69OOK_MODE_RX:
            writeReg(REG_OPMODE, (readReg(REG_OPMODE) & 0xE3) | RF_OPMODE_RECEIVER);
      if (_isRFM69HW) setHighPowerRegs(false);
            break;
        case RF69OOK_MODE_SYNTH:
            writeReg(REG_OPMODE, (readReg(REG_OPMODE) & 0xE3) | RF_OPMODE_SYNTHESIZER);
            break;
        case RF69OOK_MODE_STANDBY:
            writeReg(REG_OPMODE, (readReg(REG_OPMODE) & 0xE3) | RF_OPMODE_STANDBY);
            break;
        case RF69OOK_MODE_SLEEP:
            writeReg(REG_OPMODE, (readReg(REG_OPMODE) & 0xE3) | RF_OPMODE_SLEEP);
            break;
        default: return;
    }

    // waiting for mode ready is necessary when going from sleep because the FIFO may not be immediately available from previous mode
    while (_mode == RF69OOK_MODE_SLEEP && (readReg(REG_IRQFLAGS1) & RF_IRQFLAGS1_MODEREADY) == 0x00); // Wait for ModeReady

    _mode = newMode;
}

void RFM69LPL::sleep() {
  //power saving sleep mode
  setMode(RF69OOK_MODE_SLEEP);
}

void RFM69LPL::setPowerLevel(byte powerLevel){
  // set output power: 0=min, 31=max
  // this results in a "weaker" transmitted signal, and directly results in a lower RSSI at the receiver
  _powerLevel = powerLevel;
  writeReg(REG_PALEVEL, (readReg(REG_PALEVEL) & 0xE0) | (_powerLevel > 31 ? 31 : _powerLevel));
}

int8_t RFM69LPL::readRSSI(bool forceTrigger) {
  if (forceTrigger)
  {
    // RSSI trigger not needed if DAGC is in continuous mode
    writeReg(REG_RSSICONFIG, RF_RSSI_START);
    while ((readReg(REG_RSSICONFIG) & RF_RSSI_DONE) == 0x00); // Wait for RSSI_Ready
  }
  return -(readReg(REG_RSSIVALUE) >> 1);
}

byte RFM69LPL::readReg(byte addr){
  select();
  SPI.transfer(addr & 0x7F);
  byte regval = SPI.transfer(0);
  unselect();
  return regval;
}

void RFM69LPL::writeReg(byte addr, byte value){
  select();
  SPI.transfer(addr | 0x80);
  SPI.transfer(value);
  unselect();
}

void RFM69LPL::select() {
  // Select the transceiver
  // set RFM69 SPI settings
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV4); //decided to slow down from DIV2 after SPI stalling in some instances, especially visible on mega1284p when RFM69 and FLASH chip both present
  digitalWrite(_slaveSelectPin, LOW);
}

void RFM69LPL::unselect() {
  // UNselect the transceiver chip
  digitalWrite(_slaveSelectPin, HIGH);
}

void RFM69LPL::setHighPower(bool onOff) {
  _isRFM69HW = onOff;
  writeReg(REG_OCP, _isRFM69HW ? RF_OCP_OFF : RF_OCP_ON);
  if (_isRFM69HW) // turning ON
    writeReg(REG_PALEVEL, (readReg(REG_PALEVEL) & 0x1F) | RF_PALEVEL_PA1_ON | RF_PALEVEL_PA2_ON); // enable P1 & P2 amplifier stages
  else
    writeReg(REG_PALEVEL, RF_PALEVEL_PA0_ON | RF_PALEVEL_PA1_OFF | RF_PALEVEL_PA2_OFF | _powerLevel); // enable P0 only
}

void RFM69LPL::setHighPowerRegs(bool onOff) {
  //PA regs
  writeReg(REG_TESTPA1, onOff ? 0x5D : 0x55);
  writeReg(REG_TESTPA2, onOff ? 0x7C : 0x70);
}

void RFM69LPL::readAllRegs(){
  // for debugging
  byte regVal;
  for (byte regAddr = 1; regAddr <= 0x4F; regAddr++) {
    regVal = readReg(regAddr);
    Serial.print(regAddr, HEX);
    Serial.print(" - ");
    Serial.print(regVal,HEX);
    Serial.print(" - ");
    Serial.println(regVal,BIN);
  }
}

byte RFM69LPL::readTemperature(byte calFactor){
  // returns centigrade
  setMode(RF69OOK_MODE_STANDBY);
  writeReg(REG_TEMP1, RF_TEMP1_MEAS_START);
  while ((readReg(REG_TEMP1) & RF_TEMP1_MEAS_RUNNING));
  return ~readReg(REG_TEMP2) + COURSE_TEMP_COEF + calFactor; // 'complement' corrects the slope, rising temp = rising val
}                                                            // COURSE_TEMP_COEF puts reading in the ballpark, user can add additional correction

void RFM69LPL::rcCalibration(){
  //RC calibration mode
  writeReg(REG_OSC1, RF_OSC1_RCCAL_START);
  while ((readReg(REG_OSC1) & RF_OSC1_RCCAL_DONE) == 0x00);
}

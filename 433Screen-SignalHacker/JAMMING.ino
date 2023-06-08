#define TRIGGER_INCREASE 0
#define TRIGGER_DECREASE 1
void sendJammingSignal(){
  int dbm = radio_T._dbm;
  int cursor = 0;
  float frequency;
  float frequenc2 = radio_T._frequency;
  float sweep_freq;
  bool sweep_ON = false; bool sweep_dir = true;
  radio_T.setTransmitPower(dbm, PA_MODE_PA1_PA2_20dbm, OCP_OFF);
  radio_T.txBegin();
  if(_mode == SQR_MODE){
    ledcSetup(0, 2500, 8); //channel 0, 8 bit res
    ledcAttachPin(DIO2_T, 0);
    frequency = 2500;
    UI.drawText(String(frequency), 63, 20, 1, NORMAL);
  }
  else if(_mode == CONT_MODE){
    frequency = radio_T._frequency;
    UI.drawText(String(frequency, 3), 63, 20, 1, NORMAL);
  }
  else if(_mode == SWEEP_MODE){
    frequency = 433.900;
    frequenc2 = 434.000;
    sweep_freq = 433.900;
    UI.drawText(String(frequency, 3), 63, 20, 1, NORMAL);
    UI.drawText(String(frequenc2, 3), 63, 40, 1, NORMAL);
  }
  UI.drawText("MODE: ", 0, 0, 1, NORMAL); UI.drawText(modes[_mode], 40, 0, 1, NORMAL);
  UI.drawText("frequency:", 0, 20, 1, INVERS); 
  UI.drawText("frequenc2: ", 0, 40, 1, NORMAL); 
  UI.drawText("SEND", 80, 50, 1, NORMAL);
  delay(200);
  while(1){
    if(sweep_ON){
      if(sweep_dir && sweep_freq < frequenc2) {
        sweep_freq += 0.001;
      }
      else if(sweep_dir && sweep_freq >= frequenc2) {
        sweep_dir = !sweep_dir; // change direction
      }
      if(!sweep_dir && sweep_freq > frequency) {
        sweep_freq -= 0.001;
      } 
      else if(!sweep_dir && sweep_freq <= frequency) {
         sweep_dir = !sweep_dir; // change direction
      }
      radio_T.setFrequencyMHz(sweep_freq);
    }
    if(UI.clickA()){
      rotate_cursor(&cursor);
      delay(300);
    }
    if(UI.clickUP()){
      while(UI.clickUP()){
        trigger_change(&cursor, &frequency, &frequenc2, TRIGGER_INCREASE, &sweep_ON);
        speedDelay();
      }
      speed_cnt = 0; //slow back down
      ms = 200;
      delay(200);
    }
    if(UI.clickDOWN()){
      while(UI.clickDOWN()){
        trigger_change(&cursor, &frequency, &frequenc2, TRIGGER_DECREASE, &sweep_ON);
        speedDelay();
      }
      speed_cnt = 0; //slow back down
      ms = 200;
      delay(200);
    }
    if(UI.clickB()){
      pushEEPROMSettings(); //save changes
      break; 
    }
  }
}

void trigger_change(int * cursor, float *frequency1, float *frequency2, int change_type, bool* sweep_ON){
  if(*cursor == 0){
    if(_mode == CONT_MODE){
      if(change_type == TRIGGER_INCREASE){
        (*frequency1) = (*frequency1) + 0.001; radio_T.setFrequencyMHz(*frequency1);
        Serial.println(*frequency1); UI.updateText(String(*frequency1, 3), 63, 20, 1, NORMAL, 8);
      }
      else{
        (*frequency1) = (*frequency1) - 0.001; radio_T.setFrequencyMHz(*frequency1);
        Serial.println(*frequency1); UI.updateText(String(*frequency1, 3), 63, 20, 1, NORMAL, 8);
      }
    }
    else if(_mode == SQR_MODE){
      if(change_type == TRIGGER_INCREASE){
        (*frequency1) = (*frequency1) + 50; 
        Serial.println(*frequency1); UI.updateText(String(*frequency1), 63, 20, 1, NORMAL, 8);
        ledcSetup(0, (uint32_t)(*frequency1), 8);
      }
      else{
        (*frequency1) = (*frequency1) - 50; 
        Serial.println(*frequency1); UI.updateText(String(*frequency1), 63, 20, 1, NORMAL, 8);
        ledcSetup(0, (uint32_t)(*frequency1), 8);
      }
    }
    else if(_mode == SWEEP_MODE){
      if(change_type == TRIGGER_INCREASE){
         (*frequency1) = (*frequency1) + 0.001;
         Serial.println(*frequency1); UI.updateText(String(*frequency1, 3), 63, 20, 1, NORMAL, 8);
      }
      else{
         (*frequency1) = (*frequency1) - 0.001;
         Serial.println(*frequency1); UI.updateText(String(*frequency1, 3), 63, 20, 1, NORMAL, 8);
      }
    }
  }
  else if(*cursor == 1){
    if(_mode == CONT_MODE){ //unused 
      if(change_type == TRIGGER_INCREASE){
        
      }
      else{
       
      }
    }
    else if(_mode == SQR_MODE){//unused 
      if(change_type == TRIGGER_INCREASE){
        
      }
      else{
        
      }
    }
    else if(_mode == SWEEP_MODE){
      if(change_type == TRIGGER_INCREASE){
         (*frequency2) = (*frequency2) + 0.001;
         Serial.println(*frequency2); UI.updateText(String(*frequency2, 3), 63, 40, 1, NORMAL, 8);
      }
      else{
         (*frequency2) = (*frequency2) - 0.001;
         Serial.println(*frequency2); UI.updateText(String(*frequency2, 3), 63, 40, 1, NORMAL, 8);
      }
    }
  }
  if(*cursor == 2){
    if(_mode == CONT_MODE){
      if(change_type == TRIGGER_INCREASE){
        ledOn();
        radio_T.send(1);
      }
      else{
        ledOff();
        radio_T.send(0);
      }
    }
    else if(_mode == SQR_MODE){
      if(change_type == TRIGGER_INCREASE){
        ledOn();
        ledcWrite(0, 127); //sqr wave, 50 duty cycle
      }
      else{
        ledOff();
        ledcWrite(0, 0);
      }
    }
    else if(_mode == SWEEP_MODE){
      if(change_type == TRIGGER_INCREASE){
        ledOn();
        radio_T.send(1);
        (*sweep_ON) = true;
      }
      else{
        ledOff();
        radio_T.send(0);
        (*sweep_ON) = false;
      }
    }
  }
}


void rotate_cursor(int * cursor){
  (*cursor)++;
  if(*cursor == 3) *cursor = 0;
      if(*cursor == 0){
        UI.updateText("frequency:", 0, 20, 1, INVERS, 12); //Serial.println("updated freq");      
        UI.updateText("SEND", 80, 50, 1, NORMAL, 5);
      }
      if(*cursor == 1){
        UI.updateText("frequenc2:", 0, 40, 1, INVERS, 12);//Serial.println("updated dbm"); //update current 
        UI.updateText("frequency:", 0, 20, 1, NORMAL, 12); //normalize previous
        
      }
      if(*cursor == 2){
        UI.updateText("SEND", 80, 50, 1, INVERS, 5); //Serial.println("updated SEND");
        UI.updateText("frequenc2:", 0, 40, 1, NORMAL, 12);
      }
}

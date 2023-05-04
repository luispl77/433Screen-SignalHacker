void graphicAnalyser(){
  int x = 0;
  radio_R.rxBegin();
  delay(200);
  while(1){
    //gx_analyser.updateText(String(digitalRead(DIO2_R)), 0, 0, 1, NORMAL, 1);
    if(digitalRead(DIO2_R) == 1){
      gx_analyser.drawPixel(x, 20, 1); //white
      gx_analyser.drawPixel(x, 30, 0); //black
    }
    else{
      gx_analyser.drawPixel(x, 20, 0);
      gx_analyser.drawPixel(x, 30, 1);
    }
      //gx_analyser.drawPixel(x + 10, 20, 0);
      //gx_analyser.drawPixel(x + 10, 30, 0);
    x++;
    if(x == 128) x = 0;
    
    if(gx_analyser.clickB()){

      break;
    }
  }
}

void ledAnalyser(){
  int x = 0;
  unselect_SD();
  radio_R.rxBegin();
  digitalWrite(2, HIGH); delay(200); digitalWrite(2, LOW); delay(200); 
  led_analyser.drawText("B: exit", 10, 50, 1, NORMAL);
  led_analyser.updateText(String(read_rssi_threshold()), 0, 30, 1, NORMAL, 4);
  delay(200);
  while(1){
    if(digitalRead(DIO2_R) == 1){
      digitalWrite(2, HIGH);
    }
    else{
      digitalWrite(2, LOW);
    }
    
    led_analyser.updateText(String(read_rssi()), 0, 10, 1, NORMAL, 4);
    
    if(led_analyser.clickB()){
       digitalWrite(2, LOW);
      break;
    }
  }
}

byte read_rssi(){
      radio_R.writeReg(REG_RSSICONFIG, 0x01); //trigger read
      return radio_R.readReg(REG_RSSIVALUE);
}

byte read_rssi_threshold(){
      return radio_R.readReg(REG_RSSITHRESH);
}

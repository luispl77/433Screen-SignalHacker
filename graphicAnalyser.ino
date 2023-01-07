void graphicAnalyser(){
  int x = 0;
  unselect_T();
  unselect_SD();
  radio_R.initializeReceive();
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
  unselect_T();
  unselect_SD();
  radio_R.initializeReceive();
  digitalWrite(2, HIGH); delay(200); digitalWrite(2, LOW); delay(200); 
  led_analyser.drawText("RF output -> On-Board LED.", 0, 0, 1, NORMAL);
  led_analyser.drawText("B: exit", 10, 50, 1, NORMAL);
  delay(200);
  while(1){
    if(digitalRead(DIO2_R) == 1){
      digitalWrite(2, HIGH);
    }
    else{
      digitalWrite(2, LOW);
    }
    if(led_analyser.clickB()){
       digitalWrite(2, LOW);
      break;
    }
  }
}

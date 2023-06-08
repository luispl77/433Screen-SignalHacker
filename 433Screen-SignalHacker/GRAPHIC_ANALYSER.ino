void graphicAnalyser(){
  int x = 0;
  radio_R.rxBegin();
  delay(200);
  while(1){
    //UI.updateText(String(digitalRead(DIO2_R)), 0, 0, 1, NORMAL, 1);
    if(digitalRead(DIO2_R) == 1){
      UI.drawPixel(x, 20, 1); //white
      UI.drawPixel(x, 30, 0); //black
    }
    else{
      UI.drawPixel(x, 20, 0);
      UI.drawPixel(x, 30, 1);
    }
      //UI.drawPixel(x + 10, 20, 0);
      //UI.drawPixel(x + 10, 30, 0);
    x++;
    if(x == 128) x = 0;
    
    if(UI.clickB()){
      radio_R.standby();
      break;
    }
  }
}

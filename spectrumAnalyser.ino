void spectrumAnalyser(){
  int x = 0;
  unselect_T();
  unselect_SD();
  radio_R.initializeReceive();
  delay(200);
  while(1){
    //spc_analyser.updateText(String(digitalRead(DIO2_R)), 0, 0, 1, NORMAL, 1);
    if(digitalRead(DIO2_R) == 1){
      spc_analyser.drawPixel(x, 20, 1); //white
      spc_analyser.drawPixel(x, 30, 0); //black
    }
    else{
      spc_analyser.drawPixel(x, 20, 0);
      spc_analyser.drawPixel(x, 30, 1);
    }
    x++;
    if(x == 128) x = 0;
    if(spc_analyser.clickB()){

      break;
    }
  }
}

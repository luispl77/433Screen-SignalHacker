void transmitterConfig(){
  while(1){
    if(t_config.clickA()){
      //changeCursor();
      delay(300);
    }
    if(t_config.clickUP()){
      //triggerIncrease();
      delay(200);
    }
    if(t_config.clickDOWN()){
      //triggerDecrease();
      delay(200);
    }
    if(t_config.clickB()){

      break;
    }
  }
}

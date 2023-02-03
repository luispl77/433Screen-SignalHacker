void macMode(){
  initialize_radio_car();
  mac_mode.drawText("A: clutch in", 0, 0, 1, NORMAL);
  mac_mode.drawText("B: clutch out", 0, 10, 1, NORMAL);
  mac_mode.drawText("UP: forward", 0, 20, 1, NORMAL);
  mac_mode.drawText("DOWN: backward", 0, 30, 1, NORMAL);
  
  mac_mode.drawText("EN: reboot/exit", 0, 50, 1, NORMAL);
  while(1){
    if(mac_mode.clickA()){
      pulse(2500);
     
    }
    else if(!mac_mode.clickA() && !mac_mode.clickB()){
      pulse(2100); 
      
    }
    else if(mac_mode.clickB()){
      pulse(2300); 
      
    }
    
    
    
    if(mac_mode.clickUP()){
     pulse(1500); 
      
    }
    else if(!mac_mode.clickUP() && !mac_mode.clickDOWN()){
     pulse(1700); 
    }
    else if(mac_mode.clickDOWN()){
     pulse(1900); 
     
    }
     
  }
}

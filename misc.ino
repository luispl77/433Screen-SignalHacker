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

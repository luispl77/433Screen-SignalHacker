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

void showBattery(){
  float reading = analogRead(35);
  pinMode(35, INPUT);
  Serial.print("analog: ");
  Serial.println(reading);
  Serial.print("corresponding voltage: ");
  Serial.println((reading/4096)*6.6, 3);
  Serial.print("offset: 3.6-3.25 = 0.35  ");
  Serial.println((reading/4096)*6.6 + 0.35, 3); //offset 0.35, actually its more like 0.49
  main_menu.drawText("bat: ", 0, 0, 1, NORMAL);
  main_menu.drawText(String((reading/4096)*6.6 + 0.49, 2), 30, 0, 2, NORMAL);
  main_menu.drawText("V", 80, 0, 2, NORMAL);
  delay(2000);
}

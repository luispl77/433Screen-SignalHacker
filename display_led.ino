void initializeDisplay(){
    pinMode(BUILTIN_LED, OUTPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  drawText("LPL", 10, 15, 2, NORMAL);
  drawText("ROBOTICS", 10, 35, 2, NORMAL);
  display.drawRect(0, 0, display.width(), display.height(), SSD1306_WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();
}

void drawRectangle(){
  display.drawRect(0, 0, display.width(), display.height(), SSD1306_WHITE);
  display.display();
}

void drawText(String text, int x, int y, int text_size, int inverse){
  display.setTextSize(text_size); 
  if(inverse == 1){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  }
  else if (inverse == 0){
    display.setTextColor(SSD1306_WHITE);
  }
  else if (inverse == 2){
    display.setTextColor(SSD1306_BLACK);
  }
  display.setCursor(x, y);
  display.print(text);
  display.display();
}

void ledOn(){
  digitalWrite(BUILTIN_LED, HIGH);
}

void ledOff(){
  digitalWrite(BUILTIN_LED, LOW);
}

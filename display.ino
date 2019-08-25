

void displayIntro() {
  Wire.begin();
  lcd.begin(16,2);
  delay(2000);  
  lcd.init();
  lcd.print("Toniobot ");
  delay(1000);
  lcd.print("v1.0");
  delay(2000);  
  lcd.clear();
  lcd.blink();  
  lcd.print("Mission:");
  delay(2000); 
  lcd.clear();
  lcd.blink(); 
  lcd.print("Destroy all");
  lcd.setCursor(0,1);
  lcd.print("humans");
  delay(4000); 
}

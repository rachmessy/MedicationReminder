#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//here is the source I used to figure out the display: https://www.youtube.com/watch?v=SHORUnKgpKE&t=394s

//address begins at 0x27, 16 column 4 row dispaly
LiquidCrystal_I2C lcd(0x27, 16, 4);

//test counters
int counter1 = 0;
int counter2 = 0;
int counter3 = 0;
int counter4 = 0;

void setup() {
  //initialize lcd
  lcd.init();
  lcd.backlight();
}

void loop() {
  //checking first row prints
  lcd.setCursor(0, 0);
  lcd.print("Slot 1: ");
  lcd.print(counter1);
  //checking second row prints
  lcd.setCursor(0, 1);
  lcd.print("Slot 2: ");
  lcd.print(counter2);
  //checking third row prints
  lcd.setCursor(0, 2);
  lcd.print("Slot 3: ");
  lcd.print(counter3);
  //Found out (0,4) doesn't work had to directly address memory location 
  lcd.command(0xC0 + 0x14); 
  lcd.print("Slot 4: ");
  lcd.print(counter4);
  //increment counters
  counter1 += 1;
  counter2 += 2;
  counter3 += 3;
  counter4 += 4;
  //update every second and ensure they actually update
  delay(1000);
}

#include <Wire.h>
#include <EEPROM24LC256_512.h>
#include <LiquidCrystal.h>

const int numRows = 2;
const int numCols = 16;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

EEPROM256_512 mem_2;

byte storage512[128];

void setup() {
  byte address;
  boolean verify = true;
  Wire.begin();
  lcd.begin(numCols, numRows);
  lcd.write(" I2C eeprom");
  lcd.setCursor(6, 1);
  lcd.write("restore");
  delay(1000);
  lcd.clear();
  lcd.write("24XX512, 24LC512");
  lcd.setCursor(0, 1);
  lcd.write("24F512, 24AA512");
  delay(2000);
  address = scanBus();
  mem_2.begin(address, 1);
  
  fillEeprom();
  lcd.clear();
  if (verifyFill() == true) {
    lcd.print("Fill 0xFF OK");
  }
  else {
    lcd.print("Fill 0xFF failed");
    verify = false;
  }
  if (verify == true) {
  writeSaglamPages();
  }
  lcd.clear();
  if (verifyCopy() == true) {
    lcd.clear();
    lcd.print("Copy succesfull");
    }
else {
  lcd.print("Copy failed!!!!");
  while(true);
}
  //markPages(); //Test amaçlı sayfa başlıklarına sıra numaralarını yazdırır. 0x0001, 0x0002,... 0x01FF gibi
}

void loop() {/*Run Application once*/}

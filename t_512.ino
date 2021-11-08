
    byte saglamPage0[] = {
    0xc4, 0x09, 0x00, 0x00, 0x3f, 0x42, 0x0f, 0x00, 0x3f, 0x42, 0x0f, 0x00, 
    0x00, 0x31, 0x31, 0x2c, 0x01, 0x2c, 0x01, 0x05, 0x0f, 0x0a, 0x05, 0x02, 
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x32, 0x01, 0x02, 0x01, 
    0x18, 0x32, 0xcf, 0xd8, 0x00, 0x00, 0x16, 0x00, 0x0e, 0x9c, 0xb1, 0x41, 
    0x00, 0x00, 0x80, 0x3f, 0xcc, 0x09, 0x00, 0x00, 0xe7, 0xff, 0xff, 0xff, 
    0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xdd, 0x0c, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x38, 0x08, 0x00, 
    0x88, 0x13, 0x00, 0x00, 0x94, 0x63, 0x08, 0x00, 0x10, 0x27, 0x00, 0x00, 
    0xac, 0xe5, 0x08, 0x00, 0xa8, 0x61, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 
    0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x87, 0xe1, 0x07, 0x00, 0x80, 0xe1, 0x07, 0x00
    };
    
    byte saglamPage1[] = {
    0x33, 0x38, 0x08, 0x00, 
    0x3a, 0x38, 0x08, 0x00, 0x94, 0x63, 0x08, 0x00, 0x96, 0x63, 0x08, 0x00, 
    0x7b, 0xbe, 0x09, 0x00, 0x7b, 0xbe, 0x09, 0x00, 0x00, 0x00, 0x10, 0x00, 
    0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0x69, 0xca, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x3d, 0x0e, 0x08, 0x00, 0x73, 0x0e, 0x08, 0x00, 0x00, 0x02, 0x00, 0x1b, 
    0x00, 0x00, 0x00, 0x00, 0xe5, 0xef, 0xf7, 0xfe, 0x02, 0x14, 0x00, 0x01, 
    0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x15, 0x00, 0x3c, 
    0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf4, 0x01, 0xe8, 0x03, 0xd0, 0x07, 0x00, 
    0x69, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff
};

void writeSaglamPages() {
  lcd.clear();
  lcd.print("Writing Page 0..");
  mem_2.writePage(0, saglamPage0);
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("Writing Page 1..");
  mem_2.writePage(1, saglamPage1);
  delay(1000);
}

boolean verifyFill() {
  boolean verify = true;
  int i = 0;
  byte tempBuffer[128];
  fill512Buffer();
  lcd.clear();
  lcd.print("Verifing 0xFFill");
  delay(500);
  for(i;i<512;i++) {
    
    mem_2.readPage(i, tempBuffer);
    delay(5);
    lcd.setCursor(0,1);
    lcd.print(i);
    lcd.print(": ");
    if (comparePages(tempBuffer, storage512, 128)) {
      lcd.print("OK    ");
    }
    else {
      lcd.print("Failed!!!");
      verify = false;
      while(true);
    }
  }
  /*lcd.setCursor(0,1);
  Serial.println("\nFill verify...");*/
  return verify;
}

boolean verifyCopy() {
  boolean verify = false;
  int i = 0;
  byte tempBuffer[128];
  lcd.clear();
  lcd.print("Verifing copy...");
  
    mem_2.readPage(0, tempBuffer);
    delay(5);
    if (comparePages(tempBuffer, saglamPage0, 128)) {
      lcd.setCursor(0, 1);
      lcd.print("Page0 verified...");
      verify = true;
    }
    else {
      lcd.setCursor(0, 1);
      lcd.print("Page0 failed...");
      while(true);
    }

mem_2.readPage(1, tempBuffer);
    delay(5);
    if (comparePages(tempBuffer, saglamPage1, 128)) {
      lcd.setCursor(0, 1);
      lcd.print("Page1 verified...");
    }
    else {
      lcd.setCursor(0, 1);
      lcd.print("Page1 failed...");
      verify = false;
      while(true);
    }
  delay(1000);
  lcd.print("\nCopy done...");
  return verify;
}

boolean comparePages(byte rereadPage[], byte masterPage[], int n) {
   boolean result = true;
   
   for(int i = 0; i < n; i++){
       if (rereadPage[i] != masterPage[i]) {
       result = false; }
}
return result;
}

void fillEeprom() {
  int i = 0;
  fill512Buffer();
  lcd.clear();
  lcd.print("Fill eeprom 0xFF's");
  lcd.setCursor(0 ,1);
  lcd.print("Page: ");
  
  for(i;i<512;i++) {
    mem_2.writePage(i, storage512);
    delay(5);
    lcd.setCursor(6 ,1);
    lcd.print(i);
    lcd.print("   ");
  }
  lcd.setCursor(0, 1);
  lcd.print("Fillin 0xFF done");
}

/*void markPages() {
  int i = 0;
  fill512Buffer();
  Serial.println("Marking pages with indexes...");
  Serial.print("Page: ");
  
  for(i;i<512;i++) {
    
    storage512[0] = i  >> 8;
    storage512[1] = i & 0xFF;
    
    mem_2.writePage(i, storage512);
    delay(5);
    Serial.print(i);
    Serial.print(", ");
    if (i % 32 == 0) {
      Serial.print("\n");
    }
  }
  Serial.println("\nDone...");
}*/

void fill512Buffer()
{ 
  int i=0;
  for(i=0; i<128;i++)
  {
    storage512[i]=0b11111111 ;
  }
}

byte scanBus() {
  byte error, address, foundAddress;
  int nDevices;
  lcd.clear();
  lcd.print("Scanning bus...");
  nDevices = 0;
  for(address = 88; address > 79; address-- )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      lcd.clear();
      lcd.print("I2C device at:");
      lcd.setCursor(4, 1);
      lcd.print("0x");
      lcd.setCursor(6, 1);
      lcd.print(address, HEX);
      foundAddress = address;
      delay(500);
      nDevices++;
    }
    else if (error==4)
    {
      lcd.clear();
      lcd.print("Unknow error @");
      lcd.setCursor(4, 1);
      lcd.print("0x");
      lcd.setCursor(6, 1);
      lcd.print(address, HEX);
      while(true);
    }
    delay(100);
  }
  if (nDevices == 0) {
    lcd.clear();
    lcd.write("No I2C devices!");
    lcd.setCursor(0, 1);
    lcd.print("found!!!!!!");
    while(true);
  }
  else
      lcd.clear();
      lcd.print("Using device at");
      lcd.setCursor(4, 1);
      lcd.print("0x");
      lcd.setCursor(6, 1);
      lcd.print(foundAddress, HEX);
      delay(2000);
 return foundAddress - 0x50;
 //-------------------------------
}

void clear512Buffer()
{
  int i=0;
  for(i=0;i<128;i++)
  {
       storage512[i]=(byte)(0b00000000);
  }
}

/*void print512Buffer()
{
  int i=0;
  for(i=0;i<128;i++)
  {
    Serial.print("Byte: "); Serial.print(i);
    Serial.print(" Data: "); Serial.println(storage512[i],BIN);
  } 
}*/




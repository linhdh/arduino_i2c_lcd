#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int device_address = 0x0;
LiquidCrystal_I2C *lcd = NULL;

void setup() {
  Serial.begin (9600);

  // Leonardo: wait for serial port to connect
  //while (!Serial) 
  //{
  //}

  Serial.println ();
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;
  
  Wire.begin();
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
    {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      if (count == 1)
      {
        device_address = i;
      }
      delay (1);  // maybe unneeded?
    } // end of good response
  } // end of for loop
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");

  //Setup lcd
  lcd = new LiquidCrystal_I2C(device_address, 16, 2);
  lcd->init();
  lcd->clear();
  lcd->backlight();
  lcd->setCursor(2, 0);
  lcd->print("Hello world!");
  lcd->setCursor(2, 1);
  lcd->print("LCD Tutorial");
}  // end of setup

void loop() {}

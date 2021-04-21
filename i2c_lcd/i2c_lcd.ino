#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int device_address = 0x0;
LiquidCrystal_I2C *lcd = NULL;

byte Degree[8] = {
  0b00000,
  0b01110,
  0b10001,
  0b10001,
  0b01110,
  0b00000,
  0b00000,
  0b00000
};

void setup() {
  sensors.begin();
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
  lcd->createChar(0, Degree);
}  // end of setup

void loop() {
  sensors.requestTemperatures();  
  int tempc = sensors.getTempCByIndex(0);
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Temp: ");
  lcd->print(tempc);
  lcd->write(0);  //shows degrees character
  lcd->print("C");

  lcd->setCursor(0, 1);
  lcd->print("Temp: ");
  lcd->print((tempc * 9.0) / 5.0 + 32.0);
  lcd->write(0);  //shows degrees character
  lcd->print("F");
  
  delay(1000);
}

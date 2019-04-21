#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "SoftwareSerial.h"

#define bulb1 2
#define bulb2 3
#define bulb3 4

SoftwareSerial sms(7, 8);
LiquidCrystal_I2C lcd(0x27, 16, 2);

String textMessage;

String bulb1Status="OFF";
String bulb2Status="OFF";
String bulb3Status="OFF";

void setup() {
  digitalWrite(bulb1, HIGH);
  digitalWrite(bulb2, HIGH);
  digitalWrite(bulb3, LOW);
  // put your setup code here, to run once:
  Serial.begin(9600);
  sms.begin(9600);
  lcd.begin();

  pinMode(bulb1, OUTPUT);
  pinMode(bulb2, OUTPUT);
  pinMode(bulb3, OUTPUT);

  //--------------------------------
  lcd.backlight();
  lcd.clear();
    lcd.setCursor(0, 0);
  lcd.print(" REMOTE LIGHT");
  lcd.setCursor(0, 1);
  lcd.print("CONTROL SYSTEM");
  
  //---------------------------------

  Serial.print("GPRS ready...\r\n");
  sms.print("AT+CMGF=1\r\n");
  delay(1000);
  sms.print("AT+CMGDA=1\r\n");
  delay(1000);
  sms.print("AT+CNMI=2,2,0,0,0\r\n");


  delay(1000);

lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:

  lcd.setCursor(0,0);
  lcd.print("B1:");
  lcd.setCursor(4,0);
  lcd.print(bulb1Status);

  
  lcd.setCursor(8,0);
  lcd.print("B2:");
  lcd.setCursor(12,0);
  lcd.print(bulb2Status);

   lcd.setCursor(0,1);
  lcd.print("B3:");
  lcd.setCursor(4,1);
  lcd.print(bulb3Status);
  if (sms.available() > 0) {


    textMessage = sms.readString();
    Serial.print(textMessage);
    delay(100);

    if (textMessage.indexOf("**********") >= 0) {
      if (textMessage.indexOf("BULB1 ON") >= 0) {
        digitalWrite(bulb1, LOW);
        bulb1Status = "ON";

      }

      if (textMessage.indexOf("BULB2 ON") >= 0) {
        digitalWrite(bulb2, LOW);
        bulb2Status = "ON";

      }

      if (textMessage.indexOf("BULB3 ON") >= 0) {
        digitalWrite(bulb3, HIGH);
        bulb3Status = "ON";

      }

      if (textMessage.indexOf("BULB1 OFF") >= 0) {
        digitalWrite(bulb1, HIGH);
        bulb1Status = "OFF";

      }

      if (textMessage.indexOf("BULB2 OFF") >= 0) {
        digitalWrite(bulb2, HIGH);
        bulb2Status = "OFF";

      }

      if (textMessage.indexOf("BULB3 OFF") >= 0) {
        digitalWrite(bulb3, LOW);
        bulb3Status = "OFF";

      }
    }
  }
  delay(400);
  lcd.clear();
}

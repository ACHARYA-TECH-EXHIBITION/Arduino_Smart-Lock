#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define siron 6
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  lcd.begin();
  lcd.clear();
  lcd.backlight();
  pinMode(siron,OUTPUT);

  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  
  lcd.print("    Welcome    ");

  lcd.setCursor(0,1);
  lcd.print(" Tap your card! ");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "B1 28 7B 1B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    lcd.clear();
    lcd.print("    Welcome    ");
    lcd.setCursor(0,1);
    lcd.print("Hrishikesh Prateek");
    digitalWrite(siron,HIGH);
    delay(100);
    digitalWrite(siron,LOW);
    delay(2000);

    lcd.clear();

     lcd.print("    Welcome    ");
     lcd.setCursor(0,1);
     lcd.print(" Tap your card! ");
    
  }else if(content.substring(1) == "04 33 0A E2 D5 5E 80"){
      
    Serial.println("Authorized access");
    Serial.println();
    lcd.clear();
    lcd.print("    Welcome    ");
    lcd.setCursor(0,1);
    lcd.print("   Sudipan C.");
    digitalWrite(siron,HIGH);
    delay(100);
    digitalWrite(siron,LOW);
    delay(2000);

    lcd.clear();

     lcd.print("    Welcome    ");
     lcd.setCursor(0,1);
     lcd.print(" Tap your card! ");
  }else if(content.substring(1) == "1F 07 50 EC"){
      
    Serial.println("Authorized access");
    Serial.println();
    lcd.clear();
    lcd.print("    Welcome    ");
    lcd.setCursor(0,1);
    lcd.print("  Mohit Kumar.  ");
    digitalWrite(siron,HIGH);
    delay(100);
    digitalWrite(siron,LOW);
    delay(2000);

    lcd.clear();

     lcd.print("    Welcome    ");
     lcd.setCursor(0,1);
     lcd.print(" Tap your card! ");
  }
 
 else   {
    Serial.println(" Access denied");
    digitalWrite(siron,HIGH);
    lcd.clear();
    lcd.print("  Unauthorized!  ");
    lcd.setCursor(0,1);
    lcd.print("  Card Invalid  ");
    delay(1000);
    digitalWrite(siron,LOW);
    
    lcd.clear();
    lcd.print("    Welcome    ");
    lcd.setCursor(0,1);
    lcd.print(" Tap your card! ");
  }
} 

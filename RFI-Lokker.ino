#include <SPI.h> // SPI-Bibiothek hinzufügen Tag=56 5C 1F F8 Karte= 79 3C A3 55
#include <MFRC522.h> // RFID-Bibiothek hinzufügen
#include <Wire.h> // Wire Bibliothek hochladen
#include <LiquidCrystal_I2C.h>// Vorher hinzugefügte LiquidCrystal_I2C Bibliothek hochladen

#define SS_PIN 10 // SDA an Pin 10 (bei MEGA anders)
#define RST_PIN 9 // RST an Pin 9 (bei MEGA anders)

LiquidCrystal_I2C lcd(0x27, 16, 2);   //Hier wird festgelegt um was für einen Display es sich handelt.
MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID-Empfänger benenn

void setup(){
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  
  lcd.begin(); //Im Setup wird der LCD gestartet
  SPI.begin(); // SPI-Verbindung aufbauen
  mfrc522.PCD_Init(); // Initialisierung des RFID-Empfänger
}

void loop(){
  if (!mfrc522.PICC_IsNewCardPresent()){ // Wenn karte erkannt
    return; // gehe weiter...
  }
  if (mfrc522.PICC_ReadCardSerial() == {0x56, 0x5C, 0x1F 0xF8}){
    lcd.setCursor(0,0); //Ab hier kann das I2C LCD Modul genau wie das einfache LCD Modul programmiert werden.
    for(byte i = 0; i < mfrc522.uid.size; i++){
      lcd.print(mfrc522.uid.uidByte[i], HEX); // Dann wird die UID ausgelesen, die aus vier einzelnen Blöcken besteht und der Reihe nach an den Serial Monitor gesendet. Die Endung Hex bedeutet, dass die vier Blöcke der UID als HEX-Zahl (also auch mit Buchstaben) ausgegeben wird
      lcd.print(" "); // Der Befehl „Serial.print(" ");“ sorgt dafür, dass zwischen den einzelnen ausgelesenen Blöcken ein Leerzeichen steht.
    }
    
    lcd.setCursor(0,1);  // lcd.setCursor um Zeichen und Zeile anzugeben
    lcd.print("Hallo Joel"); // lcd.print um etwas auf dem Display anzeigen zu lassen.
    digitalWrite(3, HIGH);
    delay(5000);
    digitalWrite(3, LOW);
    lcd.clear();
    lcd.backlight();
  }


/*
This file include RFID modul that send message on some phone number when card ID is the same as ID 
in if function. If card ID is the same as set ID in code, then buzzer is on for 100ms and relay is on.

*/

#include <SPI.h>
#include <MFRC522.h>
#include<SoftwareSerial.h>
int count = 0;
SoftwareSerial gsm(4,5);
 
#define SS_PIN 53
#define RST_PIN 49


#define Buzzer 7 //buzzer pin
#define Relay 8  //relay pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

 
void setup() 
{
  pinMode(Buzzer, OUTPUT);
  digitalWrite(Buzzer, LOW); //BUZZER off at startup
  pinMode(Relay, OUTPUT);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Put your card to the reader...");
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
  Serial.print("");
  content.toUpperCase();
  if (content.substring(1) == "91 40 26 2F") //Replace by your UID
  {
    delay(50);
 // Serial.begin(9600);
  gsm.begin(9600);
    digitalWrite(Buzzer, HIGH);
    delay(100);
    digitalWrite(Buzzer, LOW);
    delay(50);
    Serial.println("Authorized access");
    Serial.println();
       digitalWrite(Relay, HIGH);
       delay(10000);
       digitalWrite(Relay, LOW);
    delay(50);
    delay(100);
  gsm.println("AT+CMGF=1");
  delay(500);
  gsm.println("AT+CMGS=\"+385xxxxxxxxx\"\r"); //replace x by your number
  delay(500);
  gsm.println("Lid NO1 is opened!"); //message
  delay(100);
  gsm.println((char)26);
  delay(500);
  }
   if (content.substring(1) == "D5 A2 CE 83") //Replace by your UID
  {
    delay(50);
  //Serial.begin(9600);
  gsm.begin(9600);
    digitalWrite(Buzzer, HIGH);
    delay(100);
    digitalWrite(Buzzer, LOW);
    delay(50);
    Serial.println("Authorized access");
    Serial.println();
        digitalWrite(Relay, HIGH);
       delay(10000);
       digitalWrite(Relay, LOW);
    delay(50);
    delay(100);
  gsm.println("AT+CMGF=1");
  delay(500);
  gsm.println("AT+CMGS=\"+385xxxxxxxxx\"\r"); //replace x by your number
  delay(500);
  gsm.println("Lid NO2 is opened!"); //message 
  delay(100);
  gsm.println((char)26);
  delay(500);
}

   else { 
    digitalWrite(Buzzer, HIGH);
    delay(500);
    digitalWrite(Buzzer, LOW);
    delay(50);
  digitalWrite(Relay, LOW);
  delay(100);
    Serial.println("Access denied");
    Serial.println();
    delay(500);
  }
} 

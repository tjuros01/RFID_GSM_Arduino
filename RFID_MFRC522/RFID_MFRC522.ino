
#include <SPI.h>   // RFID library
#include <MFRC522.h>  //RFID library

#define Buzzer 7    //Buzzer connected to ground (-) and pin 7 (+), not neccessary for project
#define Relay 8  //Relay pin if necessary for project
#define SS_PIN 53
#define RST_PIN 49  //Reset pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  pinMode(Buzzer, OUTPUT);
  digitalWrite(Buzzer, LOW); //BUZZER off at startup
  pinMode(Relay, OUTPUT);
 
  
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
//Serial.println();

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
//  Show UID on serial monitor
 // Serial.print("UID tag :");
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
  delay(50);
  content.toUpperCase();
  
  if (content.substring(1) == "91 40 26 2F")  // depends on card number
  {
    digitalWrite(Buzzer, HIGH); //buzzer on for 100s
    delay(100);
    digitalWrite(Buzzer, LOW);
    delay(50);
    
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(Relay, HIGH);
    delay(10000);
    digitalWrite(Relay, LOW);
    delay(50);
    delay(200);
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
    delay(200);
  }
} 

/*
The circuit:
* RX is digital pin 10 (connect to TX of GSM Modem)
* TX is digital pin 11 (connect to RX of GSM Modem)
*/
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup()
{
// Open serial communications and wait for port to open:
Serial.begin(9600);

Serial.println("Texting through GSM Modem");

// set the data rate for the SoftwareSerial port
mySerial.begin(9600);

 mySerial.print("AT+CMGF=1\r");                                                        // AT command to send SMS message
  delay(100);
  mySerial.println("AT + CMGS = \"+639399150254\"");                                     // recipient's mobile number, in international format
  delay(100);
  mySerial.println("Hello, world. This is a text message.");        // message to send
  delay(100);
  mySerial.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(100); 
  mySerial.println();
  delay(5000);                                     // give module time to send SMS
  SIM900power();                                   // turn off module
  
}


void loop() // run over and over
{
// print response over serial port
if (mySerial.available())
Serial.write(mySerial.read());
}



void SIM900power()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);
}
 

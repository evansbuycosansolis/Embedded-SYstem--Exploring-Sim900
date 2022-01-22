#include <SoftwareSerial.h>
SoftwareSerial SIM900(0, 1);
 
void setup()
{
  SIM900.begin(19200);
  SIM900power();  
  delay(20000);  // give time to log on to network. cx
}
  
void sendSMS()
{

  SIM900.print("AT+CMGF=1\r");                                                        // AT command to send SMS message
  delay(100);
  SIM900.println("AT + CMGS = \"+639399150254\"");                                     // recipient's mobile number, in international format
  delay(100);
  SIM900.println("Hello, world. This is a text message from an Arduino Uno.");        // message to send
  delay(100);
  SIM900.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(100); 
  SIM900.println();
  delay(5000);                                     // give module time to send SMS
  SIM900power();                                   // turn off module
}
 
void loop()
{
  Serial.print("Sending...");
  sendSMS();
  do {} while (1);
}

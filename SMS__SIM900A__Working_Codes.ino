#include <SoftwareSerial.h>

SoftwareSerial SIM900Notification(0, 1);



void setup()
{
 Serial.begin (9600);
  SIM900Notification.begin(19200);
  SIM900NotificationpowerON();  
  delay(1000);  // give time to log on to network.
  SIM900Notification.println("AT+CMGD=1,4"); 

}
  


void SIM900NotificationpowerON()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(9, HIGH);
  delay(1000);
}

void SIM900NotificationpowerOFF()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(9, LOW);
  delay(1000);
}

void sendSMS()
{
 
  //===========================================
  SIM900Notification.print("AT + CMGF = 1 \r");                                                        // AT command to send SMS message
  delay(100);
  SIM900Notification.println("AT + CMGS = \"+639399150254\"");                                     // recipient's mobile number, in international format
  delay(100);
   SIM900Notification.println("SIM900 Test");
  Serial.println("sent");
   
     delay(100);

  //===========================================
  
  SIM900Notification.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(100); 
  SIM900Notification.println();
  delay(5000);                                              // give module time to send SMS
 // SIM900NotificationpowerOFF();                                  // turn off module
  
} //end sendSMS






//============= Void Loop =============
void loop()
{
  sendSMS();
  delay (5000);
} 
//============= Void Loop =============

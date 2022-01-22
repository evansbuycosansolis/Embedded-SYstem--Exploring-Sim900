#include <SoftwareSerial.h>

SoftwareSerial SIM900Notification(0,1);



void setup()
{
  SIM900Notification.begin(19200);
  SIM900Notificationpower();  
  delay(1000);  // give time to log on to network.

}
  


void SIM900Notificationpower()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);
}


void sendSMS()
{
 
  //===========================================
  SIM900Notification.print("AT + CMGF = 1 \r");                                                        // AT command to send SMS message
  delay(100);
  SIM900Notification.println("AT + CMGS = \"+639288232774\"");                                     // recipient's mobile number, in international format
  delay(100);
   SIM900Notification.println("May Makawat!");
     delay(100);

  //===========================================
  
  SIM900Notification.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(100); 
  SIM900Notification.println();
  delay(5000);                                              // give module time to send SMS
  SIM900Notificationpower();                                  // turn off module
  
} //end sendSMS






//============= Void Loop =============
void loop()
{
  sendSMS();
  delay (5000);
} 
//============= Void Loop =============





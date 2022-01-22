#include "SIM900.h"
#include <SoftwareSerial.h>
#include <String.h>
#include <TinyGPS.h>
#include "sms.h"

SoftwareSerial mySerial(0, 1);


char buffer[164];      
int count=0;                     
SoftwareSerial GPS(6, 7);
TinyGPS gps;
unsigned long fix_age;
long lat, lon;
float LAT, LON;

void gpsdump(TinyGPS &gps);
bool feedgps();
void getGPS();



void setup() {
  mySerial.begin(9600); 
  GPS.begin(9600);  
  //SIM900power();  
  Serial.begin(9600);
  delay(500);
  mySerial.println("AT+CPIN=\"5317\"");
  delay(500);
  Sim900_Inti();
}

void loop() {
     mySerial.listen();
     if (mySerial.available())                // If date is comming from from GSM shield)
     {
         while(mySerial.available())          // reading data into char array 
         {
              buffer[count++]=mySerial.read();  // writing data into array
              delay(20);
              if(count == 164)
                 break;
         }
         Serial.write(buffer,count);           // if no data transmission ends, write buffer to hardware serial port
         if(strstr(buffer,"$$$"))
            Cmd_Read_Act();                    //Read the 'COMMAND' sent to SIM900 through SMS
         clearBufferArray();                   // call clearBufferArray function to clear the storaged data from the array
         count = 0;                            // set counter of while loop to zero
     }
    if (Serial.available())
       mySerial.write(Serial.read());
    //CalibrateGPS(); //for testing   
}


//Function reads the SMS sent to SIM900 shield.
void Cmd_Read_Act(void)                       
{ 
     //Comparing password entered with password stored in program
     if (strstr(buffer,"$$$"))      
     {
         Serial.println("Password Authenticated.");
         Serial.println("Sending reply SMS. ");
         SendTextMessage2();            
     }
     for (int i=0; i<count;i++)
     {
       buffer[i]=NULL; // clear all index of array with command NULL
     }
}
 
void SendTextMessage2()
{
   
    mySerial.print("AT+CMGF=1\r");    //Sending the SMS in text mode
    delay(500);
    mySerial.println("AT + CMGS = \"+639399150254\"");//The predefined phone number
    delay(500);
    mySerial.println("Please wait..Your car is tracking");//the content of the message
    delay(500);  
    mySerial.println((char)26);//the ASCII code of the ctrl z is 26
    delay(5000);
    mySerial.println();
    int counter=0;
    GPS.listen();
    for (;;)
    {
       long lat, lon;
       unsigned long fix_age, time, date, speed, course;
       unsigned long chars;
       unsigned short sentences, failed_checksum;
       long Latitude, Longitude;
       // retrieves /- lat/long in 100000ths of a degree
       gps.get_position(&lat, &lon, &fix_age);
       getGPS();
       Serial.print("Latitude : ");
       Serial.print(LAT/100000,7);
       Serial.print(" :: Longitude : ");
       Serial.println(LON/100000,7);
       if (LAT == 0 && LON == 0)
           continue;    
       counter++;
       if (counter<30)
          continue;    
       mySerial.print("AT+CMGF=1\r");    //Sending the SMS in text mode
       delay(500);
       mySerial.println("AT + CMGS = \"+306972167876\"");//The predefined phone number
       delay(500);
       //the content of the message 
       mySerial.print("Your car location is : http://maps.google.com/maps?q=");
       mySerial.print(LAT/100000,7);
       mySerial.print(",");
       mySerial.print(LON/100000,7);
       mySerial.print(" Latitude : ");
       mySerial.print(LAT/100000,7);
       mySerial.print(" & Longitude : ");
       mySerial.println(LON/100000,7);
       //end
       delay(500);
       mySerial.println((char)26);//the ASCII code of the ctrl z is 26
       delay(5000);
       mySerial.println();
       counter=0;
       break;
   }      
}
 
 
 
void Sim900_Inti(void)
{
  mySerial.println("AT+CMGF=1");    // Set GSM shield to sms mode
  Serial.println("AT+CMGF=1");
  delay(500);
  mySerial.println("AT+CNMI=2,2");//,0,0,0
  Serial.println("AT+CMGF=1");
  delay(500);
} 
 
// function to clear buffer array
void clearBufferArray()                             
{
    for (int i=0; i<count;i++)
      buffer[i]=NULL; // clear all index of array with command NULL
}
 



void DialVoiceCall()
{
  mySerial.println("ATD + +306972167876;");//dial the number
  delay(100);
  mySerial.println();
}


void SIM900power()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);
}

/***GPS DATA***/
//GPS//
void getGPS()
{
     bool newdata = false;
     unsigned long start = millis();
     while (millis() - start < 1000)
     {
        if (feedgps ())
        {
          newdata = true;
        }
     }
     if (newdata)
        gpsdump(gps);
}


bool feedgps()
{
   while (GPS.available())
   {
      if (gps.encode(GPS.read()))
          return true;
   }return 0;
}


void gpsdump(TinyGPS &gps)
{
    gps.get_position(&lat, &lon);
    LAT = lat;
    LON = lon;
    feedgps(); 
}


void CalibrateGPS()
{
  long lat, lon;
  unsigned long fix_age, time, date, speed, course;
  unsigned long chars;
  unsigned short sentences, failed_checksum;
 
  // retrieves +/- lat/long in 100000ths of a degree
  gps.get_position(&lat, &lon, &fix_age);
 
  getGPS();
  Serial.print("Latitude : ");
  Serial.print(LAT/100000,7);
  Serial.print(" :: Longitude : ");
  Serial.println(LON/100000,7);
}

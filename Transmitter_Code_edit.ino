/* Transmitter code
 * Example of sending data from an Ardunio UNO to NodeMCU through UART
 * Using this code you can send multiple data packets 
 * for instance from different sensors to a NodeMCU from an Arduino
 * This code was written for the Telemedicine project of Dhaka University BMPT Department
 * Author: MD Fiaz Islam Bhuiyan, The University of Texas at Dallas
 * Date: 16th July 2018
   -----------------------------------------------------------------------*/

#include <SoftwareSerial.h>

//SoftwareSerial com (2,3);   //Defines a serial connection with RX line on GPIO 2 and TX line on GPIO 3.
const int ldrPin = A0;
int ldrVal = 0;

//const char startOfNumberDelimiter = '<';
const char endOfNumberDelimiter   = '|';

//char toSend[20];


void setup()                        // beginning of the set up function
{
                                    // The setup code runs once
   
  Serial.begin(115200);
 // com.begin(115200);
  srand(42);
  pinMode(ldrPin, INPUT);

}
void loop ()
 {
  ldrVal = analogRead(ldrPin);
 
     Serial.print ('A');        // specifier for LDR data
     Serial.print (ldrVal);    // send the number
     Serial.print (endOfNumberDelimiter);  
     Serial.println ();
     Serial.print ('B');    
     Serial.print ((rand ()%2));    // send the number
     Serial.print (endOfNumberDelimiter);  
     Serial.println ();
     Serial.print ('C');    
     Serial.print ((rand ()%3));    // send the number
     Serial.print (endOfNumberDelimiter);  
     Serial.println ();
     Serial.print ('D');    
     Serial.print ((rand ()%4));    // send the number
     Serial.print (endOfNumberDelimiter);  
     Serial.println ();
     Serial.print ('E');    
     Serial.print ((rand ()%5));    // send the number
     Serial.print (endOfNumberDelimiter);  
     Serial.println ();
     Serial.print ('F');    
     Serial.print ((rand ()%6));    // send the number
     Serial.print (endOfNumberDelimiter);  
     Serial.println ();
     Serial.print ('G');    
     Serial.print ((rand ()%7));    // send the number
     Serial.print (endOfNumberDelimiter);  
     Serial.println ();
     Serial.print ('H');    
     Serial.print ((rand ()%8));    // send the number
     Serial.print (endOfNumberDelimiter);  
     Serial.println ();
   
 delay (1000);
 }  // end of loop


 

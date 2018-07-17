/* Receiver code for NodeMCU
 * Example of sending data from an Ardunio UNO to NodeMCU through UART
 * Using this code you can send multiple data packets 
 * for instance from different sensors to a NodeMCU from an Arduino UNO
 * The data received in displayed in the serial monitor
 * Additionaly this code creates an WiFi access point in the NodeMcu 
 * Which shows the data in a webpage accessible by pc or mobile phone
 * the data also updates automaticallyevery 10 seconds
 * it also allows u to control a LED connected to pin D1 of NodeMCU
 * This code was written for the Telemedicine project of Dhaka University BMPT Department
 * Author: MD Fiaz Islam Bhuiyan, The University of Texas at Dallas
 * Date: 16th July 2018
   -----------------------------------------------------------------------*/


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include<SoftwareSerial.h>

IPAddress    apIP(42, 42, 42, 42);  // Defining a static IP address: local & gateway
                                    // Default IP in AP mode is 192.168.4.1

/* This are the WiFi access point settings. Update them to your likin */
const char *ssid = "ESP8266";
const char *password = "ESP8266Test";

// Define a web server at port 80 for HTTP
ESP8266WebServer server(80);

const int ledPin = D3; // an LED is connected to NodeMCU pin D1 (ESP8266 GPIO5) via a 1K Ohm resistor

bool ledState = false;


SoftwareSerial com(D1,D2); // RX, TX

enum {getLdrSensor, getRandomData1, getRandomData2, getRandomData3, getRandomData4, getRandomData5, getRandomData6, getRandomData7 };

int whichNumber = getLdrSensor;

int brightness, r1, r2, r3, r4, r5, r6, r7;
String toPrint = "No Value";

const char endOfNumberDelimiter   = '|';




void handleRoot() {
  digitalWrite (LED_BUILTIN, 0); //turn the built in LED on pin DO of NodeMCU on
  digitalWrite (ledPin, server.arg("led").toInt());
  ledState = digitalRead(ledPin);

 /* Dynamically generate the LED toggle link, based on its current state (on or off)*/
  char ledText[80];
  
  if (ledState) {
    strcpy(ledText, "LED is on. <a href=\"/?led=0\">Turn it OFF!</a>");
  }

  else {
    strcpy(ledText, "LED is OFF. <a href=\"/?led=1\">Turn it ON!</a>");
  }
 
  ledState = digitalRead(ledPin);

  char html[1000];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

//  int brightness = analogRead(A0);
//  brightness = (int)(brightness + 5) / 10; //converting the 0-1024 value to a (approximately) percentage value
//  processInput();

// Build an HTML page to display on the web-server root address
  snprintf ( html, 1000,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='10'/>\
    <title>ESP8266 WiFi Network</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; font-size: 1.5em; Color: #000000; }\
      h1 { Color: #AA0000; }\
    </style>\
  </head>\
  <body>\
    <h1>ESP8266 Wi-Fi Access Point and Web Server Demo</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <p>Brightness: %d%</p>\
    <p>Random1: %d%</p>\
    <p>Random2: %d%</p>\
    <p>Random3: %d%</p>\
    <p>Random4: %d%</p>\
    <p>Random5: %d%</p>\
    <p>Random6: %d%</p>\
    <p>Random7: %d%</p>\
    <p>%s<p>\
    <p>This page refreshes every 10 seconds. Click <a href=\"javascript:window.location.reload();\">here</a> to refresh the page now.</p>\
  </body>\
</html>",

    hr, min % 60, sec % 60,
    brightness,
    r1,
    r2,
    r3,
    r4,
    r5,
    r6,
    r7,
    ledText
  );
  server.send ( 200, "text/html", html );
  digitalWrite ( LED_BUILTIN, 1 );
}

void handleNotFound() {
  digitalWrite ( LED_BUILTIN, 0 );
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
  digitalWrite ( LED_BUILTIN, 1 ); //turn the built in LED on pin DO of NodeMCU off
}

void setup() {
  pinMode ( ledPin, OUTPUT );
  digitalWrite ( ledPin, 0 );
  
  delay(1000);
  Serial.begin(115200);
  com.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  //set-up the custom IP address
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  
  
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
  server.on ( "/", handleRoot );
  server.on ( "/led=1", handleRoot);
  server.on ( "/led=0", handleRoot);
  server.on ( "/inline", []() {
    server.send ( 200, "text/plain", "this works as well" );
  } );
  server.onNotFound ( handleNotFound );
  
  server.begin();
  Serial.println("HTTP server started");
}


//=====================================  New Functions 


void processNumber (const long n)
 {
  
  switch (whichNumber)
    {
    case getLdrSensor: 
      Serial.print ("LDR Value = ");
      toPrint = "LDR Value = ";
      brightness = n;
      break;
      
    case getRandomData1: 
      Serial.print ("Random Data1 = ");
      toPrint = "Random Data1 = ";
      r1 = n;
      break;

    case getRandomData2: 
      Serial.print ("Random Data2 = ");
      toPrint = "Random Data2 = ";
      r2 = n;
      break;

    case getRandomData3: 
      Serial.print ("Random Data3 = ");
      toPrint = "Random Data3 = ";
      r3 = n;
      break;

    case getRandomData4: 
      Serial.print ("Random Data4 = ");
      toPrint = "Random Data4 = ";
      r4 = n;
      break;

    case getRandomData5: 
      Serial.print ("Random Data5 = ");
      toPrint = "Random Data5 = ";
      r5 = n;
      break;

    case getRandomData6: 
      Serial.print ("Random Data6 = ");
      toPrint = "Random Data6 = ";
      r6 = n;
      break;

    case getRandomData7: 
      Serial.print ("Random Data7 = ");
      toPrint = "Random Data7 = ";
      r7 = n;
      break;
    }

  
  Serial.println (n);
 }  // end of processNumber
 
void processInput ()
 {
 static long receivedNumber = 0;
 static boolean negative = false;
 
 byte c = com.read ();
 
 switch (c)
   {
     
   case endOfNumberDelimiter:  
     if (negative) 
       processNumber (- receivedNumber); 
     else
       processNumber (receivedNumber); 

   // fall through to start a new number
   case 'A': 
     receivedNumber = 0; 
     negative = false;
     whichNumber = getLdrSensor;
     break;
   case 'B': 
     receivedNumber = 0; 
     negative = false;
     whichNumber = getRandomData1;
     break;
   case 'C': 
     receivedNumber = 0; 
     negative = false;
     whichNumber = getRandomData2;
     break;
   case 'D': 
     receivedNumber = 0; 
     negative = false;
     whichNumber = getRandomData3;
     break;
   case 'E': 
     receivedNumber = 0; 
     negative = false;
     whichNumber = getRandomData4;
     break;
   case 'F': 
     receivedNumber = 0; 
     negative = false;
     whichNumber = getRandomData5;
     break;
   case 'G': 
     receivedNumber = 0; 
     negative = false;
     whichNumber = getRandomData6;
     break;
   case 'H': 
     receivedNumber = 0; 
     negative = false;
     whichNumber = getRandomData7;
     break;
     
   case '0' ... '9': 
     receivedNumber *= 10;
     receivedNumber += c - '0';
     break;
     
   case '-':
     negative = true;
     break;
     
   } // end of switch  
 }  // end of processInput


void loop() {
  if (com.available())
  {
    processInput();
  }
  server.handleClient();
}

#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
   
char ssid[] = "blahblahblah";    //  your network SSID (name) 
char pass[] = "blahblahblah";   // your network password

int status = WL_IDLE_STATUS;
WiFiClient  client;

// On ESP8266:  0 - 1023 maps to 0 - 1 volts
#define VOLTAGE_MAX 1.0
#define VOLTAGE_MAXCOUNTS 1023.0

unsigned long myChannelNumber = 123456;
const char * myWriteAPIKey = "8L4H8L4H8L4H";

void setup() 
{
  WiFi.begin(ssid, pass);
  ThingSpeak.begin(client);
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading 
  // On Uno,Mega,YunArduino:  0 - 1023 maps to 0 - 5 volts
  // On ESP8266:  0 - 1023 maps to 0 - 1 volts
  // On MKR1000,Due: 0 - 4095 maps to 0 - 3.3 volts
  float voltage = sensorValue * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);

  int sample = 17;

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  ThingSpeak.writeField(myChannelNumber, 1, sample, myWriteAPIKey);
  delay(20000); // ThingSpeak will only accept updates every 15 seconds.
}

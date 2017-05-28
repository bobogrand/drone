#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define samples 5000
// wifi

void setup()
{
  Serial.begin(115200);
}

void loop()
{
    if(analogRead(A0) > 50){
      for (int i = 0; i < samples; i += 1){
        int data;
        data= analogRead(A0);
        Serial.println(data);
        delayMicroseconds(60);
      }
      delay(100);
    }
    
}




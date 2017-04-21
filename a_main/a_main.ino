/*
 * Reads a differential pressure sensor and converts it to a 
 * velocity using the Pitot Tube equation. 
 * Also logging to an SD card for further analysis
 */
#include <SPI.h>
#include <SD.h>


const int chipSelect = 10;   // SD card pin
const int switchPin = 2;    // on/off switch pin
const int ledPin = 3;        // led logging indicator
int SnsrPin = A0;           // pitot sensor analog input pin
int pitotVal = 0;           // pitot sensor value
int switchState = 0;        // the state of the switch
float strmVel = 0.0;
unsigned long logTime = 0;
// function prototypes
float senseStrm();
void logData(int sensor, float velocity, unsigned long timer);

void setup() 
{
  Serial.begin(9600);
  while(!Serial)
  {
    ;// wait for serial connection
  }
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.println("Initializing SD card...");
  if (!SD.begin(chipSelect))
  {
    Serial.println("init failed");
  }
  else
  {
    Serial.println("init done");
  }
}

void loop() 
{
  unsigned long timer = millis();
  int counter = 0;
  switchState = digitalRead(switchPin);  // see what state switch is in
  while (switchState == HIGH)
  {
    digitalWrite(ledPin,HIGH);
    Serial.println("sensor on");
    if(counter == 0)
    {
     logTime = timer;    // freeze moment in time 
    }
    strmVel = senseStrm();
    logData(strmVel, pitotVal, logTime);
    Serial.print("analog Val::");
    Serial.print(pitotVal);
    Serial.print("\t");
    Serial.print("velocity::");
    Serial.print(strmVel);
    Serial.print("\t");
    Serial.print("time::"); 
    Serial.println(logTime);   
  }
  digitalWrite(ledPin,LOW);
  Serial.println("Sensor off");
  counter++;

  delay(100);
}




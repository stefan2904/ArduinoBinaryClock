// Simple Binary Clock, by Patrick & Stefan \o/

// http://playground.arduino.cc/Code/Time
// http://playground.arduino.cc/Code/DCF77

#include "DCF77.h"
#include "Time.h"

// Pin-assignment based on Arduino Nano pinout:
// http://pighixxx.com/nanopdf.pdf

#define DEBUG false

#define DCF_PIN 2           // Connection pin to DCF 77 device
#define DCF_INTERRUPT 0     // Interrupt number associated with pin DCF_PIN

#define H10 3 // D3
#define H20 4 // D4

#define H1 5 // D5
#define H2 6 // D6
#define H4 7 // D7
#define H8 8 // D8

#define M10 9 // D9
#define M20 10 // D10
#define M40 11 // D11
#define M1  12 // D12
#define M2  13 // D13
#define M4  14 // A0
#define M8  15 // A1

time_t time;

// DCF77 is DST aware, so no need to take care of that.
DCF77 DCF = DCF77(DCF_PIN, DCF_INTERRUPT);

void setup() {

  // set fake time: setTime(hr, min, sec, day, month, yr);
  setTime(10, 30, 0, 30, 05 , 2016);

  // Setup Serial Interface:
  Serial.begin(9600);

  // Setup IO:
  pinMode(H10, OUTPUT); pinMode(H20, OUTPUT);
  pinMode(H1, OUTPUT); pinMode(H2, OUTPUT); pinMode(H4, OUTPUT); pinMode(H8, OUTPUT);

  pinMode(M10, OUTPUT); pinMode(M20, OUTPUT); pinMode(M40, OUTPUT);
  pinMode(M1, OUTPUT); pinMode(M2, OUTPUT); pinMode(M4, OUTPUT); pinMode(M8, OUTPUT);

  // Test LEDs
  toggleLEDs();

  // Setup DCF77:
  DCF.Start();
  Serial.println("Waiting for DCF77 time ... ");
  Serial.println("It will take at least 2 minutes until a first update can be processed.");
}

int loopCnt = 0;
bool dcfTimeFound = false;
bool lastStatus = LOW;

void loop() {
  //delay(1000);
  delay(10);

  if(dcfTimeFound == false) {
    dcfActivityDisplay();
  }

  if(loopCnt % 100 == 0) {   
    time_t DCFtime = DCF.getTime(); // Check if new DCF77 time is available
    if (DCFtime != 0)
    {
      Serial.println("Time is updated");
      setTime(DCFtime);
      dcfTimeFound = true;
    } else if (dcfTimeFound == false && !DEBUG) { // not found and never found
      toggleLEDs();
    } 
    if(dcfTimeFound == true) {
      digitalClockDisplay();
    }
    loopCnt = 0;
  }

  loopCnt++;
}

void toggleLEDs() {
  lastStatus = !lastStatus;
  for(int i = H10; i <= H8; i++) {
    setLED(i, lastStatus == true ? 0 : 1, "");
  }
  for(int i = M10; i <= M8; i++) {
    if(i != M40) 
      setLED(i, lastStatus == false ? 0 : 1, "");
  }
}

void dcfActivityDisplay(){
  int sensorValue = digitalRead(DCF_PIN);
  if(DEBUG) {
    for(int i = H10; i <= M8; i++) {
      setLED(i, sensorValue, "");
    }
  } else {
    setLED(M40, sensorValue, "");
  }
  
}

void digitalClockDisplay() {
  int h = hour();
  int m = minute();

  Serial.print(h);
  Serial.print(":");
  Serial.print(m);
  Serial.println();

  setLED(H10, (h / 10) & 0x1, "H10");
  setLED(H20, (h / 10) & 0x2, "H20");

  setLED(H1, (h % 10) & 0x1, " H1");
  setLED(H2, (h % 10) & 0x2, " H2");
  setLED(H4, (h % 10) & 0x4, " H4");
  setLED(H8, (h % 10) & 0x8, " H8");

  setLED(M10, (m / 10) & 0x1, "M10");
  setLED(M20, (m / 10) & 0x2, "M20");
  setLED(M40, (m / 10) & 0x4, "M40");

  setLED(M1, (m % 10) & 0x1, " M1");
  setLED(M2, (m % 10) & 0x2, " M2");
  setLED(M4, (m % 10) & 0x4, " M4");
  setLED(M8, (m % 10) & 0x8, " M8");
}

void setLED(int id, int cond, char* name) {
  boolean status = cond != 0;

  digitalWrite(id, status ? HIGH : LOW);

//    Serial.print("LED ");
//    Serial.print(name);
//    Serial.print(": ");
//    Serial.print(status ? "on" : "off");
//    Serial.println();
}






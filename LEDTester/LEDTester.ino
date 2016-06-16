// LED Tester for
// Simple Binary Clock, by Patrick & Stefan \o/

// Pin-assignment based on Arduino Nano pinout:
// http://pighixxx.com/nanopdf.pdf

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

int cnt = 0;

void setup() {
  // Setup Serial Interface:
  Serial.begin(9600);

  // Setup IO:
  pinMode(H10, OUTPUT); pinMode(H20, OUTPUT);
  pinMode(H1, OUTPUT); pinMode(H2, OUTPUT); pinMode(H4, OUTPUT); pinMode(H8, OUTPUT);

  pinMode(M10, OUTPUT); pinMode(M20, OUTPUT); pinMode(M40, OUTPUT);
  pinMode(M1, OUTPUT); pinMode(M2, OUTPUT); pinMode(M4, OUTPUT); pinMode(M8, OUTPUT);

  Serial.println("Welcome to Patrick & Stefan's LED Tester!");
  delay(2000);
  
}

void loop() {
  delay(500);
  digitalClockDisplay();
}

void digitalClockDisplay() {
  for(int i = H10; i <= M8; i++) {
    setLED(i, LOW);
  }
  setLED((cnt % (M8 - H10 + 1)) + H10, HIGH);
  
  //Serial.print("poke ");
  //Serial.println(cnt);

  cnt++;
}

void setLED(int id, boolean status) {
  digitalWrite(id, status);
  if(status == HIGH) {
    Serial.print("enabling LED ");
    Serial.println(id);
  }
}





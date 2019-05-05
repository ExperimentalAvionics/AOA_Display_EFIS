// LED Bar display for Angle of Attack
// the display works as an I2C slabe to Display Unit
// Assumption is that the AoA value is 2 bytes (int) and presented in degrees x 10 (120 = 12 degrees)


#include <Wire.h>

int i = 0; // counter
unsigned long currentMillis;
int AOA = 0;
int AOAmin = -1;
int AOAmax = 16;
int topLED = 2;
int x = 0;

void setup() 
{
   Serial.begin(115200);    
// init the pins 2-11
  for (int i = 2; i <= 11; i++) {
    pinMode(i, OUTPUT);  
    delay(10);
  }   

  delay(1000);

  for (int i = 2; i <= 11; i++) {
    digitalWrite(i, HIGH); 
    delay(200);
  }

// Configuring I2C Slave with address x09
  Wire.begin(9); 
  Wire.onReceive(receiveEvent);

}

void receiveEvent(int bytes) {
  x = 0;
//  Serial.print("Data received = ");
  while (Wire.available()) { // loop through all the bytes received
    x = x << 8 | Wire.read(); // receive byte shifting earlier received bytes left
  }
}

void loop()
{
  AOA= round((float)x/10.0);

  topLED = map(AOA, AOAmin, AOAmax, 11, 2); // map doesnt work properly sometimes

  for (int i = topLED; i <= 11; i++) {
    digitalWrite(i, LOW); 
  }
  
  for (int i = 2; i < topLED; i++) {
    digitalWrite(i, HIGH); 
  }
  
  delay(100);               // wait for a moment

  
}

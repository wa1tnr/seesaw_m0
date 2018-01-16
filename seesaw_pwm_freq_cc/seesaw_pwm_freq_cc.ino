// Tue Jan 16 17:30:19 UTC 2018

// The Lawn Sprinkler

// previous:
// Tue Jan 16 16:45:28 UTC 2018

// calibration of PWM 16 bit analogWrite:

// 2.9 percent to 10.7 percent duty cycle, full excursion.


// Seesaw PWM Frequency setter program
// with active Duty Cycle variances - to sweep the servo motor arm

// setPWMFreq(uint8_t pin, uint16_t freq)

#define NOUNS " HAUTL   GELBAR   FERGUS "    // nonsense to print to the terminal 
                                             // which is used to identify 
                                             // small revisions to the code

// setup: Metro M0 Express, 4-wires: SDA SCL 5VDC GND to Seesaw Breakout

#include "Adafruit_seesaw.h"

Adafruit_seesaw ss; // this is a specialized  i2c driver with pre-established useful values

void setup() {
  uint16_t  freq  = 50; // frequency of PWM in Hertz - real value will be 44.58 Hz

  Serial.begin(9600);
  while (!Serial) {
    delay(44);
  }

  if(!ss.begin()){  // remember this is i2c - an i2c conversation has just begun
    Serial.println("Error");
    while(1);
  }
  else Serial.print("seesaw started  "); Serial.println(NOUNS); 
  delay(400);

  // set the PWM frequency (the 'carrier') in Hertz.  50 Hz is typical for a servo.

  // setPWMFreq(uint8_t pin, uint16_t freq)
  ss.setPWMFreq(
    (uint8_t)      6,   // PWM on Pin 6 of the Seesaw Breakout
    (uint16_t)  freq    // frequency of PWM in Hertz
    );

  delay(120);
}


void loop() {
  int       step = 50; // can be any small integer
  // investigate any range in duty cycle that interests you
  for (int dutyCy  = 1900; dutyCy  <7100; dutyCy  = dutyCy  + step) {

    // write the duty cycle value to the PWM pin's handler
    // analogWrite(uint8_t pin, uint16_t value, uint8_t width)
    ss.analogWrite(
      (uint8_t)        6, // Pin 6
      (uint16_t)  dutyCy, // 1800 here means 2.7 % duty cycle - may be somewhat too low for a servo
      (uint8_t)       16  // 8 or 16 bit width for 'value'
      );

    // delay, print messages, delay some more
    delay(250);
    Serial.print("  "); Serial.print(dutyCy); Serial.print("  ");

    // to get a human-appreciable delay, add some here:

    delay(200); // long delay at bottom of the 'for' loop
  }
  Serial.print("LOOP again  ");
}





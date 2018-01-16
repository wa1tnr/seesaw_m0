// Tue Jan 16 16:26:05 UTC 2018

// Seesaw PWM Frequency setter program

// setPWMFreq(uint8_t pin, uint16_t freq)

#define NOUNS " FERGUS  ELROY  DAGMAR " // nonsense to print to the terminal 
                                             // which is used to identify 
                                             // small revisions to the code

// The Seesaw PWM function seems to operate at only 7 discrete frequencies:

//    2.7 Hz   11 Hz   44 Hz   89 Hz   178 Hz   356 Hz  713 Hz (exact decimals below).

// It's doing so by taking a single reference frequency, and prescaling (dividing) it.

//   2.786 Hz  to    8    2.786 x 4 =  11.144
//  11.14  Hz  to   26   11.144 x 4 =  44.576
//  44.58  Hz  to   76   44.58  x 2 =  89.16
//  89.16  Hz  to  141   89.16  x 2 = 178.32
// 178.3   Hz  to  251  178.32  x 2 = 356.64
// 356.7   Hz  to  501  356.64  x 2 = 713.28
// 713.4   Hz

// seesaw/seesaw/bsp/bsp_timer.cpp:

// 51         uint8_t prescale = TC_CTRLA_PRESCALER_DIV256_Val;
// 52         if( freq > 500) prescale = TC_CTRLA_PRESCALER_DIV1_Val;
// 53         else if( freq > 250 ) prescale = TC_CTRLA_PRESCALER_DIV2_Val;
// 54         else if( freq > 140 ) prescale = TC_CTRLA_PRESCALER_DIV4_Val;
// 55         else if( freq > 75 ) prescale = TC_CTRLA_PRESCALER_DIV8_Val;
// 56         else if( freq > 25 ) prescale = TC_CTRLA_PRESCALER_DIV16_Val;
// 57         else if( freq > 7 ) prescale = TC_CTRLA_PRESCALER_DIV64_Val;


// setup: Metro M0 Express, 4-wires: SDA SCL 5VDC GND to Seesaw Breakout

#include "Adafruit_seesaw.h"

Adafruit_seesaw ss; // this is a specialized  i2c driver with pre-established useful values

void setup() {
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
}


// main loop: Step the PWM frequency and measure with a meter or a piezo buzzer to annunciate it

void loop() {
  int step = 20; // can be any small integer

  // investigate any range in freq that interests you
  for (int freq  = 13; freq  <750; freq  = freq  + step) {

    // set the PWM frequency (the 'carrier') in Hertz.  50 Hz is typical for a servo.

    // setPWMFreq(uint8_t pin, uint16_t freq)
    ss.setPWMFreq(
      (uint8_t)      6,   // PWM on Pin 6 of the Seesaw Breakout
      (uint16_t)  freq    // frequency of PWM in Hertz
      );

    delay(250);


    // write the duty cycle value to the PWM pin's handler

    // analogWrite(uint8_t pin, uint16_t value, uint8_t width)
    ss.analogWrite(
      (uint8_t)        6, // Pin 6

      // vary the duty cycle here, if you want to see some servo motor arm sweeping:
      (uint16_t)    1800, // 2.7 % duty cycle - may be somewhat too low for a servo

      // (uint16_t)  100,  // good for very low frequency work - not useful for servo

      (uint8_t)       16  // 8 or 16 bit width for 'value'
      );

    // delay, print messages, delay some more
    delay(250);
    Serial.print("  "); Serial.print(freq); Serial.print("  ");
    delay(3000); // long delay at bottom of the 'for' loop
  }
}


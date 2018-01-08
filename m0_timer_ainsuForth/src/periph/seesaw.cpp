// Mon Jan  8 23:02:05 UTC 2018
// 4737-a0c-00g- // +cribs +dump_cribs +freq +analog_write_demo +seesaw_WORKING

// Mon Jan  8 22:24:07 UTC 2018
// 4737-a0c-00f- // +cribs +dump_cribs +freq +analog_write_demo

// https://learn.adafruit.com/adafruit-seesaw-atsamd09-breakout/arduino-wiring-test

#include <Arduino.h>
#include "../../yaffa.h"
#include "../../Dictionary.h"

#include "Adafruit_seesaw.h"

Adafruit_seesaw ss;

// Mon Jan  8 21:51:45 UTC 2018
// 4737-a0c-00e- // +cribs

// dare I even say it.  The seesaw.  Maybe a bit of vocabulary?

// 08 January 2018  21:46 UTC.


// freq ( n -- )

// the freq word purports to send new frequency data via i2c.
// that would change the PWM carrier from its default (near 490 Hz?)
// to some other value -- to 50 Hz, for instance.

// It most likely depends on a standard sketch for the Arduino,
// meant to communicate with the Adafruit Seesaw breakout.

// This is all fiction, at the moment.

// Mon Jan  8 20:10:36 UTC 2018
// 4737-a0c-00c- // +cribs


/*******************************************************************************/

/*
  Fade

  This example shows how to fade an LED on pin 6 of a seesaw board using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On the SAMD09 breakout these are pins 5, 6, and 7
*/

// #include "Adafruit_seesaw.h"

// Adafruit_seesaw ss;
 
// Connect an LED through a small resistance (~1k ohms, maybe less)
// to Pin 6 of the Seesaw Breakout (use one of the PWM pins).

// The forth word here is 'freq' though we are not doing that yett.

// This is just a test word to determine if Seesaw conversation
// is occuring over i2c using this target board (Metro M0 Express,
// nominally; maybe Arduino M0 Pro or Feather M0 Express may be
// used as well.  Untested except on the Metro M0 Express as of
// 08 Jan 2018 23:01 UTC).

int led = 6;           // the PWM pin the LED is attached to
int brightness = 1;    // how bright the LED is
int fadeAmount = 36;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup_seesaw_freq() {
  // Serial.begin(9600);
  
  if(!ss.begin()){
    Serial.println("ERROR!");
    while(1);
  }
  else Serial.println("seesaw started");
}

// the loop routine runs over and over again forever:
void loop_seesaw_freq() {
  // set the brightness of pin 9:
  ss.analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(100);
}

const char freq_str[] = "freq";
void _freq(void) {
  Serial.println();
  Serial.print("  placeholder for the freq word's behavior.\r\n");
  setup_seesaw_freq();
  Serial.print(" No further keyboard response is possible -- endless loop --\r\n");
  Serial.print(" press RESET to regain control.  Or wait 40 cycles. ;)\r\n");
  // while(-1) {
  for (int i = 0; i < 40; i++) {
      loop_seesaw_freq();
      // Serial.println("Seen line 91");
      delay(800);
  }
  // }
}


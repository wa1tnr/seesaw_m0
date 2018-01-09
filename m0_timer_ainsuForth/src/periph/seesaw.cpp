// Tue Jan  9 02:02:45 UTC 2018
// 4737-a0c-00g- // +cribs +dump_cribs +freq +analog_write_demo +seesaw_WORKING

// Seems that the Seesaw simply isn't responding to  
// ------------
// setPWMFreq() 
// ------------
// though too early to be certain that's so.

// Mon Jan  8 23:02:05 UTC 2018


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

int led = 5;
int buzzer = 6;
int brightness = 1;    // how bright the LED is
int brightness_FREQ = 10;   // for the FREQ thing not the LED.
int fadeAmount = 36;    // how many points to fade the LED by

void setup_seesaw_freq() {
  
  if(!ss.begin()){
    Serial.println("ERROR!");
    while(1);
  }
  else Serial.println("seesaw started");
}


void loop_seesaw_freq() {
  ss.analogWrite(led, brightness);

  brightness = brightness + fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(100);
}

// buzzer:

void seesaw_freqb() {
  ss.analogWrite(buzzer, 122); // duty cycle
  delay(500);
}

const char freq_str[] = "freq";
void _freq(void) {
  Serial.println();
  setup_seesaw_freq();

  for (int i = 0; i < 40; i++) {
      loop_seesaw_freq();
      delay(800);
  }
}


const char freqb_str[] = "freqb"; // ( n -- )  n is the frequency, placed on TOS (top of stack)
void _freqb(void) {
  setup_seesaw_freq();
  seesaw_freqb();

  // ss.setPWMFreq(buzzer,dStack_pop()); // how values are passed internally

  delay(500);

  ss.setPWMFreq(buzzer,dStack_pop()); // place an integer on the stack by 
                                      // typing it at the ok prompt and
                                      // pressing ENTER.
                                      // the dot-s word ('.s') confirms it is present.
  delay(500);
}


/*

doco

setPWMFreq()
void Adafruit_seesaw::setPWMFreq ( uint8_t pin, uint16_t freq ) 		

set the PWM frequency of a PWM-enabled pin. Note that on SAMD09, SAMD11 boards the frequency will be mapped to closest match fixed frequencies. Also note that PWM pins 4 and 5 share a timer, and PWM pins 6 and 7 share a timer. Changing the frequency for one pin will change the frequency for the other pin that is on the timer.

Parameters
    pin    the number of the pin to change frequency of. On the SAMD09 breakout,
           this corresponds to the number on the silkscreen. on the default seesaw
           firmware on the SAMD09 breakout, pins 5, 6, and 7 are PWM enabled.
    freq    the frequency to set.

Returns
    none 

*/


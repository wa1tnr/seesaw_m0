// Fri Jan 12 21:54:45 UTC 2018
// 4737-a0d-00a- // +cribs +freq +fade +pw

// Tue Jan  9 19:53:04 UTC 2018
// 4737-a0c-00s- // +cribs +freq +fade +seesaw_path_change


// Tue Jan  9 04:30:43 UTC 2018
// 4737-a0c-00j- // +cribs +freq +fade

// Tue Jan  9 02:02:45 UTC 2018
// 4737-a0c-00g- // +cribs +dump_cribs +freq +analog_write_demo +seesaw_WORKING

// TEST SIX.

// Seems that the Seesaw simply isn't responding to  
// ------------
// setPWMFreq() 

// closest ref besides the obvious one(s):
// https://learn.adafruit.com/16-channel-pwm-servo-driver/library-reference

// ------------
// though too early to be certain that's so.

// Mon Jan  8 23:02:05 UTC 2018


// Mon Jan  8 22:24:07 UTC 2018
// 4737-a0c-00f- // +cribs +dump_cribs +freq +analog_write_demo

// https://learn.adafruit.com/adafruit-seesaw-atsamd09-breakout/arduino-wiring-test


// oh boy no depth word present.  Makeshift.

// 102   char depth = dStack_size(); // from a file named similar to 'stack ops'

#include <Arduino.h>
#include "../../../yaffa.h"
#include "../../../Dictionary.h"

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
  Fade - Adafruit Industries (supplied in the corresponding Library as Fade.ino)

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


// ============================================================================
// =======================  12 January Friday 23:49 UTC  ======================
// ============================================================================
// The BUZZER was there to troubleshoot and annuciate the 50 Hz pwm signal
// meant for the servo motor.  For the moment, this pin will continue to
// be referred to as the BUZZER - with the understanding that, for the more
// advanced use, one connects the servo motor to the same two terminals
// formerly occupied by the piezo buzzer device.
// ============================================================================

int led = 5;
int buzzer = 6; // Note!  buzzer is the servo motor - use EITHER device here
int brightness = 1;    // how bright the LED is
int brightness_FREQ = 10;   // for the FREQ thing not the LED.
int fadeAmount = 36;    // how many points to fade the LED by

void setup_seesaw() {
  if(!ss.begin()){
    Serial.println("ERROR!");
    while(1);
  }
  else Serial.print("seesaw started");
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

void seesaw_freq() {
  // ss.analogWrite(buzzer, 32222, 16); // duty cycle // third parameter is 8 or 16 for 'width'
  ss.analogWrite(buzzer, 90);
  delay(50);
}



const char fade_str[] = "fade"; // rename to match elsewhere
void _fade(void) {
  setup_seesaw();
  Serial.print(" "); // tidy

  for (int i = 0; i < 40; i++) {
      loop_seesaw_freq();
      delay(800);
  }
}

const char pw_str[] = "pw"; // ( n -- )  n is the pulse width/duty cycle, placed on TOS (top of stack)
void _pw(void) {
  // empty skeleton function for the moment.  Get all structures in place by modifying 4 files or so.
  // okay the hooks are present for the pw word.  Now, make it useful.
  char depth = dStack_size();

  // validate TOS range 1-180

  if (depth < 1) {
      dStack_push(-4); // throw an error - stack underflow.
      _throw();
      _quit(); // we caught it in time - can quit nicely.
      return;  // do not execute the code, below.  Done for this round. ;)
  }

  dStack_push(0);
  _max();
  dStack_push(199);
  // map 22 to 180
  _min();
  _dupe();
  Serial.print(".  valid input, pw: ");
  Serial.print(dStack_pop()); // consumes one of the duplicates to print it here.
  Serial.print("\r\n ");
  // the system wanted to range from 5 to 27.  Normalized to zero reference (0 to 22).
  // add back the 5 when writing:
  // ss.analogWrite(buzzer,(dStack_pop()+5)); // duty cycle (position of the servo arm/horn)
  ss.analogWrite(buzzer,(dStack_pop()+0)); // duty cycle (position of the servo arm/horn)
  delay(500);
}
const char freq_str[] = "freq"; // ( n -- )  n is the frequency, placed on TOS (top of stack)
void _freq(void) {
  char depth = dStack_size();

  // validate TOS range 40-1000

  if (depth < 1) {
      // dStack_push(-1); // throw an error - abort
      dStack_push(-4); // throw an error - stack underflow.
      _throw();
      _quit(); // we caught it in time - can quit nicely.
      return;  // do not execute the code, below.  Done for this round. ;)
  }

  setup_seesaw(); // ideally this should be a separate word in forth.

  delay(500);

  dStack_push(40);
  _max();
  dStack_push(1000);
  _min();

  _dupe();

  // _dot_s(); // print the stack.  should be two stack items.

  Serial.print(".  valid input, freq: ");
  Serial.print(dStack_pop()); // consumes one of the duplicates to print it here.
  Serial.print("\r\n ");

  // Serial.print(".s -- immediately prior to the call to setPWMFreq().\r\n");

  // _dot_s(); // print the stack.  should be one stack item.

  // stack has one last copy left, which it will use, here:

  ss.setPWMFreq(buzzer,dStack_pop()); // place an integer on the stack by 
                                      // typing it at the ok prompt and
                                      // pressing ENTER.
                                      // the dot-s word ('.s') confirms it is present.

  // seesaw_freq(); // ex. ss.analogWrite(buzzer, 90);
  dStack_push(1); // throw an error - stack underflow.
  _pw();

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


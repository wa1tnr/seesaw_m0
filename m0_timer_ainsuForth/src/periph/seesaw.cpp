// Mon Jan  8 22:01:58 UTC 2018
// 4737-a0c-00f- // +cribs +dump_cribs +freq

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

#include <Arduino.h>
#include "../../yaffa.h"
#include "../../Dictionary.h"

/*******************************************************************************/
const char freq_str[] = "freq";
void _freq(void) {
  Serial.println();
  Serial.print("  placeholder for the freq word's behavior.\r\n");
}


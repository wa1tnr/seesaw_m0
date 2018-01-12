// Fri Jan 12 21:54:45 UTC 2018
// 4737-a0d-00a- // +cribs +freq +fade +pw

// servo motor stuff: pw, freq

// Mon Jan  8 22:01:58 UTC 2018
// 4737-a0c-00f- // +cribs +dump_cribs +freq

// Mon Jan  8 20:10:36 UTC 2018
// 4737-a0c-00c- // +cribs

// based on help.*

// Thu Jun 22 20:49:39 UTC 2017
// 4735-a0p-04-

#include <Arduino.h>
#include "../../yaffa.h"
#include "../../Dictionary.h"
// #include "../../Error_Codes.h"

/*******************************************************************************/
/*******************************************************************************/
const char cribs_str[] = "cribs";
void _cribs(void) {
  Serial.println();
  Serial.print("    ainsuForth - seesaw.\r\n\r\n");
  Serial.print("    Crib Sheet -- GCLK  timer stuff - 08 Jan 2018 forward.\r\n");
  Serial.print("    EDIT ME:  m0_timer_ainsuForth/src/dict/cribs.cpp \r\n");

  Serial.println("");

  Serial.print("This is an extensible Forth - you may add words to its dictionary\r\n");
  Serial.print("at any time, without recompiling in the Arduino IDE.\r\n");

  Serial.print("Temporary words typed here by you, and compiled in SRAM only - \r\n\r\n");

  Serial.print("  these are not stored across reboots\r\n");
  Serial.print("  (they aren't in the flash dictionary):\r\n\r\n");

  Serial.print(" : fastblink  6 gendiv     4 per0   timers ; \r\n");
  Serial.print(" : medblink   6 gendiv     9 per0   timers ; \r\n");
  Serial.print(" : slowblink  6 gendiv    14 per0   timers ; \r\n");
  Serial.print(" : vsloblink  6 gendiv    44 per0   timers ; \r\n");
  Serial.print(" : usloblink  6 gendiv   122 per0   timers ; \r\n");
  Serial.println("");
  Serial.print("    from:  m0_timer_ainsuForth/src/app/timer/timer.cpp" );
  Serial.println("");

  Serial.println(" usloblink 20000 delay fastblink 10123 delay medblink\r\n");
  Serial.println("");
  Serial.println(" hex here 100 - 40 dump\r\n");
  Serial.println(" fastblink fade   << they run independently and simultaneously.\r\n");
  Serial.println(" fastblink fade decimal 43 emit   << prints '+' after routine completes.\r\n");
  Serial.println(" : cmp 37 pw 222 delay pw ;   << fast compare two different pw - call with a value on TOS.\r\n");
  Serial.println("50 freq  << supposed to be canonical, but in practice freq can be a wide variety of values.\r\n");
  Serial.println("122 freq 54 pw 222 delay 10 pw  << seems very responsive");
  Serial.println(" The 'warm' word is a soft reset and is the usual way to restart ainsuForth.\r\n");

  // Serial.print("    x

}


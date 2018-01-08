// Mon Jan  8 19:54:09 UTC 2018
// wanted shorter pulse on LED 13

// Thu Jul  6 19:10:43 UTC 2017
// 0103-a0c-01-
// 4735-b0a-00-

// CANAFT--PIBOK

#include <Arduino.h>

#include "../../../yaffa.h" // this sketch is an ainsuForth application

#undef HAS_NEO_PIXEL_LIB // 07 Jan 2018 quick kludge to avoid NeoPixel issue
#ifdef HAS_NEO_PIXEL_LIB
#include "../../periph/neo_pixel.h" // that's src/periph/neo_pixel.h
#endif

/******************************************************************************/
/** Global Variables                                                         **/
/******************************************************************************/
int flip_flop = 1;
int buzzPin = 13 ; // A5

/*  specific to the timer-counter sketch  */
void darkenBuzzPin(void) { // turn off buzzPin
 digitalWrite(buzzPin, 0); // turn off
}

void darkenlight(void) {
  digitalWrite(13, 0); // turn off
  delay(2000);
}

void brightenBuzzPin(void) { // turn on buzzPin
  digitalWrite(buzzPin, 1); // turn on
}

void brightenlight(void) {
  digitalWrite(13, 1); // turn on
  delay(220);
}

void brightenlightShort(void) {
  digitalWrite(13, 1); // turn on
  delay(5);
}

void blinkenlight(void) {
  brightenlight();
  darkenlight();
}

void blinkenlightShort(void) {
  brightenlightShort();
  darkenlight();
}

extern void introduction(); // {
//     blinkenlight(); Serial.print(".");
// }


void setup_buzzPin(void) {
  // LED PA_17 - mapped by Arduino as digital 13

  pinMode(buzzPin, 1); // OUTPUT
  pinMode(13, 1); // OUTPUT

  darkenlight();  // not needed - insurance.
  blinkenlight(); delay(44);
  darkenlight(); // turn off so to notice the gap
  delay(234);
}


void pinToggle(void) { // implement a flip-flop using a very short counter
  flip_flop = flip_flop + 1 ;
  if (flip_flop > 0) {
    flip_flop = -1 ;    // reset the flip_flop state
    darkenBuzzPin();   // turn off buzzPin
  } else {
    brightenBuzzPin(); // turn on buzzPin
  }
}


// end.

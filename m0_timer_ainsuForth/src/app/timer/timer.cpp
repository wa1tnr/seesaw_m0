// Mon Jan  8 20:10:36 UTC 2018
// 4737-a0c-00c- // +cribs

// bugfix for this one file, timer.cpp:                  08 Jan 2018 20:35 UTC

// dStack_push(21); // need 21 bright for the selected, timer-controlled colors
// This is removed and was an artifact of NeoPixel specific code.  Notice the
// stack kept growing with a bunch of '21' entries.  This was the offending line.

// Thu Jul  6 19:10:43 UTC 2017
// 0103-a0c-01-
// 4735-b0a-00-

// CANAFT--PIBOK

#include <Arduino.h>
// 07 Jan 2018: intention is to control all compiles from yaffa.h and compatibility.h if present in base directory.
#include "../../../yaffa.h" // this sketch is an ainsuForth application


#undef HAS_NEO_PIXEL_LIB //  override for quick universal compile avoiding NeoPixel presence issue -- 07 Jan 2018

#ifdef HAS_NEO_PIXEL_LIB
  #include "../../periph/neo_pixel.h" // that's src/periph/neo_pixel.h
#endif

#include "../../dict/max_min.h"
#include "../../dict/cblink.h"
#include "../../kernel/throw.h" // seems unlikely this is the way to reference the kernel

int clock    = 0x04;

int gendiv   = 0x03;

// int period0  = 0x7e;
// int period1  = 0x31;

int period0  = 0xfe;
int period1  = 0x65; //   - observed: the red 13 led could stand to run slower
                     //     but its better to try to speed up per1 - neopx

// int period1  = 0x65;
// int period1  = 0xca;

extern void setup_buzzPin(void);
extern void pinToggle(void); // led pin 13
// 07 Jan 2018: commented out.  Maybe not an issue.
// extern void colorTime(void);
extern void introduction();

void eightBitMaxMin(void) {
  dStack_push(0);
  _max();
  dStack_push(255);
  _min();
}

// void tc4ccMaxMin(void) {
//   dStack_push(0);
//   _max();
//   dStack_push(period0);
//   _min();
// } 

// void periodMaxMin(void) {
//   dStack_push(0);
//   _max();
//   dStack_push(255);
//   _min();
// } 

void clock_(void) { // generic clock #4
  dStack_push(0);
  _max();
  dStack_push(7);
  _min();
  clock = dStack_pop();
}


void period1_(void) {
  // periodMaxMin();  // experiment suggests 0-255 as reasonable -- no need for special limits
  eightBitMaxMin();
  period1 = dStack_pop();
}


void period0_(void) {
  // periodMaxMin();
  eightBitMaxMin();
  period0 = dStack_pop();
}

// void tc4cc0_(void) {
//   tc4ccMaxMin();
//   tc4_cc0 = dStack_pop();
// }

void gendiv_(void) {
  eightBitMaxMin();
  gendiv = dStack_pop();
}

void setup_tc() {
/*
 32 KHz clock - test words

in forth:

decimal  ( an immediate word )

: fastblink  6 gendiv     4 per0   timers ;
: medblink   6 gendiv     9 per0   timers ;
: slowblink  6 gendiv    14 per0   timers ;
: vsloblink  6 gendiv    44 per0   timers ;
: usloblink  6 gendiv   122 per0   timers ;


*/

  /* [ http://forum.arduino.cc/index.php?topic=332275.17 ] */

  /* [ https://github.com/adafruit/Adafruit_SleepyDog/blob/master/utility/WatchdogSAMD.cpp ] */

  /** division register **/

  GCLK->GENDIV.reg  = GCLK_GENDIV_DIV(gendiv) |   // clock rate divisor
                      GCLK_GENDIV_ID(0x04); // clock = 0x04 - generic clock #4

  // alternate syntax:
  // REG_GCLK_GENDIV = GCLK_GENDIV_DIV(0xfd) |
  //                   GCLK_GENDIV_ID(4);

  while (GCLK->STATUS.bit.SYNCBUSY);

  GCLK->GENCTRL.reg = GCLK_GENCTRL_IDC |
                      GCLK_GENCTRL_GENEN |
                      GCLK_GENCTRL_SRC_XOSC32K |         // slow clock.
                      GCLK_GENCTRL_ID(0x04);             // clock = 0x04

                   /**  (GCLK_GENCTRL) FDPLL output */

                   // GCLK_GENCTRL_SRC_GCLKGEN1 |        // alt. slow clock.
                   // GCLK_GENCTRL_SRC_OSCULP32K |       // alt. slow clock.
                   // GCLK_GENCTRL_SRC_XOSC32K |         // slow clock.
                   // GCLK_GENCTRL_SRC_OSC8M |           // mild clock rate.
                   // GCLK_GENCTRL_SRC_DFLL48M |         // standard clock.

                   // assume three clock rates are available:
                   //     48 MHz (fast)
                   //      8 MHz (mild)
                   //     32 KHz (quite slow)

  while (GCLK->STATUS.bit.SYNCBUSY);

  // REG_GCLK_CLKCTRL  = GCLK_CLKCTRL_CLKEN |            // alternate syntax

  GCLK->CLKCTRL.reg    = GCLK_CLKCTRL_CLKEN |
                         GCLK_CLKCTRL_GEN_GCLK4 |
                         GCLK_CLKCTRL_ID_TC4_TC5;        // in pairs: 2&3; 4&5; 6&7.

  while (GCLK->STATUS.bit.SYNCBUSY);
 
  REG_TC4_CTRLA       |= TC_CTRLA_MODE_COUNT8;

  while (TC4->COUNT8.STATUS.bit.SYNCBUSY);

  REG_TC5_CTRLA       |= TC_CTRLA_MODE_COUNT8;

  while (TC5->COUNT8.STATUS.bit.SYNCBUSY);

  REG_TC4_COUNT8_CC0   = 0x00 ;

  while (TC4->COUNT8.STATUS.bit.SYNCBUSY);

  REG_TC5_COUNT8_CC0   = 0x00;

  while (TC5->COUNT8.STATUS.bit.SYNCBUSY);

  REG_TC4_COUNT8_PER   = period0;

  while (TC4->COUNT8.STATUS.bit.SYNCBUSY);

  REG_TC5_COUNT8_PER   = period1;

  while (TC5->COUNT8.STATUS.bit.SYNCBUSY);

  NVIC_SetPriority(TC4_IRQn, 0);
  NVIC_EnableIRQ(TC4_IRQn);

  NVIC_SetPriority(TC5_IRQn, 1);
  NVIC_EnableIRQ(TC5_IRQn);

  REG_TC4_INTFLAG     |= TC_INTFLAG_MC0 |
                         TC_INTFLAG_OVF;


  REG_TC5_INTFLAG     |= TC_INTFLAG_MC0 |
                         TC_INTFLAG_OVF;


  REG_TC4_INTENSET     = TC_INTENSET_MC0 |
                         TC_INTENSET_OVF;


  REG_TC5_INTENSET     = TC_INTENSET_MC0 |
                         TC_INTENSET_OVF;


  // 1024 256 64 16 8 4 2 1:
  // DIV1024  DIV256  DIV64  DIV16  DIV8  DIV4  DIV2  DIV1

  //  REG_TC4_CTRLA |= TC_CTRLA_PRESCALER_DIV1024 |
  //  REG_TC4_CTRLA |= TC_CTRLA_PRESCALER_DIV256  |
  //  REG_TC4_CTRLA |= TC_CTRLA_PRESCALER_DIV64   |
  //  REG_TC4_CTRLA |= TC_CTRLA_PRESCALER_DIV16   |
  //  REG_TC4_CTRLA |= TC_CTRLA_PRESCALER_DIV1    |
  //  REG_TC4_CTRLA |= TC_CTRLA_PRESCALER_DIV2    |
  //  REG_TC4_CTRLA |= TC_CTRLA_PRESCALER_DIV4    |
  //  REG_TC4_CTRLA |= TC_CTRLA_PRESCALER_DIV8    |

  REG_TC4_CTRLA       |= TC_CTRLA_PRESCALER_DIV64   |
                         TC_CTRLA_ENABLE;

  while (TC4->COUNT8.STATUS.bit.SYNCBUSY);


  REG_TC5_CTRLA       |= TC_CTRLA_PRESCALER_DIV64   |
                         TC_CTRLA_ENABLE;

  while (TC5->COUNT8.STATUS.bit.SYNCBUSY);

  // The timer will display on the onboard NeoPixel,
  //    to further visualize it, as a demonstration.

  // bugfix: remove the push to the data stack - not needed without NeoPixel vocabulary/events coded.
  // dStack_push(21); // need 21 bright for the selected, timer-controlled colors
  // 07 Jan 2018: NeoPixel payload .. maybe.  Depends on presence of NPX hardware (can be external to the target board, if provided for elsewhere).
  // _npxBright();    // pixels.setBrightness(dStack_pop());

  // candidate payload statement follows on the next line - 08 Jan 2018 20:44 UTC:
  // pinToggle(); // payload // led pin 13
}


void TC4_Handler() {     
  if (TC4->COUNT8.INTFLAG.bit.OVF && TC4->COUNT8.INTENSET.bit.OVF) {
    REG_TC4_INTFLAG = TC_INTFLAG_OVF;
  }

  if (TC4->COUNT8.INTFLAG.bit.MC0 && TC4->COUNT8.INTENSET.bit.MC0) {
    pinToggle(); // payload // led pin 13
    REG_TC4_INTFLAG = TC_INTFLAG_MC0;
  }
}


void TC5_Handler() {
  if (TC5->COUNT8.INTFLAG.bit.OVF && TC5->COUNT8.INTENSET.bit.OVF) {
    REG_TC5_INTFLAG = TC_INTFLAG_OVF;
  }

  if (TC5->COUNT8.INTFLAG.bit.MC0 && TC5->COUNT8.INTENSET.bit.MC0) {
    // 07 Jan 2018: payload (certain this one instance that is the case).
    // Anything useful could go here to tell the human 'something has happened'.
    // I chose to do something with a NeoPixel -- could be a wide variety of things, though.
    // colorTime(); // payload // neo pixel
    REG_TC5_INTFLAG = TC_INTFLAG_MC0;
  }
}

// end.

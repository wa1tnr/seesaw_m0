// Thu Jul  6 19:10:43 UTC 2017
// 0103-a0c-01-
// 4735-b0a-00-

#include <Arduino.h>
#include "../../yaffa.h"
#include "timers.h"
#include "../app/timer/timer.h"

const char timers_str[] = "timers"; // local idiom ainsuForth
void _timers(void) {
  setup_tc();
}


// gendiv period clock
const char gendiv_str[] = "gendiv"; // local idiom ainsuForth
void _gendiv(void) {
  gendiv_();
}


const char period1_str[] = "per1"; // local idiom ainsuForth
void _period1(void) {
  period1_();
}


const char period0_str[] = "per0"; // local idiom ainsuForth
void _period0(void) {
  period0_();
}

// const char tc4cc0_str[] = "cc0"; // local idiom ainsuForth
// void _tc4cc0(void) {
//   tc4cc0_();
// }

const char clock_str[] = "clock"; // local idiom ainsuForth
void _clock(void) {
  clock_();
}

// end.

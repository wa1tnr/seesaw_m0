// Mon Jan  8 22:01:58 UTC 2018
// 4737-a0c-00f- // +cribs +dump_cribs +freq

// Mon Jan  8 20:10:36 UTC 2018
// 4737-a0c-00c- // +cribs

// Thu Jun 22 20:49:39 UTC 2017
// 4735-a0p-04-

#include <Arduino.h>
#include "../../yaffa.h"
#include "../../Dictionary.h"
// #include "../../Error_Codes.h"

/*******************************************************************************/
/*******************************************************************************/
const char help_str[] = "help";
void _help(void) {
  Serial.println();
  Serial.print("    type 'words' instead of 'help'.  'cribs' for a crib sheet.\r\n");
}


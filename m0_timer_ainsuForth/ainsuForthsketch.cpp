// Thu Jul  6 19:10:43 UTC 2017
// 0103-a0c-01-
// 4735-b0a-00-

// PIBOK

// A4 - LCD backlight
// A5 - buzzPin (also an LED)

#include <Arduino.h>
#include "yaffa.h"
#include "ainsuForthsketch.h"
#include "src/periph/neo_pixel.h"
#include "src/dict/max_min.h" // departure to allow forth words 'max' and 'min'
#include "src/dict/cblink.h"
#include "src/app/timer/timer.h" // spaghetti coding
#include "Error_Codes.h"

/******************************************************************************/
/**  The Arduino M0 pro has 0x4000 as bootloader offset                      **/
/******************************************************************************/

/******************************************************************************/
/** Major and minor revision numbers                                         **/
/******************************************************************************/
#define YAFFA_MAJOR 0
#define YAFFA_MINOR 7
#define MAKESTR(a) #a
#define MAKEVER(a, b) MAKESTR(a*256+b)
asm(" .section .version\n"
    "yaffa_version: .word " MAKEVER(YAFFA_MAJOR, YAFFA_MINOR) "\n"
    " .section .text\n");

/******************************************************************************/
/** Common Strings & Terminal Constants                                      **/
/******************************************************************************/
const char prompt_str[] = "";                // const char prompt_str[] = ">> ";
const char compile_prompt_str[] = " compiled\r\n"; // ainsu: gforthism.
                                             // const char compile_prompt_str[] = "|  ";
const char ok_str[] = " ok"; //  = " OK";

// const char sp_str[]          = " ";
// const char tab_str[]         = "\t";
// const char hexidecimal_str[] = "$";
// const char octal_str[]       = "0";
// const char binary_str[]      = "%";
// const char zero_str[]        = "0";

/******************************************************************************/
/** Global Variables                                                         **/
/******************************************************************************/
// int scale = 1;
// int cscale = 1;
// int ctogl = -1 ;
// int buzzPin = 13 ; // A5
// uint8_t sound = 1; // 0 = off  1 = on

/******************************************************************************/
/**  Text Buffers and Associated Registers                                   **/
/******************************************************************************/
char* cpSource;                 // Pointer to the string location that we will
                                // evaluate. This could be the input buffer or
                                // some other location in memory
char* cpSourceEnd;              // Points to the end of the source string
char* cpToIn;                   // Points to a position in the source string
                                // that was the last character to be parsed
char cDelimiter = ' ';          // The parsers delimiter
char cInputBuffer[BUFFER_SIZE]; // Input Buffer that gets parsed
char cTokenBuffer[WORD_SIZE];   // Stores Single Parsed token to be acted on

/******************************************************************************/
/**  Stacks and Associated Registers                                         **/
/**                                                                          **/
/**  Control Flow Stack is virtual right now. But it may be but onto the     **/
/**  data stack. Error checking should be done to make sure the data stack   **/
/**  is not corrupted, i.e. the same number of items are on the stack as     **/
/**  at the end of the colon-sys as before it is started.                    **/
/******************************************************************************/
// stack_t dStack;
// stack_t rStack;
/******************************************************************************/
/**  Flash Dictionary Structure                                              **/
/******************************************************************************/
const flashEntry_t* pFlashEntry = flashDict;   // Pointer into the flash Dictionary

/******************************************************************************/
/**  User Dictionary is stored in name space.                                **/
/******************************************************************************/
userEntry_t* pLastUserEntry = NULL;
userEntry_t* pUserEntry = NULL;
userEntry_t* pNewUserEntry = NULL;

/******************************************************************************/
/**  Flags - Internal State and Word                                         **/
/******************************************************************************/
uint8_t flags;                 // Internal Flags
uint8_t wordFlags;             // Word flags

/******************************************************************************/
/** Error Handling                                                           **/
/******************************************************************************/
int8_t errorCode = 0; // ainsuForth: stays.

/******************************************************************************/
/**  Forth Space (Name, Code and Data Space) and Associated Registers        **/
/******************************************************************************/
char* pPNO;                  // Pictured Numeric Output Pointer
cell_t forthSpace[FORTH_SIZE]; // Reserve a block on RAM for the forth environment
cell_t* pHere;               // HERE, points to the next free position in
                             // Forth Space
cell_t* pOldHere;            // Used by "colon-sys"
cell_t* pCodeStart;          // used by "colon-sys" and RECURSE
cell_t* pDoes;               // Used by CREATE and DOES>

/******************************************************************************/
/** Forth Global Variables                                                   **/
/******************************************************************************/
uint8_t state; // Holds the text interpreters compile/interpreter state
cell_t* ip;    // Instruction Pointer
cell_t w;      // Working Register
uint8_t base;  // stores the number conversion radix

/******************************************************************************/


/*  specific to the timer-counter sketch  */
// extern void darkenBuzzPin(void); // { // turn off buzzPin
//  digitalWrite(buzzPin, 0); // turn off
// }

// extern void darkenlight(void); // {
//  digitalWrite(13, 0); // turn off
//  delay(2000);
// }

// extern void brightenBuzzPin(void); // { // turn on buzzPin
//  digitalWrite(buzzPin, 1); // turn on
// }

// extern void brightenlight(void); // {
//  digitalWrite(13, 1); // turn on
//  delay(220);
// }

extern void blinkenlight(void);

void introduction() {
//     blinkenlight(); Serial.print(".");
}

// extern void setup_tc_locally_two(); // { }

// extern void led13Off(void); // {
//   digitalWrite(13, 0); // turn off
// }

// extern void led13On(void); // {
//   digitalWrite(13, 1); // turn on
// }

// 1: scale  1, then 2, then -1: darken.
// 2: scale -1, then 0:          brighten.
// 3: scale  0, then 1, then -1: darken.
// 4: scale -1, then 0:          brighten.

// extern void coolBlueLight(void); // {
//     dStack_push(0); // red
//     dStack_push(12); // green
//     dStack_push(30); // blue
// 0 1 5
//     _rgb();
// }

// extern void greenLight(void); // {
//     dStack_push(0); // red
//     dStack_push(12); // green
//     dStack_push(0); // blue
//     _rgb();
// }

// extern void magLight(void); // {
//    dStack_push(12); // red
//    dStack_push(0); // green
//    dStack_push(12); // blue
//    _rgb();
// }

// extern void colorToggle(void); // {
//  ctogl = ctogl + 1 ;

//  if (ctogl == 0) {
//    greenLight();
//  }

//  if (ctogl == 1) {
//    magLight();
//  }
//  if (ctogl == 2) {
//    coolBlueLight();
//    ctogl = -1 ;
//  }
// }



// extern void pinToggle(void); // { }
//   scale = scale + 1 ;

//   if (scale > 0) {
//     scale = -1 ;    // reset
//     darkenBuzzPin();   // turn off buzzPin
//   } else {
//     brightenBuzzPin(); // turn on buzzPin
//   }
// }


// extern void colorTime(void); // {
  // different rate
//   cscale = cscale + 1; // color
//   if (cscale > 7) {
//     cscale = -1 ;
//     colorToggle();
//   }
// }

// void TC4_Handler()             // Interrupt Service Routine (ISR) for timer TC4
// {     
//   if (TC4->COUNT8.INTFLAG.bit.OVF && TC4->COUNT8.INTENSET.bit.OVF)             
//   {
//     REG_TC4_INTFLAG = TC_INTFLAG_OVF;      // Clear the OVF interrupt flag
//   }

//   if (TC4->COUNT8.INTFLAG.bit.MC0 && TC4->COUNT8.INTENSET.bit.MC0)             
//   {
//    pinToggle();
//    colorTime();
//    REG_TC4_INTFLAG = TC_INTFLAG_MC0;      // Clear the MC0 interrupt flag
//   }

//   if (TC4->COUNT8.INTFLAG.bit.MC1 && TC4->COUNT8.INTENSET.bit.MC1)           
//   {
//    REG_TC4_INTFLAG = TC_INTFLAG_MC1;      // Clear the MC1 interrupt flag
//   }
// }




void blink_m(void) {
#ifdef HAS_NEO_PIXEL_LIB
  delay(1200);
  _mblink(); // magenta 100 ms blip on neoPixel
  delay(1100);
#endif
  delay(100);
 // 2500 ms is 24 pulses per minute
}

// extern void brightMaxMin(void); // { // ( bright -- adj_bright )
//   dStack_push(2);
//   _max();
//   dStack_push(64);
//   _min();
// }

/******************************************************************************/
/** Initialization                                                           **/
/******************************************************************************/
void setup(void) {                
  uint16_t mem;
#ifdef HAS_NEO_PIXEL_LIB
  setup_neoPixel();
#endif

  setup_buzzPin(); // must relocate this or qualify it somehow

  // magentaDull();
  Serial.begin(19200);        // Open serial communications:
  // Serial.begin(57600);     // Open serial communications:
  // Serial.begin(115200);    // Open serial communications:
  while (!Serial) {
    blink_m();
  }

  delay(3 * 100); // 300 ms

//   dStack_push(13); // brightness minimal: 13 decimal
//   brightMaxMin();
//   _npxBright();    // pixels.setBrightness(dStack_pop());

  _cblink();

  delay(3 * 100); // 300 ms

  flags = ECHO_ON;
  base = DECIMAL;

  pHere = &forthSpace[0];
  pOldHere = pHere;
  
  Serial.print("\n warm boot message - early bird.  //  KEPOK  PIBOK--HABILLEAUX"); // instant confirmation

  delay(9 * 100); // 900 ms - optional - useful when coded for a 4+ second delay
                  // to give the operator time to task switch from upload
                  // to first signon.
  signOn();
  Serial.print(prompt_str);
}



/**                                                 **/
/** void compilePrompt(void);                       **/
/**                                                 **/
/** loop helper function                            **/
/**    -- when to print the compiler prompt         **/
/**       and what form it should take, depending   **/
/**       on how free the serial buffer is, to      **/
/**       print non-critical status info to the     **/
/**       terminal.                                 **/
/**                                                 **/

void compilePrompt(void) {
    int waiting = 0;
    waiting = Serial.available();
    if (waiting < 3) { // light traffic - there is slack enough to allow verbose output
	Serial.print(compile_prompt_str);
    } else {
        if (waiting < 20) { // moderate traffic
	    Serial.print("ul \r\n"); // let user know that player-piano code upload speeds were noticed
        } else {
          if (waiting < 50) { // heavy traffic -- just the line endings are echo'd back to the user
            Serial.print("\r\n");
          } // else: inbound is just too fast -- print nothing extra
        } 
    }
}

/******************************************************************************/
/** Outer interpreter                                                        **/
/******************************************************************************/
void loop(void) {
  cpSource = cpToIn = cInputBuffer;
  cpSourceEnd = cpSource + getLine(cpSource, BUFFER_SIZE);
  if (cpSourceEnd > cpSource) {
      interpreter();
    if (errorCode) {
        errorCode = 0;
    } else {
      if (!state) {
        Serial.print(ok_str);
        // This shows a DOT for each item on the data stack
        char i = dStack_size();
        while(i--) {
            Serial.print(".");
        }
        Serial.println();
      }
    }


  } else { // test failed; do not run interpreter().
    Serial.println(ok_str); // Leo Brodie 'Starting Forth' expects an ok here
  } // replace these four lines with a single closing curly brace
    // to restore YAFFA behavior.


  if (state) {
      compilePrompt();
  } else {
      Serial.print(prompt_str);
  }
}


/******************************************************************************/
/** freeMem returns the amount of free forth space left.                     **/
/******************************************************************************/
static unsigned int freeMem(void) {
//   return (pHere - forthSpace);
}

/******************************************************************************/
/**  YAFFA - Yet Another Forth for Arduino                                   **/
/**  Version 0.7.0                                                           **/
/**                                                                          **/
/**  File: YAFFA.ino                                                         **/
/**  Copyright (C) 2012 Stuart Wood (swood@rochester.rr.com)                 **/
/**                                                                          **/
/**  This file is part of YAFFA.                                             **/
/**                                                                          **/
/**  YAFFA is free software: you can redistribute it and/or modify           **/
/**  it under the terms of the GNU General Public License as published by    **/
/**  the Free Software Foundation, either version 2 of the License, or       **/
/**  (at your option) any later version.                                     **/
/**                                                                          **/
/**  YAFFA is distributed in the hope that it will be useful,                **/
/**  but WITHOUT ANY WARRANTY; without even the implied warranty of          **/
/**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           **/
/**  GNU General Public License for more details.                            **/
/**                                                                          **/
/**  You should have received a copy of the GNU General Public License       **/
/**  along with YAFFA.  If not, see <http://www.gnu.org/licenses/>.          **/
/**                                                                          **/
/******************************************************************************/
/**                                                                          **/
/**  DESCRIPTION:                                                            **/
/**                                                                          **/
/**  YAFFA is an attempt to make a Forth environment for the Arduino that    **/
/**  is as close as possible to the ANSI Forth draft specification DPANS94.  **/
/**                                                                          **/
/**  The goal is to support at a minimum the ANS Forth C core word set and   **/
/**  to implement wrappers for the basic I/O functions found in the Arduino  **/
/**  library.                                                                **/
/**                                                                          **/
/**  YAFFA uses two dictionaries, one for built in words and is stored in    **/
/**  flash memory, and the other for user defined words, that is found in    **/
/**  RAM.                                                                    **/
/**                                                                          **/
/******************************************************************************/

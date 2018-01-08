// Thu Jul  6 19:10:43 UTC 2017
// 0103-a0c-01-
// 4735-b0a-00-

/**  YAFFA - Yet Another Forth for Arduino                                   **/
// scroll to end of file for intellectual property notices - wa1tnr

// 28 June 2017: testing now on Adafruit Feather M0 Express.
//               Somewhat easily adapted to use with Arduino M0 Pro.

#ifndef __YAFFA_H__
#define __YAFFA_H__



// -------  use this to switch between them   ---------

// 07 Jan 2018: this should solve hardware issue by omitting NeoPixel support specific to 
// Feather M0 Express (and maybe other Adafruit NeoPixel-equipped M0 boards):
#define NEO_PIXEL_LIB_ENABLED // swap these two
#undef NEO_PIXEL_LIB_ENABLED  // swap these two

// -------  use this to switch between them   ---------



#ifdef NEO_PIXEL_LIB_ENABLED
  #ifndef HAS_NEO_PIXEL_LIB
    #define HAS_NEO_PIXEL_LIB
  #endif
#endif

#ifndef NEO_PIXEL_LIB_ENABLED
  #ifdef HAS_NEO_PIXEL_LIB
    #undef HAS_NEO_PIXEL_LIB
  #endif
#endif

#define EXT_KERN_ALLOT
#define EXT_KERN_CONSTANT
#define EXT_KERN_XTTONAME
// #define INT_KERN_XTTONAME
#define EXT_KERN_STRINGS
#define EXT_KERN_SIGN_ON
#define EXT_KERN_ENTRY
#define EXT_KERN_EXEC_WORD
#define EXT_KERN_GETKEY
#define EXT_KERN_GETLINE
#define EXT_KERN_IS_WORD_NUMBER
#define EXT_KERN_GETTOKEN
#define EXT_KERN_STACKS
#define EXT_KERN_INTERPRETER
#define EXT_KERN_DROP
#define EXT_KERN_EQ
#define EXT_KERN_EVALUATE
#define EXT_KERN_EXIT
#define EXT_KERN_OVER
#define EXT_KERN_S_QUOTE
#define EXT_KERN_VARIABLE
#define EXT_KERN_THROW
#define EXT_KERN_JUMP
#define EXT_KERN_LEAVE_SYS
#define EXT_KERN_LITERAL
#define EXT_KERN_LOOP_SYS
#define EXT_KERN_PLUS_LOOP_SYS
#define EXT_KERN_QUIT
#define EXT_KERN_SUBROUTINE
#define EXT_KERN_ZJUMP

// -----------------------------------------------------------------------
// 
// either/or:
// 
// do not define both the INT_ and the EXT_ version of each #define below.
// 
// because, that would be bad.
// 
// -----------------------------------------------------------------------

// choose one, not both, of the following two lines:
#define EXT_KERN_TYPE
// #define INT_KERN_TYPE

// choose one, not both, of the following two lines:
#define EXT_KERN_DO_SYS
// #define INT_KERN_DO_SYS

// They mean, roughly, 'use the external code for the definition of type()
// and of do_sys()' .. or, alternately, use the internal ('orginal') code
// for those functions.  That's what the EXT_ and INT_ prefixes specify --
// external or internal versions of the same code.

// One aim of this project is to externalize much of the code, to a separate
// source file, per function.

// You got this.   10 June 2017  de  wa1tnr

#define EXT_KERN_DOT_QUOTE
// #define INT_KERN_DOT_QUOTE



/******************************************************************************/
/** Memory Alignment Macros                                                  **/
/******************************************************************************/
#define ALIGN_P(x)  x = (cell_t*)(((size_t)x + 3) & -4)
#define ALIGN(x)  x = (cell_t)(((size_t)x + 3) & -4)

#define T_SIZE(x) pow( 256, sizeof( x ) ) - 1
#define MAX_OF(type) \
        (((type)(~0LU) > (type)((1LU<<((sizeof(type)<<3)-1)) -1LU)) ? \
        (long unsigned int)(type)(~0LU) : \
        (long unsigned int)(type)((1LU<<((sizeof(type)<<3)-1))-1LU))
#define MIN_OF(type) \
        (((type)(1LU<<((sizeof(type)<<3)-1)) < (type)1) ? \
        (long int)((~0LU)-((1LU<<((sizeof(type)<<3)-1))-1LU)) : \
        0L)

/******************************************************************************/
/** Memory Types                                                             **/
/******************************************************************************/
typedef int32_t cell_t;
typedef uint32_t ucell_t;
typedef int64_t dcell_t;
typedef uint64_t udcell_t;

/******************************************************************************/
/**  Environmental Constants and Name Strings                                **/
/******************************************************************************/
#define CORE          TRUE      // Complete Core Word Set
#define CORE_EXT      FALSE     // Complete Extended Core Word Set
#define FLOORED       TRUE      // Floored Division is default
#define MAX_CHAR      0x7E      // Max. value of any character


/******************************************************************************/
/** CPU / Board Specific                                                           **/
/**   STRING_SIZE - Maximum length of a counted string, in characters        **/
/**   HOLD_SIZE   - Size of the pictured numeric output string buffer, in    **/
/**                 characters                                               **/
/**   PAD_SIZE    - Size of the scratch area pointed to by PAD, in characters**/
/**   RSTACK_SIZE - Size of the return stack, in cells                       **/
/**   STACK_SIZE  - Size of the data stack, in cells                         **/
/**   BUFFER_SIZE - Size of the input text buffer, in characters. The min.   **/
/**                 size for an ANS Forth is 80.                             **/
/**   TOKEN_SIZE  - Size of the token (Word) buffer. Max. length of a        **/
/**                 Definitions names shall is TOKEN_SIZE - 1 characters.    **/
/**   FORTH_SIZE  - Size of Forth Space in bytes                             **/
/******************************************************************************/


/* chosen method to compile for specific hardware */

//   see: /home/user/.arduino15/packages/adafruit/hardware/samd/1.0.17/boards.txt:

//   example:
//          adafruit_feather_m0.build.extra_flags=-DARDUINO_SAMD_ZERO -D__SAMD21G18A__ {build.usb_flags}

//            definitve?


// see: /home/user/.arduino15/packages/adafruit/hardware/samd/1.0.17/boards.txt:

// boards.txt:adafruit_feather_m0.build.extra_flags=-DARDUINO_SAMD_ZERO -D__SAMD21G18A__ {build.usb_flags}
// boards.txt:adafruit_feather_m0_express.build.extra_flags=-DARDUINO_SAMD_ZERO -DARDUINO_SAMD_FEATHER_M0 -DADAFRUIT_FEATHER_M0_EXPRESS -D__SAMD21G18A__ {build.usb_flags}
// boards.txt:adafruit_metro_m0.build.extra_flags=-D__SAMD21G18A__  -DARDUINO_SAMD_ZERO -DADAFRUIT_METRO_M0_EXPRESS {build.usb_flags}
// boards.txt:adafruit_circuitplayground_m0.build.extra_flags=-DCRYSTALLESS -DARDUINO_SAMD_ZERO -D__SAMD21G18A__ -DADAFRUIT_CIRCUITPLAYGROUND_M0 {build.usb_flags}

// boards.txt:adafruit_feather_m0.build.extra_flags=
//     -DARDUINO_SAMD_ZERO
//     -D__SAMD21G18A__ {build.usb_flags}

// boards.txt:adafruit_feather_m0_express.build.extra_flags=
//     -DARDUINO_SAMD_ZERO
//     -DARDUINO_SAMD_FEATHER_M0
//     -DADAFRUIT_FEATHER_M0_EXPRESS
//     -D__SAMD21G18A__ {build.usb_flags}

// boards.txt:adafruit_metro_m0.build.extra_flags=
//     -D__SAMD21G18A__
//     -DARDUINO_SAMD_ZERO
//     -DADAFRUIT_METRO_M0_EXPRESS {build.usb_flags}

// boards.txt:adafruit_circuitplayground_m0.build.extra_flags=
//     -DCRYSTALLESS
//     -DARDUINO_SAMD_ZERO
//     -D__SAMD21G18A__
//     -DADAFRUIT_CIRCUITPLAYGROUND_M0 {build.usb_flags}

// see: /home/user/.arduino15/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/samd.h

// --- snip ---
// #elif defined (__SAMD21G17A__)
// #include "samd21/include/samd21.h"
// #elif defined (__SAMD21G17AU__)
// #include "samd21/include/samd21.h"

// #elif defined (__SAMD21G18A__)
// #include "samd21/include/samd21.h"

// #elif defined (__SAMD21G18AU__)
// #include "samd21/include/samd21.h"
// --- snip ---

// assume this works for Feather M0 Express, Metro M0 Express, and Arduino M0 Pro:

// #ifndef _SAMD21G18A_
// #define _SAMD21G18A_
// #endif




// ---------------- neopixel pin assignment - Feather M0 Express ----------------
// using    -DADAFRUIT_FEATHER_M0_EXPRESS
// #if defined(ADAFRUIT_FEATHER_M0_EXPRESS) // just what it says, heh
  // #define HAS_NEO_PIXEL_PIN_8 // the onboard NeoPixel is connected to Pin 8
// #endif

// override for quick compile - any SAMD21G18A board except Feather M0 Express, which is already configured:

// uncomment three lines to override: --- 07 January 2018 -- this solves
// the compile problem.

// introduces another: if you are not on a NeoPixel board (Feather M0
// Express, others) it breaks things.  Hmm.

// #ifndef HAS_NEO_PIXEL_PIN_8
//  #define HAS_NEO_PIXEL_PIN_8
// #endif
#ifndef HAS_NEO_PIXEL_PIN_8
  #define HAS_NEO_PIXEL_PIN_8
#endif
// ----------- end, neopixel pin assignment - Feather M0 Express ----------------





#if defined(__SAMD21G18A__) // Arduino Zero
  static const unsigned long SRAM_SIZE = 32;
  #define PROC_STR "SAMD21G18A"
//  #define STRING_SIZE   31
  #define HOLD_SIZE     64
  #define PAD_SIZE      128
  #define RSTACK_SIZE   32
  #define STACK_SIZE    32
  #define BUFFER_SIZE   255
  #define WORD_SIZE     32
  
#elif defined(__AVR_ATSAM3X8E__) // Due
#elif defined(_AVR_AR9331__) // Yun 400Mhz
#else
#endif

static const unsigned long FORTH_SIZE    ((SRAM_SIZE*1024*2)/(sizeof(cell_t)*3));
  


/*******************************************************************************/
/**                       Enable Dictionary Word Sets                         **/
/*******************************************************************************/
#define CORE_EXT_SET
#define DOUBLE_SET
#define EXCEPTION_SET
#define LOCALS_SET
#define MEMORY_SET
#define FACILITY_SET
#define TOOLS_SET
#define SEARCH_SET
#define STRING_SET
#define EN_ARDUINO_OPS

/******************************************************************************/
/**  Numbering system                                                        **/
/******************************************************************************/
#define DECIMAL 10
#define HEXIDECIMAL 16
#define OCTAL 8
#define BINARY 2

/******************************************************************************/
/**  ASCII Constants                                                         **/
/******************************************************************************/
#define ASCII_BS    8
#define ASCII_TAB   9
#define ASCII_NL    10
#define ASCII_ESC   27
#define ASCII_CR    13
#define ASCII_DEL   127 // 0x7f

/******************************************************************************/
/**  Forth True and False                                                    **/
/******************************************************************************/
#define TRUE        -1      // All Bits set to 1
#define FALSE       0       // All Bits set to 0

/******************************************************************************/
/**  Flags - Internal State                                                  **/
/******************************************************************************/
#define ECHO_ON        0x01    // Echo characters typed on the serial input
#define NUM_PROC       0x02    // Pictured Numeric Process
#define EXECUTE        0x04

/******************************************************************************/
/**  wordFlags - Flags used to define word properties                        **/
/******************************************************************************/
// 
#define NORMAL         0x00
#define SMUDGE         0x20    // Word is hidden during searches
#define COMP_ONLY      0x40    // Word is only usable during compilation
#define IMMEDIATE      0x80    // Word is executed during compilation state
#define LENGTH_MASK    0x1F    // Mask for the length of the string

/******************************************************************************/
/**  Control Flow Stack Data Types                                           **/
/******************************************************************************/
#define COLON_SYS    -1
#define DO_SYS       -2
#define CASE_SYS     -3
#define OF_SYS       -4
#define LOOP_SYS     -5
#define LEAVE_SYS    -6

/******************************************************************************/
/**  User Dictionary Header                                                  **/
/******************************************************************************/
typedef struct  {            // structure of the user dictionary
  void*        prevEntry;    // Pointer to the previous entry
  cell_t*      cfa;          // Code Field Address
  uint8_t      flags;        // Holds the length of the following name 
                             // and any flags.
  char         name[];       // Variable length name
} userEntry_t;

/******************************************************************************/
/**  Flash Dictionary Structure                                              **/
/******************************************************************************/
typedef void (*func)(void);         // signature of functions in dictionary

typedef struct  {                   // Structure of the dictionary
  const char*    name;              // Pointer the Word Name in flash
  const func     function;          // Pointer to function
  const uint8_t  flags;             // Holds word type flags
} flashEntry_t;

extern const flashEntry_t flashDict[];        // forward reference

/******************************************************************************/
/**  Stack Structure.                                                        **/
/******************************************************************************/
typedef struct {
  uint8_t       top;                      // The data stack index
  cell_t        d[STACK_SIZE];            // The data stack
  const uint8_t size = STACK_SIZE;
} stack_t;

/******************************************************************************/
/**  Flash Dictionary Index References                                       **/
/**  This words referenced here must match the order in the beginning of the **/
/**  dictionary flashDict[]                                                  **/
/******************************************************************************/
#define EXIT_IDX           1
#define LITERAL_IDX        2
#define TYPE_IDX           3
#define JUMP_IDX           4
#define ZJUMP_IDX          5
#define SUBROUTINE_IDX     6
#define THROW_IDX          7
#define DO_SYS_IDX         8
#define LOOP_SYS_IDX       9
#define LEAVE_SYS_IDX      10
#define PLUS_LOOP_SYS_IDX  11
#define EXECUTE_IDX        12
#define S_QUOTE_IDX        13
#define DOT_QUOTE_IDX      14
#define VARIABLE_IDX       15
#define OVER_IDX           16
#define EQUAL_IDX          17
#define DROP_IDX           18

#endif


/******************************************************************************/
/**  YAFFA - Yet Another Forth for Arduino                                   **/
/**                                                                          **/
/**  File: YAFFA.h                                                           **/
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
/** Processor Specific Definitions                                           **/
/**                                                                          **/
/** ARDUINO_ARCH_SAMD                                                        **/
/**    __ARDUINO_SAMD_ZERO__ - Supported                                     **/
/**                                                                          **/
/** ARDUINO_ARCH_ESP8266 - In work                                           **/
/**    __ARDUINO_ESP8266_ESP01                                               **/
/**    __ARDUINO_ESP8266_ESP12                                               **/
/**    __ARDUINO_MOD_WIFI_ESP8266                                            **/
/**                                                                          **/
/** Board                   Architecture  Flash        SRAM        EEPROM    **/
/** ------                  ------------- ------       ------      -------   **/
/** Zero                    SAMD          256K         32K         -         **/
/** NodeMCU Amica Module    ESP8266                                          **/
/**                                                                          **/
/******************************************************************************/


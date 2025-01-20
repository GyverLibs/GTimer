This is an automatic translation, may be incorrect in some places. See sources and examples!

# Gtimer
Light and universal software timer
- works with `Millis`,` Micros` and any other pharmacy functions of the `Unsigned Long uptime ()` `` `` `
- 3 operating modes: interval timer, timeout, overflow
- 3 memory options: 8, 16 and 32 bits periods
- the possibility of suspension and continuation of the account
- two options for the phase of intervals
- easy implementation - two variables for a timer + 1 byte of settings
- Collback and virtual function for inheritance

## compatibility
All platforms

## Content
- [use] (#usage)
- [versions] (#varsions)
- [installation] (# Install)
- [bugs and feedback] (#fedback)

<a id = "USAGE"> </A>

## Usage
> [! Note]
> The timer correctly passes through the "overwhelming" of pharmacy function (Millis, Micros)

### operating mode
- `gtmode :: Interval` - the timer is restarted after the operation
- `gtmode :: timeout` - the timer stops after the trigger
- `gtmode :: overflow` - the timer works after the trigger

! [Mode] (doc/mode.png)

### phase mode
In the `Keepphase` mode, the interval is multiple of the period even with delays in the program:

! [Mode] (doc/phase.png)

## H initialization
The library contains 6 timer options:
- `gtimer` - 32 bits periods (up to 4 294 967 295)
- `gtimer16` - 16 bits periods (up to 65 535)
- `gtimer8` - 8 bit periods (up to 255)
- `gtimercb`,` gtimercb16`, `gtimercb8` - the same

`` `CPP
Gtimerx <uptime> (Uint32_t Time, Bool Start = FALSE, GTMODE MODE = GTMODE :: Interval, Bool Keepphase = False);
`` `

- `uptime` - Aptima function (` Millis`, `Micros`, its own function of the` Unsigned Long uptime (VOID) `)
- `time` - time in timer units
- `Start` - start right away
- `mode` - mode of operation
- `KEEPPHASE - interval phase mode

### description of classes
### gtimerx

`` `CPP
// Keep the phase in Interval mode.
VOID KEEPPHASE (BOOL KEEP);

// Keep the phase on Interval mode
bool getphase ();

// set time in timer units
VOID settime (uint32_t time);

// set time (for MS)
VOID settime (uint32_t ms, uint32_t sec, uint16_t min = 0, uint16_t hur = 0, uint16_t day = 0);

// Get time in timer units
T gettime ();

// Set the mode: gtmode :: interval, gtmode :: timeout, gtmode :: overflow
VOID setmode (gtmode mode);

// Get mode: gtmode :: interval, gtmode :: Timeout, gtmode :: overflow
Gtmode getmode ();

// Launch with time (for MS)
VOID Start (Uint32_t MS, Uint32_T Sec, Uint16_t Min = 0, Uint16_t Hour = 0, Uint16_T Day = 0);

// Launch with time and regime
Void Start (Uint32_T Time, Gtmode Mode);

// Launch with time
VOID Start (Uint32_T Time);

// Run/restart
VOID Start ();

// suspend
VOID PAUSE ();

// Continue
VOID Resume ();

// Stop
VOID Stop ();

// Call the operation
VOID form ();

// Timer launched
Bool Running ();

// There is time left in the timer units
T getleft ();

// There is time left at 8 bits (0 .. 255)
uint8_t getleft8 ();

// there is a 16 bit time (0 .. 65 535)
uint16_t getleft16 ();

// ticker, call in LOOP.Will return True when triggeredAI
Bool Tick ();

// Call Tick
Operator Bool ();
`` `

### gtimercbx

`` `CPP
// Connect the timer processor
Void Attach (Timercallback CB);

// Disable the timer handler
VOID Detach ();

// Launch in the time of the timeout
VOID Starttimeout (Uint32_T Time, Timercallback CB);

// Launch in interval mode
VOID Startinterval (Uint32_T Time, Timercallback CB);

// Launch in the overflow mode
VOID Startoverflow (Uint32_T Time, Timercallback CB);

// is called when triggered
Virtual Void OnReady ();
`` `

- `Timercallback` - the function of the species` void f () `
- `void* thisgtimer` - a pointer for the current timer inside the handle

### Examples
#### Ordinary
`` `CPP
#include <arduino.h>
#include <gtimer.h>

Gtimer <millis> tmr1;

VOID setup () {
Serial.Begin (115200);

TMR1.Setmode (gtmode :: Timeout);
TMR1.Settime (2000);
tmr1.start ();
}

VOID loop () {
if (TMR1) serial.println ("Timeout");

static gtimer <millis> tmr2 (500, True);
IF (TMR2) serial.println ("Interval");
}
`` `

#### Processor
`` `CPP
#include <arduino.h>
#include <gtimer.h>

Gtimercb <millis> tmr1, TMR2;

VOID Ontimer () {
Serial.println ("Ready 2");
}

VOID setup () {
Serial.Begin (115200);

// Lambda
tmr1.startinTerval (500, [] () {
Serial.println ("Ready 1");

// appeal to the current timer
// static_cast <gtimercb <millis>*> (thisgtimer)-> stop ();
});

// External
TMR2.STARTINTERVAL (1000, Ontimer);
}

VOID loop () {
TMR1.Tick ();
TMR2.Tick ();
}
`` `

### virtual
`` `CPP
#include <arduino.h>
#include <gtimer.h>

Class testtimer: public gtimercb <millis> {
Public:
using gtimercb <millis> :: gtimercb;

VOID online () {
Serial.println ("Ready");
}
};

TestTimer TMR (500, True);

VOID setup () {
Serial.Begin (115200);
}

VOID loop () {
TMR.Tick ();
}
`` `

<a ID = "Versions"> </a>

## versions
- V1.0

<a id = "Install"> </a>
## Installation
- The library can be found by the name ** gtimer ** and installed through the library manager in:
- Arduino ide
- Arduino ide v2
- Platformio
- [download the library] (https://github.com/gyverlibs/gtimer/archive/refs/heads/main.zip). Zip archive for manual installation:
- unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
- unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
- unpack and put in *documents/arduino/libraries/ *
- (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!

<a id = "Feedback"> </a>

## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!

When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code
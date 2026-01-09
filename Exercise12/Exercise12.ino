
/**
 * @mainpage Reaction Game (5 LEDs + Button)
 *
 * @section intro Overview
 * This project implements a simple **reaction game** using five LEDs and a single push button.
 * The LEDs step from left to right; the player must press the button **exactly when the middle LED is lit**
 * to score a hit. Wrong timing counts as a miss. The speed increases with each hit, and after
 * 10 hits you get a celebratory animation.
 *
 * @section rules Game rules
 * - LEDs (pins 8–12) light up one at a time in a loop.
 * - Press the button (pin 2) **while LED3 (pin 10) is ON** → **Hit**.
 * - Press at any other time → **Miss**.
 * - Each hit speeds up the sequence by 100 ms (down to a minimum of 100 ms).
 * - At 10 hits, a **You Win** animation plays and the game resets, except for the speed.
 *
 * @section hardware Hardware & wiring
 * - 5x LEDs with resistors → digital pins: 8, 9, 10, 11, 12.
 * - 1x push button with resistor → digital pin 2, using `INPUT_PULLUP` (pressed = HIGH).
 * - Jumperwires 
 * - AVR global interrupts are enabled (`sei()`), and `INT0` (pin 2) triggers on FALLING edges.
 *
 * @section files Files & structure
 * - Single Arduino sketch: `Exercise12.ino`
 * - Uses AVR headers for interrupts.
 *
 * @see setup()
 * @see loop()
 * @see myISR()
 * @see hitBlink()
 * @see missBlink()
 * @see youWin()
 */

/**
 * @file Exercise12.ino
 * @brief Reaction game using an external interrupt to detect button presses.
 *
 * @author Frederikke Biehe
 * @date 2026-01-09
 *
 * The sketch drives a 5‑LED sequence and registers button presses via INT0.
 * The ISR sets flags for the main loop to handle hit/miss animations without
 * doing heavy work inside the interrupt context.
 */


#include <avr/interrupt.h>  ///< AVR intrinsics for `sei()`


/** @name Pin assignments
 *  @brief Digital pins for LEDs and button.
 *  @{
 */
#define LED1 8
#define LED2 9
#define LED3 10
#define LED4 11
#define LED5 12
#define BUTTONPIN 2


/** @} */

/** @brief Index of the currently active LED (0..4).
 *  @details Volatile because read in ISR and updated in the main loop.
 *  @see myISR()
 */

volatile byte ledNo = 0;


/** @brief Millis timestamp of the last accepted interrupt (for debouncing).
 *  @details Volatile since accessed in both ISR and main loop.
 *  @see myISR()
 */
volatile unsigned long lastInterruptTime = 0;


/** @brief Flag set by ISR to request a "hit" blink in the main loop.
 *  @see myISR()
 *  @see hitBlink()
 */
volatile bool doHitBlink = false;

/** @brief Flag set by ISR to request a "miss" blink in the main loop.
 *  @see myISR()
 *  @see missBlink()
 */
volatile bool doMissBlink = false;

/** @brief Number of successful hits since last reset. */
int hits = 0;
/** @brief Number of misses since last reset. */
int misses = 0; 
/** @brief Step counter used to derive `ledNo`. */
int counter = 0;
** @brief Delay (ms) between LED steps; decreases with hits, min 100 ms. */
int pause = 1000;


/**
 * @brief Arduino initialization.
 *
 * Initializes serial output, configures I/O pins, attaches `INT0` to the
 * button on pin 2 (falling edge), and enables global interrupts.
 *
 * @see myISR()
 * @see loop()
 */
void setup() {
  Serial.begin(9600);
  randomSeed(1);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  pinMode(BUTTONPIN, INPUT_PULLUP);   // Button reads LOW
  attachInterrupt(0, myISR, FALLING); // INT0 on falling edge
  sei();                              // Enable global interrupts (AVR)
}


/**
 * @brief Main gameplay loop.
 *
 * Priority order:
 * 1. If a **hit** was requested by the ISR → play @ref hitBlink and count a hit.
 * 2. Else if a **miss** was requested → play @ref missBlink and count a miss.
 * 3. Else advance the LED sequence and apply timing rules.
 *
 * When @p hits reaches 10 → run @ref youWin and reset counters.
 *
 * @see myISR()
 * @see hitBlink()
 * @see missBlink()
 * @see youWin()
 */

void loop() {
    // Handle any pending blink requests first, so the normal loop does not overwrite them.
  if (doHitBlink) {
    doHitBlink = false; // clear flag
    hitBlink();
    hits++;
    Serial.print("Hits: ");   Serial.println(hits);
    Serial.print("Misses: "); Serial.println(misses);
    Serial.println("------");

    // Speed up the sequence but keep a safe minimu
    pause = max(100, pause - 100);
  }
  else if (doMissBlink) {
    doMissBlink = false; // clear flag
    missBlink();
    misses++;
  }
  else {
    // Normal LED stepping only when no blink is active
    ledNo = counter % 5;
    counter++;

    // Turn all LEDs off
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);

    // Turn the current LED on
    switch (ledNo) {
      case 0: digitalWrite(LED1, HIGH); break;
      case 1: digitalWrite(LED2, HIGH); break;
      case 2: digitalWrite(LED3, HIGH); break;
      case 3: digitalWrite(LED4, HIGH); break;
      case 4: digitalWrite(LED5, HIGH); break;
    }
    delay(pause);

    // Once 8 hits is reached, the LEDs light in random order
    if (hits == 8) {
      // random LED on briefly
      byte r = random(0, 5);
      digitalWrite(LED1, r == 0 ? HIGH : LOW);
      digitalWrite(LED2, r == 1 ? HIGH : LOW);
      digitalWrite(LED3, r == 2 ? HIGH : LOW);
      digitalWrite(LED4, r == 3 ? HIGH : LOW);
      digitalWrite(LED5, r == 4 ? HIGH : LOW);
      delay(pause);
    }

    // Win condition
    if (hits == 10) {
      youWin();
      hits = 0;
      misses = 0;
      counter = 0;
    }
  }
}

/**
 * @brief External interrupt service routine for button (INT0 on pin 2).
 *
 * Implements a simple 200 ms debounce. Uses the current `ledNo` to decide
 * whether the press was a **hit** (only when `ledNo == 2`, meaning LED3 is lit)
 * or a **miss**. Sets one of the flags for the main loop to process.
 *
 * @note Keep ISRs short: no delays or heavy work here.
 * @see loop()
 * @see hitBlink()
 * @see missBlink()
 */
void myISR() {
  unsigned long now = millis(); // reading is OK; avoid waiting on it
  if (now - lastInterruptTime > 200) { // 200 ms debounce
    if (ledNo == 2) {doHitBlink = true;}
    else {doMissBlink = true;}
    lastInterruptTime = now;
  }
}


/** @brief Blink animation for a successful hit.
 *
 * Blinks LED3 three times: ON 200 ms, OFF 100 ms.
 *
 * @see myISR()
 * @see loop()
 */
void hitBlink() {
  // Blink LED3 three times
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED3, HIGH);
    delay(200);
    digitalWrite(LED3, LOW);
    delay(100);
  }
}

/**
 * @brief Miss indication: all LEDs off for 1 second.
 *
 * @see myISR()
 * @see loop()
 */
void missBlink() {
  // Turn all off for 1 second (or 6 seconds if you meant 6000)
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  delay(1000); // off for 1 second
}


/**
 * @brief "You win" celebration animation (after 10 hits).
 *
 * Sequence:
 * 1. Odd/even sparkle toggled 4 times.
 * 2. Forward–back chase (round trip).
 * 3. Odd/even sparkle toggled 4 times again.
 * 4. Finish: all LEDs off.
 *
 * @post The caller (@ref loop) resets @ref hits, @ref misses and @ref counter.
 * @see loop()
 */
void youWin() {  
// 1) Odd/even sparkle (4 toggles)
  for (int i = 0; i < 4; i++) {
    // odds on, evens off
    digitalWrite(LED1, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED5, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED4, LOW);
    delay(100);

    // flip: odds off, evens on
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED4, HIGH);
    delay(100);
  }
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);

  // 2) Forward–back chase (one round-trip)
  int pins[5] = { LED1, LED2, LED3, LED4, LED5 };
  for (int i = 0; i < 5; i++) {
    digitalWrite(pins[i], HIGH);
    delay(120);
    digitalWrite(pins[i], LOW);
  }
  for (int i = 4; i >= 0; i--) {
    digitalWrite(pins[i], HIGH);
    delay(120);
    digitalWrite(pins[i], LOW);
  }

  // 3) Odd/even sparkle (4 toggles)
  for (int i = 0; i < 4; i++) {
    // odds on, evens off
    digitalWrite(LED1, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED5, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED4, LOW);
    delay(100);

    // flip: odds off, evens on
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED4, HIGH);
    delay(100);
  }

  // finish: all off
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
}

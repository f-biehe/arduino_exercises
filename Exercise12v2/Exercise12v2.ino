/**
 * @file Exercise12.ino
 * @brief This sketch demonstrates XYZ functionality.
 */

/**
 * @brief Initializes the Arduino setup.
 */

#include <avr/interrupt.h>

#define LED1 8
#define LED2 9
#define LED3 10
#define LED4 11
#define LED5 12
#define BUTTONPIN 2

volatile int state = LOW;
volatile unsigned long lastInterruptTime = 0;

int hits = 0;
int misses = 0; 
int counter = 0;
int pause = 1000;
int ledNo = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(1);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(BUTTONPIN, INPUT_PULLUP);
  attachInterrupt(0, myISR, RISING);
  sei();  // turn on interrupts
}




/**
 * @brief Main loop function.
 */


void loop() {
  ledNo = counter % 5;
  counter++;

  // Turn all LEDs off first
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);

  // Turn the current LED on
  switch (ledNo) {
    case 0: digitalWrite(LED1, HIGH); delay(pause); break;
    case 1: digitalWrite(LED2, HIGH); delay(pause); break;
    case 2: digitalWrite(LED3, HIGH); delay(pause); break;
    case 3: digitalWrite(LED4, HIGH); delay(pause); break;
    case 4: digitalWrite(LED5, HIGH); delay(pause); break;
  }

  if (hits == 8) {
    ledNo = random(0,5);
    switch (ledNo) {
      case 0: 
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW); 
        delay(pause); break;
      case 1: 
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, HIGH); 
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW);
        delay(pause); break;
      case 2: 
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW); 
        delay(pause); break;
      case 3: 
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, HIGH);
        digitalWrite(LED5, LOW); 
        delay(pause); break;
      case 4: 
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, HIGH); 
        delay(pause); break;
    }
  }
  if (hits == 10) {
    youWin();
  }
}
void myISR() {
  unsigned long now = millis();
  if (now - lastInterruptTime > 200) { //200 ms debounce
    state = !state;
    if (ledNo == 2) {
      hitBlink();
      hits++;
      counter = 0;
      pause = pause - 100; //speeds up the blinking
    } else {
      missBlink();
      misses++;
      counter = 0;
    }

    Serial.print("Hits: ");
    Serial.println(hits);
    Serial.print("Misses: ");
    Serial.println(misses);
    Serial.println("------");
    lastInterruptTime = now;
  }
}


void hitBlink() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED3, HIGH); // turn LED on
    delay(200);
    digitalWrite(LED3, LOW);  // turn LED off
    delay(200);
  }
  Serial.println("hit");
}

void missBlink() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  delay(6000); //turn off for 1 second
  Serial.println("miss");
}

void youWin() {

}






#define RED 10
int redLed = RED;

#define blinkTime 200
int dot = blinkTime;
int dash = 3 * blinkTime;
int spaceBetweenLetters = 3 * blinkTime;
int spaceBetweenWords = 7 * blinkTime;



// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(redLed, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  blinkS();
  delay(spaceBetweenLetters);
  blinkO();
  delay(spaceBetweenLetters);
  blinkS();
  delay(spaceBetweenWords);
}

void blinkS() {
  for (int i = 0; i < 3; i++) {
  digitalWrite(redLed, HIGH);
  delay(dot);
  digitalWrite(redLed, LOW);
  delay(dot);
  }
}

void blinkO() {
  for (int i = 0; i < 3; i++) {
  digitalWrite(redLed, HIGH);
  delay(dash);
  digitalWrite(redLed, LOW);
  delay(dot);  
  }
}
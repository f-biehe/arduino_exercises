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
  blinkF();
  delay(spaceBetweenLetters);
  blinkR();
  delay(spaceBetweenLetters);
  blinkE();
  delay(spaceBetweenLetters);
  blinkD();
  delay(spaceBetweenLetters);
  blinkE();
  delay(spaceBetweenLetters);
  blinkR();
  delay(spaceBetweenLetters);
  blinkI();
  delay(spaceBetweenLetters);
  blinkK();
  delay(spaceBetweenLetters);
  blinkK();
  delay(spaceBetweenLetters);
  blinkE();
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

void blinkF() {
  digitalWrite(redLed, HIGH);
  delay(dot);
  digitalWrite(redLed, LOW);
  delay(dot);

  digitalWrite(redLed, HIGH);
  delay(dot);
  digitalWrite(redLed, LOW);
  delay(dot);

  digitalWrite(redLed, HIGH);
  delay(dash);
  digitalWrite(redLed, LOW);
  delay(dot);

  digitalWrite(redLed, HIGH);
  delay(dot);
  digitalWrite(redLed, LOW);
  delay(dot); 
}

void blinkR() {
  digitalWrite(redLed, HIGH);
  delay(dot);
  digitalWrite(redLed, LOW);
  delay(dot);

  digitalWrite(redLed, HIGH);
  delay(dash);
  digitalWrite(redLed, LOW);
  delay(dot);

  digitalWrite(redLed, HIGH);
  delay(dot);
  digitalWrite(redLed, LOW);
  delay(dot);
}

void blinkE() {
  digitalWrite(redLed, HIGH);
  delay(dot);
  digitalWrite(redLed, LOW);
  delay(dot);
}

void blinkD() {
  digitalWrite(redLed, HIGH);
  delay(dash);
  digitalWrite(redLed, LOW);
  delay(dot);

  digitalWrite(redLed, HIGH);
  delay(dot);
  digitalWrite(redLed, LOW);
  delay(dot);

  digitalWrite(redLed, HIGH);
  delay(dot);
  digitalWrite(redLed, LOW);
  delay(dot);
}

void blinkI() {
  for (int i = 0; i < 2; i++) {
  digitalWrite(redLed, HIGH);
  delay(dash);
  digitalWrite(redLed, LOW);
  delay(dot);  
  }
}

void blinkK() {
  digitalWrite(redLed, HIGH);
  delay(dash);
  digitalWrite(redLed, LOW);
  delay(dot);  

  digitalWrite(redLed, HIGH);
  delay(dot);
  digitalWrite(redLed, LOW);
  delay(dot); 

  digitalWrite(redLed, HIGH);
  delay(dash);
  digitalWrite(redLed, LOW);
  delay(dot); 

}

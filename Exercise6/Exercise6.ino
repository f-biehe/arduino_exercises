/*
This code make 1 or more LED(s) light up when a letter is entered into the serial monitor
the code in not case sensitive
led1 corresponds to 'a'
led2 corresponds to 'b'
led3 corresponds to 'c'
led4 corresponds to 'd'
led5 corresponds to 'e'

if a different letter is entered all leds light up
if a different character is entered, all leds turn off
*/

#define LED1 9 
#define LED2 10 
#define LED3 11 
#define LED4 12
#define LED5 13

int led1 = LED1;
int led2 = LED2;
int led3 = LED3;
int led4 = LED4;
int led5 = LED5;

char myChar;

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

}

void loop() {
  if (Serial.available() > 0) {
    myChar = Serial.read();
    myChar = myChar -'a'+'A';
  }
  switch (myChar) {
    case 65:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      break;
    case 66:
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      break;
    case 67:
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      break;
    case 68:
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, LOW);
      break;
    case 69:
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, HIGH);
      break;
    case 70 ... 90:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      break;
    default:
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
  }
}

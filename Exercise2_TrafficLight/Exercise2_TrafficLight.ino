#define RED 10
int redLed = RED;

#define YELLOW 11
int yellowLed = YELLOW;

#define GREEN 12
int greenLed = GREEN;

#define PAUSE 1000

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
 pinMode(redLed, OUTPUT);
 pinMode(yellowLed, OUTPUT);
 pinMode(greenLed, OUTPUT);
}

void loop() {
  digitalWrite(redLed, HIGH);
  Serial.println("STOP");
  delay(PAUSE);
  digitalWrite(yellowLed, HIGH);
  delay(PAUSE);
  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, HIGH);
  Serial.println("GO");
  delay(PAUSE);
  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, HIGH);
  Serial.println("SLOW");
  delay(PAUSE);
  digitalWrite(yellowLed, LOW);
}

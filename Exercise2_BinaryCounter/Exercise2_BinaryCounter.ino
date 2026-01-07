#define LED1 10
int led1 = LED1;

#define LED2 11
int led2 = LED2;

#define LED3 12
int led3 = LED3;

#define PAUSE 1000

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);  
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 8; i++) {
     if (i % 2 == 1) {
      digitalWrite(led1, HIGH);
    }

    if ((i >> 1) % 2 == 1) {
      digitalWrite(led2, HIGH);
    }

    if ((i >> 2) % 2 == 1) {
      digitalWrite(led3, HIGH);
    }

    Serial.println(i, BIN);
    Serial.println(i>>1);
    Serial.println(i>>2);
    Serial.println("-------");
    delay(PAUSE);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    delay(PAUSE);
  }
  
}

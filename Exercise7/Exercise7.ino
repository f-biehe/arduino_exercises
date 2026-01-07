/*
Takes 3 comma seperated numbers (0-255) and turns an RGB LED that color. 
*/

#define REDPIN 10
#define GREENPIN 11
#define BLUEPIN 12

int redLED = REDPIN;
int greenLED = GREENPIN;
int blueLED = BLUEPIN;

int redValue;
int greenValue;
int blueValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    redValue = Serial.parseInt();
    greenValue = Serial.parseInt();
    blueValue = Serial.parseInt();
    Serial.print("RED: ");
    Serial.println(redValue);
    Serial.print("GREEN: ");
    Serial.println(greenValue);
    Serial.print("BLUE: ");
    Serial.println(blueValue);    
  }
  setColor(redValue, greenValue, blueValue);
}

void setColor(int red, int green,  int blue) {
  analogWrite(redLED, red);
  analogWrite(greenLED,  green);
  analogWrite(blueLED, blue);
}

/*
Use the voltage to control the color of the LED. When applying 0V on the A0 pin the RGB LED should be
purple and when applying maximum voltage it should be red. When tuning the potentiometer, the RGB LED
should slowly fade between the different colors
*/

#define POTENTIONMETERPIN A0
#define REDPIN 10
#define GREENPIN 11
#define BLUEPIN 12

int redLED = REDPIN;
int greenLED = GREENPIN;
int blueLED = BLUEPIN;

int redValue = 255;
int greenValue = 0;
uint8_t blueValue;

int potPin = POTENTIONMETERPIN;
int potValue = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(potPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  potValue = analogRead(potPin);
  Serial.print("Voltage: ");
  Serial.print(convertToVoltage(potValue));
  blueValue = 255 - convertToRGBValue(potValue);
  Serial.print(" blue: ");
  Serial.println(blueValue);
  setColor(redValue, greenValue, blueValue);
  delay(500);
}

float convertToVoltage(int potValue) {
  return map(potValue, 0L, 675L, 0L, 3.3L);
}

int convertToRGBValue(int potValue) {
  return map(potValue, 0L, 675L, 0L, 255L);
}

void setColor(int red, int green,  int blue) {
  analogWrite(redLED, red);
  analogWrite(greenLED,  green);
  analogWrite(blueLED, blue);
}

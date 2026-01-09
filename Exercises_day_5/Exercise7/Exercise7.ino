// Define a union Data with members for int, float, and char
union Data {
  int dataInt;
  float dataFloat;
  char dataChar;
};

// Create one Data variable
Data dataReadings;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Store an int, then print it
  dataReadings.dataInt = 5;
  Serial.println(dataReadings.dataInt);
  // Store a float in the same union, then print it
  dataReadings.dataFloat = 6.67;
  Serial.println(dataReadings.dataFloat);
  // Note what happens to the earlier value
  Serial.println(dataReadings.dataInt); // this doesn't give a number that makes sense, since the int has been overwritten by a float.
}

void loop() {
  // put your main code here, to run repeatedly:

}

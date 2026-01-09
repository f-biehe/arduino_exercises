// Define a union Conversion with a float member
union Conversion {
  float number;
  // Add a 4-byte array member to the same union
  byte array[4];
} myConversion;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Store a float value in the union
  myConversion.number = 45.67f;
  // Print the float
  Serial.println(myConversion.number);
  // Print each byte value in the array in hex
  for (int i = 0; i < 4; i++) {
  Serial.println(myConversion.array[i], HEX);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

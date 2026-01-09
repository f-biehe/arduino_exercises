// Define a Car struct with make and year
struct Car {
  String make;
  int year;
};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Create a Car value and call the function
  printCarDetails("Clio", 2007);
}

void loop() {
  // put your main code here, to run repeatedly:

}

// Write a function that accepts a Car parameter
void printCarDetails (String make, int year) {
  struct Car myCar;
  myCar.make = make;
  myCar.year = year;

  // Inside the function, print make and year
  Serial.print("Make: ");
  Serial.println(myCar.make);
  Serial.print("Year: ");
  Serial.println(myCar.year);
}

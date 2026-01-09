// Define a Student struct with name, age, grade
struct Student {
  String name;
  int age;
  int grade;
} myStudent; // Create one Student variable

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Fill in each field
  myStudent.name = "Frederikke";
  myStudent.grade = 12;
  myStudent.age = 25;

  // Print the fields using dot notation
  Serial.print("Name: ");
  Serial.println(myStudent.name);
  Serial.print("Age: ");
  Serial.println(myStudent.age);
  Serial.print("Grade: ");
  Serial.println(myStudent.grade);

}

void loop() {
  // put your main code here, to run repeatedly:

}

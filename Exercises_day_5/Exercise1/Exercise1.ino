// Declare an int variable x and set it to 10
int x = 10;
// Declare an int pointer p
int *p;

void setup() {
  // put your setup code here, to run once:
  // Store the address of x inside p
  p = &x;
  // Print the value of x by dereferencing p
  x = *p;
  Serial.begin(9600);
  Serial.print(x);
}

void loop() {
  // put your main code here, to run repeatedly:

}

// Declare an int variable x
int x = 5;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Declare an int pointer p pointing to x
  int *p;
  p = &x;
  // Declare an int pointer-to-pointer q pointing to p
  int **q;
  q = &p;
  // Use q to modify x indirectly
  **q = 15;
  // Print x
  Serial.print(x);
}

void loop() {
  // put your main code here, to run repeatedly:

}

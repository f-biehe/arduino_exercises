// Create an int array with 5 values
int a[5] = {1,2,3,4,5};
// Create an int pointer p 
int *p;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //p refers to the first element of a
  p = &a[0];
  // Loop from index 0 to 4
  for (int i = 0; i < 5; i++) {
    Serial.println(*p + i);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

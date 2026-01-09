// Declare a float variable temperature and set it to 36.6
float temp = 36.6;
// Declare a float pointer p 
float *p;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // point p to temperature
  p = &temp;
  // Change temperature by writing through p
  *p = 37.8;
  // Print temperature to confirm it changed
  Serial.print(temp);
}

void loop() {
  // put your main code here, to run repeatedly:

}

// Define a Sensor struct with a name field
struct Sensor {
  String name;

  // Inside Sensor, include a union with temperature, humidity, status
  union {
    float temperature;
    int humidity;
    char status;
  } data;
};

// Create a Sensor value
  struct Sensor roomSensor = {"Living room"};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Store a temperature value in the union
  roomSensor.data.temperature = 21.6f;
  // Print the sensor name and temperature
  Serial.print("Name: ");
  Serial.println(roomSensor.name);
  Serial.print("Temp: ");
  Serial.println(roomSensor.data.temperature);
}

void loop() {
  // put your main code here, to run repeatedly:

}

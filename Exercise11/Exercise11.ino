//Thermometer with thermistor printing to an LCD display

/*thermistor parameters:
 * RT0:  10 000 Ω
 * B: 3977 K +- 0.75%
 * T0:  25 C
 * +- 5%
 */
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,  16, 2);

#define VLTPIN A0

//These  values are in the datasheet
#define RT0 10000   // Ω
#define B 3977      //  K

#define VCC 5    //Supply  voltage
#define R 10000  //R=10KΩ

float vlt, temp, RT, VR, ln, T0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  T0 = 25 + 273.15;             //Temperature  T0 from datasheet, conversion from Celsius to kelvin

  lcd.init(); //initialize lcd screen
  lcd.backlight(); //turn on backlight
  lcd.setCursor(0,0);
  lcd.print("Temperature [C]");
}

void loop() {
  // calculate temperature
  vlt = analogRead(VLTPIN);     //read analog value
  vlt = (5.0 / 1023.0) * vlt;   //Conversion to voltage

  VR = VCC - vlt;
  RT = vlt / (VR / R);          //Resistance of RT

  ln = log(RT / RT0);
  temp = (1 / ((ln / B) + (1 / T0))); //Temperature from thermistor

  temp =  temp - 273.15;        //Conversion to Celsius

  Serial.print(temp);
  Serial.println("°C");
  delay(1000);


  
  lcd.setCursor(0,1);
  lcd.print(temp);

  delay(1000);
}

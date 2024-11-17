#include <LiquidCrystal.h>
#include"DHT.h"// Download this library from the link given below
#define DHTPIN 8// Define pin of the DHT11 sensor data pin
#define DHTTYPE DHT22// Define the type of the sensor. for DHT22 type DHT22 instead of DHT11
DHT dht(DHTPIN, DHTTYPE);// Create an object of type DHT to access all the functions of the library

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//aca pongo para el de humedad de suelo
int SensorPin = A0;

//aca el rele (el que corta)
int RelePin = 13;

void setup(){
  Serial.begin(9600);// Set baud rate for serial communication
  dht.begin();// Initiate DHT sensor

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  pinMode(RelePin,OUTPUT);
}
 
void loop(){
  delay(2000); // Wait a few seconds between measurements

  float humidity = dht.readHumidity(); // Read humidity
  float tempC = dht.readTemperature(); // Read temperature in Celsius
    //aca lo de humedad de suelo
  int humedad = analogRead(SensorPin);


  lcd.clear(); // Clear the LCD display

  if (isnan(humidity) || isnan(tempC)) {
      lcd.setCursor(0, 0);
      lcd.print("Failed");
  } else {
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.print(tempC);
      lcd.print((char)223); // Print the degree symbol
      lcd.print("C");

      lcd.setCursor(0, 1);
      lcd.print("Humo: ");
      lcd.print(humidity);
      lcd.print("%");
  }

   delay(2000);
  //Ahora muestro la humedad de suelo
  lcd.clear(); // Clear the LCD display
  lcd.setCursor(0, 0);
  lcd.print("Suelo: ");
  lcd.print(humedad);

  //Serial.print(humedad);
  digitalWrite(RelePin,HIGH);
  delay(2000);
  digitalWrite(RelePin,LOW);

}
#include <Wire.h>

#include <OneWire.h>

#include <LiquidCrystal_I2C.h>

#include <DallasTemperature.h>


#define ONE_WIRE_BUS 2                

LiquidCrystal_I2C lcd(0x27, 16, 2);


DeviceAddress thermometerAddress;   
OneWire oneWire(ONE_WIRE_BUS);      
DallasTemperature tempSensor(&oneWire);

const int trigPin = 12;
const int echoPin = 13;
const int ledRed = 3;
const int ledGreen = 4;

long duration;
int distance;

void setup() {
    lcd.begin();

  lcd.print("Hello, world!");
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);

  Serial.begin(9600);
                      
  Serial.println("Meternomy Temperature IC Test");
  Serial.println("Locating devices...");
  tempSensor.begin();                         

  if (!tempSensor.getAddress(thermometerAddress, 0))
    Serial.println("Unable to find Device.");
  else {
    Serial.print("Device Meternomy Address: ");
    printAddress(thermometerAddress);
    Serial.println();
  }

  tempSensor.setResolution(thermometerAddress, 9);    
}

void loop() {

  tempSensor.requestTemperatures();                   
  displayTemp(tempSensor.getTempC(thermometerAddress));  
  delay(500);   
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  
  if (distance > 10) {
      Serial.print("Distance = ");
      Serial.print(distance);
      Serial.println(" cm");
      digitalWrite(ledRed, LOW);
      digitalWrite(ledGreen, HIGH);
      delay(5000);
    }
    else {
      Serial.print("Distance = ");
      Serial.print(distance);
      Serial.println(" cm");
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledRed, HIGH);
      delay(5000);
    }

  }

  void displayTemp(float temperatureReading) {             // temperature comes in as a float with 2 decimal places

  // show temperature °C
  Serial.print(temperatureReading);      // serial debug output
  Serial.print("°");
  Serial.print("C  ");

}


// print device address from the address array
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

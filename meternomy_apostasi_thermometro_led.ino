#include <LiquidCrystal.h>

#include <Wire.h>

#include <OneWire.h>

#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2  

 
LiquidCrystal lcd(1, 10, 6, 7, 8, 9);

const int trigPin = 12;
const int echoPin = 13;
const int ledRed = 3;
const int ledGreen = 4;

long duration;
int distance;


DeviceAddress thermometerAddress;   
OneWire oneWire(ONE_WIRE_BUS);      
DallasTemperature tempSensor(&oneWire);


void setup() {
lcd.begin(16,2);
  

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);



  lcd.blink();
  delay(1000);
  lcd.print("M");
  delay(200);
  lcd.print("E");
  delay(200);
  lcd.print("T");
  delay(200);
  lcd.print("E");
  delay(200);
  lcd.print("R");
  delay(200);
  lcd.print("N");
  delay(200);
  lcd.print("O");
  delay(200);
  lcd.print("M");
  delay(200);
  lcd.print("Y");
  delay(200);
  lcd.print(" L");
  delay(200);
  lcd.print("T");
  delay(200);
  lcd.print("D");
  delay(2000);
  lcd.noBlink();
  lcd.clear();
    
  
  tempSensor.begin();                         

  if (!tempSensor.getAddress(thermometerAddress, 0))
    lcd.println("Unable to find Device.");
  else {
    lcd.print("Device Meternomy Address: ");
    printAddress(thermometerAddress);
    lcd.println();
  }

  lcd.noCursor();
  lcd.clear();
    
  
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
  
  
  if (distance > 50) {
    
      digitalWrite(ledRed, HIGH);
      digitalWrite(ledGreen, LOW);
      
    }
    else {
    
      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledRed, LOW);
      
    }
  
      lcd.print("LIQUID LEVEL:");
      lcd.print(distance);
      lcd.print(" CM");
  	  delay(500);
  
    for (int positionCounter = 0; positionCounter < 13; positionCounter++) 
  {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(250);
                  
  }
}

void displayTemp(float temperatureReading) {         

  lcd.setCursor(0,1);
  lcd.print("TEMPERATURE:");
  delay(2000);
 
  lcd.print(temperatureReading);      
  lcd.print("°");
  lcd.print("C  ");

}


void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    lcd.print(deviceAddress[i], HEX);
  }
  delay(1000);
  lcd.noCursor();
  lcd.clear();
}

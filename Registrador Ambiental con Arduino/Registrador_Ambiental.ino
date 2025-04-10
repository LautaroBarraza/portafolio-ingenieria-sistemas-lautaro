#include <OneWire.h>
#include <DallasTemperature.h>
#include <TimerOne.h>
#include <Wire.h>
#include "RTClib.h"
#include <SHT21.h>  // incluir la biblioteca SHT21
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

RTC_DS1307 rtc;
SHT21 sht; 

float temp;     // variable para almacenar la temperatura
float humidity; // variable para almacenar la humedad

const byte ONE_WIRE_BUS = 5;
// Configurar una instancia OneWire para comunicarse con dispositivos OneWire.
OneWire oneWire(ONE_WIRE_BUS);
// Pasa nuestra referencia OneWire al sensor de temperatura Dallas.
DallasTemperature sensors(&oneWire);

byte numDevices = 0;

DeviceAddress sensorAddress1 = { 0x28, 0xB9, 0x9E, 0x75, 0xD0, 0x1, 0x3C, 0x73 };
DeviceAddress sensorAddress2 = { 0x28, 0xD8, 0x20, 0x75, 0xD0, 0x1, 0x3C, 0x6A };

LiquidCrystal_I2C lcd(0x27,16,2);  //
byte ant=-1;
byte nuevo=-1;

bool nombreSensor = false;
void setup() {
 // pon tu código de configuración aquí, para que se ejecute una vez:
  Serial.begin(9600);
  Timer1.initialize();
  sensors.begin();
  Wire.begin();       // comenzar Wire (I2C)
  rtc.begin();
  lcd.init();
  lcd.backlight();
  byte address[8];
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MEDIDOR");
  lcd.setCursor(0, 1);
  lcd.print("AMBIENTAL V1.0");
}
void loop() {
  
  if (Serial.available() > 0) {   
    nuevo = Serial.read() - '0'; // Convertir el carácter recibido en un número
  } 
    // Verifica si se seleccionó el sensor 1
    if (nuevo == 1) {
      if(!nombreSensor){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sensor A");
        nombreSensor = true;
      }
      
      lcd.setCursor(0, 1);
      sensors.requestTemperatures();
      float temperatureC = sensors.getTempC(sensorAddress1);
      lcd.print(temperatureC);
      if (Serial.available() > 0) {
        byte temp = Serial.read() - '0';
        if(temp==1 or temp==2 or temp==3 or temp==4){
          if(temp!=nuevo){
            nuevo=temp;
            nombreSensor=false;
        }
        } // Convertir el carácter recibido en un número
      }
    }

    // Verifica si se seleccionó el sensor 2
    if (nuevo == 2) {
      if(!nombreSensor){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sensor B");
        nombreSensor=true;
      }
      
      lcd.setCursor(0, 1);
      sensors.requestTemperatures();
      float temperatureC = sensors.getTempC(sensorAddress2);
      lcd.print(temperatureC);
      if (Serial.available() > 0) {
        byte temp = Serial.read() - '0';
        if(temp==1 or temp==2 or temp==3 or temp==4){
          if(temp!=nuevo){
            nuevo=temp;
            nombreSensor=false;
        }
        }
      }
    }

    // Verifica si se seleccionó la hora actual
    if (nuevo == 3) {
      if(!nombreSensor){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Clock");
      nombreSensor=true;
      }
      
      lcd.setCursor(0, 1);
      DateTime now = rtc.now();
      lcd.print(now.year());
      lcd.print("/");
      lcd.print(now.month());
      lcd.print("/");
      lcd.print(now.day());
      lcd.print("  ");
      lcd.print(now.hour());
      lcd.print(":");
      lcd.print(now.minute());
      if (Serial.available() > 0) {
        byte temp = Serial.read() - '0';
        if(temp==1 or temp==2 or temp==3 or temp==4){
          if(temp!=nuevo){
            nuevo=temp;
            nombreSensor=false;
        }
        }
      }
    }

    // Verifica si se seleccionó el sensor de humedad y temperatura
    if (nuevo == 4) {
      if(!nombreSensor){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SHT 21");
        nombreSensor=true;
      }
      
      lcd.setCursor(0, 1);
      temp = sht.getTemperature();  // obtiene la temperatura de SHT 
      humidity = sht.getHumidity(); // obtiene la humedad de SHT
      
      lcd.print("T:");
      lcd.print(temp);
      lcd.print(" H:");
      lcd.print(humidity);
      if (Serial.available() > 0) {
        byte temp = Serial.read() - '0';
        if(temp==1 or temp==2 or temp==3 or temp==4){
          if(temp!=nuevo){
            nuevo=temp;
            nombreSensor=false;
        }
        }
      }
    }
    
}

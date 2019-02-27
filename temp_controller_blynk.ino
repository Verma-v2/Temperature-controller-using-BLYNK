/*** Copyright [2019] [Gyanendra Verma]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.

* we are not responsible for any physical damage caused by the user or to the user. Saftey precautions are mandotery while tesing 
* We recommande user's to test the code in care of mentors.
* while using ac load please beware, a mistake could cause a big accident.
* you are free to use the code as you want, but if you are using it don't forget to give credit :)
*/
// Libraries find them on github and blynk plateform. 
#define BLYNK_DEBUG
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#include<LiquidCrystal.h>
#include <DallasTemperature.h> //Temperature sensor library.



//pins setup

int ONE_WIRE_BUS=2;
SoftwareSerial EspSerial(10, 9);
const int rs = 12, en = 11, d4 = A3, d5 = A2, d6 = A1, d7 = A0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int powled= 8;
int led= 3;
WidgetLCD lcd1(V2);

WidgetTerminal terminal(V1); // V1 and same other pins starting from V are virtual pins. Read about blynk virtual pins to know more.

int ledPin = 13;

//variable setup
float dstemp; 
int mintemp = 23; // minimum temperature
int maxtemp = 29; // Maximum temperature
BlynkTimer timer;
//wifi
ESP8266 wifi(&EspSerial);
#define ESP8266_BAUD 115200

/// temperature sensor
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

//Wifi Setup
char auth[] = "Your_blynk_auth_token"; //Token Here;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Your WIFI ssid"; 
char pass[] = "Your WIFI Password";

/*****************************************************************************Void Setup*********************************************************/
void setup() {
 //Serial COmmunication start
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  lcd.setCursor(0,0);
  lcd.print("Welcome");

 Blynk.begin(auth, wifi, ssid, pass);
  lcd.begin(16,2);
  sensors.begin();

  //Pin setup
  
pinMode(powled,OUTPUT);
 pinMode(led,OUTPUT);
 pinMode(ledPin, OUTPUT);  

 //timer setup

  timer.setInterval(2000, mySensorEvent);
  timer.setInterval(2000, condition);
  

 
  

}
/***************************************************************loop*********************************************************/
void loop() {
    Blynk.run();
    timer.run();
    digitalWrite(ledPin,HIGH);
}


/***********************************************Blynk setups Sensor and switch************************************************************************************************/


//getting Sensor Data
void mySensorEvent(){
  sensors.requestTemperatures(); 
 dstemp= (sensors.getTempCByIndex(0));
 
 lcd.setCursor(0,0);
 lcd.println("Temp:");
 lcd.print( dstemp );
  lcd.print((char)223);
  lcd.print("C");
  lcd1.print(0, 0, "Temp= ");
  lcd1.print( 5,0, dstemp );
 
}

 //set temp pin reading
 BLYNK_WRITE(V3) {
  int pinValue(param.asInt());
  mintemp= pinValue;
  Serial.println(mintemp);
  Serial.println(pinValue);
 
 }
  BLYNK_WRITE(V4) {
  int pinValu(param.asInt());
  maxtemp= pinValu;
  Serial.println(maxtemp);
  Serial.println(pinValu);
 
 }


 
 /************************************************************logic*******************************************************/
 void condition(){ 
  Blynk.virtualWrite(V5,mintemp);
  Blynk.virtualWrite(V6,maxtemp);
if ( dstemp >=mintemp && dstemp<= maxtemp){
      digitalWrite(powled,HIGH);
      digitalWrite(led,LOW);
      lcd.setCursor(0,1);
      lcd.print("DEVICE ST:");
      lcd.print("ON  ");
      lcd1.print(0, 1,"DEVICE ST:");
      lcd1.print( 10 ,1 ,"ON  " );
     
      }
      else{
    
        digitalWrite(powled,LOW);
        digitalWrite(led,HIGH);
        lcd.setCursor(0,1);
        lcd.print("DEVICE ST:");
        lcd.print("OFF");
        lcd1.print(0, 1,"DEVICE ST:");
        lcd1.print( 10 ,1 ,"OFF" );
        
       
        }
 }
/********************************************************************************The End*************************************************************************************************************/
//By: Gyanendra Verma
 

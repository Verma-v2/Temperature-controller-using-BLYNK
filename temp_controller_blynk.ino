#define BLYNK_DEBUG
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#include<LiquidCrystal.h>
#include <DallasTemperature.h>



//pins setup

int ONE_WIRE_BUS=2;
SoftwareSerial EspSerial(10, 9);
const int rs = 12, en = 11, d4 = A3, d5 = A2, d6 = A1, d7 = A0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int powled= 8;
int led= 3;
WidgetLCD lcd1(V2);

WidgetTerminal terminal(V1);

int ledPin = 13;

//variable setup
float dstemp; 
int mintemp = 23;
int maxtemp = 29;
BlynkTimer timer;
ESP8266 wifi(&EspSerial);
#define ESP8266_BAUD 115200
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

//Wifi Setup
char auth[] = "04365696abd448aaa36b13fa94aecc23";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Aiotronix";
char pass[] = "0900gyan500";

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
 

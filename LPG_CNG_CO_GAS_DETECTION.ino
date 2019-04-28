#include <LiquidCrystal.h>

float sensorVoltage,sensorValue,sensorVoltage1,sensorValue1;
float a=1.5, b=2.5;
int buzzer=3;
int LED6=4;
int LED7=5;
int fan=6;
LiquidCrystal lcd(13,12,11,10,9,8);

void setup() 
{
   Serial.begin(9600);
   lcd.begin(16,2);
   pinMode(buzzer, OUTPUT); 
   pinMode(LED6, OUTPUT);
   pinMode(LED7, OUTPUT);
   pinMode(fan, OUTPUT);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Air Pollution");
   lcd.setCursor(0,1);
   lcd.print("Control System");
  delay(5000);
}
void loop() 
{

  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  sensorVoltage = (sensorValue/1024)*5.0;
  Serial.print("MQ6 sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V    ");
  
  sensorValue1 = analogRead(A1);
  Serial.println(sensorValue1);
  sensorVoltage1 = (sensorValue1/1024)*5.0;
  Serial.print("MQ7 sensor voltage = ");
  Serial.print(sensorVoltage1);
  Serial.println(" V    ");
  lcd.clear();
  lcd.print("MQ6=");
  lcd.setCursor(4,0);
  lcd.print(sensorVoltage);
  lcd.setCursor(8,0);
  lcd.print("MQ7=");
  lcd.setCursor(12,0);
  lcd.print(sensorVoltage1);
 
 
  if(sensorVoltage>a || sensorVoltage1>b){
       lcd.setCursor(0,1);
       lcd.print("Gas detected");
       if(sensorVoltage>a){
        lcd.clear();
       lcd.setCursor(0,1);
       lcd.print("LPG/CNG Gas");
       digitalWrite(LED6, HIGH);
       digitalWrite(buzzer,HIGH);
       digitalWrite(fan, HIGH);
            delay(3000);
       } 
       if(sensorVoltage1>b)
        lcd.clear();
       lcd.setCursor(0,1);
       lcd.print("CO Gas");
       digitalWrite(LED7, HIGH);
       digitalWrite(buzzer,HIGH);
       digitalWrite(fan, HIGH);
            delay(3000);
  }
   else {
       lcd.setCursor(0,1);
       lcd.print("Normal condition");
       digitalWrite(LED6, LOW);
       digitalWrite(LED7, LOW);
       digitalWrite(buzzer,LOW);
       digitalWrite(fan, LOW);
   }
}

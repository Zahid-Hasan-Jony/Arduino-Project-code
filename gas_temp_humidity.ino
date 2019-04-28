#include <dht.h>

dht DHT;

#define DHT11_PIN 5

int buzzer=3;
int motorA1=9;
int motorA2=10;
int motorEN=11;
int LED1=4;
int LED2=6;

void setup() 
{
   Serial.begin(9600);
   pinMode(buzzer, OUTPUT); 
   pinMode(LED1, OUTPUT);
   pinMode(LED2, OUTPUT);
   pinMode(motorA1,OUTPUT);
   pinMode(motorA2,OUTPUT);

  Serial.println("Library version");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
}

 void motorforward()
  {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  }
void motorstop()
  {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  }
  
void loop() 
{
  float sensorVoltage; 
  float sensorValue;
 
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  sensorVoltage = (sensorValue/1024)*5.0;
 
  Serial.print("sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");

  // READ DATA
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    case DHTLIB_ERROR_CONNECT:
        Serial.print("Connect error,\t");
        break;
    case DHTLIB_ERROR_ACK_L:
        Serial.print("Ack Low error,\t");
        break;
    case DHTLIB_ERROR_ACK_H:
        Serial.print("Ack High error,\t");
        break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;
  }
  // DISPLAY DATA
  Serial.print(DHT.humidity, 1);
  Serial.print(",\t");
  Serial.println(DHT.temperature, 1);
  delay(1000);

  
  if(sensorVoltage>1.30)
 {
    digitalWrite(LED1, HIGH);
    digitalWrite(buzzer,HIGH);
    analogWrite(motorEN, 255);
    motorforward();
    delay(500);
 }
 else if(DHT.temperature>35){
     digitalWrite(LED2, HIGH);
     analogWrite(motorEN, 255);
     motorforward();
     delay(500);
 }
 else {
        digitalWrite(buzzer,LOW);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        motorstop();

 }
} 

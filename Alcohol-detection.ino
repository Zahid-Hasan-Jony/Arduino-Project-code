int buzzer=3;
int led=6;

void setup() 
{
   Serial.begin(9600);
   pinMode(buzzer, OUTPUT); 
   pinMode(led,OUTPUT);
    delay(10000);
  
}

 
void loop() 
{
  float sensorVoltage; 
  float sensorValue;
 
  sensorValue = analogRead(A0);
  sensorVoltage = sensorValue/1024*3.3;
 
  Serial.print("sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
  //delay(1000);
  
  if(sensorVoltage>.90)
 {

    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    delay(100);
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(led,HIGH);
    delay(3000);
 }
 else {
        digitalWrite(buzzer,LOW);
        digitalWrite(led,LOW);

 }
}

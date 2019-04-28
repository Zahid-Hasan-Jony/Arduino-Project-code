float sensorVoltage,sensorValue;
float a=1.6;                    //threshold voltage of gas leaksage is equalto "a"
int motorA1=9;
int motorA2=10;
int motorEN=11;
int buzzer=3;
int LEDgas=4;

void setup() 
{
   Serial.begin(9600);
   pinMode(buzzer, OUTPUT); 
   pinMode(LEDgas, OUTPUT);
   pinMode(motorA1,OUTPUT);
   pinMode(motorA2,OUTPUT);
   pinMode(motorEN,OUTPUT);
}
 void motorforward()
  {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW); }
void motorstop()
  {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  }
void loop() 
{
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  sensorVoltage = (sensorValue/1024)*5.0;
  Serial.print("sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V    ");
  
  if(sensorVoltage>a){
       Serial.println("gas leakaged");
       Serial.println("Fan on");
       digitalWrite(LEDgas, HIGH);
       digitalWrite(buzzer,HIGH);
       analogWrite(motorEN, 255);
       motorforward();
       delay(100);
   }
   else {
       digitalWrite(LEDgas, LOW);
       digitalWrite(buzzer,LOW);
       analogWrite(motorEN,0);
       motorstop();
   }
}

int sensorPin=A0;
int sensorValue=0;
int leddry=8;
int ledwet=10;
int motorA1=3;
int motorA2=5;
int motorEN=6;                            
 
  void motorforward()
  {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  }

  void motorbackward()
  {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  }
  void motorstop()
  {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  }
  
void setup() {
  
   Serial.begin(9600);
   pinMode(leddry,OUTPUT);
   pinMode(ledwet, OUTPUT);
    pinMode(motorEN,OUTPUT);
    pinMode(motorA1,OUTPUT);
    pinMode(motorA2,OUTPUT);
}

void loop() {
  sensorValue= analogRead(sensorPin);
  Serial.println(sensorValue); 
  delay(10);
   float motorspeed;
  motorspeed= 255;
  analogWrite(motorEN, motorspeed);


  if(sensorValue>900) {
    digitalWrite(leddry,HIGH);           
    digitalWrite(ledwet,LOW);       
    motorforward();              
  }
  else if(sensorValue<400){
    digitalWrite(leddry,LOW);     
    digitalWrite(ledwet,HIGH);     
     motorstop();   
    }
  }

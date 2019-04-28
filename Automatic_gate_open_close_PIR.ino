#include <Servo.h>
int pirPin1=5;
int pirPin2=6;
int angle = 0;
Servo myservo1;
Servo myservo2;

int C1time=30;
int C2time=30;
long unsigned int lowIn;
long unsigned int lowIn;
long unsigned int pause=5000;
boolean locklow =true;
boolean takelowTime;

void setup()
{
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(pirPin1, INPUT);
  pinMode(pirPin2, INPUT);
  myservo.attach(3);

 digitalWrite(pirPin1, LOW);
 digitalWrite(pirPin2, LOW);

 Serial.print("calibrating sensor");
 for(int=0;i<C1time; i++) {
  delay(1000);
 }
}
void loop()
{
  if ( digitalRead(pirPin1) == HIGH){
    for(angle = 0;angle <=90; angle++)
  { 
  myservo.write(angle);
  delay(10);
}
  }
  else if ( digitalRead(pirPin2) == HIGH){
     for(angle = 0;angle<=90; angle++)
{
  myservo.write(angle);
  delay(10);
 }
  }
  else if ( digitalRead(pirPin1) == LOW && digitalRead(pirPin2) == LOW){
     for(angle = 90;angle >=0; angle--)
{
  myservo.write(angle);
  delay(10);
 }
  }
  else if (digitalRead(pirPin1) == HIGH && digitalRead(pirPin2) == HIGH){
     for(angle = 0;angle <=90; angle++)
    {
     myservo.write(angle);
     delay(10);
    }
  }
}

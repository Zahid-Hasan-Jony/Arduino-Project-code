#include <Servo.h>
#define trig A0
#define echo A1
float sensorVoltage,sensorValue;
float a=1.6;
int buzzer=A3;
int LEDgas=A4;
int led=11;
int lamp=12;
int motorleft1 = 2;
int motorleft2 = 3;
int motorright1 = 4;
int  motorright2 = 5;
int  motorleftenb = 9;
int motorrightenb = 10;
int pos =0;
int pos1=90;
String data;
int command ;
int x;
float distance;
Servo head;
Servo right;
Servo left;
Servo mouth;

float sending() {
  float duration, cm;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  cm = duration / 58.82;
  return cm;
}
void setup() {
   pinMode(buzzer, OUTPUT); 
   pinMode(LEDgas, OUTPUT);
  pinMode(motorleft1, OUTPUT);
  pinMode(motorleft2, OUTPUT);
  pinMode(motorright1, OUTPUT);
  pinMode(motorright2, OUTPUT);
  pinMode(motorleftenb, OUTPUT);
  pinMode(motorrightenb, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  head.attach(6);
  right.attach(7);
  left.attach(8);
  mouth.attach(13);
  Serial.begin(9600);
}
void robotforward() {
  digitalWrite(motorleft1, HIGH);
  digitalWrite(motorleft2, LOW);
  digitalWrite(motorright1, HIGH);
  digitalWrite(motorright2, LOW);
}
void robotbackward() {
  digitalWrite(motorleft1, LOW);
  digitalWrite(motorleft2, HIGH);
  digitalWrite(motorright1, LOW);
  digitalWrite(motorright2, HIGH);
}
void robotleft() {
  digitalWrite(motorleft1, LOW);
  digitalWrite(motorleft2, HIGH);
  digitalWrite(motorright1, HIGH);
  digitalWrite(motorright2, LOW);
}
void robotright() {
  digitalWrite(motorleft1, HIGH);
  digitalWrite(motorleft2, LOW);
  digitalWrite(motorright1, LOW);
  digitalWrite(motorright2, HIGH);
}
void robotstop() {
  analogWrite(motorleftenb, 0);
  analogWrite(motorrightenb, 0);
}
void loop() {
sensorValue = analogRead(A2);
  Serial.println(sensorValue);
  sensorVoltage = (sensorValue/1024)*5.0;
  Serial.print("sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V    ");
  
  if(sensorVoltage>a){
       analogWrite(LEDgas, 200);
       analogWrite(buzzer,200);
       delay(100);
   }
   else {
       analogWrite(LEDgas, 0);
       analogWrite(buzzer,0);
   }

  if (Serial.available()) {
    data = Serial.readStringUntil('\n');
    Serial.println(data);
    if (data == "1" || data == "U" || data == "ran fast" || data == "Ran fast" || data == "run fast" || data == "Run fast") {
      analogWrite(motorleftenb, 200);
      analogWrite(motorrightenb, 200);
      x = 1;
      Serial.println("Motorforawrd");
      robotforward();
      distance = sending();
      Serial.println(distance);
      if (distance < 30) {
        robotbackward();
        delay(200);
        robotstop();
      }
      data = "*1#";
    }
    else if (data == "5" || data == "Run slow" || data == "run slow" || data == "ran slow" || data == "Ran slow") {
      analogWrite(motorleftenb, 120);
      analogWrite(motorrightenb, 120);
      x = 5;
      Serial.println("Motorforawrd");
      robotforward();
      distance = sending();
      Serial.println(distance);
      if (distance < 30) {
        robotbackward();
        delay(200);
        robotstop();
      }
      data = "*5#";
    }
    else if (data == "6" || data == "Run" || data == "run" || data == "ran" || data == "Ran") {
      analogWrite(motorleftenb, 150);
      analogWrite(motorrightenb, 150);
      x = 6;
      Serial.println("Motorforawrd");
      robotforward();
      distance = sending();
      Serial.println(distance);
      if (distance < 30) {
        robotbackward();
        delay(200);
        robotstop();
      }
      data = "6";
    }
    else if (data == "2" || data == "backward" || data == "Backward" || data == "D") {
      analogWrite(motorleftenb, 255);
      analogWrite(motorrightenb, 255);
      x = 2;
      Serial.println("Motorbackward");
      robotbackward();
      data = "2";
    }
    else if (data == "4" || data == "Left" || data == "left" || data == "L") {
      analogWrite(motorleftenb, 200);
      analogWrite(motorrightenb, 200);
      robotleft();
      Serial.println("Motorleft");
      delay(400);
      robotforward();
         distance = sending();
      Serial.println(distance);
      if (distance < 30) {
        robotstop();
        delay(200);
      }
    }
    else if (data == "3" || data == "Right" || data == "right" || data == "R") {
      analogWrite(motorleftenb, 200);
      analogWrite(motorrightenb, 200);
      Serial.println("Motorright");
      robotright();
      delay(400);
      robotforward();
      distance = sending();
      Serial.println(distance);
      if (distance < 30) {
        robotstop();
        delay(200);
      }
    }
    else if (data == "Stop" || data == "0"  || data == "C" || data == "stop") {
      Serial.println("Motorstop");
      robotstop();
      delay(150);
    }
    else if (data == "look right" || data == "Look right") {
        for (pos1 = 90; pos1 >= 0; pos1--)
        head.write(pos1);
    }
    else if (data == "*look left#" || data == "*Look left#" || data == "*30#" || data == "look left" || data == "Look left") {
        for (pos1 = 90; pos1 <=180; pos1++)
        head.write(pos1);
    }
    else if (data == "*10#" || data == "*look forward#" || data == "*Look forward#" || data == "look forward" || data == "Look forward") {
        for (pos1 =0; pos1 <=90; pos1++){
        head.write(pos1);
      }
    }
    else if (data == "Left hand up" || data == "*13#" || data == "left hand up" || data == "c") {
        for (pos = 100; pos >= 0; pos--)
        left.write(pos);
    }
    else if (data == "*31#" || data == "left hand down" || data == "Left hand down" || data == "f") {
        for (pos = 0; pos <= 100; pos++)
        left.write(pos);
    }
    else if (data == "*21#" || data == "right hand up" || data == "Right hand up" || data == "e") {
        for (pos = 100; pos >= 0; pos--)
        right.write(pos);
    }
    else if (data == "*12#" || data == "a" || data == "Right hand down" || data == "right hand down") {
        for (pos = 0; pos <= 100; pos++)
        right.write(pos);
    }
    else if (data == "both hands up" || data == "Both hands up" || data == "*14#" || data == "b") {
         for (pos = 100; pos >= 0; pos--)
         right.write(pos);
         for (pos = 100; pos >= 0; pos--)
         left.write(pos);
    }
     else if (data == "both hands down" || data == "Both hands down" || data == "41" || data == "g") {
        for (pos = 0; pos <= 100; pos++)
        right.write(pos);
        for (pos = 0; pos <= 100; pos++)
        left.write(pos);
    }
        else if (data == "41" || data == "j" || data == "open mouth" || data == "mouth open") {
        for (pos = 0; pos <=60; pos++)
        mouth.write(pos);
    }
        else if (data == "*12#" || data == "k" || data == "close mouth" || data == "mouth close") {
        for (pos = 60; pos >=0; pos--)
        mouth.write(pos);
    }
    else {
      Serial.println("give a proper voice command");
    }
    robotforward();
    Serial.println("robotforward");
    Serial.println("Inside Serial");
  }
  else {
    Serial.println("Outside Serial");
    // robotforward();
    //Serial.println("forward");
    if (data == "*1#" || x == 1) {
      robotforward();
      distance = sending();
      Serial.println(distance);
      if (distance < 30) {
        robotstop();
        delay(300);
      }
      Serial.println("Robot  full speed");
      delay(50);
    }
    else if (data == "*6#" || x == 6) {
      analogWrite(motorleftenb, 180);
      analogWrite(motorrightenb, 180);
      robotforward();
      distance = sending();
      Serial.println(distance);
      if (distance < 30) {
        robotstop();
        delay(300);
      }
      Serial.println("Robot  medium speed");
      delay(50);
    }
    else if (data == "*5#" || x == 5) {
      analogWrite(motorleftenb, 120);
      analogWrite(motorrightenb, 120);
      robotforward();
      distance = sending();
      Serial.println(distance);
      if (distance < 30) {
        robotstop();
        delay(300);
      }
      Serial.println("Robot  slow running");
      delay(50);
    }
    else if (data == "*2#" || x == 2) {
      robotbackward(); 
      Serial.println("Robot Backward");
      delay(50);
    }
  }

}

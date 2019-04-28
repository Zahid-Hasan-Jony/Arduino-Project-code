#include <AFMotor.h>
//#define Button 7
AF_DCMotor Motor_A(1); // set up motors.MOTOR12_1KHZ
AF_DCMotor Motor_B(2);
AF_DCMotor Motor_C(3);
  int flameSensorPin = A0;
  int flameSensorReading; 
  int pinDevice1 = 9;
  int pinDevice2 = 10;
  int x;
  String data;

void setup() {
    Serial.begin(9600);
    Motor_A.setSpeed(200);
    Motor_B.setSpeed(200);
    Motor_C.setSpeed(200);
    pinMode(pinDevice1, OUTPUT);
    pinMode(pinDevice2, OUTPUT);
    //pinMode(Button, INPUT);
}
void sensor(){
   while(flameSensorReading<100) {    
          Motor_C.run(FORWARD);
          Motor_A.run(RELEASE);
          Motor_B.run(RELEASE);
          digitalWrite(pinDevice1,HIGH);
          digitalWrite(pinDevice2,LOW);
        break;
        }
}
    void AutoForward() {
               flameSensorReading = analogRead(flameSensorPin); 
         Serial.print("Analog reading = ");
         Serial.println(flameSensorReading);
         delay (200);
         
          Motor_A.run(FORWARD);
          Motor_B.run(FORWARD);
          Motor_C.run(RELEASE);
         digitalWrite(pinDevice1,LOW);
         digitalWrite(pinDevice2,HIGH);
 
    }
void loop() {
         flameSensorReading = analogRead(flameSensorPin); 
         Serial.print("Analog reading = ");
         Serial.println(flameSensorReading);
         delay (200);
     /*    if(digitalRead(7)==HIGH){
          x=7;}*/
         
     if (Serial.available()) {

    data = Serial.readStringUntil('\n');
    Serial.println(data);
    
    if (data == "U" || data == "1") {
        Motor_A.run(FORWARD);
        Motor_B.run(FORWARD);
        Motor_C.run(RELEASE); 
        digitalWrite(pinDevice1,LOW);
       digitalWrite(pinDevice2,HIGH);
        x=1;
        Serial.println("Robot Forward");
               if (flameSensorReading<100){
        digitalWrite(pinDevice1, HIGH);
        digitalWrite(pinDevice2, LOW);
        Motor_A.run(RELEASE);
        Motor_B.run(RELEASE);
        Motor_C.run(FORWARD);
      }
        data = "1";
    }
    else if (data == "2" || data == "D") {
        Motor_A.run(BACKWARD);
        Motor_B.run(BACKWARD);
        Motor_C.run(RELEASE);
        x=2;
        Serial.println("Robot Backward");
        data = "2";
    }
    else if (data == "4" || data == "R") {
        Motor_A.run(FORWARD);
        Motor_B.run(BACKWARD);
      Serial.println("Robotleft");
      delay(800);
        Motor_A.run(FORWARD);
        Motor_B.run(FORWARD);
        Motor_C.run(RELEASE);
        digitalWrite(pinDevice1,LOW);
        digitalWrite(pinDevice2,HIGH);
               if (flameSensorReading<100){
        digitalWrite(pinDevice1, HIGH);
        digitalWrite(pinDevice2, LOW);
        Motor_A.run(RELEASE);
        Motor_B.run(RELEASE);
        Motor_C.run(FORWARD);
      }
    }
    else if (data == "3" || data == "L") {
        Motor_A.run(BACKWARD);
        Motor_B.run(FORWARD);
        Serial.println("Robotright");
        delay(800);
        Motor_A.run(FORWARD);
        Motor_B.run(FORWARD);
        Motor_C.run(RELEASE);
        digitalWrite(pinDevice1,LOW);
        digitalWrite(pinDevice2,HIGH);
        
          if (flameSensorReading<100){
        digitalWrite(pinDevice1, HIGH);
        digitalWrite(pinDevice2, LOW);
        Motor_A.run(RELEASE);
        Motor_B.run(RELEASE);
        Motor_C.run(FORWARD);
      }
    }
    else if (data == "0" || data == "C") {
      Serial.println("Motorstop");
        digitalWrite(pinDevice1,LOW);
        digitalWrite(pinDevice2,LOW);
        x=4;
        Motor_A.run(RELEASE);
        Motor_B.run(RELEASE);
        Motor_C.run(RELEASE);
    }
    else if (data == "6" || data == "e") {
        Motor_C.run(RELEASE);
        Motor_A.run(RELEASE);
        Motor_B.run(RELEASE);
       delay(2000);
        x=3;
    }
        else if (data == "5" || data == "a") {
        Motor_C.run(FORWARD);
        Motor_A.run(RELEASE);
        Motor_B.run(RELEASE);
        x=5;
        Serial.println("pump on");
        digitalWrite(pinDevice1, HIGH);
        digitalWrite(pinDevice2, LOW);
    }
    else {
      Serial.println("give a proper command");
    }
    Serial.println("Inside Serial");
  }
  else {
    Serial.println("Outside Serial");
    if (data == "1" || x == 1) {
         Motor_A.run(FORWARD);
         Motor_B.run(FORWARD);
         Motor_C.run(RELEASE);
         digitalWrite(pinDevice1,LOW);
         digitalWrite(pinDevice2,HIGH);
                  if (flameSensorReading<100){
                                 digitalWrite(pinDevice1, HIGH);
                                 digitalWrite(pinDevice2, LOW);
                                 Motor_A.run(RELEASE);
                                 Motor_B.run(RELEASE);
                                 Motor_C.run(FORWARD);
      }
      Serial.println("Robot running");
    }
    else if (data == "2" || x == 2) {
       Motor_A.run(BACKWARD);
       Motor_B.run(BACKWARD);
       Motor_C.run(RELEASE);
      Serial.println("Robot Backward");
     }
     else if (x==5) {
      Serial.println("pump on");
      Serial.println("Robot stop");
        digitalWrite(pinDevice1, HIGH);
        digitalWrite(pinDevice2, LOW);
        Motor_A.run(RELEASE);
        Motor_B.run(RELEASE);
        Motor_C.run(FORWARD);
    }
     else if (data == "0" || x == 4) {
      Serial.println("Robotstop");
        digitalWrite(pinDevice1,LOW);
        digitalWrite(pinDevice2,LOW);
        Motor_A.run(RELEASE);
        Motor_B.run(RELEASE);
        Motor_C.run(RELEASE);
    }
     else if (x == 3 || x==7) {
     
     for (int i=0;i<=50;i++) {
      
          AutoForward();
          sensor();
          delay(1500);
         
        Motor_A.run(BACKWARD);
        Motor_B.run(FORWARD);
        sensor();
        delay(300);
          
          AutoForward();
          sensor();
          delay(700);
       
        Motor_A.run(BACKWARD);
        Motor_B.run(FORWARD);
        sensor();
        delay(300);

        
          AutoForward();
          sensor();
          delay(1500);
         
       Motor_A.run(FORWARD);
       Motor_B.run(BACKWARD);
       sensor();
      delay(300);

          AutoForward();
          sensor();
          delay(700);

       Motor_A.run(FORWARD);
       Motor_B.run(BACKWARD);
       sensor();
      delay(300);}
      
    }
  }
}

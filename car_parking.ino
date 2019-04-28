#include <LiquidCrystal.h>
#include <Servo.h>
#define Trig A0
#define Echo A1
Servo servo;
LiquidCrystal lcd (13,12,11,10,9,8);
int ir[4]={2,3,4,5};
int obstacle[4]={1,1,1,1};

long duration;
int distance,k=0;

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  
  lcd.clear();
  lcd.print(" S&S Car Parking");
  servo.attach(7);
  delay(2000);
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  for(int i=0;i<4;i++){
  pinMode(ir[i],INPUT);}
lcd.clear ();
}
float Sonar(){
 digitalWrite(Trig, LOW);
delayMicroseconds(2);
digitalWrite(Trig, HIGH);
delayMicroseconds(10);
digitalWrite(Trig, LOW);
duration = pulseIn(Echo, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);
return distance;
}
 

void loop(){
 for (int j=0;j<4;j++){
  obstacle[j]=digitalRead(ir[j]);  
  Serial.println(obstacle[j]);
 }

  if (obstacle[0]==1){
  lcd.setCursor(0,0);
  lcd.print("1 Empty");
  }
  else{  
  lcd.setCursor(0,0);
  lcd.print("Blocked");
  }
  
  if (obstacle[1]==1){
  lcd.setCursor(8,0);
  lcd.print("2 Empty");
  }
  else{  
  lcd.setCursor(8,0);
  lcd.print("Blocked");
  }
  
  if (obstacle[2]==1){
  lcd.setCursor(0,1);
  lcd.print("3 Empty");
  }
  else{  
  lcd.setCursor(0,1);
  lcd.print("Blocked");
  }
  
  if (obstacle[3]==1){
  lcd.setCursor(8,1);
  lcd.print("4 Empty");
  }
  else{  
  lcd.setCursor(8,1);
  lcd.print("Blocked");
  }
  delay(50);
  
  int S=Sonar();
  int k=90;
  while (S<10 && ( obstacle[0]==1 || obstacle[1]==1 || obstacle[2]==1 || obstacle[3]==1))
  {
    k=0;
    Serial.print("loop");
    servo.write(k);
    delay(4000);
    int S=Sonar();
    if(S>10) break;
    }
    servo.write(k);
   }

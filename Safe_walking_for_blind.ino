
#define trigPin  A0  
#define echoPin  A1  
int value1=83;
int value2=90;
int buzzervcc=11;
float search(void)
  {
    float duration = 0.00;                // Float type variable declaration 
    float CM = 0.00; 
            
      digitalWrite(trigPin, LOW);        // Trig_pin output as OV (Logic Low-Level) 
      delayMicroseconds(2);              // Delay for 2 us
    
      //Send 10us High Pulse to Ultra-Sonic Sonar Sensor "trigPin" 
      digitalWrite(trigPin, HIGH);       // Trig_pin output as 5V (Logic High-Level)
      delayMicroseconds(10);             // Delay for 10 us 
    
      digitalWrite(trigPin, LOW);        // Trig_pin output as OV (Logic Low-Level)  
    duration = pulseIn(echoPin, HIGH); // Start counting time, upto again "echoPin" back to Logical "High-Level" and puting the "time" into a variable called "duration" 
    CM = (duration / 58.82); //Convert distance into CM. 
    
   return CM;
  }
 
void setup() {
     Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT); 
    pinMode(buzzervcc,OUTPUT);
}
void loop() { 
  
  float cm=search();

  if(cm<value1){
    
       digitalWrite(buzzervcc,LOW);
       Serial.print("You are in safe zone.There is no hole. distance is--");
       Serial.println(cm);
       delay(300);
   }
   else if(cm>value1 && cm<value2){
    
        Serial.print("Please be cureful. The distance is--");
        Serial.println(cm);
        delay(300);
        digitalWrite(buzzervcc,HIGH);
        delay(200);
        digitalWrite(buzzervcc,LOW);
        delay(200);
        digitalWrite(buzzervcc,HIGH);
        delay(200);
        digitalWrite(buzzervcc,LOW);
        delay(200);
        digitalWrite(buzzervcc,HIGH);
        delay(200);
        digitalWrite(buzzervcc,LOW);
        delay(200);
        digitalWrite(buzzervcc,HIGH);
   }
   else{
       
       digitalWrite(buzzervcc,HIGH);
       Serial.print("There is a hole in front of you.");
       Serial.println(cm);
       delay(300);
    }
}

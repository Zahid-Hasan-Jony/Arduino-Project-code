int trig = 12;
int echo = 13;
const int PWMERPin = 10;
const int PWMELPin = 9; 
const int L1Pin = 7;
const int L2Pin = 6;
const int L3Pin = 5;
const int L4Pin = 4;

int motorRF()
  {
    digitalWrite(L1Pin,HIGH);
    digitalWrite(L2Pin,LOW);
}
int motorRB()
  {
    digitalWrite(L1Pin,LOW);
    digitalWrite(L2Pin,HIGH);
}
int motorRS()
  {
    digitalWrite(L1Pin,LOW);
    digitalWrite(L2Pin,LOW);
}
int motorLF()
  {
    digitalWrite(L3Pin,HIGH);
    digitalWrite(L4Pin,LOW);
}
int motorLB()
  {
    digitalWrite(L3Pin,LOW);
    digitalWrite(L4Pin,HIGH);
}
int motorLS()
  {
    digitalWrite(L3Pin,LOW);
    digitalWrite(L4Pin,LOW);
}
void setup() 
{
   Serial.begin(9600);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT); 
    pinMode(PWMELPin, OUTPUT);
    pinMode(PWMERPin, OUTPUT);
    pinMode(L1Pin, OUTPUT);
    pinMode(L2Pin, OUTPUT);
    pinMode(L3Pin, OUTPUT);
    pinMode(L4Pin, OUTPUT);
    pinMode(11,OUTPUT);
    digitalWrite(11,HIGH);
}

void loop() 
{
     int duration, distance;
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration =pulseIn(echo, HIGH);
  distance = (duration / 58.82);
  Serial.print(distance);
  Serial.println("cm");
  delay(50);
        if(distance>=25)
        {
           motorRF();
           motorLF();
          analogWrite(PWMERPin,200);
          analogWrite(PWMELPin,200);
        }
        else 
        {

           motorRB();
           motorLB();
          analogWrite(PWMERPin,200);
          analogWrite(PWMELPin,200);
          delay(100);
           motorLF();
           motorRS();         
          analogWrite(PWMELPin,200);
        }
}

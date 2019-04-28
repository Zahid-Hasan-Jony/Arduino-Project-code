#define LDRR A0
#define LDRL A1
#define LDRC A2
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
    pinMode(PWMELPin, OUTPUT);
    pinMode(PWMERPin, OUTPUT);
    pinMode(L1Pin, OUTPUT);
    pinMode(L2Pin, OUTPUT);
    pinMode(L3Pin, OUTPUT);
    pinMode(L4Pin, OUTPUT);
}

void loop() 
{
  float valueC=analogRead(LDRC);
  Serial.print("  central LDR= ");
   Serial.print(valueC);
  // delay(150);
  float valueR=analogRead(LDRR);
  Serial.print("  Right LDR= ");
   Serial.print(valueR);
 //  delay(150);
  float valueL=analogRead(LDRL);
  Serial.print("  Left LDR= ");
   Serial.println(valueL);
 // delay(150);
        if(valueC>(valueR+40) && valueC>(valueL+40))
        {
           motorRF();
           motorLF();
          analogWrite(PWMERPin,150);
          analogWrite(PWMELPin,150);
        }
        else if(valueR>(valueC+40) && valueR>(valueL+40))
        {
           motorLS();
           motorRF();         
          analogWrite(PWMERPin,100);
        }
         else if(valueL>(valueC+40) && valueL>(valueR+40))
        {
           motorLF();
           motorRS();
          analogWrite(PWMELPin,100);
        }
        else
        {
          motorLS();
          motorRS();
        }
}

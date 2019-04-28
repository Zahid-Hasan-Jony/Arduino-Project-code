int led=13;
int trig=3;
int echo=2;
int motor=4;
void setup() {
  
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);
  pinMode(motor, OUTPUT);
  digitalWrite(motor,HIGH);

}

void loop() {
    int duration , distance;
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration / 2) / 21.9;
  Serial.print(distance);
  Serial.println("cm");
 delay(50);
 if (distance>33) {
  digitalWrite(motor,LOW);
  digitalWrite(led,HIGH);
  Serial.println("Motor ON");
 }
 else if(distance<6){
  
  digitalWrite(motor,HIGH);
  digitalWrite(led,LOW);
  Serial.println("Motor OFF");
 }

}

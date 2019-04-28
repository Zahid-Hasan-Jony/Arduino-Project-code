int trig = 2;
int echo = 3;
int pin =9;
int trig1 =4;
int echo1 =5;
int pin1 =10;
int ledRed=6;
int ledGreen=7;
void setup() {

  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(pin1, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
}

void loop() {
      digitalWrite(ledRed, LOW);
      digitalWrite(ledGreen, LOW);
  int duration, distance;
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration =pulseIn(echo, HIGH);
  distance = (duration/2)/21.9;
  Serial.print(distance);
  Serial.println("cm");
  delay(50);
  
  int duration1, distance1;
  digitalWrite(trig1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1,LOW);
  duration1 =pulseIn(echo1, HIGH);
  distance1 = (duration1/2)/21.9;
  Serial.println(" ");
  Serial.print(distance1);
  Serial.println("cm");
  delay(50);

  if (distance < 3) {
    tone(pin, 349.23);
  }
  else if ((3 < distance) && (distance < 5)) {
    tone(pin, 369.99);
    digitalWrite(ledRed, HIGH);
  }
   else if ((3 < distance) && (distance < 5)) {
    tone(pin, 369.99);
    digitalWrite(ledRed, HIGH);
  }
   else if ((5 < distance) && (distance < 7)) {
    tone(pin, 392);
    digitalWrite(ledRed, HIGH);
  }
   else if ((7 < distance) && (distance < 9)) {
    tone(pin, 415.3);
  }
   else if ((9 < distance) && (distance < 11)) {
    tone(pin, 440);
    digitalWrite(ledRed, HIGH);
  }
   else if ((11 < distance) && (distance < 13)) {
    tone(pin, 466.16);
    digitalWrite(ledRed, HIGH);
  }
   else if ((13 < distance) && (distance < 15)) {
    tone(pin, 493.88);
    digitalWrite(ledRed, HIGH);
  }
   else if ((15 < distance) && (distance < 18)) {
    tone(pin, 523.25);
  }
  else if ((18 < distance) && (distance < 22)) {
    tone(pin, 554.37);
     digitalWrite(ledRed, HIGH);
  }
   else if ((20 < distance) && (distance < 23)) {
    tone(pin, 587.33);
  }
   else if ((23 < distance) && (distance < 26)) {
    tone(pin, 622.25);
    digitalWrite(ledRed, HIGH);
  }
   else if ((26 < distance) && (distance < 28)) {
    tone(pin, 659.26);
    digitalWrite(ledRed, HIGH);
  }
  else {
    noTone(pin);
  }
    if (distance1 < 3) {
    tone(pin,2217.5);
  }
  else if ((3 < distance1) && (distance1 < 5)) {
    tone(pin1, 1864.7);
    digitalWrite(ledGreen, HIGH);
  }
   else if ((3 < distance1) && (distance1 < 5)) {
    tone(pin1, 1760.0);
    digitalWrite(ledGreen, HIGH);
  }
   else if ((5 < distance1) && (distance1 < 7)) {
    tone(pin1, 1480.0);
  }
   else if ((7 < distance1) && (distance1 < 9)) {
    tone(pin1, 1318.5);
    digitalWrite(ledGreen, HIGH);
  }
   else if ((9 < distance1) && (distance1 < 11)) {
    tone(pin1, 1244.5);
  }
   else if ((11 < distance1) && (distance1 < 13)) {
    tone(pin1, 1661.2);
    digitalWrite(ledGreen, HIGH);
  }
   else if ((13 < distance1) && (distance1 < 15)) {
    tone(pin1, 2793.8);
  }
   else if ((15 < distance1) && (distance1 < 18)) {
    tone(pin1, 1174.7);
    digitalWrite(ledGreen, HIGH);
  } 
  else if ((18 < distance1) && (distance1 < 20)) {
    tone(pin1, 1108.7);
  }
   else if ((20 < distance1) && (distance1 < 23)) {
    tone(pin1, 1046.5);
    digitalWrite(ledGreen, HIGH);
  }
   else if ((23 < distance1) && (distance1 < 26)) {
    tone(pin1, 932.32);
  }
   else if ((26 < distance1) && (distance1 < 28)) {
    tone(pin1, 880.00);
    digitalWrite(ledGreen, HIGH);
  }
   else if ((28 < distance1) && (distance1 < 31)) {
    tone(pin1, 783.99);
    digitalWrite(ledGreen, HIGH);
  }
   else if ((31 < distance1) && (distance1 < 34)) {
    tone(pin1, 739.99);
    digitalWrite(ledGreen, HIGH);
  }
   else if ((34 < distance1) && (distance1 < 37)) {
    tone(pin1, 698.46);
    digitalWrite(ledGreen, HIGH);
  }
  else {
    noTone(pin1);
  }
}

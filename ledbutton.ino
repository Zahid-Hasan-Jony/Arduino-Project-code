#define LED 11
#define BUTTON 10

void setup() {
  pinMode(11, OUTPUT);
  pinMode(10, INPUT);
  Serial.begin(9600);

}

void loop() {
  if (digitalRead(10) == HIGH) {
    digitalWrite(LED, HIGH);
    int  data=digitalRead(10);
    Serial.println(data);
  }
  
  else {
    digitalWrite(LED, LOW);
    int  data=digitalRead(10);
    Serial.println(data);
}
}

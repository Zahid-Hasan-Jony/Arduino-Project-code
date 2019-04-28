#include <SoftwareSerial.h>
SoftwareSerial BT(0, 1); //TX, RX  pins of arduino respetively
String command;
int relay =2;
void setup()
{
 BT.begin(9600);
 Serial.begin(9600);
  pinMode(relay, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, HIGH);
}

void loop() {
  digitalWrite(relay,LOW);
  Serial.println("low");
  delay(5000);
  digitalWrite(relay,HIGH);
  Serial.println("high");
  delay(3000);
 while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  command += c; //build the string.
   
  } 
  if (command.length() > 0) {
    Serial.println(command);
  if(command == "light on" || command == "switch on") //this command will be given as an input to switch on light1
  {
    digitalWrite(2, LOW);
  }
  else if(command == "light off" ||   command == "switch off") //this command will be given as an input to switch off light1 simillarly other commands work
  {
    digitalWrite(2, HIGH);
  }
  else if (command == "lamp on")
  {
    digitalWrite (3, HIGH);
  }
  else if ( command == "lamp off")
 {
   digitalWrite (3, LOW);
 }
  else if (command == "fan on")
 {
   digitalWrite (4, HIGH);
 }
  else if (command == "fan off")
 {
   digitalWrite (4, LOW);
 }
  else if (command == "all on") //using this command you can switch on all devices
 {
   digitalWrite (2, HIGH);
   digitalWrite (3, HIGH);
   digitalWrite (4, HIGH);
 }
  else if (command == "off")//using this command you can switch off all devices
 {
   digitalWrite (2, LOW);
   digitalWrite (3, LOW);
   digitalWrite (4, LOW);
 }
command="";}}
}


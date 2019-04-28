#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#include <SoftwareSerial.h>
float pulse = 0;
float temp = 0;
SoftwareSerial bl(9,10);

// Variables
int pulsePin = A0; 
int blinkPin = 7 ;
int fadePin = 13; 
int fadeRate = 0;


volatile int BPM;
volatile int Signal; 
volatile int IBI = 600; 
volatile boolean Pulse = false; 
volatile boolean QS = false; 

static boolean serialVisual = true; 
volatile int rate[10]; 
volatile unsigned long sampleCounter = 0;
volatile unsigned long lastBeatTime = 0; 
volatile int P = 512; 
volatile int T = 512; 
volatile int thresh = 525; 
volatile int amp = 100; 
volatile boolean firstBeat = true; 
volatile boolean secondBeat = false;

void setup()
{
lcd.begin(20, 4);
pinMode(blinkPin,OUTPUT); 
pinMode(fadePin,OUTPUT); 
Serial.begin(9600);
interruptSetup(); 

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Patient Health");
lcd.setCursor(0,1);
lcd.print("Monitoring ");
lcd.setCursor(0,2);
lcd.print("Done By Adittya");
delay(4000);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Initializing....");
delay(2000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Getting Data....");
bl.begin(9600);
}

// Where the Magic Happens
void loop()
{
serialOutput();
if (QS == true) 
{


fadeRate = 255; 
serialOutputWhenBeatHappens();
QS = false; 
}
ledFadeToBeat();
delay(20); // take a break
read_temp();
}
void ledFadeToBeat()
{
fadeRate -= 15; // set LED fade value
fadeRate = constrain(fadeRate,0,255);
analogWrite(fadePin,fadeRate); 
}
void interruptSetup()
{

TCCR2A = 0x02; 
TCCR2B = 0x06; 
OCR2A = 0X7C;
TIMSK2 = 0x02; 
sei(); 
}
void serialOutput()
{ 
if (serialVisual == true)
{
arduinoSerialMonitorVisual('-', Signal);
}
else
{
sendDataToSerial('S', Signal);
}
}
void serialOutputWhenBeatHappens()
{  
Serial.print("*** Heart-Beat Happened *** ");
Serial.print("BPM: ");
Serial.println(BPM);
}
else
{
sendDataToSerial('B',BPM); 
sendDataToSerial('Q',IBI); 
}
}
void arduinoSerialMonitorVisual(char symbol, int data )
{
const int sensorMin = 0; 
const int sensorMax = 1024;
int sensorReading = data; 
int range = map(sensorReading, sensorMin, sensorMax, 0, 11);

// range value:
switch (range)
{
case 0:
Serial.println(""); 
break;
case 1:
Serial.println("---");
break;
case 2:
Serial.println("------");
break;
case 3:
Serial.println("---------");
break;
case 4:
Serial.println("------------");
break;
case 5:
Serial.println("--------------|-");
break;
case 6:
Serial.println("--------------|---");
break;
case 7:
Serial.println("--------------|-------");
break;
case 8:
Serial.println("--------------|----------");
break;
case 9:
Serial.println("--------------|----------------");
break;
case 10:
Serial.println("--------------|-------------------");
break;
case 11:
Serial.println("--------------|-----------------------");
break;
}
}

void sendDataToSerial(char symbol, int data )
{
Serial.print(symbol);
Serial.println(data);
}
ISR(TIMER2_COMPA_vect)
{
cli(); 
Signal = analogRead(pulsePin); 
sampleCounter += 2; 
int N = sampleCounter - lastBeatTime; 

if(Signal < thresh && N > (IBI/5)*3) 
{
if (Signal < T) 
{
T = Signal;
}
}
if(Signal > thresh && Signal > P)
{ 
P = Signal; 
} 
if (N > 250)
{ 
if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3) )
{
Pulse = true; 
digitalWrite(blinkPin,HIGH); 
IBI = sampleCounter - lastBeatTime; 
lastBeatTime = sampleCounter; 

if(secondBeat)
{ 
secondBeat = false;
for(int i=0; i<=9; i++) 
{
rate[i] = IBI;
}
}
if(firstBeat)
{
firstBeat = false; 
secondBeat = true;
sei();
return;
}
word runningTotal = 0;
for(int i=0; i<=8; i++)
{ 
rate[i] = rate[i+1]; 
runningTotal += rate[i];
}
rate[9] = IBI; 
runningTotal += rate[9]; 
runningTotal /= 10;
BPM = 60000/runningTotal; 
QS = true; 
pulse = BPM;
}
}
if (Signal < thresh && Pulse == true)
{ 
digitalWrite(blinkPin,LOW); 
Pulse = false;
amp = P - T; 
thresh = amp/2 + T; 
P = thresh; 
T = thresh;
}
if (N > 2500)
{ 
thresh = 512;
P = 512; 
T = 512; // set T default
lastBeatTime = sampleCounter; 
firstBeat = true;
secondBeat = false; 
}
sei();
}

void read_temp()
{
int temp_val = analogRead(A1);
float mv = (temp_val/1024.0)*5000;
float cel = mv/10;
temp = (cel*9)/5 + 32;

Serial.print("Temperature:");
Serial.println(temp);
bl.print("BPM is:   ");
bl.println(BPM);
bl.print("Temperature:");
bl.println(temp);
bl.println(" ");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("BPM :");
lcd.setCursor(7,0);
lcd.print(BPM);
lcd.setCursor(0,1);
lcd.print("Temp.:");
lcd.setCursor(7,1);
lcd.print(temp);
lcd.setCursor(13,1);
lcd.print("*F");
delay(2000);
}


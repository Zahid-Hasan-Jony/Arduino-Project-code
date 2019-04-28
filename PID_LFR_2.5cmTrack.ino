#define   inA         2
#define   inB         3
#define   inC         4
#define   inD         7
#define   enA         5
#define   enB         6

int leftBaseSpeed   = 120;
int rightBaseSpeed  = 120;
int maxSpeed        = 160;
long int check;
#define NUM_SENSORS   4
bool flag=true;

int thresholds[NUM_SENSORS] = {700, 700, 700,  700};
//int thresholds[NUM_SENSORS] = {800, 800, 800,  800};
int ledPins[5]              = {8, 9, 10, 11};
int sensorValues[NUM_SENSORS], sValues[NUM_SENSORS], lastSensor;

float kp=4.0;
float kd=3.0;
float ki=0.0;
float prevError;

void setup()
{
  motorInit();
  otherInit();
  
}

void loop()
{
  if (sValues[0]==1 && sValues[3]==1 && (flag) && (sValues[1]==0 || sValues[2]==0))
  { while(1){
    float error=readSensorblack(); 
    lineFollowblack();
    if(sValues[0]==1 && sValues[3]==1) break;
  }
  flag=false;
  }
  else
  lineFollow();
}

void motorInit()
{
  pinMode(inA, OUTPUT);
  pinMode(inB, OUTPUT);
  pinMode(inC, OUTPUT);
  pinMode(inD, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  digitalWrite(inA, HIGH);
  digitalWrite(inB, HIGH);
  digitalWrite(inC, HIGH);
  digitalWrite(inD, HIGH);
}

void otherInit()
{
 for (int i = 0; i < 4; i++) pinMode(ledPins[i], OUTPUT);
  lastSensor = 0;
  prevError = 0;
  Serial.begin(9600);
}


void lineFollow()
{
  float error, delSpeed;
  float P, D,I;
  
  error = readSensor();

  Serial.print("error = ");
  Serial.println(error);
  if (error == 420)
  {
    //wheel(120,120);
    //delay(2);
    wheel(0,0);
    delay(300);
    //If previously left sensor was on the line, turn left
    if (lastSensor == 1){ 
    wheel(-80,80);
    delay(10);
    while(true) {
      error = readSensor();
      if(sValues[2]==1 || sValues[1]==1) break;
      wheel(-80,80);
    }
    wheel(100,-100);
    delay(30);
  }
    //Else if the previously right sensor on the line, turn right
    else if (lastSensor == 2)
    {
    wheel(100,-100);
    delay(10);
    while(true) {
      error = readSensor();
      if(sValues[1]==1 || sValues[2]==1) break;
      wheel(80,-80);
    }
    wheel(-80,80);
    delay(30);
  }
      }
  else if(error==400){
    
    wheel(-80,80);
    delay(300);
    while(true) {
      error = readSensor();
      if(sValues[1]==1 || sValues[2]==1) break;
      wheel(-80,80);
    }
    wheel(80,-90);
    delay(30);
  }
  else
  {
    //Calculate P I D
    P = kp * error;
    I = ki * (I+error);
    D = kd * (error - prevError);
    delSpeed = (P + I + D);

    wheel((leftBaseSpeed - delSpeed), (rightBaseSpeed+ delSpeed));
    if ((error - prevError) != 0) delay(5);
    prevError = error;
  }
}
void lineFollowblack()
{
  float error, delSpeed;
  float P, D,I;
  
  error = readSensorblack();

  Serial.print("error = ");
  Serial.println(error);
  if (error == 420)
  {
    //wheel(120,120);
    //delay(2);
    wheel(0,0);
    delay(300);
    //If previously left sensor was on the line, turn left
    if (lastSensor == 1){ 
    wheel(-100,100);
    delay(10);
    while(true) {
      error = readSensor();
      if(sValues[2]==1 || sValues[1]==1) break;
      wheel(-100,100);
    }
    wheel(100,-100);
    delay(5);
  }
    //Else if the previously right sensor on the line, turn right
    else if (lastSensor == 2)
    {
    wheel(100,-100);
    delay(10);
    while(true) {
      error = readSensor();
      if(sValues[1]==1 || sValues[2]==1) break;
      wheel(100,-100);
    }
    wheel(-100,100);
    delay(5);
  }
      }
  else
  {
    //Calculate P I D
    P = kp * error;
    I = ki * (I+error);
    D = kd * (error - prevError);
    delSpeed = (P + I + D);

    wheel((leftBaseSpeed - delSpeed), (rightBaseSpeed+ delSpeed));
    if ((error - prevError) != 0) delay(5);
    prevError = error;
  }
}

float readSensor()
{
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    sensorValues[i] = analogRead(i);
    Serial.println(sensorValues[i]);
    if (sensorValues[i] < thresholds[i])
    {
      sValues[i] = 1;
     digitalWrite(ledPins[i], HIGH);
      //Serial.print(sValues[i]);
    }
    else
    {
      sValues[i] = 0;
      digitalWrite(ledPins[i], LOW);
      //Serial.print(sValues[i]);
    }
  }
  Serial.println("   ");
  

  float sumS, sumWS;
  float linePos, error;
  sumS = sValues[0] + sValues[1] + sValues[2] + sValues[3];
       Serial.print("sumS = ");
   Serial.println(sumS);
  if (sumS == 0)
  {
    return 420;
  }
else if(sumS==4)
{
  check++;
  if(check>50){
  wheel(0,0);
  while(1);
}
}
 else if (sValues[0]==0 && sValues[3]==1 && (sValues[1]==1 || sValues[2]==1))
  {
    return 400;
  }
  sumWS = (sValues[3] * 4 + sValues[2] * 3 + sValues[1] * 2 + sValues[0] * 1)*10;
     Serial.print("sumWS = ");
   Serial.println(sumWS);
  linePos = (sumWS / sumS);
     Serial.print("linePos = ");
   Serial.println(linePos);
  error = linePos - 25;
  
  if (sValues[3] == 1) lastSensor = 1;
  else if (sValues[0] == 1) lastSensor = 2;
  return error;
}

float readSensorblack()
{
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    sensorValues[i] = analogRead(i);
    Serial.println(sensorValues[i]);
    if (sensorValues[i] > thresholds[i])
    {
      sValues[i] = 1;
     digitalWrite(ledPins[i], HIGH);
      //Serial.print(sValues[i]);
    }
    else
    {
      sValues[i] = 0;
      digitalWrite(ledPins[i], LOW);
      //Serial.print(sValues[i]);
    }
  }
  Serial.println("   ");
  

  float sumS, sumWS;
  float linePos, error;
  sumS = sValues[0] + sValues[1] + sValues[2] + sValues[3];
       Serial.print("sumS = ");
   Serial.println(sumS);
  if (sumS == 0)
  {
    return 420;
  }

  sumWS = (sValues[3] * 4 + sValues[2] * 3 + sValues[1] * 2 + sValues[0] * 1)*10;
     Serial.print("sumWS = ");
   Serial.println(sumWS);
  linePos = (sumWS / sumS);
     Serial.print("linePos = ");
   Serial.println(linePos);
  error = linePos - 25;
  
  if (sValues[3] == 1) lastSensor = 1;
  else if (sValues[0] == 1) lastSensor = 2;
  return error;
}
void wheel(int leftSpeed, int rightSpeed)
{
 
  if ( leftSpeed == 0)
  {
    digitalWrite(inC, HIGH);
    digitalWrite(inD, HIGH);
  }
  if ( leftSpeed > 0)
  {
    digitalWrite(inC, HIGH);
    digitalWrite(inD, LOW);
  }
  else if ( leftSpeed < 0)
  {
    digitalWrite(inC, LOW);
    digitalWrite(inD, HIGH);
  }


  if ( rightSpeed == 0)
  {
    digitalWrite(inA, HIGH);
    digitalWrite(inB, HIGH);
  }
  if ( rightSpeed > 0)
  {
    digitalWrite(inA, HIGH);
    digitalWrite(inB, LOW);
  }
  else if ( rightSpeed < 0)
  {
    digitalWrite(inA, LOW);
    digitalWrite(inB, HIGH);
  }
  if (abs(leftSpeed) > maxSpeed) leftSpeed = maxSpeed;
  if (abs(rightSpeed) > maxSpeed) rightSpeed = maxSpeed;

  analogWrite(enA, abs(rightSpeed)+15);
  analogWrite(enB, abs(leftSpeed));
 Serial.print("rightspeed :");
Serial.println(rightSpeed);
Serial.print("leftspeed :");
Serial.println(leftSpeed);
}

#define   inA         2
#define   inB         3
#define   inC         4
#define   inD         7
#define   enA         5
#define   enB         6

int leftBaseSpeed   = 140;
int rightBaseSpeed  = 140;
int maxSpeed        = 160;
long int check;

#define NUM_SENSORS   5

int thresholds[NUM_SENSORS] = {500, 500, 500,  500, 500};
int ledPins[5]              = {22, 25, 26, 27, 30};
int sensorValues[NUM_SENSORS], sValues[NUM_SENSORS], lastSensor;

float kp  = 12.0;
float kd  = 60.0;
float ki  = 0.0;
float prevError;

void setup()
{
  motorInit();
  otherInit();
}

void loop()
{
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
  for (int i = 0; i < 5; i++) pinMode(ledPins[i], OUTPUT);
  lastSensor = 0;
  prevError = 0;
  Serial.begin(9600);
}


void lineFollow()
{
  double error, delSpeed;
  float P, D,I;
  
  error = readSensor();
  Serial.print("error = ");
  Serial.println(error);
  if (error == 420)
  {
    //If previously left sensor was on the line, turn left
    if (lastSensor == 1) wheel(-130,130);
    //Else if the previously right sensor on the line, turn right
    else if (lastSensor == 2) wheel(130,-130);
  }

  else
  {
    //Calculate P I D
    P = kp * error;
    I = ki * (I+error);
    D = kd * (error - prevError);
    delSpeed = (P + I + D);

    wheel((leftBaseSpeed + delSpeed), (rightBaseSpeed- delSpeed));
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
    if (sensorValues[i] > thresholds[i])
    {
      sValues[i] = 0;
      digitalWrite(ledPins[i], LOW);
      //Serial.print(sValues[i]);
    }
    else
    {
      sValues[i] = 1;
      digitalWrite(ledPins[i], HIGH);
    //  Serial.print(sValues[i]);
    }
  }
  Serial.println("   ");
  

  float sumS, sumWS;
  float linePos, error;
  sumS = sValues[0] + sValues[1] + sValues[2] + sValues[3] + sValues[4];
       Serial.print("sumS = ");
   Serial.println(sumS);
  if (sumS == 5)
  {
    return 420;
  }
else if(sumS==0)
{
  check++;
  if(check>100){
  wheel(0,0);
  while(1);
  }
}
  sumWS = (sValues[0] * 1 + sValues[1] * 2 + sValues[2] * 3 + sValues[3] * 4 + sValues[4] * 5);
     Serial.print("sumWS = ");
   Serial.println(sumWS);
  linePos = (sumWS / sumS);
     Serial.print("linePos = ");
   Serial.println(linePos);
  error = linePos - 3;
  if (sValues[4] == 0) lastSensor = 1;
  else if (sValues[0] == 0) lastSensor = 2;
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

  analogWrite(enA, abs(rightSpeed));
  analogWrite(enB, abs(leftSpeed));
 Serial.print("rightspeed :");
Serial.println(rightSpeed);
Serial.print("leftspeed :");
Serial.println(leftSpeed);
}

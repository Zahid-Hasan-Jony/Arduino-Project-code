const int trigpin = 9;
const int echopin = 8;
#define speedOfSound 350

#define kw 3
#define wdown 20
#define wup 10

#define   inA         2
#define   inB         3
#define   inC         4
#define   inD         7
#define   enA         5
#define   enB         6

int leftBaseSpeed   = 90;
int rightBaseSpeed  = 90;
int maxSpeed        = 170;

#define NUM_SENSORS   6

int thresholds[NUM_SENSORS] = {700, 600, 600,  600, 700, 600};
int ledPins[6]              = {30, 27, 26, 25, 22, 29};
int sensorValues[NUM_SENSORS], sValues[NUM_SENSORS], lastSensor;
float valp,vali,vald;
float kp=6.0;
float kd=5.0;
float ki=5.0;
float prevError;
void setup()
{
  motorInit();

  otherInit();
}
void loop()
{
   valp = analogRead(8);
  kp = map(valp, 0, 1023, 0, 20);
    vali = analogRead(9);
   ki = map(vali, 0, 1023, 0, 20);
   vald = analogRead(10);
  kd = map(vald, 0, 1023, 0, 20);
    Serial.print("P = ");
  Serial.println(kp);
    Serial.print("I = ");
  Serial.println(ki);
    Serial.print("D = ");
  Serial.println(kd);

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

  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  Serial.begin(9600);
}
float readSensor()
{
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    sensorValues[i] =  analogRead(i);
    //    Serial.print(sensorValues[i]);
    delay(1);

    if (sensorValues[i] < thresholds[i])
    {
      sValues[i] = 1;
       digitalWrite(ledPins[i], HIGH);
    }
    else
    {
      sValues[i] = 0;
      digitalWrite(ledPins[i], LOW);
    }
  }
  float error, sumS, sumWS, linePos;

  sumS = sValues[0] + sValues[1] + sValues[2] + sValues[3] + sValues[4];

  if (sumS == 0) {
    return 420;
  }
  
else if(sumS==5)
{
  return 410;
}

else if(sValues[0]==1 && sValues[5]==0 && sValues[2]==1 )
{
  return 400;
}
  sumWS = (sValues[0] * 1 + sValues[1] * 2 + sValues[2] * 3 + sValues[3] * 4 + sValues[4] * 5);
   Serial.print("sumWS = ");
   Serial.println(sumWS);
  linePos = (sumWS / sumS);
     Serial.print("linePos = ");
   Serial.println(linePos);
  error = linePos - 3;

  if (sValues[0] == 1) lastSensor = 1;
  else if (sValues[4] == 1) lastSensor = 2;

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
void lineFollow()
{

  double s, error, delSpeed;
  float P, D, I;
  error = readSensor();
   Serial.print("error = ");
  Serial.println(error);
  if (error == 420)
  {
    wheel(0, 0);
    delay(50);
  //  s = sonar();
    //Serial.print("distance= ");
    //Serial.println(s);
//    if (s < wdown || (s > wdown && s < wup)) a_sonar();
    

    //else
    //{
      
        //error = readSensor();
        if (lastSensor == 1) wheel(-150, 150);
   
        else if (lastSensor == 2) wheel(150, -150);
      
    //}
  }
  else if(error ==410)
  {
    wheel(100,-100);
    delay(200);
  }
  
  else if(error ==400)
  {
    wheel(-100,100);
    delay(350);
  }
  else
  {
        s = sonar();
    Serial.print("distance= ");
    Serial.println(s);
     if ( s < wup && (sValues[2]==1 || sValues[3]==1 || sValues[1]==1)) bridge();
      
      else {
        //Calculate P I D
      
      P = kp * error;
      I = ki * (I+error);
      D = kd * (error - prevError);
      delSpeed = (P + I + D);

      //Setting the motors
      wheel((leftBaseSpeed + delSpeed), (rightBaseSpeed - delSpeed));
      if ((error - prevError) != 0) delay(5);

      prevError = error;
    }
  }
  }


float sonar()
{
  // digitalWrite (trigpin, LOW);
  //delayMicroseconds(2);

  digitalWrite (trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite (trigpin, LOW);
  //delayMicroseconds(10);
  long duration = pulseIn (echopin, HIGH);
  int distance = duration * 0.017;
  //Serial.println (distance );
  if (distance > 100) return 100;
  return distance;
}

/*void a_sonar()
{
  while(1){
    float error = readSensor();
    float sonar_error = 20 - sonar();
    wheel(leftBaseSpeed - sonar_error * kw, rightBaseSpeed + sonar_error * kw);
    if (error != 420)
      break;
  }
}*/
void bridge()
 {
     
      
  double error, delSpeed;
  float P, D, I;

  error = readSensor();
      //Calculate P and D
      P = kp * error;
      I = ki * (I+error);
      D = kd * (error - prevError);
      delSpeed = (P + I + D);

      //Setting the motors
      wheel((140 + delSpeed), (140 - delSpeed));
      if ((error - prevError) != 0) delay(5);

      prevError = error;
     
    }

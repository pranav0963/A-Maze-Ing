#include <Servo.h>
#include <LiquidCrystal.h>
  
Servo servo1; //x-axis
Servo servo2; //y-axis
int joyX = 0; //analog pins
int joyY = 1;
int state;
int flag=0;
int until=1;

int servoVal;

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int trigPin1 = 6;
const int echoPin1 = 2;

const int trigPin2 = 4;
const int echoPin2 = 13;

long duration;
int distance;

void setup() 
{
  servo1.attach(3);
  servo2.attach(5); 
  Serial.begin(9600);

  lcd.begin(16, 2);
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}
  

void loop()
{
  if (Serial.available()>0)
  {
    state=Serial.read();
    flag=0;
    lcd.setCursor(0,0);
    lcd.print(" A-MAZE-ING");
  }  

  if (state == '1')
  {while(until != '0')
    {
      servoVal = analogRead(joyX);
      servoVal = map(servoVal, 0, 1023, 130, 180);
      servo1.write(servoVal);

      servoVal = analogRead(joyY);
      servoVal = map(servoVal, 0, 1023, 130, 180);
      servo2.write(servoVal);
      delay(50);

      if(flag==0)
      {
        Serial.println("NORMAL MODE");
        lcd.setCursor(0, 1);
        lcd.print(" NORMAL MODE ");
        flag=1;
      }

      if (Serial.available()>0)
      {
        until=Serial.read();
      }
    }
    Serial.println("BYE WORLD");
    until = 1;
  }

  else if (state == '2')
  {while(until != '0')
    {
      servoVal = analogRead(joyX);
      servoVal = map(servoVal, 1023, 0, 130, 180);
      servo1.write(servoVal);

      servoVal = analogRead(joyY);
      servoVal = map(servoVal, 1023, 0, 130, 180);
      servo2.write(servoVal);
      delay(50);

      if(flag==0)
      {
        Serial.println("INVERSE MODE");
        flag=1;
        lcd.setCursor(0, 1);
        lcd.print(" INVERSE MODE");
      }

      if (Serial.available()>0)
      {
        until=Serial.read();
      }
    }
    Serial.println("BYE WORLD");
    until = 1;
  }

  else if (state == '3')
  {while(until != '0')
    {
      servoVal = analogRead(joyX);
      servoVal = map(servoVal, 0, 1023, 130, 180);
      servo1.write(servoVal);

      servoVal = analogRead(joyY);
      servoVal = map(servoVal, 0, 1023, 130, 180);
      servo2.write(servoVal);
      delay(1000);

      if(flag==0)
      {
        Serial.println("SLOMO MODE");
        flag=1;
        lcd.setCursor(0, 1);
        lcd.print(" SLOMO MODE  ");
      }

      if (Serial.available()>0)
      {
        until=Serial.read();
      }
    }
    Serial.println("BYE WORLD");
    until = 1;
  }
  
  else if (state == '4')
  {
    while(until != '0')
    { digitalWrite(trigPin1, LOW);
      delayMicroseconds(2);

      digitalWrite(trigPin1, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin1, HIGH);

      duration = pulseIn(echoPin1, HIGH);
      distance = duration*0.034/2;

      Serial.print("Distance: ");
      Serial.println(distance);

      servoVal = map(distance, 0, 30, 130, 170);
      servo1.write(servoVal);

      digitalWrite(trigPin2, LOW);
      delayMicroseconds(2);

      digitalWrite(trigPin2, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin2, HIGH);

      duration = pulseIn(echoPin2, HIGH);
      distance = duration*0.034/2;

      Serial.print("Distance: ");
      Serial.println(distance);

      servoVal = map(distance, 0, 30, 130, 170);
      servo2.write(servoVal);

      delay(400);

      if(flag==0)
      {
        Serial.println("GOD MODE");
        flag=1;
        lcd.setCursor(0, 1);
        lcd.print(" GOD MODE    ");
      }

      if (Serial.available()>0)
      {
        until=Serial.read();
      }
    }
    Serial.println("BYE WORLD");
    until = 1;
  }
}
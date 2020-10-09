/*
  # Face tracking using arduino - Code #
  # Code by Harsh Dethe
  # 09 Sep 2018.
*/

#include<Servo.h>

Servo servoVer; //Vertical Servo
Servo servoHor; //Horizontal Servo

int x;
int y;

int prevX;
int prevY;

void setup()
{
  Serial.begin(9600);
  servoVer.attach(5); //Attach Vertical Servo to Pin 5
  servoHor.attach(6); //Attach Horizontal Servo to Pin 6
  servoVer.write(90);
  servoHor.write(90);
}

void Pos() {
  if(prevX != x || prevY != y)
    
  {
    int servoX = map(x, 700, 0, 40, 140);
    int servoY = map(y, 450, 0, 140, 40);

    servoX = min(servoX, 40);
    servoX = max(servoX, 140);
    servoY = min(servoY, 40);
    servoY = max(servoY, 140);
    
    servoHor.write(servoX);
    servoVer.write(servoY);
  }
}

void Demo() {

  servoHor.write(40);
  delay(100);
  //servoHor.write(140);

  servoVer.write(40);
  }


void loop()
{
  if(Serial.available() > 0)
  {
    if(Serial.read() == 'X')
    {
      x = Serial.parseInt();
      Pos();
      //if(Serial.read() == 'Y')
      //{
      //  y = Serial.parseInt();
      //  Pos();
        //Demo();
      }
    }
    while(Serial.available() > 0)
    {
      Serial.read();
    }
  }
}
  


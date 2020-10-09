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

int panangle = 90;
int tiltangle = 90;

void setup() {
  Serial.begin(9600);
  servoVer.attach(10); //Attach Vertical Servo to Pin 5
  servoHor.attach(9); //Attach Horizontal Servo to Pin 6
  servoVer.write(90);
  servoHor.write(90);
  }

// void Pos() {
//   if(prevX != x || prevY != y)

//   {
    
//     int servoX = map(x, 0, 848, 140, 40);
//     int servoY = map(y, 0, 480, 40, 140);

//     servoX = min(servoX, 40);
//     servoX = max(servoX, 140);
//     servoY = min(servoY, 40);
//     servoY = max(servoY, 140);
    
//     servoHor.write(servoX);
//     servoVer.write(servoY);
//     }
//   }

// void Demo() {

//   servoHor.write(40);
//   delay(100);
//   //servoHor.write(140);

//   servoVer.write(40);
//   }

//     //###############
//     //#my camera size is 848,480
//     //##################
//     //if the face is on the right side of the screen, position x >= 424 then pan_angle -- 
//     //if the face is on the left side (position 0 <= x < 424) then pan_angle ++
//     //
//     //if the face is in the upper part 0 <= y < 240) tilt up tiltangle--
//     //if the face is in the lower part 0 <= y < 240) tilt down tiltangle++
//     //

void Mover() {

    if (0 <= x && x <424) {
      panangle ++;
      Serial.print("panning up: ");
      Serial.println(panangle);
    }
    if (424 <= x && x <848) {
      panangle --;
      Serial.print("panning down: ");
      Serial.println(panangle);      
    }
    if (0 <= y && y < 240) {
      tiltangle --;
      Serial.print("tilting down: ");
      Serial.println(tiltangle);      
    }
    if (0 <= y && y < 240) {
      tiltangle ++;
      Serial.print("tilting up: ");
      Serial.println(tiltangle);      
    }
    //bigger than 40
    panangle = max(panangle, 40);
    //smaller than 140
    panangle = min(panangle, 140);
    tiltangle = max(tiltangle, 40);
    tiltangle = min(tiltangle, 140);    
    servoHor.write(panangle);
    servoVer.write(tiltangle);
    }

void loop() {
  if(Serial.available() > 0)
  {
    if(Serial.read() == 'X')
    {
      x = Serial.parseInt();
      
      if(Serial.read() == 'Y')
      {
        y = Serial.parseInt();
        Mover();
        //Pos();
        //Demo();
      }
    }
    while(Serial.available() > 0)
    {
      // panangle = 90;
      // tiltangle = 90;
      // servoHor.write(panangle);
      // servoVer.write(tiltangle);  
      Serial.read();
      }
    }
  }
  


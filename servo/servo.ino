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

/////////////////
// setup timing
/////////////////
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
//need two time storages to compare to for 2 timers or one of em never gets called
unsigned long previousMillis1 = 0;        
unsigned long previousMillis2 = 0; 
// constants won't change:
//the subscriber timing, as fast as possible?
const long interval1 = 5;
//the pubishe rtimerto reach arou!nd 10Hz
const long interval2 = 100;
////////////////////
/////////////////////

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

// void Find_min_max() {
//determine where camera is pointing to when min and max values are chosen
//   servoHor.write(40);
//   delay(100);
//   //servoHor.write(140);

//   servoVer.write(40);
//   }

//     //###############
//     //#my camera size is 848,480
  /// more like 1024 wide
//     //##################
//     //if the face is on the right side of the screen, position x >= 424 then pan_angle -- 
//     //if the face is on the left side (position 0 <= x < 424) then pan_angle ++
//     //
//     //if the face is in the upper part 0 <= y < 240) tilt up tiltangle--
//     //if the face is in the lower part 0 <= y < 240) tilt down tiltangle++
//     //

void Mover() {
//change in steps of 5 for speed
    if (0 <= x && x < 512) {
      panangle = panangle + 2;
      Serial.print("panning up: ");
      Serial.println(panangle);
    }
    if (512 <= x && x <= 1024 ) {
      panangle = panangle - 2;
      Serial.print("panning down: ");
      Serial.println(panangle);      
    }
    if (0 <= y && y < 240) {
      tiltangle = tiltangle - 2;
      Serial.print("tilting down: ");
      Serial.println(tiltangle);      
    }
    if (240 <= y && y <= 480) {
      tiltangle = tiltangle + 2;
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
  // unsigned long currentMillis = millis();

  // if (currentMillis - previousMillis2 >= interval2) {
  //     // save the last time you blinked the LED
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
          //Find_min_max();
        }
      }
      while(Serial.available() > 0)
       {
      //   // panangle = 90;
      //   // tiltangle = 90;
      //   // servoHor.write(panangle);
      //   // servoVer.write(tiltangle);  
         Serial.read();
         }
      }
    //}
  }
  


// Include NewPing Library-------
#include "NewPing.h"
#include <Servo.h>

// Hook up sensor with Trigger to Arduino Pin 9, Echo to Arduino pin 10
#define TRIGGER_PIN 9
#define ECHO_PIN 10

// Hook up sensor2 with Trigger to Arduino Pin 3, Echo to Arduino pin 5
#define TRIGGER_PIN2 3
#define ECHO_PIN2 5

// Maximum distance for ping (in centimeters).--------
#define MAX_DISTANCE 400

// NewPing setup of pins and maximum distance ----------
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);
float duration, distance, distance2;

//SERVO STUFF---------------
Servo myservo;  // create servo object to control a servo
Servo myservo2;
int pos = 75; //the position the servo will move too when triggered
//BOOLEAN STUFF -------------------------------------------------------
bool inrange;
bool oneinrange;
bool twoinrange;

//-----------------------------------------------------------------------------------------------------------
void setup() {

  Serial.begin(9600); //uhhhhhhh

  myservo.attach(6);  // attaches the servo on pin 6 to the servo object

  myservo.write(10); //resets the servo

  myservo2.attach(11);

  myservo2.write(10);

}

//-----------------------------------------------------------------------------------------------------------

void loop() {

  oneinrange  = false;
  twoinrange = false;
  inrange = false;
  Serial.println("Check number 1");
  check();
  Serial.println("");


  if (inrange == true) //otherwise, tell the servo to move, wait for it, tell it to move back.
  {
    delay(500);
    Serial.println("Check 2");
    check();

    if (inrange = true) {
      Serial.println("Slapping...");
      myservo.write(pos);
      myservo2.write(pos);

      delay(400);

      myservo.write(10);
      myservo2.write(10);
    }

  
  Serial.println("");
  delay(500); //wait to allow everything to finish before doing everything again. This delay essentially sets how quickly the loop loops
  }
}

//-----------------------------------------------------------------------------------------------------------
void check() {

  Serial.println ("checking sensors...");

  // Send ping, get distance in cm
  distance = sonar.ping_cm();
  distance2 = sonar2.ping_cm();

  if (distance >= 40 || distance <= 2) //if nothing is detected in sensor1
  {
    Serial.println("1 nothing detected");
    Serial.print("Distance1 = ");
    Serial.println(distance);
    oneinrange = false;

  }

  else
  {
    Serial.println("1 detected");
    Serial.print("Distance1 = ");
    Serial.println(distance);
    oneinrange = true;
  }

  if (distance2 >= 40 || distance2 <= 2)//if nothing is detected in sensor2
  {
    Serial.println("2 nothing detected");
    Serial.print("Distance2 = ");
    Serial.println(distance2);
    twoinrange = false;

  }

  else
  {
    Serial.println("2 detected");
    Serial.print("Distance2 = ");
    Serial.println(distance2);
    twoinrange = true;
  }

  if (oneinrange == true || twoinrange == true) {

    inrange = true;
  }

  else
  {
    inrange = false;
  }

  Serial.print("In range = ");
  Serial.println(inrange);


}

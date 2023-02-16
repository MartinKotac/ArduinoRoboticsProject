#include <AFMotor.h>     // library for motor shield
#include <Servo.h>       // library for servo motor
#include <NewPing.h>     // library for ultrasonic sensor

const int Trig_Pin = A0;
const int Echo_Pin = A1;
const int Max_Speed = 180;
const int Max_Dist = 250;

NewPing ultra_sonic(Trig_Pin, Echo_Pin, Max_Dist);

AF_DCMotor motor2(2); // initialize motor2 on the M2 ports on the driver shield
AF_DCMotor motor4(4); // initialize motor4 on the M4 ports on the driver shield

Servo myservo;

int distance=250;
int speedSet=0;
boolean goesForward=false;

void setup() {
  myservo.attach(10);
  myservo.write(90);
  delay(2000);
  distance=readDistance();
  delay(100);
  moveForward();
}

void loop() {
  int dist_R = 0;
  int dist_L = 0;
  delay(100);
  
  if(distance<=25){
    moveStop();
    delay(100);

    moveBackward();
    delay(200);

    moveStop();
    delay(100);
    
    dist_R = right_Distance();
    delay(100);
    dist_L = left_Distance();
    delay(100);

    if(dist_R <= dist_L){
      turnLeft();
      moveStop();
    }
    else{
      turnRight();
      moveStop();
    }
  }
  else{
    moveForward();
  }
  distance = readDistance();

}

int left_Distance(){
  myservo.write(160);
  delay(500);
  int dist = readDistance();
  delay(100);
  myservo.write(90);
  return dist;
  delay(100); 
}

int right_Distance(){
  myservo.write(20);
  delay(500);
  int dist = readDistance();
  delay(100);
  myservo.write(90);
  return dist;
  delay(100);
}

int readDistance(){
  int cm = ultra_sonic.ping_cm();
  if(cm<=0){                        // this is done in case when sensor gives -ve value which is absurd
     cm=250;
     }
 return cm;
}

void moveStop() {
  motor2.run(RELEASE);
  motor4.run(RELEASE);
  } 

void moveForward() {
  if(!goesForward){
    goesForward=true;     
    motor2.run(FORWARD);
    motor4.run(FORWARD);     
   for (speedSet = 0; speedSet < Max_Speed; speedSet +=2){ // slowly bring the speed up to avoid loading down the batteries too quickly
    motor2.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
   }
  }
}
void moveBackward() {
    goesForward=false;
    motor2.run(BACKWARD);
    motor4.run(BACKWARD);  
  for (speedSet = 0; speedSet < Max_Speed; speedSet +=2){ // slowly bring the speed up to avoid loading down the batteries too quickly
    motor2.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}

void turnLeft() {
  motor2.run(FORWARD);
  motor4.run(BACKWARD);     
  delay(500);    
  motor2.run(FORWARD);
  motor4.run(FORWARD);
}

void turnRight() {
  motor2.run(BACKWARD);
  motor4.run(FORWARD);     
  delay(500);
  motor2.run(FORWARD);
  motor4.run(FORWARD);
}
  
  
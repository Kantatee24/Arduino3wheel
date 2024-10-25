#include <Servo.h>
#include <PS2X_lib.h>
#include <AFMotor.h>
#define SERVO_PIN 2
/*#define CMD 32
#define CLK 30
#define ATT 28
#define DATA 34*/

Servo servo1;
Servo servo2;

PS2X ps2x;

int error = 0;
byte type = 0;
byte vibrate = 0;

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
int MIN_POS = 87;
int MAX_POS = 180;
int MIN_POS1 = 87;
int MAX_POS1 = 180;
int pos = 90;


void setup() {
  delay(1000);
  Serial.begin(9600);  
  servo1.attach(10);
  servo2.attach(9);

  servo1.write(pos); 
  delay(1000);
  
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  error = ps2x.config_gamepad(33, 35, 31, 37, true, true); /*CLK, CMD, ATT, DATA */
  

  if (error == 0) {
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  }

  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  //Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }
}

void loop()
{
ps2x.read_gamepad(false, false); 
  if(ps2x.Button(PSB_CIRCLE)) {
    Serial.println("Circle");
    }
  else if(ps2x.Button(PSB_CROSS)) { 
    Serial.println("Cross");
     }
  else if(ps2x.Button(PSB_SQUARE)) {
    Serial.println("Square");
    }
  else if(ps2x.Button(PSB_TRIANGLE)) 
    Serial.println("Triangle");
  else if(ps2x.Button(PSB_L1)) {
    Serial.println("L1");
   handleL1();}
  else if(ps2x.Button(PSB_L2)){ 
    Serial.println("L2");
    handleL2();}
  else if(ps2x.Button(PSB_L3)) 
    Serial.println("L3");
  else if(ps2x.Button(PSB_R1)) {
    Serial.println("R1");
    handleR1();
    }
  else if(ps2x.Button(PSB_R2)) { 
    Serial.println("R2");
   handleR2();
    }
  else if(ps2x.Button(PSB_R3)) 
    Serial.println("R3");
  else if(ps2x.Button(PSB_START)) 
    Serial.println("Start");
  else if(ps2x.Button(PSB_SELECT)) 
    Serial.println("Select");
  
else if(ps2x.Button(PSB_PAD_UP))  {
    Serial.println("Up");
    Forward();
  }
 else if(ps2x.Button(PSB_PAD_DOWN)) {
    Serial.println("Down");
    Backward(); }

else if(ps2x.Button(PSB_PAD_LEFT)) {
    Serial.println("Left");
    TL();}


else if(ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.println("Right");
    TR();}
else {
    Stop();
  }
 delay(10); 
}


int x = 200;
void Forward()
{
  motor1.run(BACKWARD);
  motor1.setSpeed(x);
  motor4.run(BACKWARD); //release
  motor4.setSpeed(x);
  motor3.run(FORWARD);
  motor3.setSpeed(x);
  delay(50);
}

void Backward()
{
  motor1.run(FORWARD);
  motor1.setSpeed(x);
  motor4.run(RELEASE);
  motor4.setSpeed(x);
  motor3.run(BACKWARD);
  motor3.setSpeed(x);
  delay(50);
}

void Stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(50);
}

void TL()
{

  motor1.run(BACKWARD);
  motor1.setSpeed(x);
  motor2.run(FORWARD);
  motor2.setSpeed(x);
  motor3.run(BACKWARD);
  motor3.setSpeed(x);
  delay(50);

}



void TR()
{
  motor1.run(FORWARD);
  motor1.setSpeed(x);
  motor2.run(BACKWARD);
  motor2.setSpeed(x);
  motor3.run(FORWARD);
  motor3.setSpeed(x);
  delay(50);
}
//----------------------------------------------------------------

void handleL1() {
  Serial.println("L1");
  pos += 2;
  if (pos > MAX_POS) pos = MAX_POS;
  servo1.write(pos);
  delay(50);
}

void handleR1() {
  Serial.println("R1");
  pos -= 2;
  if (pos < MIN_POS) pos = MIN_POS;
  servo1.write(pos);
  delay(50);
}
void handleL2() {
  Serial.println("L2");
  pos += 2;
  if (pos > MAX_POS1) pos = MAX_POS1;
  servo2.write(pos);
  delay(50);
}

void handleR2() {
  Serial.println("R2");
  pos -= 2;
  if (pos < MIN_POS1) pos = MIN_POS1;
  servo2.write(pos);
  delay(50);
}

//*********************************************//
//                   MINIBOT                   //
//                  SUMOSONIC                  //
//                                             //
// This programs a sumobot with built in line  //
// sensor to avoid lines and stay in a ring.   //
//   It also has an ultrasonic sensor that     //
// tells the bot to bump the target but avoids //
//          the ring if detected.              //
//               Codes by:                     //
//        e-Gizmo Mechatronix Central          //
//         Taft, Manila, Philippines           //
//           http://www.egizmo.com             //
//                May 15,2016                  //
//*********************************************//

// INITIALIZATION:
#include <NewPing.h>

#define LEFT_LINE_SENSOR          5       // Line sensor left 
#define CENTER_LINE_SENSOR        6       // Line sensor center
#define RIGHT_LINE_SENSOR         7       // Line sensor right

#define MOTOR_1_DIRECTION         8       // Motor control HIGH = FWD, LOW = BWD
#define MOTOR_1_SPEED             9       // Speed input
#define MOTOR_2_SPEED            10       // Speed input
#define MOTOR_2_DIRECTION        11       // Motor control HIGH = FWD, LOW = BWD
#define ULTRA_TRIGGER            12       // US ULTRA_TRIGGER pin
#define ULTRA_ECHO                3       // US echo pin 

int MAX_DISTANCE = 100;
NewPing sonar(ULTRA_TRIGGER,ULTRA_ECHO,MAX_DISTANCE); // NewPing setup of pins and maximum DISTANCE.

int speed;
int BUMP_SPEED = 250;              
int SAFE_SPEED = 120;                      // Neutral speed
int STUCK_TIMER = 0;
int TIMER = 10;
int ROTATE_TIME = 5;
int LINER = 0;
int RANDOMIZER = 0;
float DISTANCE;                            // DISTANCE measured by the ultrasonic sensor

// INPUTS AND OUTPUTS
void setup() {                
  Serial.begin(9600);

  // DEFAULT PINS OF THE MOTOR DRIVER (8,9,10,11)
  pinMode(MOTOR_1_DIRECTION, OUTPUT);       // Set all motor driver pins to output
  pinMode(MOTOR_1_SPEED, OUTPUT);
  pinMode(MOTOR_2_SPEED, OUTPUT);
  pinMode(MOTOR_2_DIRECTION, OUTPUT);

  pinMode(LEFT_LINE_SENSOR, INPUT);         // All line sensor pins should be set as input
  pinMode(CENTER_LINE_SENSOR, INPUT);
  pinMode(RIGHT_LINE_SENSOR , INPUT);
}

// MAIN PROGRAM
void loop()  {

  int LINE_SENSE_LEFT =      digitalRead(LEFT_LINE_SENSOR);
  int LINE_SENSE_CENTER =    digitalRead(CENTER_LINE_SENSOR);
  int LINE_SENSE_RIGHT =     digitalRead(RIGHT_LINE_SENSOR);

  delay(10);
  unsigned int uS = sonar.ping();           // Send ping, get ping time in microseconds (uS).
  DISTANCE = sonar.convert_cm(uS);
  Serial.println(DISTANCE);
  // IF ALL SENSORS DETECTS NOTHING
  if((LINE_SENSE_LEFT == 1 || CENTER_LINE_SENSOR == 1) || LINE_SENSE_RIGHT == 1)
  {
    LINER+=1;
  }

  // LOOKING FOR OPPONENT TO BUMP
  while(LINER == 0 && DISTANCE > 15)
  {
    SAFE_DRIVE();
    break;
  }

  // If there is an enemy and there is no line detected
  while((DISTANCE < 15 && DISTANCE > 0) && LINER == 0) 
  {
    CHARGE();
    break;
  }

  // Turn around if line is detected:
  if(LINER >= 1)
  {
    ROTATE();
  }
  LINER = 0;
}

// PRESET FUNCTIONS:
void SAFE_DRIVE()
{    
  digitalWrite(MOTOR_1_DIRECTION, HIGH);
  digitalWrite(MOTOR_2_DIRECTION, HIGH);
  analogWrite(MOTOR_1_SPEED, SAFE_SPEED);    
  analogWrite(MOTOR_2_SPEED, SAFE_SPEED);    
}

void WIGGLE()
{
  digitalWrite(MOTOR_1_DIRECTION,LOW);
  digitalWrite(MOTOR_1_SPEED,HIGH);
  digitalWrite(MOTOR_2_SPEED,HIGH);
  digitalWrite(MOTOR_2_DIRECTION,HIGH);
  delay(200);
  digitalWrite(MOTOR_1_DIRECTION,HIGH);
  digitalWrite(MOTOR_1_SPEED,HIGH);
  digitalWrite(MOTOR_2_SPEED,HIGH);
  digitalWrite(MOTOR_2_DIRECTION,LOW);
  delay(200);
  digitalWrite(MOTOR_1_DIRECTION,LOW);
  digitalWrite(MOTOR_1_SPEED,LOW);
  digitalWrite(MOTOR_2_SPEED,LOW);
  digitalWrite(MOTOR_2_DIRECTION,LOW);
}

// DEFAULT REACTION AFTER TIMER RUNS OUT
void ROTATE() 
{
  digitalWrite(MOTOR_1_DIRECTION,LOW);
  digitalWrite(MOTOR_2_DIRECTION,HIGH);
  digitalWrite(MOTOR_1_SPEED,HIGH);
  digitalWrite(MOTOR_2_SPEED,HIGH);
  delay(300);
}

void RETREAT()
{
  digitalWrite(MOTOR_1_DIRECTION,LOW);
  digitalWrite(MOTOR_2_DIRECTION,LOW);
  for(speed = 100; speed>=0; speed--)
  {
    analogWrite(MOTOR_1_SPEED, speed);    
    analogWrite(MOTOR_2_SPEED, 125);    
    delay(10);    
  }  
  TIMER=10;
}

void STOP()
{
  digitalWrite(MOTOR_1_DIRECTION,HIGH);
  digitalWrite(MOTOR_2_DIRECTION,HIGH);
  analogWrite(MOTOR_1_SPEED,1);
  analogWrite(MOTOR_2_SPEED,1);
  delay(10);
}

void CHARGE()
{
  digitalWrite(MOTOR_1_DIRECTION,HIGH);
  analogWrite(MOTOR_1_SPEED,BUMP_SPEED);
  analogWrite(MOTOR_2_SPEED,BUMP_SPEED);
  digitalWrite(MOTOR_2_DIRECTION,HIGH);
}
// PROGRAM ENDS AND LOOP BACK FOREVER                                                                                                                                                   // PARZ







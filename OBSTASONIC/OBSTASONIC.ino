//*********************************************//
//                   MINIBOT                   //
//                 OBSTASONIC                  //
//                                             //
//  This enables a bot to avoid obstacles and  //
//          may also solve mazes.              //
//               Codes by:                     //
//        e-Gizmo Mechatronix Central          //
//         Taft, Manila, Philippines           //
//           http://www.egizmo.com             //
//                May 15,2016                  //
//*********************************************//

// INITIALIZATION:
#include <NewPing.h>

#define MOTOR_1_DIRECTION         8       // Motor control HIGH = FWD, LOW = BWD
#define MOTOR_1_SPEED             9       // Speed input
#define MOTOR_2_SPEED            10       // Speed input
#define MOTOR_2_DIRECTION        11       // Motor control HIGH = FWD, LOW = BWDD
#define ULTRA_TRIGGER            12       // US ULTRA_TRIGGER pin
#define ULTRA_ECHO                3       // US echo pin 
#define DETECT_RANGE             10       // Detection Range

int MAX_DISTANCE = 100;
NewPing sonar(ULTRA_TRIGGER,ULTRA_ECHO,MAX_DISTANCE); // NewPing setup of pins and maximum DISTANCE.

int SAFE_SPEED = 120;                       // Neutral speed
int STUCK_TIMER = 0;
int TIMER = 0;
int RANDOMIZER = 0;
int speed;

// VARIABLES
int z = 0;
int y = 0;

float DISTANCE;                             // DISTANCE measured by the ultrasonic sensor

// INPUTS AND OUTPUTS
void setup() {                
  Serial.begin(9600);

  // DEFAULT PINS OF THE MOTOR DRIVER (8,9,10,11)
  pinMode(MOTOR_1_DIRECTION, OUTPUT);     
  pinMode(MOTOR_1_SPEED, OUTPUT);
  pinMode(MOTOR_2_SPEED, OUTPUT);
  pinMode(MOTOR_2_DIRECTION, OUTPUT);
}

// MAIN PROGRAM
void loop()  {

  ULTRA_READ_DISTANCE();
  if(DISTANCE > DETECT_RANGE || DISTANCE == 0)
  {
    SAFE_DRIVE();
  }

  // TURN LEFT AFTER THE FIRST DETECTION OF THE SENSOR
  if((z == 0 && DISTANCE <= DETECT_RANGE && DISTANCE != 0) && (y == 0 ))
  {
    REVERSE();
    delay(400);
    z = 1;
  }

  if(z == 1  && TIMER <= 10)
  {

    LEFT_TURN();
    TIMER++;
    STUCK_TIMER++;
    delay(40);

    if(TIMER == 10)
    {
      TIMER = 20;
      y = 1;
      z = 2;
    }
  }

  // TURN RIGHT AFTER THE 2ND DETECTION OF THE SENSOR
  if(DISTANCE != 0 && DISTANCE <= DETECT_RANGE && y == 1)
  {
    y = 2;
  }

  if(y == 2 && TIMER >= 10)
  {

    RIGHT_TURN();
    TIMER++;
    STUCK_TIMER++;
    delay(40);

    if(TIMER == 30)
    {
      TIMER = 0;
      y = 0;
      z = 0;
    }
  }

// IF THE BOT IS STUCK IN A CERTAIN PLACE
  if(STUCK_TIMER >= 100)
  {
    STUCK_TIMER = 0;
    REVERSE();
    delay(200);
    ROTATE();
    delay(300);
  }
}

// PRESET FUNCTIONS:
void ULTRA_READ_DISTANCE()
{
  delay(10);
  unsigned int uS = sonar.ping();         // Send ping, get ping time in microseconds (uS).
  DISTANCE = sonar.convert_cm(uS);
  Serial.println(DISTANCE); 
}

void SAFE_DRIVE()
{    
  digitalWrite(MOTOR_1_DIRECTION, HIGH);
  digitalWrite(MOTOR_2_DIRECTION, HIGH);
  analogWrite(MOTOR_1_SPEED, SAFE_SPEED);    
  analogWrite(MOTOR_2_SPEED, SAFE_SPEED);   
}

// DEFAULT REACTION AFTER TIMER RUNS OUT
void ROTATE()
{
  digitalWrite(MOTOR_1_DIRECTION,LOW);
  digitalWrite(MOTOR_2_DIRECTION,HIGH);
  digitalWrite(MOTOR_1_SPEED,SAFE_SPEED);
  digitalWrite(MOTOR_2_SPEED,SAFE_SPEED);
}

void LEFT_TURN()
{     
  digitalWrite(MOTOR_1_DIRECTION,HIGH);
  digitalWrite(MOTOR_2_DIRECTION,HIGH);
  analogWrite(MOTOR_1_SPEED,30);
  analogWrite(MOTOR_2_SPEED,SAFE_SPEED+50);
}

void RIGHT_TURN()
{
  digitalWrite(MOTOR_1_DIRECTION,HIGH);
  digitalWrite(MOTOR_2_DIRECTION,HIGH);
  analogWrite(MOTOR_1_SPEED,SAFE_SPEED+50);
  analogWrite(MOTOR_2_SPEED,30);
}

void REVERSE()
{
  digitalWrite(MOTOR_1_DIRECTION,LOW);
  digitalWrite(MOTOR_2_DIRECTION,LOW);
  analogWrite(MOTOR_1_SPEED,SAFE_SPEED);
  analogWrite(MOTOR_2_SPEED,SAFE_SPEED);
}
// PROGRAM ENDS AND LOOP BACK FOREVER                                                                                                                                                   // PARZ










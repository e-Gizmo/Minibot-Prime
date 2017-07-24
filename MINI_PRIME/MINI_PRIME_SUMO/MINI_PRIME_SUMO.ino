//*********************************************//
//                   MINIBOT                   //
//               MINI_PRIME_SUMO               //
//                                             //
// This programs a sumobot with built in line  //
//  sensor to avoid lines and stay in a ring.  //
//     It also has 3 proximity sensor that     //
// tells the bot to bump the target but avoids //
//          the ring if detected.              //
//               Codes by:                     //
//        e-Gizmo Mechatronix Central          //
//         Taft, Manila, Philippines           //
//           http://www.egizmo.com             //
//                May 15,2016                  //
//*********************************************//

// INITIALIZATION:
#define COMPACT_PROXIMITY_SENSOR_LEFT    2       // compact proximity sensor
#define COMPACT_PROXIMITY_SENSOR_CENTER  3       // compact proximity sensor
#define COMPACT_PROXIMITY_SENSOR_RIGHT   4       // compact proximity sensor

#define MOTOR_1_DIRECTION         8       // Motor control HIGH = FWD, LOW = BWD
#define MOTOR_1_SPEED             9       // Speed input
#define MOTOR_2_SPEED            10       // Speed input
#define MOTOR_2_DIRECTION        11       // Motor control HIGH = FWD, LOW = BWD

#define LEFT_LINE_SENSOR          5       // Line sensor left 
#define CENTER_LINE_SENSOR        6       // Line sensor center
#define RIGHT_LINE_SENSOR         7       // Line sensor right

// VARIABLES
int speed;
int BUMP_SPEED_LEFT = 120;                // bump the opponent speed
int BUMP_SPEED_CENTER = 255;              // bump the opponent speed
int BUMP_SPEED_RIGHT = 120;               // bump the opponent speed
int ROTATE_SPEED = 200;
int SAFE_SPEED = 110;                      // Neutral speed
int PAUSE = 200;
int TIMER = 10;
int LINER = 0;

// INPUTS AND OUTPUTS
void setup() {
  Serial.begin(9600);

  // DEFAULT PINS OF THE MOTOR DRIVER (8,9,10,11)
  pinMode(MOTOR_1_DIRECTION, OUTPUT);
  pinMode(MOTOR_1_SPEED, OUTPUT);
  pinMode(MOTOR_2_SPEED, OUTPUT);
  pinMode(MOTOR_2_DIRECTION, OUTPUT);

  pinMode(LEFT_LINE_SENSOR, INPUT);
  pinMode(CENTER_LINE_SENSOR, INPUT);
  pinMode(RIGHT_LINE_SENSOR, INPUT);

  pinMode(COMPACT_PROXIMITY_SENSOR_LEFT, INPUT);
  pinMode(COMPACT_PROXIMITY_SENSOR_CENTER, INPUT);
  pinMode(COMPACT_PROXIMITY_SENSOR_RIGHT, INPUT);

  digitalWrite(COMPACT_PROXIMITY_SENSOR_LEFT, HIGH);
  digitalWrite(COMPACT_PROXIMITY_SENSOR_CENTER, HIGH);
  digitalWrite(COMPACT_PROXIMITY_SENSOR_RIGHT, HIGH);
}
// MAIN PROGRAM
void loop()
{
  int LINE_SENSE_LEFT =      digitalRead(LEFT_LINE_SENSOR);
  int LINE_SENSE_CENTER =    digitalRead(CENTER_LINE_SENSOR);
  int LINE_SENSE_RIGHT =     digitalRead(RIGHT_LINE_SENSOR);

  int PROXIMITY_SENSE_LEFT = digitalRead(COMPACT_PROXIMITY_SENSOR_LEFT);
  int PROXIMITY_SENSE_CENTER = digitalRead(COMPACT_PROXIMITY_SENSOR_CENTER);
  int PROXIMITY_SENSE_RIGHT = digitalRead(COMPACT_PROXIMITY_SENSOR_RIGHT);

  // IF THERE IS AN OPPONENT,BUMP IT
  if (PROXIMITY_SENSE_CENTER == 1)
  {
    BUMP_THE_OPPONENTS_ON_CENTER();
    delay(PAUSE);
  }
  if (PROXIMITY_SENSE_LEFT == 1 )
  {
    BUMP_THE_OPPONENTS_ON_LEFT();
    delay(PAUSE);
  }
  if (PROXIMITY_SENSE_RIGHT == 1 )
  {
    BUMP_THE_OPPONENTS_ON_RIGHT();
    delay(PAUSE);
  }

  if ((LINE_SENSE_LEFT == 1 || LINE_SENSE_CENTER == 1) || LINE_SENSE_RIGHT == 1)
  {
    LINER += 1;
  }
  // IF ALL SENSORS DETECTS NOTHING
  if (PROXIMITY_SENSE_LEFT == 0 && PROXIMITY_SENSE_CENTER == 0 && PROXIMITY_SENSE_RIGHT == 0 && LINER == 0)
  {
    SAFE_DRIVE();
  }

  if (PROXIMITY_SENSE_LEFT == 0 && PROXIMITY_SENSE_CENTER == 0 && PROXIMITY_SENSE_RIGHT == 0 && LINER == 1)
  {
    ROTATE();
    LINER = 0;
  }
}

// PRESET FUNCTIONS
void SAFE_DRIVE()
{
  digitalWrite(MOTOR_1_DIRECTION, HIGH);
  digitalWrite(MOTOR_2_DIRECTION, HIGH);

  analogWrite(MOTOR_1_SPEED, SAFE_SPEED);
  analogWrite(MOTOR_2_SPEED, SAFE_SPEED);
  delay(100);
  TIMER--;
}
// FEEL FREE TO USE THIS FUNCTION FOR FUN
void WIGGLE()
{
  digitalWrite(MOTOR_1_DIRECTION, LOW);
  digitalWrite(MOTOR_1_SPEED, HIGH);
  digitalWrite(MOTOR_2_SPEED, HIGH);
  digitalWrite(MOTOR_2_DIRECTION, HIGH);
  delay(200);
  digitalWrite(MOTOR_1_DIRECTION, HIGH);
  digitalWrite(MOTOR_1_SPEED, HIGH);
  digitalWrite(MOTOR_2_SPEED, HIGH);
  digitalWrite(MOTOR_2_DIRECTION, LOW);
  delay(200);
  digitalWrite(MOTOR_1_DIRECTION, LOW);
  digitalWrite(MOTOR_1_SPEED, LOW);
  digitalWrite(MOTOR_2_SPEED, LOW);
  digitalWrite(MOTOR_2_DIRECTION, LOW);

}

void ROTATE()
{
  digitalWrite(MOTOR_1_DIRECTION, LOW);
  digitalWrite(MOTOR_2_DIRECTION, HIGH);
  analogWrite(MOTOR_1_SPEED, ROTATE_SPEED);
  analogWrite(MOTOR_2_SPEED, ROTATE_SPEED);
  delay(100);
}

void RETREAT()
{
  digitalWrite(MOTOR_1_DIRECTION, LOW);
  digitalWrite(MOTOR_2_DIRECTION, LOW);

  for (speed = 100; speed >= 0; speed--)
  {
    analogWrite(MOTOR_1_SPEED, speed);
    analogWrite(MOTOR_2_SPEED, 100);
    delay(10);
  }
  TIMER = 10;
}

void STOP()
{
  digitalWrite(MOTOR_1_DIRECTION, HIGH);
  digitalWrite(MOTOR_2_DIRECTION, HIGH);
  analogWrite(MOTOR_1_SPEED, 1);
  analogWrite(MOTOR_2_SPEED, 1);
  delay(10);
}

void BUMP_THE_OPPONENTS_ON_LEFT()
{
  digitalWrite(MOTOR_1_DIRECTION, LOW);
  analogWrite(MOTOR_1_SPEED, BUMP_SPEED_LEFT);
  analogWrite(MOTOR_2_SPEED, BUMP_SPEED_LEFT);
  digitalWrite(MOTOR_2_DIRECTION, HIGH);
}

void BUMP_THE_OPPONENTS_ON_CENTER()
{
  digitalWrite(MOTOR_1_DIRECTION, HIGH);
  analogWrite(MOTOR_1_SPEED, BUMP_SPEED_CENTER);
  analogWrite(MOTOR_2_SPEED, BUMP_SPEED_CENTER);
  digitalWrite(MOTOR_2_DIRECTION, HIGH);
}

void BUMP_THE_OPPONENTS_ON_RIGHT()
{
  digitalWrite(MOTOR_1_DIRECTION, HIGH);
  analogWrite(MOTOR_1_SPEED, BUMP_SPEED_RIGHT);
  analogWrite(MOTOR_2_SPEED, BUMP_SPEED_RIGHT);
  digitalWrite(MOTOR_2_DIRECTION, LOW);
}
// PROGRAM ENDS AND LOOP BACK FOREVER                                                                                                                                                   // PARZ












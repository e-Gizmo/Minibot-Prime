//*********************************************//
//                   MINIBOT                   //
//               MINI_PRIME_ MAZE              //
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
#define COMPACT_PROXIMITY_SENSOR_LEFT    2       // compact proximity sensor
#define COMPACT_PROXIMITY_SENSOR_CENTER  3       // compact proximity sensor
#define COMPACT_PROXIMITY_SENSOR_RIGHT   4       // compact proximity sensor

#define MOTOR_1_DIRECTION         8       // Motor control HIGH = FWD, LOW = BWD
#define MOTOR_1_SPEED             9       // Speed input
#define MOTOR_2_SPEED            10       // Speed input
#define MOTOR_2_DIRECTION        11       // Motor control HIGH = FWD, LOW = BWD

// VARIABLES
int NORMAL_SPEED = 120;                   // Neutral speed
int TURN_SPEED_HIGH = 120;
int TURN_SPEED_LOW = 20;
int ROTATE_SPEED = 150;
int PAUSE = 200;

// INPUTS AND OUTPUTS
void setup() 
{                
  Serial.begin(9600);

  // DEFAULT PINS OF THE MOTOR DRIVER (8,9,10,11)
  pinMode(MOTOR_1_DIRECTION, OUTPUT);       
  pinMode(MOTOR_1_SPEED, OUTPUT);
  pinMode(MOTOR_2_SPEED, OUTPUT);
  pinMode(MOTOR_2_DIRECTION, OUTPUT);

  pinMode(COMPACT_PROXIMITY_SENSOR_LEFT, INPUT);
  pinMode(COMPACT_PROXIMITY_SENSOR_CENTER, INPUT);
  pinMode(COMPACT_PROXIMITY_SENSOR_RIGHT, INPUT);

  digitalWrite(COMPACT_PROXIMITY_SENSOR_LEFT, HIGH);
  digitalWrite(COMPACT_PROXIMITY_SENSOR_CENTER, HIGH);
  digitalWrite(COMPACT_PROXIMITY_SENSOR_RIGHT, HIGH);
}

// MAIN PROGRAM
void loop()  {
  int PROXIMITY_SENSE_LEFT = digitalRead(COMPACT_PROXIMITY_SENSOR_LEFT);
  int PROXIMITY_SENSE_CENTER = digitalRead(COMPACT_PROXIMITY_SENSOR_CENTER);
  int PROXIMITY_SENSE_RIGHT= digitalRead(COMPACT_PROXIMITY_SENSOR_RIGHT);

  if(PROXIMITY_SENSE_LEFT == 0 && PROXIMITY_SENSE_CENTER == 0 && PROXIMITY_SENSE_RIGHT == 0)
  {
    FORWARD();
  }
  if(PROXIMITY_SENSE_LEFT == 1 && PROXIMITY_SENSE_CENTER == 1 && PROXIMITY_SENSE_RIGHT == 1)
  {
    BACKWARD();
    delay (PAUSE);
    ROTATE();
    delay (PAUSE);
  }
  if(PROXIMITY_SENSE_LEFT == 1)
  {
    RIGHT_TURN();
  } 
  if(PROXIMITY_SENSE_CENTER == 1)
  {
    ROTATE();
  }
  if(PROXIMITY_SENSE_RIGHT == 1)
  {
    LEFT_TURN();
  }
}

// PRESET FUNCTIONS
void FORWARD()
{    
  digitalWrite(MOTOR_1_DIRECTION, HIGH);
  digitalWrite(MOTOR_2_DIRECTION, HIGH);
  analogWrite(MOTOR_1_SPEED, NORMAL_SPEED);    
  analogWrite(MOTOR_2_SPEED, NORMAL_SPEED);    
}

void BACKWARD()
{    
  digitalWrite(MOTOR_1_DIRECTION, LOW);
  digitalWrite(MOTOR_2_DIRECTION, LOW);
  analogWrite(MOTOR_1_SPEED, NORMAL_SPEED);    
  analogWrite(MOTOR_2_SPEED, NORMAL_SPEED);
}

void ROTATE()
{
  digitalWrite(MOTOR_1_DIRECTION,LOW);
  digitalWrite(MOTOR_2_DIRECTION,HIGH);
  analogWrite(MOTOR_1_SPEED,ROTATE_SPEED);
  analogWrite(MOTOR_2_SPEED,ROTATE_SPEED);
}

void STOP()
{
  digitalWrite(MOTOR_1_DIRECTION,HIGH);
  digitalWrite(MOTOR_2_DIRECTION,HIGH);
  analogWrite(MOTOR_1_SPEED,1);
  analogWrite(MOTOR_2_SPEED,1);
}

void LEFT_TURN()
{     
  digitalWrite(MOTOR_1_DIRECTION,HIGH);
  digitalWrite(MOTOR_2_DIRECTION,HIGH);
  analogWrite(MOTOR_1_SPEED,TURN_SPEED_LOW );
  analogWrite(MOTOR_2_SPEED,TURN_SPEED_HIGH);
}

void RIGHT_TURN()
{
  digitalWrite(MOTOR_1_DIRECTION,HIGH);
  digitalWrite(MOTOR_2_DIRECTION,HIGH);
  analogWrite(MOTOR_1_SPEED,TURN_SPEED_HIGH);
  analogWrite(MOTOR_2_SPEED,TURN_SPEED_LOW );
}
// PROGRAM ENDS AND LOOP BACK FOREVER                                                                                                                                                   // PARZ
















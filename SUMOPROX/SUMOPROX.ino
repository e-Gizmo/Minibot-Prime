//*********************************************//
//                   MINIBOT                   //
//                  SUMOPROX                   //
//                                             //
// This programs a sumobot with built in line  //
//  sensor to avoid lines and stay in a ring.  //
//     It also has a proximity sensor that     //
// tells the bot to bump the target but avoids //
//          the ring if detected.              //
//               Codes by:                     //
//        e-Gizmo Mechatronix Central          //
//         Taft, Manila, Philippines           //
//           http://www.egizmo.com             //
//                May 15,2016                  //
//*********************************************//

// INITIALIZATION:
#define COMPACT_PROXIMITY_SENSOR 12       // compact proximity sensor
#define MOTOR_1_DIRECTION         8       // Motor control HIGH = FWD, LOW = BWD
#define MOTOR_1_SPEED             9       // Speed input
#define MOTOR_2_SPEED            10       // Speed input
#define MOTOR_2_DIRECTION        11       // Motor control HIGH = FWD, LOW = BWD

#define LEFT_LINE_SENSOR          5       // Line sensor left 
#define CENTER_LINE_SENSOR        6       // Line sensor center
#define RIGHT_LINE_SENSOR         7       // Line sensor right

// VARIABLES
int speed;
int BUMP_SPEED = 255;              // bump the opponent speed
int SAFE_SPEED = 90;               // Neutral speed
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

  pinMode(COMPACT_PROXIMITY_SENSOR,INPUT);
  digitalWrite(COMPACT_PROXIMITY_SENSOR, HIGH);
}
// MAIN PROGRAM
void loop()  
{
  int LINE_SENSE_LEFT =      digitalRead(LEFT_LINE_SENSOR);
  int LINE_SENSE_CENTER =    digitalRead(CENTER_LINE_SENSOR);
  int LINE_SENSE_RIGHT =     digitalRead(RIGHT_LINE_SENSOR);
  int PROXIMITY_SENSE =      digitalRead(COMPACT_PROXIMITY_SENSOR);

  // IF THERE IS AN OPPONENT,BUMP IT
  if(PROXIMITY_SENSE == 1)
  {
    BUMP_THE_OPPONENTS();
    delay(PAUSE);
    SAFE_DRIVE();
    delay(20);
  }

  if((LINE_SENSE_LEFT == 1 || LINE_SENSE_CENTER == 1) || LINE_SENSE_RIGHT == 1)
  {
    ROTATE();
    delay(PAUSE);
  }
  // IF ALL SENSORS DETECTS NOTHING
  if(PROXIMITY_SENSE == 0 && LINER == 0)
  {
    SAFE_DRIVE();
    delay(PAUSE);
  }

  if(PROXIMITY_SENSE == 0 && LINER == 1)
  {
    ROTATE();
    delay(PAUSE);
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

void ROTATE()    
{
  digitalWrite(MOTOR_1_DIRECTION,LOW);
  digitalWrite(MOTOR_2_DIRECTION,HIGH);
    analogWrite(MOTOR_1_SPEED,150);
    analogWrite(MOTOR_2_SPEED,150);
  delay(100);
}

void RETREAT()
{
  digitalWrite(MOTOR_1_DIRECTION,LOW);
  digitalWrite(MOTOR_2_DIRECTION,LOW);

  for(speed = 120; speed>=0; speed--)
  {
    analogWrite(MOTOR_1_SPEED, speed);    
    analogWrite(MOTOR_2_SPEED, 120);    
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

void BUMP_THE_OPPONENTS()
{
  digitalWrite(MOTOR_1_DIRECTION,HIGH);
  analogWrite(MOTOR_1_SPEED,BUMP_SPEED);
  analogWrite(MOTOR_2_SPEED,BUMP_SPEED);
  digitalWrite(MOTOR_2_DIRECTION,HIGH);
}
// PROGRAM ENDS AND LOOP BACK FOREVER                                                                                                                                                   // PARZ












//*********************************************//
//                   MINIBOT                   //
//                  OBSTAPROX                  //
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
#define COMPACT_PROXIMITY_SENSOR 12       // compact proximity sensor
#define MOTOR_1_DIRECTION         8       // Motor control HIGH = FWD, LOW = BWD
#define MOTOR_1_SPEED             9       // Speed input
#define MOTOR_2_SPEED            10       // Speed input
#define MOTOR_2_DIRECTION        11       // Motor control HIGH = FWD, LOW = BWD

int NORMAL_SPEED = 120;                   // Neutral speed
int TIMER = 0;
int STUCK_TIMER = 0;

// VARIABLES
int z = 0;
int y = 0;

// INPUTS AND OUTPUTS
void setup()
{
  Serial.begin(9600);

  // DEFAULT PINS OF THE MOTOR DRIVER (8,9,10,11)
  pinMode(MOTOR_1_DIRECTION, OUTPUT);
  pinMode(MOTOR_1_SPEED, OUTPUT);
  pinMode(MOTOR_2_SPEED, OUTPUT);
  pinMode(MOTOR_2_DIRECTION, OUTPUT);

  pinMode(COMPACT_PROXIMITY_SENSOR, INPUT);

  digitalWrite(COMPACT_PROXIMITY_SENSOR, HIGH);
}

// MAIN PROGRAM
void loop()  {
  int PROXIMITY_SENSE = digitalRead(COMPACT_PROXIMITY_SENSOR);
  if (PROXIMITY_SENSE == 0)
  {
    FORWARD();
  }

  // TURN LEFT AFTER THE FIRST DETECTION OF THE SENSOR
  if ((z == 0 && PROXIMITY_SENSE == 1) && y == 0)
  {
    STOP();
    delay(200);
    BACKWARD();
    delay(300);
    z = 1;
  }
  if (z == 1  && TIMER <= 10)
  {
    LEFT_TURN();
    TIMER++;
    STUCK_TIMER++;
    delay(80);
    if (TIMER == 10)
    {
      TIMER = 20;
      y = 1;
      z = 2;
    }
  }

  // TURN RIGHT AFTER THE 2ND DETECTION OF THE SENSOR
  if (PROXIMITY_SENSE == 1 && y == 1)
  {
    STOP();
    delay(200);
    BACKWARD();
    delay(300);
    y = 2;
  }
  if (y == 2 && TIMER >= 20)
  {
    RIGHT_TURN();
    TIMER++;
    STUCK_TIMER++;
    delay(80);
    if (TIMER == 30)
    {
      TIMER = 0;
      y = 0;
      z = 0;
    }
  }

  // IF THE BOT IS STUCK IN A CERTAIN PLACE
  if (STUCK_TIMER >= 100)
  {
    STUCK_TIMER = 0;
    STOP();
    delay(500);
    BACKWARD();
    delay(500);
    ROTATE();
    delay(500);
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

// DEFAULT REACTION AFTER TIMER RUNS OUT
void ROTATE()
{
  digitalWrite(MOTOR_1_DIRECTION, LOW);
  digitalWrite(MOTOR_2_DIRECTION, HIGH);
  digitalWrite(MOTOR_1_SPEED, NORMAL_SPEED);
  digitalWrite(MOTOR_2_SPEED, NORMAL_SPEED);
}

void STOP()
{
  digitalWrite(MOTOR_1_DIRECTION, HIGH);
  digitalWrite(MOTOR_2_DIRECTION, HIGH);
  analogWrite(MOTOR_1_SPEED, 1);
  analogWrite(MOTOR_2_SPEED, 1);
  delay(10);
}

void LEFT_TURN()
{
  digitalWrite(MOTOR_1_DIRECTION, HIGH);
  digitalWrite(MOTOR_2_DIRECTION, HIGH);
  analogWrite(MOTOR_1_SPEED, 1);
  analogWrite(MOTOR_2_SPEED, 170);
}

void RIGHT_TURN()
{
  digitalWrite(MOTOR_1_DIRECTION, HIGH);
  digitalWrite(MOTOR_2_DIRECTION, HIGH);
  analogWrite(MOTOR_1_SPEED, 170);
  analogWrite(MOTOR_2_SPEED, 1);
}
// PROGRAM ENDS AND LOOP BACK FOREVER                                                                                                                                                   // PARZ








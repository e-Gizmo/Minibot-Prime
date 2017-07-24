//*********************************************//
//                   MINIBOT                   //
//               MINI_PRIME_LINE               //
//                                             //
// This demo program will  follow a black line //
//  path laid out on a light colored surface   //
//         track width is 15-19mm wide.        //
//                Codes by:                    //
//        e-Gizmo Mechatronix Central          //
//         Taft, Manila, Philippines           //
//           http://www.egizmo.com             //
//                May 15,2016                  //
//*********************************************//

// INITIALIZATION:
#define MOTOR_1_DIRECTION         8       // Motor control HIGH = FWD, LOW = BWD
#define MOTOR_1_SPEED             9       // Speed input
#define MOTOR_2_SPEED            10       // Speed input
#define MOTOR_2_DIRECTION        11       // Motor control HIGH = FWD, LOW = BWD

#define LEFT_LINE_SENSOR          5       // Line sensor left 
#define CENTER_LINE_SENSOR        6       // Line sensor center
#define RIGHT_LINE_SENSOR         7       // Line sensor right

// VARIABLES
long int RTC;
int  LINE_SENSE=0;
int GIVE_UP=0;
int LAST_SENSE;
int RUN_SPEED=120;

// TIMERS
byte  RETRY_DELAY=0;
byte  LED_FLASH=25;

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
  RTC=millis()+10;
}

// MAIN PROGRAM
void loop()                     
{
  // HARDWARE TIMER SERVICE
  if(millis()>=RTC)
  {
    RTC=RTC+10;
    if(RETRY_DELAY>0) RETRY_DELAY--;
    if(LED_FLASH>0)
    {
      LED_FLASH--;
      if(LED_FLASH==0)
      {
        LED_FLASH=25;
        PORTB ^= 0x20;
      }
    }        
  }      

  // READ THE STATUS OF THE LINE SENSOR
  LINE_SENSE=0;
  if(digitalRead(LEFT_LINE_SENSOR)==LOW) LINE_SENSE=1;
  if(digitalRead(CENTER_LINE_SENSOR)==LOW) LINE_SENSE=LINE_SENSE+2;
  if(digitalRead(RIGHT_LINE_SENSOR)==LOW) LINE_SENSE=LINE_SENSE+4;

  // IF NO LINES ARE DETECTED
  if((LINE_SENSE==0) & (RETRY_DELAY==0))
  {
    if(GIVE_UP<10)
    {
      // REVERSE FOR 20MS
      if(LAST_SENSE==1) RUN_BOT(RUN_SPEED*15/10,RUN_SPEED,LOW);
      if(LAST_SENSE==3) RUN_BOT(RUN_SPEED*12/10,RUN_SPEED,LOW);
      if(LAST_SENSE==4) RUN_BOT(RUN_SPEED,RUN_SPEED*15/10,LOW);
      if(LAST_SENSE==6) RUN_BOT(RUN_SPEED,RUN_SPEED*12/10,LOW);
      delay(40);
      GIVE_UP++;
    }
    else
      STOP();
  }
  // IF LINE IS DETECTED
  if(LINE_SENSE!=7)
  {
    LAST_SENSE=LINE_SENSE;
    GIVE_UP=0;
    RETRY_DELAY=50;
  }
  // EXTREME LEFT
  if(LINE_SENSE==6)
  {
    FORWARD();
    analogWrite(MOTOR_1_SPEED, RUN_SPEED);
    analogWrite(MOTOR_2_SPEED, 0);
    delay(50);
  }
  // CENTER LINE
  if((LINE_SENSE==5)|(LINE_SENSE==0))
  {
    RUN_BOT(RUN_SPEED,RUN_SPEED,HIGH);
    delay(50);
  }      
  // TURN LEFT
  if(LINE_SENSE==4)
  {
    STOP();
    FORWARD();
    analogWrite(MOTOR_1_SPEED, RUN_SPEED*12/10);
    delay(50);
  }
  // EXTREME RIGHT
  if(LINE_SENSE==3)
  {
    FORWARD();
    analogWrite(MOTOR_2_SPEED, RUN_SPEED);
    analogWrite(MOTOR_1_SPEED, 0);
    delay(50);
  }
  // TURN RIGHT
  if(LINE_SENSE==1)
  {
    STOP();
    FORWARD();
    analogWrite(MOTOR_2_SPEED, RUN_SPEED*12/10);
    delay(50);
  }
}
// PRESET FUNCTIONS
void RUN_BOT(int spd1,int spd2, boolean direction )
{
  digitalWrite(MOTOR_1_DIRECTION,direction);
  digitalWrite(MOTOR_2_DIRECTION,direction);
  analogWrite(MOTOR_2_SPEED, spd1);
  analogWrite(MOTOR_1_SPEED, spd2); 
}

void FORWARD(void)
{
  digitalWrite(MOTOR_1_DIRECTION,HIGH);
  digitalWrite(MOTOR_2_DIRECTION,HIGH);
}    

void ROTATE_BOT(int speed, boolean direction)
{
  digitalWrite(MOTOR_1_DIRECTION,direction);
  digitalWrite(MOTOR_2_DIRECTION,~direction);
  analogWrite(MOTOR_1_SPEED, speed);
  analogWrite(MOTOR_2_SPEED, speed); 
}

void STOP(void)
{
  analogWrite(MOTOR_1_SPEED, 0);
  analogWrite(MOTOR_2_SPEED, 0); 
}
// PROGRAM ENDS AND LOOP BACK FOREVER                                                                                                                                                   // PARZ

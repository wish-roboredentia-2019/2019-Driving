/*
* @file QuadMotorDriverShield.ino
* @brief QuadMotorDriverShield.ino  Motor control program
*
* Every 2 seconds to control motor positive inversion
*
* @author linfeng(490289303@qq.com)
* @version  V1.0
* @date  2016-4-5
*/
const int E1 = 3; ///<Motor1 Speed
const int E2 = 11;///<Motor2 Speed
const int E3 = 5; ///<Motor3 Speed
const int E4 = 2; ///<Motor4 Speed

const int M1 = 4; ///<Motor1 Direction
const int M2 = 12;///<Motor2 Direction
const int M3 = 8; ///<Motor3 Direction
const int M4 = 7; ///<Motor4 Direction


void M1_advance(char Speed) ///<Motor1 Advance
{
 digitalWrite(M1,HIGH);
 analogWrite(E1,Speed);
}
void M2_advance(char Speed) ///<Motor2 Advance
{
 digitalWrite(M2,HIGH);
 analogWrite(E2,Speed);
}
void M3_advance(char Speed) ///<Motor3 Advance
{
 digitalWrite(M3,HIGH);
 analogWrite(E3,Speed);
}
void M4_advance(char Speed) ///<Motor4 Advance
{
 digitalWrite(M4,HIGH);
 analogWrite(E4,Speed);
}

void M1_back(char Speed) ///<Motor1 Back off
{
 digitalWrite(M1,LOW);
 analogWrite(E1,Speed);
}
void M2_back(char Speed) ///<Motor2 Back off
{
 digitalWrite(M2,LOW);
 analogWrite(E2,Speed);
}
void M3_back(char Speed) ///<Motor3 Back off
{
 digitalWrite(M3,LOW);
 analogWrite(E3,Speed);
}
void M4_back(char Speed) ///<Motor4 Back off
{
 digitalWrite(M4,LOW);
 analogWrite(E4,Speed);
}



void setup() {
  Serial.begin(9600);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);

/**
  for(int i=3;i<9;i++)
    pinMode(i,OUTPUT);
  for(int i=11;i<13;i++)
    pinMode(i,OUTPUT);
    **/
}

void forward(){
   M1_advance(50);
   M2_advance(50);
   M3_advance(50);
   M4_advance(50); 
}
void left(){
  M1_advance(25);
  M2_advance(50);
  M3_advance(25);
  M4_advance(50); 
  
}
void right(){
  M1_advance(50);
  M2_advance(25);
  M3_advance(50);
  M4_advance(50); 
}

void loop() {

/*delay(2000); ///<Delay 2S
M1_back(100);
M2_back(100);
M3_back(100);
M4_back(100);
delay(2000); ///<Delay 2S */
double a3read = analogRead(A3)/204.6;
double a4read = analogRead(A4)/204.6;

if(a3read > 4.0 && a4read > 4.0){
  forward();
}
else if( a3read < 4.0){
    left();
  }
else{
   right ();
  }
  
}

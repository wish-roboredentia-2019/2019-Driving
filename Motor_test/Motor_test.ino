const int E1 = 3; ///<Motor1 Speed
const int E2 = 11;///<Motor2 Speed
const int E3 = 5; ///<Motor3 Speed
const int E4 = 2; ///<Motor4 Speed

const int M1 = 4; ///<Motor1 Direction
const int M2 = 12;///<Motor2 Direction
const int M3 = 8; ///<Motor3 Direction
const int M4 = 7; ///<Motor4 Direction

// set solenoid pin
int solenoidPin = 10;
// for shooting farther away for the smaller cup
bool tallCup = true;
int shootCounter = 0;

const int buttonPin = 9;    // the number of the pushbutton pin
int isObstaclePin = 13;
int isObstacle = HIGH; // HIGH means no obstacle

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(isObstaclePin, INPUT);
  pinMode(solenoidPin, OUTPUT); 

  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
}

void M1_advance(char Speed) ///<Motor1 Advance
{
 digitalWrite(M1,LOW);
 analogWrite(E1,Speed);
}
void M2_advance(char Speed) ///<Motor2 Advance
{
 digitalWrite(M2,LOW);
 analogWrite(E2,Speed);
}
void M3_advance(char Speed) ///<Motor3 Advance
{
 digitalWrite(M3,LOW);
 analogWrite(E3,Speed);
}
void M4_advance(char Speed) ///<Motor4 Advance
{
 digitalWrite(M4,LOW);
 analogWrite(E4,Speed);
}

void M1_back(char Speed) ///<Motor1 Back off
{
 digitalWrite(M1,HIGH);
 analogWrite(E1,Speed);
}
void M2_back(char Speed) ///<Motor2 Back off
{
 digitalWrite(M2,HIGH);
 analogWrite(E2,Speed);
}
void M3_back(char Speed) ///<Motor3 Back off
{
 digitalWrite(M3,HIGH);
 analogWrite(E3,Speed);
}
void M4_back(char Speed) ///<Motor4 Back off
{
 digitalWrite(M4,HIGH);
 analogWrite(E4,Speed);
}

void backward(){
   M1_back(40);
   M2_back(40);
   M3_back(40);
   M4_back(40); 
}

void forward(){
   M1_advance(40);
   M2_advance(40);
   M3_advance(40);
   M4_advance(40); 
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
  M4_advance(25); 
}

void stopDriving(){
    M1_advance(0);
    M2_advance(0);
    M3_advance(0);
    M4_advance(0);
}

void turnLeft90(){
  unsigned long starttime = millis();
  unsigned long endtime = starttime;
  while ((endtime - starttime) <= 1530) // do this loop for up to 1000mS
  {
    Serial.println("Inside right turn90");
    // code here
    M1_back(100);
    M2_advance(100);
    M3_back(100);
    M4_advance(100);
    endtime = millis();
  }

  for (int i = 0; i < 50; i++) {
    Serial.println("Moving forward in right turn90");
    normalDriving();
  }
}

void turnRight90(){
  unsigned long starttime = millis();
  unsigned long endtime = starttime;
  while ((endtime - starttime) <= 1510) // do this loop for up to 1000mS
  {
    Serial.println("Inside right turn90");
    // code here
    M1_advance(100);
    M2_back(100);
    M3_advance(100);
    M4_back(100);
    endtime = millis();
  }

  for (int i = 0; i < 50; i++) {
    Serial.println("Moving forward in right turn90");
    normalDriving();
  }
}

void normalDriving() {
    Serial.println("in Normal driving");
    double a3read = analogRead(A3)/204.6;
    double a4read = analogRead(A4)/204.6;

    if(a3read > 4.0 && a4read > 4.0)
    {
       forward();
    }
    else if(a3read < 4.0)
    {
       left();
    }
    else if (a4read < 4.0)
    {
       right();
    } 
  
}

void driving() {
    Serial.println("in driving");
    double a3read = analogRead(A3)/204.6;
    double a4read = analogRead(A4)/204.6;
    double a1read = analogRead(A1)/204.6;

    double a0read = analogRead(A0)/204.6;
    double a2read = analogRead(A2)/204.6;
    
    Serial.print("a3: ");
    Serial.print(a3read);
    Serial.print(", a4: ");
    Serial.println(a4read);
    //Serial.println("a1:" + a1read);
    
    if (a1read > 4.0)
    {
      turnRight90();
    }
    else if(a3read > 4.0 && a4read > 4.0)
    {
       forward();
    }
    else if(a3read < 4.0)
    {
       left();
    }
    else if (a4read < 4.0)
    {
       right();
    } 
  
}

void shoot() {
  Serial.println("ACTUALLY SHOOTING!!");
  Serial.print(tallCup);
  shootCounter = shootCounter + 1;
  digitalWrite(solenoidPin, HIGH);      //Switch Solenoid ON
  delay(500);                          //Wait
  digitalWrite(solenoidPin, LOW);       //Switch Solenoid OFF
  delay(1000);                          //Wait
}

void loop() {
    /*isObstacle = digitalRead(isObstaclePin);
    double a1read = analogRead(A1)/204.6;

    Serial.print("Shoot counter: ");
    Serial.println(shootCounter);
    
    if ((isObstacle == LOW) && (shootCounter < 5))
    {
      Serial.println("OBSTACLE!!!");
      unsigned long starttime = millis();
      unsigned long endtime = starttime;
      int timer;
      if (tallCup == true)
      {
        timer = 500;
        tallCup = false;
      }
      else
      {
        timer = 30;
        tallCup = true;
      }
      while ((endtime - starttime) <= timer) {
        Serial.println("moving forward after obstacle detection");
        normalDriving();
        endtime = millis();
      }
      Serial.println("delaying for shooting");
      stopDriving();
      delay(1000);
      Serial.println("SHOOT!!!");
      //shoot!! 
      shoot();
      shoot();
      while (a1read < 4) {
        backward();
        a1read = analogRead(A1)/204.6;
      }
      turnLeft90();
    }
    else if ((isObstacle == HIGH) && (shootCounter < 5)) {
       Serial.println("No Obstacle - Driving");
       driving();
    }
    else if (shootCounter >= 5)
    {
      Serial.println("Stop Driving - Shoot Counter reached");
      stopDriving();
    }*/
    //delay(200);

  // button code
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
  //Serial.println(reading);
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  // set the LED:
  if (ledState == LOW)
  {
    Serial.println("program running");
        isObstacle = digitalRead(isObstaclePin);
    double a1read = analogRead(A1)/204.6;

    Serial.print("Shoot counter: ");
    Serial.println(shootCounter);
    Serial.println(isObstacle);
    if ((isObstacle == LOW) && (shootCounter < 15))
    {
      Serial.println("OBSTACLE!!!");
      unsigned long starttime = millis();
      unsigned long endtime = starttime;
      int timer;
      if (tallCup == true)
      {
        timer = 450;
        tallCup = false;
      }
      else
      {
        timer = 10;
        tallCup = true;
      }
      while ((endtime - starttime) <= timer) {
        Serial.println("moving forward after obstacle detection");
        normalDriving();
        endtime = millis();
      }
      Serial.println("delaying for shooting");
      stopDriving();
      delay(1000);
      Serial.println("SHOOT!!!");
      //shoot!! 
      shoot();
      shoot();
      shoot();
      while (a1read < 4) {
        backward();
        a1read = analogRead(A1)/204.6;
      }
      turnLeft90();
    }
    else if ((isObstacle == HIGH) && (shootCounter < 15)) {
       Serial.println("No Obstacle - Driving");
       driving();
    }
    else if (shootCounter >= 15)
    {
      Serial.println("Stop Driving - Shoot Counter reached");
      stopDriving();
    }
  }
  else {
    Serial.println("program stopped");
    stopDriving();
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}

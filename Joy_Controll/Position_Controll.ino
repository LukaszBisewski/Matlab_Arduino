#include <Servo.h>
#define JoyButton   11 
#define LeftServo   8  
#define RightServo  9

String readString;
Servo myservo1;  
Servo myservo2;
int pos1;
int pos2;
int servoVal;           
const int joyH = 0;        
const int joyV = 1;        
int buttonState = 0;
int lastButtonState = 0;

boolean joyTask = false;

void setup() 
{
 Serial.begin(9600);
 myservo1.attach(LeftServo);  
 myservo2.attach(RightServo);
 pinMode(JoyButton, INPUT);
}

void loop() {

  buttonState = digitalRead(JoyButton);
  if (buttonState != lastButtonState) 
  {
    joyTask = !joyTask;
    while(digitalRead(JoyButton) == HIGH){
      }
    if(joyTask){
      digitalWrite(13, HIGH);
    }
    else{
      digitalWrite(13, LOW);
    }
  }
    if (joyTask == true) 
  {
    joystickRead();
  }
  else
  {
    serialRead();
  }
}
void serialRead(){
 while (Serial.available()) 
 {
 delay(10);  
 if (Serial.available() > 0)
 {
   char c = Serial.read();  
   readString += c; 
 }
}
if (readString.length() > 0)
{
  validateInputData();
  
  myservo1.write(pos1); 
  myservo2.write(pos2);
  readString="";
 }
}
void validateInputData()
{
  pos1 = readString.substring(0, read-String.indexOf("|")).toInt();
  pos2 = readString.substring(readString.indexOf("|") + 1, re-adString.length()).toInt();
}
void logInSerial()
{
  Serial.print("pozycja x: ");
  Serial.print(pos1);
  Serial.print(" pozycja y: ");
  Serial.println(pos2);
}
void joystickRead()
{
  servoVal = analogRead(joyH);          
  servoVal = map(servoVal, 0, 1023, 0, 180);     
  myservo2.write(servoVal);                        

  servoVal = analogRead(joyV);           
  servoVal = map(servoVal, 0, 1023, 0, 180);     
  myservo1.write(servoVal);                       
   delay(15);         


#include <Servo.h>

Servo myservo;

int blades=4,ir=5,pos=0,x=10,flag=0,fluct=50;
long presentrpm,prevrpm=0,currenttime=0,revpm=0,prevstate;
void setup() {
  // put your setup code here, to run once:
  pinMode(ir,INPUT);
  Serial.begin(9600);
myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() 
{
  // put your main code here, to run repeatedly:
currenttime=millis();
while((millis()-currenttime)<2000)
{
  prevstate=digitalRead(ir);
  
  if(prevstate!=digitalRead(ir))
  {revpm++;}
}
presentrpm=revpm*30/(2*blades);
Serial.println(presentrpm);
revpm=0;



if(presentrpm-prevrpm>int(fluct/2) or abs(prevrpm-presentrpm)<fluct or presentrpm==0)
{
  pos=pos+x;
  if(pos>=180 or pos<=0)
  {x=-x;}
//  Serial.println(pos);
  myservo.write(pos);
  prevrpm = presentrpm;
}
  else
{
  prevrpm = presentrpm;
  if (!flag)
  {
    x = -x;
    myservo.write(pos+x);
    flag = 1;  
  }
  else 
  {
    x=-x;
     myservo.write(pos+x);
    delay(15000);
    flag = 0;
  }
 // Serial.println(flag);
}
}

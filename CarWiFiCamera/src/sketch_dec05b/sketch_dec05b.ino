#include <Servo.h>    //舵机控制库
#include <DistanceSRF04.h>
DistanceSRF04 Dist;
int distance;
int EN2 = 14;  
int EN3 = 15;
int EN4 = 16;
int EN5 = 17;
int LED1 = 6; 
int LED2 = 7; 
int EA = 3;
int EB = 5;
int val,kkl,lkf;
int lx=90;
//2路舵机
Servo servoX; //云台X轴舵机 左右
Servo servoY; //云台Y轴舵机 上下
int mkk;
///////////////////////////////////////
void ting(void)
        {
          analogWrite(EA,0);
          analogWrite(EB,0); 
          digitalWrite(EN2,LOW);   
          digitalWrite(EN3,LOW);
          digitalWrite(EN4,LOW);   
          digitalWrite(EN5,LOW);       
        }
        
void qian(void)
        { 
          analogWrite(EA,254);//调节参数可调速度（0-255）
          analogWrite(EB,255);//调节参数可调速度（0-255）      
          digitalWrite(EN2,LOW);
          digitalWrite(EN3,HIGH);
          digitalWrite(EN4,LOW);
          digitalWrite(EN5,HIGH);
        }
void hou(void)
        {        
          analogWrite(EA,255);//调节参数可调速度（0-255）
          analogWrite(EB,255); //调节参数可调速度（0-255） 
          digitalWrite(EN2,HIGH);
          digitalWrite(EN3,LOW);
          digitalWrite(EN4,HIGH);
          digitalWrite(EN5,LOW);            
        }
void zuo(void)
        {        
          analogWrite(EA,180);//调节参数可调速度（0-255）
          analogWrite(EB,180); //调节参数可调速度（0-255）
          digitalWrite(EN2,LOW);
          digitalWrite(EN3,HIGH);
          digitalWrite(EN4,HIGH);
          digitalWrite(EN5,LOW);     
        }        
void you(void)
        {        
          analogWrite(EA,180);//调节参数可调速度（0-255）
          analogWrite(EB,180); //调节参数可调速度（0-255）
          digitalWrite(EN2,HIGH);
          digitalWrite(EN3,LOW);
          digitalWrite(EN4,LOW);
          digitalWrite(EN5,HIGH);
          
        }  
//舵机左转
void servo_left()
{
  int servotemp=servoX.read();//获取舵机目前的角度值
  servotemp-=2;//舵机运动1度
  if(servotemp<170&&servotemp>10) //我定义的舵机旋转角度为10度到170度
  servoX.write(servotemp);
  else if (servotemp<=10)  servoX.write(10);
  else servoX.write(170);
}


//舵机右转
void servo_right()
{
  int servotemp=servoX.read();//获取舵机目前的角度值
  servotemp+=2;//舵机运动1度
  if(servotemp<170&&servotemp>10)//我定义的舵机旋转角度为10度到170度
  servoX.write(servotemp);
  else if (servotemp<=10)  servoX.write(10);
  else servoX.write(170);
}


//舵机上转
void servo_up()
{
  int servotemp1=servoY.read();//获取舵机目前的角度值
  servotemp1+=2;//舵机运动1度
  if(servotemp1<170&&servotemp1>10)//我定义的舵机旋转角度为10度到170度
  servoY.write(servotemp1);
  else if (servotemp1<=10)  servoY.write(10);
  else servoY.write(170);
}


//舵机下转
void servo_down()
{
  int servotemp1=servoY.read();//获取舵机目前的角度值
  servotemp1-=2;//舵机运动1度
  if(servotemp1<170&&servotemp1>10)//我定义的舵机旋转角度为10度到170度
  servoY.write(servotemp1);
  else if (servotemp1<=10)  servoY.write(10);
  else servoY.write(170);
}
void setup()
{
  Dist.begin(9,8);
  servoX.attach(10);//水平舵机接10脚
  servoY.attach(11);//上下舵机接11脚
  servoX.write(90);//输出舵机初始位置为90度
  servoY.write(90);//输出舵机初始位置为90度
  pinMode(EN2,OUTPUT);
  pinMode(EN3,OUTPUT);
  pinMode(EN4,OUTPUT);
  pinMode(EN5,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
   for(kkl=0;kkl<50;kkl++)
  {
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
    delay(500);//延时500M秒，
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    delay(500);
  }
Serial.begin(9600);//设置波特率为9600bps
  lkf=0;
}


void loop()
{ 
  distance = Dist.getDistanceCentimeter();
  if(distance<=5 & distance>1)
  {
    hou();
    delay(100);
    ting();
    distance=0;
  } 
  if(Serial.available())
  {
    lkf = Serial.read();
  switch(lkf)
  {
  case 'a':
     qian();
     servoX.write(90);
     lkf=0;  
     break;   
   case 'b':
     hou();
     lkf=0;
     break;     
   case 'c':
     zuo();
     lkf=0;
     break;
   case 'd':
    you();
    lkf=0;
     break; 
   case 'e':
    ting();
    lkf=0;
     break;  
   case 'j': 
     servo_left();
     lkf=0;
     break;
   case 'l': 
     servo_right();
     lkf=0;
     break;
   case 'k': 
    servo_up();
    lkf=0;
    break;
   case 'i':
     servo_down();
     lkf=0;
     break;
  case 'n':
     digitalWrite(LED1,HIGH);
     digitalWrite(LED2,HIGH);
     lkf=0;
     break;
  case 'm':
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    lkf=0;
    break;
    }
  }
 }


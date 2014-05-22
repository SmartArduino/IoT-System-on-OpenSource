#include "Scheduler.h";

boolean flag=false;

void setup()
{
 Serial.begin(115200);
 Sch.init(); 
 Sch.addTask(upload_data,0,2000,1);  
 Sch.addTask(check_cmd,4000,3000,1); 
 
 Sch.start();
}
void loop()
{       
     Sch.dispatchTasks();       
}

String get_res()
{
  String result=serial_read_until("\r\n");
  return result;
 
}

void upload_data()
{
  serial_clear();
  char buf[500];
  memset(buf,0,500);
  if(flag==false){
    return ; 
  }
  int n=analogRead(A0);
  float vol=n*(5.0/1023*100);
  //int t=20+random(-5,5);
  sprintf(buf,"cmd=upload&uid=demo&key=c514c91e4ed341f263e458d44b3bb0a7&sensor_name=arduino&data=");
  Serial.print(buf);
  Serial.println(vol);
  Serial.flush();
  delay(1000);
  String res=get_res();

  
}

String get_cmd()
{
  char buf[500];
  memset(buf,0,500);
  strcpy(buf,"cmd=get&uid=demo&key=c514c91e4ed341f263e458d44b3bb0a7&sensor_name=arduino");
  Serial.println(buf);
  Serial.flush();
  delay(1000);
  String res=get_res();
  return res;
}

void check_cmd()
{
  serial_clear();
  String command=get_cmd();
     if(command.indexOf("end")>=0){
          flag=false;
       //command="";
     }
     
     if(command.indexOf("begin")>=0){
          flag=true;
       //command="";
     }
}






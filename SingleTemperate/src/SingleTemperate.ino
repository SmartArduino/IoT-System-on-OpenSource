void setup()
{
 Serial.begin(115200);
}
void loop()
{
   int n=analogRead(A0);
   float vol=n*(5.0/1023*100);
   upload_sensor(vol);
   delay(5000);
}

void upload_sensor(float vol) 
{ 
     // send the HTTP PUT request: 核心代码
     char buf[200];
     memset(buf,0,200);
     int ret;
     ret=sprintf(buf,"GET /upload.php?uid=demo&key=c514c91e4ed341f263e458d44b3bb0a7&sensor_name=arduino&data=");
     Serial.print(buf); 
     Serial.print(vol);
     Serial.println(" HTTP/1.1");   
     Serial.println("Host: api.iot.fm");
     Serial.println("Connection: close");
     Serial.println(); 
 }







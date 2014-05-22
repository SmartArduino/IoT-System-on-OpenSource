
void serial_clear()
{
  while(Serial.available() > 0)
  {
    Serial.read();
  }
}

String serial_read_until(String flag)
{
  String ret="";
  char res;
  int limit=10;
  while(limit){
        if(Serial.available() > 0){
                res=char(Serial.read());
                ret+=res;                
                if(ret.endsWith(flag)){
			break;
		}
                continue;
         }
         delay(800);
         limit--;
  }
  return ret;
}

String serial_read_length(int length, int timeout)
{
        String ret="";
        long start=millis();
        int i=0;
        while(millis()-start<timeout){
            if(Serial.available() > 0){
              char res=char(Serial.read());
              ret+=res;
              i++;
            }
            if(i==length)
              break;
        }
        return ret;
}

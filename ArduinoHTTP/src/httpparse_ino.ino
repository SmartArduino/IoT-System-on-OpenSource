String get_http_header()
{
  String header=serial_read_until("\r\n\r\n");
  return header;
}

int parse_content_length(String header)
{
        int length=0;
	String tmp;
	String source=header;
	int pos=source.indexOf('\r\n');
	while(pos!=-1){
		tmp=source.substring(0,pos);
                tmp.toLowerCase();
		source=source.substring(pos+1);		
		if(tmp.startsWith("content-length")){
			int pos=tmp.indexOf(':');
                        String len=tmp.substring(pos+1);
                        len.trim();
                        length=len.toInt();
                }
                pos=source.indexOf('\r\n');				
	}
	return length;
}

String get_http_body(int length)
{
        if(!length)
          return "";
        int timeout=1000;
        String body=serial_read_length(length,timeout);
        return body;
}

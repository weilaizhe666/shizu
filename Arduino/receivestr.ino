String str = "";//接收串口字符串值，默认空
boolean lineEnd = false;//是否接收完整，默认否
char type;
int data;//存储数据值

int strToInt(String s)//字符串转数组转数字
{
  char buf[s.length() + 1];
  s.toCharArray(buf,sizeof(buf));
  return atoi(buf);
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  while(Serial.available())//有数据传入
  {
    char c = Serial.read();//读取一个字符
    str += c;//链接成字符串
    if(c == '\n')//读取到'\n'
    {
      lineEnd = true;//读取完毕
    }
  }
  if(lineEnd)
  {
    type = str.charAt(0);//判断是T还是t
    switch(type)
    {
    case 'T':
      //data = strToInt(str.substring(1));
      Serial.print("扩展帧：");
      //Serial.println(data);
      Serial.println(str.substring(1));
      break;
    case 't':
      //data = strToInt(str.substring(1));
      Serial.print("标准帧：");
      //Serial.println(data);
      Serial.println(str.substring(1));
      break;
    case 'V':
      Serial.println("SV2.5-HV2.0");
      break;
    case 'O':
      Serial.println('\r');
      break;
    case 'C':
      Serial.End();
      break;
    default:
      Serial.println('\a');
    }
    lineEnd = false;
    str = "";
  }
  delay(50);
}

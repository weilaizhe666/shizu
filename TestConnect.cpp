const byte LED=13;
char val;

void setup()
{
	pinMode(LED,OUTPUT); //设置引脚为输出
	Serial.begin(9600);  //设置速率
	Serial.println("Welcome to Arduino!");
}

void loop()
{
	if(Serial.available())  //判断已缓存字节数
	{
		val=Serial.read();  //读取第一位字节存入Val
		switch(val)
		{
		case 'V':
		  Serial.println("SV2.5-HV2.0");
		  break;
		case 'O':
		  Serial.println("Open OK");
		  break;
		case 'C':
		  Serial.println("Close OK");
		  break;
		default:
		  Serial.println("Failure\BEL");
		}
	}
}
String inputString = "";
boolean stringComplete = false;
String versionMessage = "SV2.5-HV2.0";
int state = 0;
int canBusSpeed = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  inputString.reserve(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(stringComplete)
  {
    judgeMessage(inputString);
    inputString = "";
    stringComplete = false;
    }
}

//get input
void serialEvent(){
  while(Serial.available())
  {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if(inChar == '\r')
    {
      stringComplete = true;
      }
    }
  }

void judgeMessage(String message){
  //reply version message
  char judgeChar = message.charAt(0);
  int mesLength = message.length();
  if((judgeChar == 'V') && (mesLength == 2))
  {
    replyMessage(1, versionMessage);
    }
  //rely open command
  else if((message.startsWith("O1")) && (mesLength == 3))
  {
    openCommand();
    }
  //reply close command
  else if((judgeChar == 'C') && (mesLength == 2))
  {
    closeCommand();
    }
  //reply speed command
  else if((judgeChar == 'S') && (mesLength == 3))
  {
    speedCommand(int(message.charAt(1)));
    }
  //reply message
  else if(state == 1 && (judgeChar == 't' || judgeChar == 'T'))
  {
    getMessage(message);
    }
  else
  {
    replyMessage(0, "");
    }
  
  }

//reply message
void replyMessage(int x, String message)
{
  if(x == 1)
  {
    message += "\r";
    }
  else
  {
    message += "\BEL";
    }
  int mesLength = message.length();
  for(int i = 0; i < mesLength; i++)
  {
    Serial.write(message.charAt(i));
    }
  }

//open command
void openCommand()
{
  if(state == 0)
  {
    state = 1;
    replyMessage(1, "");
    }
  else
  {
    replyMessage(0, "");
    }
  }

//close command
void closeCommand()
{
  if(state == 1)
  {
    state == 0;
    replyMessage(1, "");
    }
  else
  {
    replyMessage(0, "");
    }
  }

//speed command
void speedCommand(int speedNum)
{
  if(state == 0 && speedNum >= 0 && speedNum <= 8)
  {
    canBusSpeed = speedNum;
    replyMessage(1, "");
    }
  else
  {
    replyMessage(0, "");
    }
  }
//get message
void getMessage(String message){
  int len = message.length();
  int dataLen = 0;
  int idLen = 0;
  int times = 1;
  String cycleJudge = message.substring(len - 5, len);
  if(message[0] == 't')
  {
    dataLen = int(message[4]);
    idLen = 9;
    }
  else
  {
    dataLen = int(message[9]);
    idLen = 14;
    }
  if(dataLen < 0 || dataLen > 8)
  {
    replyMessage(0, "");
    return;
    }
  if(len != dataLen * 2 + idLen)
  {
    replyMessage(0, "");
    return;
    }
  if(cycleJudge != "0000")
  {
   //cycleMessage(message);
    }
  else
  {
    replyMessage(1, "");
    }
  }



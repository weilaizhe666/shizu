String inputString = "";
boolean stringComplete = false;
String versionMsg = "SV2.5-HV2.0";
int state = 0;
int canBusSpeed = 0;
String msgReply = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  inputString.reserve(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(stringComplete)
  {
    judgeMsg(inputString);
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
     delay(2);
    }
  }

void judgeMsg(String message){
  //reply version message
  char judgeChar = message[0];
  int msgLength = message.length();
  if((judgeChar == 'V') /*&& (msgLength == 2)*/)
  {
    msgReply = versionMsg;
    replyMsg(msgReply);
    }
  //rely open command
  else if((message.startsWith("O1")) && (msgLength == 3))
  {
    openCommand();
    }
  //reply close command
  else if((judgeChar == 'C') && (msgLength == 2))
  {
    closeCommand();
    }
  //reply speed command
  else if((judgeChar == 'S') && (msgLength == 3))
  {
    speedCommand((int)message[1]);
    }
  //reply message
  else if(state == 1 && (judgeChar == 't' || judgeChar == 'T'))
  {
    getMsg(message);
    }
  else
  {
    msgReply = "\\BEL";
    replyMsg(msgReply);
    }
  
  }

//reply message
void replyMsg(String message)
{
  int msgLength = message.length();
  for(int i = 0; i < msgLength; i++)
  {
    Serial.write(message[i]);
    }
  }

//open command
void openCommand()
{
  if(state == 0)
  {
    state = 1;
    msgReply = '\r';
    replyMsg(msgReply);
    }
  else
  {
    msgReply = "\\BEL";
    replyMsg(msgReply);
    }
  }

//close command
void closeCommand()
{
  if(state == 1)
  {
    state == 0;
    msgReply = '\r';
    replyMsg(msgReply);
    }
  else
  {
    msgReply = "\\BEL";
    replyMsg(msgReply);
    }
  }

//speed command
void speedCommand(int speedNum)
{
  if(state == 0 && speedNum >= 0 && speedNum <= 8)
  {
    canBusSpeed = speedNum;
    msgReply = '\r';
    replyMsg(msgReply);
    }
  else
  {
    msgReply = "\\BEL";
    replyMsg(msgReply);
    }
  }
//get message
void getMsg(String message){
  int len = message.length();
  int dataLen = 0;
  int idLen = 0;
  int cycleNum = 0;
  String cycleJudge = message.substring(len - 5, len);
  if(message[0] == 't')
  {
    dataLen = (int)message[4];
    idLen = 9;
    }
  else
  {
    dataLen = (int)message[9];
    idLen = 14;
    }
  if(dataLen < 0 || dataLen > 8)
  {
    msgReply = "\\BEL";
    replyMsg(msgReply);
    return;
    }
  if(len != dataLen * 2 + idLen)
  {
    msgReply = "\\BEL";
    replyMsg(msgReply);
    return;
    }
  msgReply = '\r';
  replyMsg(msgReply);
  cycleNum = changeChartoInt(cycleJudge);
  cycleMessage(message, cycleNum);
  }

int changeChartoInt(String cycleJudge){
  int num = 0;
  for(int i = 0; i < 4; i++)
  {
    num += pow(16, 3 - i) * judgeChar(cycleJudge[i]);
    }
  return num;
  }
  
int judgeChar(char a){
  switch(a)
  {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'A': return 10;
    case 'B': return 11;
    case 'C': return 12;
    case 'D': return 13;
    case 'E': return 14;
    case 'F': return 15;
    default: return 0;
    }
  }
  
void cycleMessage(String message, int cycleNum){
  return;
  }


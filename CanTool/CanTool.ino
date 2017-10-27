String inputString = "";
boolean stringComplete = false;
String versionMsg = "SV2.5-HV2.0\r";
int state = 0;
int canBusSpeed = 0;
String msgReply = "";
int msgLength = 0;
String testMsg[100] = {"t12F4112233F40110\r", "T1234567F811223344556677880000\r", "t12F4112233F40110\r"};
int testTimes = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  inputString.reserve(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(stringComplete)
  {
    msgLength = inputString.length();
    judgeMsg(inputString);
    inputString = "";
    stringComplete = false;
    msgLength = 0;
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
      break;
      }
    delay(2);
    }
  
  }

void judgeMsg(String message){
  char judgeChar = message[0];
  //reply version message
  if(judgeChar == 'V')
  {
    msgReply = versionMsg;
    replyMsg(msgReply);
    }
  //reply speed command
  else if(judgeChar == 'S')
  {
    speedCommand((int)(message[1] - '0'));
    }
  //rely open command
  else if(message.startsWith("O1"))
  {
    testTimes = 1;
    openCommand();
    }
  //reply close command
  else if(judgeChar == 'C')
  {
    closeCommand();
    }
  //reply message
  else if(state == 1 && (judgeChar == 't' || judgeChar == 'T'))
  {
    getMsg(message);
    }
  else
  {
    msgReply = (char)7;
    replyMsg(msgReply);
    }
  
  }

//reply message
void replyMsg(String message)
{
  for(int i = 0; i < message.length(); i++)
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
    if(state == 1 && testTimes ==1)
    {  
      for(int i = 0; i < 100; i++)
      {
        if(testMsg[i] == "")
        {
          break;
          }
        Serial.print(testMsg[i]);
        delay(500);
        }
      testTimes = 0;
      }
    }
  else
  {
    msgReply = (char)7;
    replyMsg(msgReply);
    }
  }

//close command
void closeCommand()
{
  if(state == 1)
  {
    state = 0;
    msgReply = '\r';
    replyMsg(msgReply);
    }
  else
  {
    msgReply = (char)7;
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
    msgReply = (char)7;
    replyMsg(msgReply);
    }
  }

//get message
void getMsg(String message){
  int dataLen = 0;
  int restLen = 0;
  int cycleNum = 0;
  String cycleJudge = message.substring(msgLength - 5, msgLength - 1);
  if(message[0] == 't')
  {
    dataLen = (int)(message[4] - '0');
    restLen = 10;
    }
  else
  {
    dataLen = (int)(message[9] - '0');
    restLen = 15;
    }
  if(dataLen < 0 || dataLen > 8)
  {
    msgReply = (char)7;
    replyMsg(msgReply);
    return;
    }
  if(msgLength != dataLen * 2 + restLen)
  {
    msgReply = (char)7;
    replyMsg(msgReply);
    return;
    }
  msgReply = '\r';
  replyMsg(msgReply);
  cycleNum = changeChartoInt(cycleJudge);
  cycleMessage(message, cycleNum);
  }

//change char to int
int changeChartoInt(String cycleJudge){
  unsigned int num = 0;
  for(int i = 0; i < 4; i++)
  {
    num += double2int(pow(16, 3 - i) * judgeChar(cycleJudge[i]));
    }
  return num;
  }

//judge char
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

// solve precision missing
int double2int(double in){
  return in > 0 ? (in + 0.5) : (in - 0.5);
  }

//cycle send message to canbus
void cycleMessage(String message, int cycleNum){
  return;
  }


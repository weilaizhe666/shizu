# 预期高频率使用函数参考 #

**整体结构**<br>
• void setup() 初始化变量， 管脚模式， 调用库函数等<br>
• void loop() 连续执行函数内的语句<br>

**功能函数**<br>
**1.数字 I/O**<br>
• pinMode(pin, mode) 数字 IO 口输入输出模式定义函数， pin 表示为 0～13， mode 表示为 INPUT 或 OUTPUT。<br>
• digitalWrite(pin, value) 数字 IO 口输出电平定义函数， pin 表示为 0～13， value 表示为 HIGH 或 LOW。<br>
• int digitalRead(pin) 数字 IO 口读输入电平函数， pin 表示为 0～13， value 表示为 HIGH 或 LOW。<br>

**2.模拟 I/O**<br>
• int analogRead(pin) 模拟 IO 口读函数， pin 表示为 0～5（Arduino Diecimila 为 0～5， Arduino nano 为 0～7）。<br>
• analogWrite(pin, value) - PWM 数字 IO 口 PWM 输出函数， Arduino 数字 IO 口标注了 PWM 的 IO 口可使用该函数， pin 表示 3, 5, 6, 9, 10, 11， value 表示为 0～255。<br>

**3.扩展 I/O**<br>
• shiftOut(dataPin, clockPin, bitOrder, value) SPI 外部 IO 扩展函数， 通常使用带 SPI 接口的 74HC595 做 8 个IO 扩展， dataPin 为数据口， clockPin 为时钟口， bitOrder 为数据传输方向（MSBFIRST 高位在前， LSBFIRST 低位在前）， value 表示所要传送的数据（0～255）， 另外还需要一个 IO 口做 74HC595 的使能控制。<br>
• unsigned long pulseIn(pin, value) 脉冲长度记录函数， 返回时间参数（us）， pin 表示为 0～13， value 为 HIGH 或 LOW。 比如 value 为 HIGH， 那么当 pin 输入为高电平时， 开始计时， 当 pin 输入为低电平时， 停止计时， 然后返回该时间。<br>

**4.时间函数**<br>
• unsigned long millis() 返回时间函数（单位 ms）， 该函数是指， 当程序运行就开始计时并返回记录的参数，该参数溢出大概需要 50 天时间。<br>
• delay(ms) 延时函数（单位 ms）。<br>
• delayMicroseconds(us) 延时函数（单位 us）。<br>

**5.数学函数**<br>
• min(x, y) 求最小值<br>
• max(x, y) 求最大值<br>
• abs(x) 计算绝对值<br>
• constrain(x, a, b) 约束函数， 下限 a， 上限 b， x 必须在 ab 之间才能返回。<br>
• map(value, fromLow, fromHigh, toLow, toHigh) 约束函数， value 必须在 fromLow 与 toLow 之间和 fromHigh 与 toHigh 之间。<br>
• pow(base, exponent) 开方函数， base 的 exponent 次方。<br>
• sq(x) 平方<br>
• sqrt(x) 开根号<br>

**6.随机数函数**<br>
• randomSeed(seed) 随机数端口定义函数， seed 表示读模拟口 analogRead(pin)函数 。<br>
• long random(max) 随机数函数， 返回数据大于等于 0， 小于 max。<br>
• long random(min, max) 随机数函数， 返回数据大于等于 min， 小于 max。<br>

**7.外部中断函数**<br>
• attachInterrupt(interrupt , mode) 外部中断只能用到数字 IO 口 2 和 3， interrupt 表示中断口初始 0 或 1， 表示一个功能函数， mode： LOW 低电平中断， CHANGE 有变化就中断， RISING 上升沿中断， FALLING下降沿中断。<br>
• detachInterrupt(interrupt) 中断开关， interrupt=1 开， interrupt=0 关。<br>

**8.中断使能函数**<br>
• interrupts() 使能中断<br>
• noInterrupts() 禁止中断<br>

**9.串口收发函数**<br>
• Serial.begin(speed) 串口定义波特率函数， speed 表示波特率， 如 9600， 19200 等。<br>
• int Serial.available() 判断缓冲器状态。<br>
• int Serial.read() 读串口并返回收到参数。<br>
• Serial.flush() 清空缓冲器。<br>
• Serial.print(data) 串口输出数据。<br>
• Serial.println(data) 串口输出数据并带回车符。<br>
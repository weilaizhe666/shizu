# Arduino 编程分析#


CanTool装置相当于一座桥梁，是CanToolApp与总线上各ECU的通信链条。通过使用Arduino硬件配合串口/蓝牙通信来实现虚拟的CANTool装置。Arduino需要编写C/C++语言程序，以满足Android/Windows平台的后期测试。

参阅《CanToolApp Problem Statement》资料及小组需求分析，我负责Arduino方面程序的编写，我认为在编程时需要考虑以下几个方面：

1.对CAN信息的接收、发送及识别等功能实现<br/>
CAN信息起到重要作用，在装置中需要对信息格式、信息分类进行准确识别以做到准确的信息传递。<br/>
①信息格式主要是：ID + DLC + DATA。DATA最长达8个字节，每个字节有8bite，即CAN信号长度范围为[1~64]bite。<br/>
②CAN信号描述可以由用户指定，这里涉及一个排列方式的平台差异。CAN信号使用Intel的Little Endian方式排列在CAN信息DATA中，CAN信号也可以按照Motorola的Big Endian方式排列在CAN信息DATA中。不同方式的数据传输及读取需要一个判断。<br/>
③在CanToolApp接发CANTool装置的CAN信息中，以大写 T 开始区分CAN扩展帧信息，以小写 t 开始区分CAN标准帧信息。

2.上位机方面<br/>
①CanTool装置将CAN信息发送到上位机，使CanToolApp软件成功接收这些信息。<br/>
②CanTool装置接受用户所设定的CAN信息，并按照规定的信息格式，将信息发送的CAN总线上。<br/>
③上位机和CanTool装置的信息传送方式为：ASCII码+ \r（即0x0d），当上位机发送给CanTool装置的信息被正确接收后，CanTool装置会返回\r,否则返回\BEL (即0x07)。

3.CAN总线ECU方面<br/>
实际上，CanTool装置要做到和CAN总线上各个ECU进行正常通信并传递信息。这次主要利用人为编造的数据进行模拟，数据模拟参照规定格式。

在Arduino上进行编程，针对以上情况设置不同的功能函数加以实现。在实际操作中，不断发现问题并持续增改。。。 。。。
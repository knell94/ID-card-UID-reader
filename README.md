# ID-card-UID-reader
Based on stm32F103RC
VCC接5V
GND接地
TXD接单片机RXD(usart2,PA3)
J27接地（等价于短接M2）串口模式
J33接地（等价于短接M4）读取8位UID
UID依靠串口中断读取
串口中断在usart.c中
波特率9600	 
usart1与计算机通信，usart2与读卡器通信

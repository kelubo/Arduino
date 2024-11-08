#include <SoftwareSerial.h>

SoftwareSerial THSerial(8, 7);  // RX——8, TX——7

unsigned char item[8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};  //16进制测温命令
unsigned char buffer[9];                                                   //数组，存储接收到的16进制字符

void setup() {
  THSerial.begin(4800);
  Serial.begin(9600);
}

void loop() {
  delay(5000);  // 放慢输出频率
  for (int i = 0 ; i < 8; i++) {  // 发送测温命令
    THSerial.write(item[i]);      // write输出
  }
  delay(100);                     // 等待测温数据返回

  while (THSerial.available()) {  //从串口中读取数据
    for (int i = 0; i < 9; i++) {
    buffer[i] = (unsigned char)THSerial.read();
    Serial.print(buffer[i], HEX);
    Serial.print("  ");
    }
  }
  Serial.print("  \n");

  // 解析数据，也即是抓出有效值
  int humidity = (buffer[3] << 8) | buffer[4];
  int temperature = (buffer[5] << 8) | buffer[6];
 
  float real_temperature = temperature / 10.0; // 实际温度
  float real_humidity = humidity / 10.0;       // 实际湿度
 
  // 打印读取的温湿度数据
  Serial.print(F("温度 Temperature: "));            //温度
  Serial.print(real_temperature);
  Serial.print(F("\u2103 \n相对湿度 Humidity: "));        //湿度
  Serial.print(real_humidity);
  Serial.println(F("%"));
}
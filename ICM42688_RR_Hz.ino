#include "ICM42688.h"

// an ICM42688 object with the ICM42688 sensor on I2C bus 0 with address 0x69
ICM42688 IMU(Wire, 0x69);

unsigned long lastUpdateTime = 0; // 时间戳，用于跟踪上次更新的时间
const unsigned long timeSlice = 100; // 时间片为100毫秒
unsigned long lastSecondTime = 0; // 记录上一秒的时间
int countUpdates = 0; // 统计一秒内更新的次数

void setup() {
  Wire.setPins(16, 13);
  Wire.begin();
  // serial to display data
  Serial.begin(115200);
  while(!Serial) {}

  // start communication with IMU
  int status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  Serial.println("ax,ay,az,gx,gy,gz,temp_C");
  lastSecondTime = millis(); // 初始化上一秒的时间
}

void loop() {
  unsigned long currentTime = millis(); // 获取当前时间

  // 每秒输出更新次数
  if (currentTime - lastSecondTime >= 1000) {
    Serial.print("Updates per second: ");
    Serial.println(countUpdates);
    countUpdates = 0; // 重置计数器
    lastSecondTime = currentTime;
  }

  if (currentTime - lastUpdateTime >= timeSlice) { // 检查是否达到时间片
    lastUpdateTime = currentTime; // 更新时间戳
    countUpdates++; // 增加本秒内的更新次数

    // read the sensor
    IMU.getAGT();
    // display the data
    Serial.print(IMU.accX(),6);
    Serial.print("\t");
    Serial.print(IMU.accY(),6);
    Serial.print("\t");
    Serial.print(IMU.accZ(),6);
    Serial.print("\t");
    Serial.print(IMU.gyrX(),6);
    Serial.print("\t");
    Serial.print(IMU.gyrY(),6);
    Serial.print("\t");
    Serial.print(IMU.gyrZ(),6);
    Serial.print("\t");
    Serial.println(IMU.temp(),6);
  }
}

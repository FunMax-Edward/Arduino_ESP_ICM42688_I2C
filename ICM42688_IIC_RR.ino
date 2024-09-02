#include "ICM42688.h"

// an ICM42688 object with the ICM42688 sensor on I2C bus 0 with address 0x68
ICM42688 IMU(Wire, 0x69);

unsigned long lastUpdateTime = 0; // 时间戳，用于跟踪上次更新的时间
const unsigned long timeSlice = 100; // 时间片为100毫秒

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
}

void loop() {
  unsigned long currentTime = millis(); // 获取当前时间
  if (currentTime - lastUpdateTime >= timeSlice) { // 检查是否达到时间片
    lastUpdateTime = currentTime; // 更新时间戳

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

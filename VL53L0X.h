#ifndef VL53L0X_H
#define VL53L0X_H

class VL53L0X {
public:
  bool init() { return true; }
  void setTimeout(uint16_t timeout) {}
  void setAddress(uint8_t address) {}
  void startContinuous(uint32_t interval = 0) {}
  uint16_t readRangeContinuousMillimeters() {
    static int mock_distance = 100;
    mock_distance += 5;
    if (mock_distance > 200) mock_distance = 100;
    return mock_distance;
  }
};

#endif
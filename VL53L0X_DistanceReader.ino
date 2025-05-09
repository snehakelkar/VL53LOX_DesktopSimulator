#include <Wire.h>          // For I2C communication
#include <VL53L0X.h>       // For using the VL53L0X distance sensor

#define SHUTDOWN_PIN 7

// 2mm distance
#define CRITICAL_DISTANCE 2

VL53L0X sensor;

void setup() {
  pinMode(SHUTDOWN_PIN, OUTPUT);
  
  digitalWrite(SHUTDOWN_PIN, HIGH);
  Serial.begin(115200);

  Wire.begin();

  // Initialize the VL53L0X sensor
  sensor.init();
  sensor.setTimeout(500);
  sensor.startContinuous();
}

void loop() {
  int distance = sensor.readRangeContinuousMillimeters();

  if (sensor.timeoutOccurred()) {
    Serial.println("Sensor timeout!");
    return;
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" mm");

  if (distance <= CRITICAL_DISTANCE) {
    digitalWrite(SHUTDOWN_PIN, LOW);  
    Serial.println("Warning: Object too close,system shut down.");
  } else {
    digitalWrite(SHUTDOWN_PIN, HIGH);
  }

 //wait before taking the next reading
  delay(100);
}

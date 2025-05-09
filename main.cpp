#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

const int CRITICAL_DISTANCE = 2;
const int MEASUREMENT_DELAY = 100;

bool shutdownPin = true;


int mockSensorReading() {
    // Randomly return a distance between 0 and 100 mm
    return rand() % 101;
}


void digitalWrite(bool state) {
    shutdownPin = state;
    std::cout << "System Power: " << (shutdownPin ? "ON" : "OFF") << std::endl;
}

int main() {
    std::srand(std::time(0)); //random seed generater

    std::cout << "Starting simulated VL53L0X + SAMD system...\n";

    // System starts ON
    digitalWrite(true);

    while (true) {
        int distance = mockSensorReading();

        std::cout << "Distance: " << distance << " mm" << std::endl;

        // If object is too close
        if (distance <= CRITICAL_DISTANCE) {
            digitalWrite(false); // simulate turning off external system
            std::cout << "Warning: Object too close, system shut down.\n";
        } else {
            digitalWrite(true); // simulate keeping system ON
        }

        // Wait before taking another measurement
        std::this_thread::sleep_for(std::chrono::milliseconds(MEASUREMENT_DELAY));
    }

    return 0;
}

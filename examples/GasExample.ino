#include "BME688.h"

BME688 sensor;

void setup() {
    Serial.begin(115200);
    if (sensor.begin()) {
        Serial.println("BME688 Initialized Successfully!");
    } else {
        Serial.println("Failed to initialize BME688!");
    }
}

void loop() {
    Serial.print("Gas Resistance: ");
    Serial.print(sensor.readGas(0));
    Serial.println(" Ω");
    
    delay(5000);
}

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
    Serial.print("Humidity: ");
    Serial.print(sensor.readHumidity());
    Serial.println(" %");
    
    delay(2000);
}

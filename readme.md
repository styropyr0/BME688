# BME688 Library

## Overview
The **BME688** library provides an easy-to-use interface for the Bosch **BME688** environmental sensor. This sensor is capable of measuring:
- **Temperature** (°C)
- **Pressure** (Pa)
- **Humidity** (%)
- **Gas Resistance** (Ω)

The library supports various oversampling settings and operation modes, allowing flexible configuration for different use cases.

---

## Features
- Simple **begin()** method to initialize the sensor
- Functions to read **temperature, pressure, humidity, and gas resistance**
- Supports **multiple oversampling** settings
- Allows configuration of **gas measurement profiles**
- Debugging options with **log output**
- Error handling with predefined error codes

---

## Installation
1. Download or clone this repository into your Arduino libraries folder.
2. Include the **BME688** library in your sketch:

```cpp
#include "BME688.h"
```

3. Initialize the sensor in the `setup()` function.

---

## Usage
### Basic Example
```cpp
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
    Serial.print("Temperature: ");
    Serial.print(sensor.readTemperature());
    Serial.println(" °C");
    
    Serial.print("Pressure: ");
    Serial.print(sensor.readPressure());
    Serial.println(" Pa");
    
    Serial.print("Humidity: ");
    Serial.print(sensor.readHumidity());
    Serial.println(" %");
    
    delay(2000);
}
```

---

## API Reference
### **Initialization**
```cpp
bool begin();
bool begin(uint8_t mode);
bool begin(uint8_t mode, uint8_t oss);
```
- Initializes the BME688 sensor.
- **mode**: Operating mode (e.g., forced mode, normal mode).
- **oss**: Oversampling setting.

### **Reading Sensor Data**
```cpp
double readTemperature();
```
- Returns the temperature in **°C**.

```cpp
double readPressure();
```
- Returns the pressure in **Pascals (Pa)**.

```cpp
double readHumidity();
```
- Returns the relative humidity in **%**.

### **Gas Measurement**
```cpp
double readGas(uint8_t profile);
```
- Reads gas resistance in **ohms (Ω)** for a given profile.

```cpp
double readGasForTemperature(uint16_t temperature);
```
- Reads gas resistance based on a target temperature.

### **Configuration Functions**
```cpp
bool setTemperatureOversampling(uint8_t oss);
bool setPressureOversampling(uint8_t oss);
bool setHumidityOversampling(uint8_t oss);
```
- Sets oversampling settings for temperature, pressure, and humidity.

```cpp
void showLogs(bool show);
```
- Enables or disables debug logging.

```cpp
void ignoreUnsafeTemperatureWarnings(bool ignore);
```
- Allows ignoring unsafe temperature warnings.

```cpp
bool isConnected();
```
- Returns **true** if the sensor is connected, otherwise **false**.

### **Error Codes**
```cpp
#define BME688_OK 0
#define BME688_E_NULL_PTR -1
#define BME688_E_COM_FAIL -2
#define BME688_E_DEV_NOT_FOUND -3
#define BME688_E_INVALID_LENGTH -4
#define BME688_E_DEV_NOT_POWERED -5
#define BME688_E_USER_REG -6
#define BME688_E_I2C -7
#define BME688_E_I2C_TIMEOUT -8
#define BME688_E_I2C_FAIL -9
#define BME688_E_SENSOR_NOT_SUPPORTED -10
#define BME688_E_SENSOR_NOT_ENABLED -11
#define BME688_E_SENSOR_NOT_POWERED -12
```
These error codes help in debugging and handling sensor issues effectively.

---

## Advanced Example
This example demonstrates how to configure the oversampling settings and read gas resistance.

```cpp
#include "BME688.h"

BME688 sensor;

void setup() {
    Serial.begin(115200);
    if (sensor.begin(BME_688_FORCED_MODE, BME_688_OSS_4)) {
        Serial.println("BME688 Initialized with Forced Mode and OSS 4!");
    } else {
        Serial.println("Initialization Failed!");
    }
    
    sensor.setTemperatureOversampling(BME_688_OSS_2);
    sensor.setPressureOversampling(BME_688_OSS_4);
    sensor.setHumidityOversampling(BME_688_OSS_8);
}

void loop() {
    Serial.print("Gas Resistance: ");
    Serial.print(sensor.readGas(0));
    Serial.println(" Ω");
    delay(5000);
}
```

---

## License
This library is open-source and available under the **MIT License**.

---

## Author
Developed by **Saurav Sajeev**.


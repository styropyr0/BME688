# BME688 Arduino Library

The **BME688 Arduino Library** is a comprehensive driver for interfacing with the Bosch BME688 environmental sensor. This library provides functionality to measure temperature, pressure, humidity, and gas resistance, supporting various oversampling settings and operation modes. It is designed to be easy to use while offering advanced features for precise environmental monitoring and gas sensing applications.

- **Author**: Saurav Sajeev
- **Latest version**: 1.0.0
- **License**: MIT

## Features

- Read temperature (°C), pressure (Pa), relative humidity (%), and gas resistance (Ω).
- Configurable oversampling settings for temperature, pressure, and humidity.
- Support for different operation modes: Sleep, Forced, and Parallel.
- Gas measurement with customizable heater profiles and target temperatures.
- Calibration parameter handling for accurate readings.
- Logging support for debugging.
- Safety features like temperature limit warnings and connection checks.

## Dependencies

- **Arduino.h**: Standard Arduino library.
- **SensorHub.h**: A custom library for sensor communication (ensure this is included in your project).

## Installation

1. **Download the Library**:
   - Clone or download this repository from GitHub (or your preferred hosting platform).

2. **Install in Arduino IDE**:
   - Open the Arduino IDE.
   - Go to `Sketch > Include Library > Add .ZIP Library...`.
   - Select the downloaded ZIP file or folder containing `BME688.h`, `BME688DEFS.h`, and any dependencies (e.g., `SensorHub.h`).

3. **Verify Dependencies**:
   - Ensure `SensorHub.h` is available in your project or installed separately.

## Usage

### Basic Example

```cpp
#include <BME688.h>

BME688 bme; // Create an instance of the BME688 class

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for Serial to initialize

  // Initialize the sensor with default settings
  if (!bme.begin()) {
    Serial.println("Failed to initialize BME688!");
    while (1);
  }

  Serial.println("BME688 initialized successfully!");
}

void loop() {
  // Read and print environmental data
  Serial.print("Temperature: ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  Serial.print("Pressure: ");
  Serial.print(bme.readPressure());
  Serial.println(" Pa");

  Serial.print("Humidity: ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.print("Gas Resistance: ");
  Serial.print(bme.readGas(0)); // Profile 0
  Serial.println(" Ω");

  delay(2000); // Wait 2 seconds before next reading
}
```

### Advanced Example with Custom Settings

```cpp
#include <BME688.h>

BME688 bme;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initialize with Forced Mode and 4x oversampling
  if (!bme.begin(BME_688_FORCED_MODE, BME_688_OSS_4)) {
    Serial.println("Failed to initialize BME688!");
    while (1);
  }

  // Enable logging for debugging
  bme.showLogs(true);

  // Set custom oversampling for temperature
  bme.setTemperatureOversampling(BME_688_OSS_8);

  // Ignore unsafe temperature warnings (use with caution)
  bme.ignoreUnsafeTemperatureWarnings(true);

  Serial.println("BME688 initialized with custom settings!");
}

void loop() {
  // Read gas resistance for a target temperature of 300°C
  Serial.print("Gas Resistance at 300°C: ");
  Serial.print(bme.readGasForTemperature(300));
  Serial.println(" Ω");

  delay(5000);
}
```

## Key Methods

### Initialization
- `bool begin()`: Initializes with default settings (Forced Mode, 1x oversampling).
- `bool begin(uint8_t mode)`: Initializes with a specific mode.
- `bool begin(uint8_t mode, uint8_t oss)`: Initializes with mode and oversampling.

### Readings
- `double readTemperature()`: Returns temperature in °C.
- `double readPressure()`: Returns pressure in Pa.
- `double readHumidity()`: Returns humidity in %.
- `double readGas(uint8_t profile)`: Returns gas resistance (Ω) for a given profile (0-9).
- `double readGasForTemperature(uint16_t temperature)`: Returns gas resistance for a target temperature.

### Configuration
- `bool setTemperatureOversampling(uint8_t oss)`: Sets temperature oversampling.
- `bool setPressureOversampling(uint8_t oss)`: Sets pressure oversampling.
- `bool setHumidityOversampling(uint8_t oss)`: Sets humidity oversampling.
- `void showLogs(bool show)`: Enables/disables debug logging.
- `void ignoreUnsafeTemperatureWarnings(bool ignore)`: Bypasses temperature safety limits (425°C default, 600°C max).

### Status
- `bool isConnected()`: Checks if the sensor is responding.

## Important Definitions (`BME688DEFS.h`)

### I2C Addresses
- `BME688_I2C_ADDR_PRIMARY`: `0x77`
- `BME688_I2C_ADDR_SECONDARY`: `0x76`

### Operation Modes
- `BME_688_SLEEP_MODE`: `0x00`
- `BME_688_FORCED_MODE`: `0x01`
- `BME_688_PARALLEL_MODE`: `0x02`

### Oversampling Settings
- `BME_688_OSS_NONE`: `0x00` (Disabled)
- `BME_688_OSS_1`: `0x01` (1x)
- `BME_688_OSS_2`: `0x02` (2x)
- `BME_688_OSS_4`: `0x03` (4x)
- `BME_688_OSS_8`: `0x04` (8x)
- `BME_688_OSS_16`: `0x05` (16x)

### Gas Heater Profiles
- Profiles 1-10 with temperatures from 200°C to 380°C (e.g., `BME_688_GAS_HEAT_PROFILE1` = 200°C).
- Wait times from 60ms to 255ms (e.g., `BME_688_GAS_WAIT_PROFILE1` = 60ms).

### Error Codes
- `BME688_OK`: `0` (Success)
- `BME688_E_DEV_NOT_FOUND`: `-3` (Device not detected)
- `BME688_E_COM_FAIL`: `-2` (Communication failure)

### Safety Limits
- Default max temperature: 425°C (`BME_688_HEAT_PLATE_MAX_TEMP` = 425).
- Absolute max temperature: 600°C (`BME_688_HEAT_PLATE_ULTRA_TEMP` = 600).

## Notes

- **Gas Measurements**: The BME688 uses a heater for gas sensing. Ensure proper wait times and temperature settings to avoid incomplete measurements or sensor damage.
- **Safety**: High temperatures (>425°C) can degrade the sensor’s lifespan. Use `ignoreUnsafeTemperatureWarnings(true)` only if necessary.
- **Calibration**: The library automatically handles calibration parameters, but ensure the sensor is properly connected during initialization.

## Troubleshooting

- **"BME688 is disconnected"**: Check wiring and I2C address.
- **"Failed to read from BME688"**: Verify power supply and communication settings.
- **Gas measurement issues**: Adjust wait time or target temperature (see `readGasForTemperature`).

## Contributing

Feel free to submit issues or pull requests to improve this library. Contributions for additional features, bug fixes, or documentation enhancements are welcome!

## License

This library is released under the [MIT License](https://opensource.org/licenses/MIT). See the `LICENSE` file for details.

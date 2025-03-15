#ifndef BME688_H
#define BME688_H

#include "Arduino.h"
#include "BME688DEFS.h"
#include "SensorHub.h"

#ifdef __cplusplus

/**
 * @class BME688
 * @brief A driver class for interfacing with the BME688 sensor.
 *
 * This class provides functions to read temperature, pressure, humidity, and gas resistance
 * from the Bosch BME688 environmental sensor. It supports different oversampling settings
 * and operation modes.
 *
 * @author Saurav Sajeev
 */
class BME688
{
public:
    /**
     * @brief Default constructor for BME688.
     */
    BME688();

    /**
     * @brief Initializes the BME688 sensor with default settings.
     * @return True if the sensor is successfully initialized, false otherwise.
     */
    bool begin();

    /**
     * @brief Initializes the BME688 sensor with a specific operation mode.
     * @param mode The operating mode for the sensor.
     * @return True if initialization is successful, false otherwise.
     */
    bool begin(uint8_t mode);

    /**
     * @brief Initializes the BME688 sensor with a specific mode and oversampling settings.
     * @param mode The operating mode.
     * @param oss The oversampling setting.
     * @return True if initialization is successful, false otherwise.
     */
    bool begin(uint8_t mode, uint8_t oss);

    /**
     * @brief Reads the current temperature from the sensor.
     * @return Temperature in degrees Celsius.
     */
    double readTemperature();

    /**
     * @brief Reads the current atmospheric pressure.
     * @return Pressure in Pascals (Pa).
     */
    double readPressure();

    /**
     * @brief Reads the relative humidity from the sensor.
     * @return Humidity as a percentage (%).
     */
    double readHumidity();

    /**
     * @brief Reads gas resistance for a given target temperature.
     * @param temperature The target temperature in degrees Celsius.
     * @return Gas resistance in ohms (Ω).
     */
    double readGasForTemperature(uint16_t temperature);

    /**
     * @brief Reads gas resistance for a specific gas profile.
     * @param profile The gas measurement profile index.
     * @return Gas resistance in ohms (Ω).
     */
    double readGas(uint8_t profile);

    /**
     * @brief Enables or disables logging for debugging purposes.
     * @param show Set to true to enable logs, false to disable.
     */
    void showLogs(bool show);

    /**
     * @brief Sets the temperature oversampling setting.
     * @param oss Oversampling setting value.
     * @return True if the setting was applied successfully, false otherwise.
     */
    bool setTemperatureOversampling(uint8_t oss);

    /**
     * @brief Sets the pressure oversampling setting.
     * @param oss Oversampling setting value.
     * @return True if the setting was applied successfully, false otherwise.
     */
    bool setPressureOversampling(uint8_t oss);

    /**
     * @brief Sets the humidity oversampling setting.
     * @param oss Oversampling setting value.
     * @return True if the setting was applied successfully, false otherwise.
     */
    bool setHumidityOversampling(uint8_t oss);

    /**
     * @brief Allows ignoring unsafe temperature warnings.
     * @param ignore Set to true to ignore warnings, false to keep them.
     */
    void ignoreUnsafeTemperatureWarnings(bool ignore);

    /**
     * @brief Checks if the sensor is connected and responding.
     * @return True if the sensor is connected, false otherwise.
     */
    bool isConnected();

private:
    SensorHub sensorHub;
    uint8_t temp_oss = BME_688_OSS_1,
            press_oss = BME_688_OSS_1,
            hum_oss = BME_688_OSS_1,
            mode = BME_688_FORCED_MODE;

    bool printLogs = false;

    // CALIBRATION CONSTANTS
    int16_t par_t16[2] = {0};
    int8_t par_t3 = 0;
    uint16_t par_p1 = 0;
    int16_t par_p16[6] = {0};
    int8_t par_p8[4] = {0};
    uint16_t par_h16[2] = {0};
    int8_t par_h8[5] = {0};
    uint8_t par_h6 = 0;
    uint8_t par_p10 = 0, res_heat_range = 0;
    int8_t par_g1 = 0, par_g3 = 0, res_heat_val = 0;
    int16_t par_g2 = 0;
    bool allowHighTemps = false;

    // CALIBRATED READINGS
    double t_fine = 0, p_fine = 0, h_fine = 0, g_fine = 0, g_res = 0;

    // Gas Sensor Profile data
    uint8_t measProfile = 0, targetTemp = 0, targetWaitTime = 0;

    // Pressure correction factor
    float cf_p = BME_688_GAS_CORRECTION_NIL;

    int32_t readRawTemp();
    int32_t readRawPres();
    int16_t readRawHum();
    int16_t readRawGas();
    double readUCTemp(int32_t adc_T);
    double readUCPres(int32_t adc_P);
    double readUCHum(int16_t adc_H);
    uint8_t readUCGas(uint16_t adc_G);
    double startGasMeasurement(uint8_t profile, uint8_t waitTime);
    bool setHeatProfiles();
    bool checkGasMeasurementCompletion();
    void printLog(String log);
    void readCalibParams();
};

#endif // __cplusplus
#endif // BME688_H
#include <BME688.h>
#include "SensorHub.h"
#include "SensorHubTemplates.h"
#include <Wire.h>

BME688::BME688() : sensorHub(BME688_I2C_ADDR_PRIMARY) {}

bool BME688::begin()
{
    if (isConnected())
    {
        sensorHub.i2c_execute(BME_688_CTRL_MEAS_HUM_REG, hum_oss);
        sensorHub.i2c_execute(BME_688_CTRL_MEAS_REG, temp_oss << 5 | press_oss << 2 | BME_688_FORCED_MODE);
        sensorHub.i2c_execute(BME_688_IIR_FILTER_REG, BME_688_IIR_FILTER_C15);
        readCalibParams();
    }
    else
        printLog(BME_688_CHECK_CONN_ERR);
    return isConnected();
}

bool BME688::begin(uint8_t mode)
{
    if (isConnected())
    {
        if (mode <= BME_688_PARALLEL_MODE)
        {
            sensorHub.i2c_execute(BME_688_CTRL_MEAS_HUM_REG, BME_688_OSS_1);
            sensorHub.i2c_execute(BME_688_CTRL_MEAS_REG, BME_688_OSS_1 << 5 | BME_688_OSS_1 << 2 | mode);
            sensorHub.i2c_execute(BME_688_IIR_FILTER_REG, BME_688_IIR_FILTER_C15);
            readCalibParams();
        }
        else
        {
            printLog(BME_688_VALUE_INVALID);
            return false;
        }
    }
    else
        printLog(BME_688_CHECK_CONN_ERR);
    return isConnected();
}

bool BME688::begin(uint8_t mode, uint8_t oss)
{
    if (isConnected())
    {
        if (mode <= BME_688_PARALLEL_MODE && oss <= BME_688_OSS_16)
        {
            sensorHub.i2c_execute(BME_688_CTRL_MEAS_HUM_REG, oss);
            sensorHub.i2c_execute(BME_688_CTRL_MEAS_REG, oss << 5 | oss << 2 | mode);
            sensorHub.i2c_execute(BME_688_IIR_FILTER_REG, BME_688_IIR_FILTER_C15);
            readCalibParams();
        }
        else
        {
            printLog(BME_688_VALUE_INVALID);
            return false;
        }
    }
    else
        printLog(BME_688_CHECK_CONN_ERR);
    return isConnected();
}

void BME688::printLog(String log)
{
    if (printLogs)
        Serial.println(log);
}

void BME688::showLogs(bool show)
{
    printLogs = show;
}

void BME688::readCalibParams()
{
    if (!(sensorHub.i2c_read_Xbit_LE(BME_688_TEMP_CALIB1_REG, &par_t16[0], 16) &&
          sensorHub.i2c_read_Xbit_LE(BME_688_TEMP_CALIB2_REG, &par_t16[1], 16) &&
          sensorHub.i2c_readByte(BME_688_TEMP_CALIB3_REG, &par_t3, 1)))
        printLog(BME_688_TEMP_CAL_EXCEPT);

    if (!(sensorHub.i2c_read_Xbit_LE(BME_688_PRES_CALIB1_REG, &par_p1, 16) &&
          sensorHub.i2c_read_Xbit_LE(BME_688_PRES_CALIB2_REG, &par_p16[1], 16) &&
          sensorHub.i2c_readByte(BME_688_PRES_CALIB3_REG, &par_p8[0], 1) &&
          sensorHub.i2c_read_Xbit_LE(BME_688_PRES_CALIB4_REG, &par_p16[2], 16) &&
          sensorHub.i2c_read_Xbit_LE(BME_688_PRES_CALIB5_REG, &par_p16[3], 16) &&
          sensorHub.i2c_readByte(BME_688_PRES_CALIB6_REG, &par_p8[1], 1) &&
          sensorHub.i2c_readByte(BME_688_PRES_CALIB7_REG, &par_p8[2], 1) &&
          sensorHub.i2c_read_Xbit_LE(BME_688_PRES_CALIB8_REG, &par_p16[4], 16) &&
          sensorHub.i2c_read_Xbit_LE(BME_688_PRES_CALIB9_REG, &par_p16[5], 16) &&
          sensorHub.i2c_readByte(BME_688_PRES_CALIB10_REG, &par_p10, 1)))
        printLog(BME_688_PRES_CAL_EXCEPT);

    if (!(sensorHub.i2c_read_Xbit_LE(BME_688_HUM_CALIB1_REG, &par_h16[0], 12) &&
          sensorHub.i2c_read_Xbit(BME_688_HUM_CALIB2_REG, &par_h16[1], 12) &&
          sensorHub.i2c_readByte(BME_688_HUM_CALIB3_REG, &par_h8[0], 1) &&
          sensorHub.i2c_readByte(BME_688_HUM_CALIB4_REG, &par_h8[1], 1) &&
          sensorHub.i2c_readByte(BME_688_HUM_CALIB5_REG, &par_h8[2], 1) &&
          sensorHub.i2c_readByte(BME_688_HUM_CALIB6_REG, &par_h6, 1) &&
          sensorHub.i2c_readByte(BME_688_HUM_CALIB7_REG, &par_h8[4], 1)))
        printLog(BME_688_HUM_CAL_EXCEPT);

    if (!(sensorHub.i2c_readByte(BME_688_GAS_CALIB1_REG, &par_g1, 1) &&
          sensorHub.i2c_read_Xbit_LE(BME_688_GAS_CALIB2_REG, &par_g2, 16) &&
          sensorHub.i2c_readByte(BME_688_GAS_CALIB3_REG, &par_g3, 1) &&
          sensorHub.i2c_readByte(BME_688_GAS_HEAT_RANGE_REG, &res_heat_range, 1) &&
          sensorHub.i2c_readByte(BME_688_GAS_HEAT_VAL_REG, &res_heat_val, 1)))
        printLog(BME_688_TEMP_CAL_EXCEPT);

    setHeatProfiles();
}

bool BME688::setHeatProfiles()
{
    readTemperature();
    for (uint8_t i = 0; i < 9; i++)
    {
        yield();
        uint8_t gasTemp = readUCGas(BME_688_GAS_START_TEMP + i * 25);
        sensorHub.i2c_execute(BME_688_GAS_WAIT_PROFILE_REG + i, BME_688_GAS_WAIT_MULFAC1 << 6 | (uint8_t)(0.25 * gasTemp - 22));
        sensorHub.i2c_execute(BME_688_GAS_RES_HEAT_PROFILE_REG + i, gasTemp);
    }
    return true;
}

bool BME688::isConnected()
{
    uint8_t pid = 0;
    if (sensorHub.is_sensor_connected() && sensorHub.i2c_readByte(BME_688_CHIP_ID_REG, &pid, 1))
        return pid == BME_688_CHIP_ID;
    return false;
}

bool BME688::setTemperatureOversampling(uint8_t oss)
{
    if (oss <= BME_688_OSS_16)
        temp_oss = oss;
    else
    {
        printLog(BME_688_VALUE_INVALID);
        return false;
    }
    return true;
}

int32_t BME688::readRawTemp()
{
    int32_t raw = 0;
    if (!sensorHub.i2c_read_Xbit(BME_688_TEMP_RAW_REG, &raw, 20))
        printLog(BME_688_READ_FAILURE);
    return raw;
}

int32_t BME688::readRawPres()
{
    int32_t raw = 0;
    if (!sensorHub.i2c_read_Xbit(BME_688_PRES_RAW_REG, &raw, 20))
        printLog(BME_688_READ_FAILURE);
    return raw;
}

int16_t BME688::readRawHum()
{
    int16_t raw = 0;
    if (!sensorHub.i2c_read_Xbit(BME_688_HUM_RAW_REG, &raw, 16))
        printLog(BME_688_READ_FAILURE);
    return raw;
}

int16_t BME688::readRawGas()
{
    int16_t raw = 0;
    if (!sensorHub.i2c_read_Xbit(BME_688_HUM_RAW_REG, &raw, 16))
        printLog(BME_688_READ_FAILURE);
    return raw;
}

double BME688::readUCTemp(int32_t adc_T)
{
    double var1 = (((double)adc_T / 16384.0) - ((double)par_t16[0] / 1024.0)) * (double)par_t16[1];
    double var2 = ((((double)adc_T / 131072.0) - ((double)par_t16[0] / 8192.0)) *
                   (((double)adc_T / 131072.0) - ((double)par_t16[0] / 8192.0))) *
                  ((double)par_t3 * 16.0);

    t_fine = var1 + var2;
    return t_fine / 5120.0;
}

double BME688::readUCPres(int32_t adc_P)
{
    double var1 = 0.0, var2 = 0.0, var3 = 0.0;
    double press_comp = 0.0;

    var1 = ((double)t_fine / 2.0) - 64000.0;
    var2 = var1 * var1 * ((double)par_p8[1] / 131072.0);
    var2 = var2 + (var1 * (double)par_p16[3] * 2.0);
    var2 = (var2 / 4.0) + ((double)par_p16[2] * 65536.0);
    var1 = ((((double)par_p8[0] * var1 * var1) / 16384.0) + ((double)par_p16[1] * var1)) / 524288.0;
    var1 = (1.0 + (var1 / 32768.0)) * (double)par_p1;
    press_comp = 1048576.0 - (double)adc_P;
    press_comp = ((press_comp - (var2 / 4096.0)) * 6250.0) / var1;
    var1 = ((double)par_p16[5] * press_comp * press_comp) / 2147483648.0;
    var2 = press_comp * ((double)par_p16[4] / 32768.0);
    var3 = (press_comp / 256.0) * (press_comp / 256.0) * (press_comp / 256.0) * ((double)par_p10 / 131072.0);
    p_fine = press_comp + (var1 + var2 + var3 + ((double)par_p8[2] * 128.0)) / 16.0;
    return p_fine;
}

double BME688::readUCHum(int16_t adc_H)
{
    double t_fine = this->t_fine / 5120.0;
    double var1 = 0, var2 = 0, var3 = 0, var4 = 0;

    var1 = adc_H - (((double)par_h16[0] * 16.0) + (((double)par_h8[0] / 2.0) * t_fine));
    var2 = var1 * (((double)par_h16[1] / 262144.0) *
                   (1.0 + (((double)par_h8[1] / 16384.0) * t_fine) +
                    (((double)par_h8[2] / 1048576.0) * t_fine * t_fine)));
    var3 = (double)par_h6 / 16384.0;
    var4 = (double)par_h8[4] / 2097152.0;
    h_fine = var2 + ((var3 + (var4 * t_fine)) * var2 * var2);
    return h_fine;
}

uint8_t BME688::readUCGas(uint16_t target_temp)
{
    double t_fine = this->t_fine / 5120.0;
    double var1 = 0, var2 = 0, var3 = 0, var4 = 0, var5 = 0;

    var1 = ((double)par_g1 / 16.0) + 49.0;
    var2 = (((double)par_g2 / 32768.0) * 0.0005) + 0.00235;
    var3 = (double)par_g3 / 1024.0;
    var4 = var1 * (1.0 + (var2 * (double)target_temp));
    var5 = var4 + (var3 * (double)t_fine);
    g_fine = (uint8_t)(3.4 * ((var5 * (4.0 / (4.0 + (double)((res_heat_range & BME_688_HEAT_RANGE_MASK) >> 4))) * (1.0 / (1.0 + ((double)res_heat_val * 0.002)))) - 25));
    return g_fine;
}

bool BME688::checkGasMeasurementCompletion()
{
    uint8_t m_Complete = 0;
    sensorHub.i2c_readByte(BME_688_GAS_MEAS_STATUS_REG1, &m_Complete, 1);
    m_Complete &= BME_688_GAS_HEAT_STAB_MASK | BME_688_GAS_VALID_REG_MASK;
    return m_Complete == BME_688_GAS_MEAS_FINISH;
}

double BME688::readTemperature()
{
    sensorHub.i2c_execute(BME_688_CTRL_MEAS_REG, temp_oss << 5 | press_oss << 2 | mode);
    delay(10);
    return readUCTemp(readRawTemp());
}

double BME688::readPressure()
{
    sensorHub.i2c_execute(BME_688_CTRL_MEAS_REG, temp_oss << 5 | press_oss << 2 | mode);
    delay(10);
    float ps = readUCPres(readRawPres()) * cf_p;
    cf_p = BME_688_GAS_CORRECTION_NIL;
    return ps;
}

double BME688::readHumidity()
{
    sensorHub.i2c_execute(BME_688_CTRL_MEAS_HUM_REG, hum_oss);
    sensorHub.i2c_execute(BME_688_CTRL_MEAS_REG, temp_oss << 5 | press_oss << 2 | mode);
    delay(10);
    return readUCHum(readRawHum());
}

double BME688::readGasForTemperature(uint16_t temperature)
{
    if (allowHighTemps || temperature <= BME_688_HEAT_PLATE_MAX_TEMP)
    {
        if (temperature < BME_688_HEAT_PLATE_ULTRA_TEMP)
        {
            uint8_t t_temp = readUCGas((uint16_t)temperature);
            uint8_t t_wait = (uint8_t)(0.25 * t_temp - 17);
            sensorHub.i2c_execute(BME_688_CTRL_GAS_REG, 0x20);
            sensorHub.i2c_execute(BME_688_GAS_WAIT_PROFILE_REG, t_wait);
            sensorHub.i2c_execute(BME_688_GAS_RES_HEAT_PROFILE_REG, t_temp);
            return startGasMeasurement(BME_688_GAS_PROFILE_START, t_wait + 5);
        }
        else
            printLog(BME_688_TEMP_EXCEED_MAX_LIMIT);
    }
    else
        printLog(BME_688_TEMP_WARNING);

    return -1.0;
}

double BME688::readGas(uint8_t profile)
{
    if (profile >= 0 && profile < 10)
        return startGasMeasurement(profile, (uint8_t)(0.25 * readUCGas(BME_688_GAS_START_TEMP * profile) - 17));
    else
        printLog(BME_688_PROFILE_OUT_OF_RANGE);
    return -1.0;
}

double BME688::startGasMeasurement(uint8_t profile, uint8_t waitTime)
{
    sensorHub.i2c_execute(BME_688_CTRL_GAS_REG, BME_688_GAS_RUN | profile);
    sensorHub.i2c_execute(BME_688_CTRL_MEAS_REG, mode);
    delay(waitTime);
    if (!checkGasMeasurementCompletion())
    {
        printLog(BME_688_GAS_MEAS_FAILURE);
        return -2.0;
    }
    uint16_t gas_adc = 0;
    uint8_t gas_range = 0;

    sensorHub.i2c_read_Xbit(BME_688_GAS_ADC_REG, &gas_adc, 10);
    sensorHub.i2c_readByte(BME_688_GAS_RANGE_REG, &gas_range, 1);

    gas_range &= BME_688_GAS_RANGE_VAL_MASK;

    uint32_t var1 = int32_t(262144) >> gas_range;
    int32_t var2 = (int32_t)gas_adc - int32_t(512);
    var2 *= int32_t(3);
    var2 = int32_t(4096) + var2;
    g_res = 1000000.0f * (float)var1 / (float)var2;
    cf_p = BME_688_GAS_CORRECTION;
    return g_res;
}

void BME688::ignoreUnsafeTemperatureWarnings(bool ignore)
{
    allowHighTemps = ignore;
    printLog(BME_688_TEMP_UNSAFE_WARNING);
}
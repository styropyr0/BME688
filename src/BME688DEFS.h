#ifndef BME688DEFS
#define BME688DEFS

#ifdef __cplusplus

#define BME688_I2C_ADDR_PRIMARY 0x77
#define BME688_I2C_ADDR_SECONDARY 0x76

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

#define BME_688_CTRL_MEAS_REG 0x74
#define BME_688_CTRL_MEAS_HUM_REG 0x72

#define BME_688_OSS_NONE 0x00
#define BME_688_OSS_1 0x01
#define BME_688_OSS_2 0x02
#define BME_688_OSS_4 0x03
#define BME_688_OSS_8 0x04
#define BME_688_OSS_16 0x05

#define BME_688_SLEEP_MODE 0x00
#define BME_688_FORCED_MODE 0x01
#define BME_688_PARALLEL_MODE 0x02

#define BME_688_TEMP_RAW_REG 0x22
#define BME_688_PRES_RAW_REG 0x1F
#define BME_688_HUM_RAW_REG 0x25
#define BME_688_CTRL_GAS_REG 0x71
#define BME_688_GAS_RAW_REG 0x2C
#define BME_688_GAS_RANGE_REG 0x2C
#define BME_688_GAS_ADC_REG 0x2C
#define BME_688_GAS_RANGE_REG 0x2D

#define BME_688_TEMP_CALIB1_REG 0xE9
#define BME_688_TEMP_CALIB2_REG 0x8A
#define BME_688_TEMP_CALIB3_REG 0x8C

#define BME_688_PRES_CALIB1_REG 0x8E
#define BME_688_PRES_CALIB2_REG 0x90
#define BME_688_PRES_CALIB3_REG 0x92
#define BME_688_PRES_CALIB4_REG 0x94
#define BME_688_PRES_CALIB5_REG 0x96
#define BME_688_PRES_CALIB6_REG 0x99
#define BME_688_PRES_CALIB7_REG 0x98
#define BME_688_PRES_CALIB8_REG 0x9C
#define BME_688_PRES_CALIB9_REG 0x9E
#define BME_688_PRES_CALIB10_REG 0xA0

#define BME_688_HUM_CALIB1_REG 0xE2
#define BME_688_HUM_CALIB2_REG 0xE1
#define BME_688_HUM_CALIB3_REG 0xE4
#define BME_688_HUM_CALIB4_REG 0xE5
#define BME_688_HUM_CALIB5_REG 0xE6
#define BME_688_HUM_CALIB6_REG 0xE7
#define BME_688_HUM_CALIB7_REG 0xE8

#define BME_688_GAS_CALIB1_REG 0xED
#define BME_688_GAS_CALIB2_REG 0xEB
#define BME_688_GAS_CALIB3_REG 0xEE
#define BME_688_GAS_HEAT_RANGE_REG 0x02
#define BME_688_GAS_HEAT_VAL_REG 0x00

#define BME_688_IIR_FILTER_REG 0x75
#define BME_688_IIR_FILTER_C0 0x00
#define BME_688_IIR_FILTER_C1 0x01
#define BME_688_IIR_FILTER_C3 0x02
#define BME_688_IIR_FILTER_C7 0x03
#define BME_688_IIR_FILTER_C15 0x04
#define BME_688_IIR_FILTER_C31 0x05
#define BME_688_IIR_FILTER_C63 0x06
#define BME_688_IIR_FILTER_C127 0x07

#define BME_688_GAS_MEAS_STATUS_REG0 0x2E
#define BME_688_GAS_MEAS_STATUS_REG1 0x2D
#define BME_688_GAS_HEAT_STAB_MASK 0x10
#define BME_688_GAS_VALID_REG_MASK 0x20
#define BME_688_GAS_NEW_DATA_MASK 0x80
#define BME_688_GAS_MEAS_MASK 0x40
#define BME_688_MEAS_MASK 0x20
#define BME_688_HEAT_RANGE_MASK 0x18
#define BME_688_GAS_RANGE_REG_MASK 0x0F
#define BME_688_GAS_MEAS_INDEX_MASK 0x0F
#define BME_688_GAS_RANGE_VAL_MASK 0x0F
#define BME_688_GAS_RUN 0x20

#define BME_688_GAS_MEAS_FINISH 0x30
#define BME_688_GAS_HEATING_INSUFFICIENT 0x10
#define BME_688_GAS_RESULT_NOT_READY 0x00
#define BME_688_GAS_PROFILE_START 0x00
#define BME_688_HEAT_PLATE_MAX_TEMP 0x1A9
#define BME_688_HEAT_PLATE_ULTRA_TEMP 0x258

// Gas wait time registers
#define BME_688_GAS_WAIT_PROFILE_REG 0x64
#define BME_688_GAS_RES_HEAT_PROFILE_REG 0x5A
#define BME_688_GAS_START_TEMP 0xC8

// Gas wait time multiplication factor
#define BME_688_GAS_WAIT_MULFAC1 0x00
#define BME_688_GAS_WAIT_MULFAC2 0x01
#define BME_688_GAS_WAIT_MULFAC3 0x02
#define BME_688_GAS_WAIT_MULFAC4 0x03

// Heater temperature (resistance) registers

// Gas Wait Times (in ms)
#define BME_688_GAS_WAIT_PROFILE1 0x3C
#define BME_688_GAS_WAIT_PROFILE2 0x50
#define BME_688_GAS_WAIT_PROFILE3 0x64
#define BME_688_GAS_WAIT_PROFILE4 0x90
#define BME_688_GAS_WAIT_PROFILE5 0xC0
#define BME_688_GAS_WAIT_PROFILE6 0xD2
#define BME_688_GAS_WAIT_PROFILE7 0xE0
#define BME_688_GAS_WAIT_PROFILE8 0xF0
#define BME_688_GAS_WAIT_PROFILE9 0xFA
#define BME_688_GAS_WAIT_PROFILE10 0xFF

// Heater Temperature (in degrees Celsius)
#define BME_688_GAS_HEAT_PROFILE1 200
#define BME_688_GAS_HEAT_PROFILE2 220
#define BME_688_GAS_HEAT_PROFILE3 240
#define BME_688_GAS_HEAT_PROFILE4 260
#define BME_688_GAS_HEAT_PROFILE5 280
#define BME_688_GAS_HEAT_PROFILE6 300
#define BME_688_GAS_HEAT_PROFILE7 320
#define BME_688_GAS_HEAT_PROFILE8 340
#define BME_688_GAS_HEAT_PROFILE9 360
#define BME_688_GAS_HEAT_PROFILE10 380

// Chip ID
#define BME_688_CHIP_ID_REG 0xD0
#define BME_688_CHIP_ID 0x61

// Correction factor
#define BME_688_GAS_CORRECTION 1.3801
#define BME_688_GAS_CORRECTION_NIL 1.0

// ------------ ERRORS -----------------

#define BME_688_CHECK_CONN_ERR "BME688 is disconnected. Check connections or make sure it is working."
#define BME_688_TEMP_CAL_EXCEPT "Exception: Failed to read temperature calibration parameters"
#define BME_688_PRES_CAL_EXCEPT "Exception: Failed to read pressure calibration parameters"
#define BME_688_HUM_CAL_EXCEPT "Exception: Failed to read humidity calibration parameters"
#define BME_688_VALUE_INVALID "Invalid value. Use a value within the range."
#define BME_688_READ_FAILURE "Exception: Failed to read from BME688"
#define BME_688_GAS_MEAS_FAILURE "Exception: Gas measurement incomplete.\nTemperature not achieved or heating might be too high for the provided wait time."
#define BME_688_TEMP_WARNING "Warning: Higher temperatures will degrade the lifespan of the sensor. \nThis operation has been automatically denied for safety. \nIf you still wish to use high temperatures, call ignoreUnsafeTemperatureWarnings(false)\nIn safe mode, Temperature limit is 425°C. Bypassing this protection will raise the limit to 600°C."
#define BME_688_TEMP_EXCEED_MAX_LIMIT "Exception: Operation blocked. The temperature value exceeds maximum limit."
#define BME_688_PROFILE_OUT_OF_RANGE "Exception: Operation blocked. Profile value should be between 0 and 9."
#define BME_688_TEMP_UNSAFE_WARNING "Warning: Higher temperatures will degrade the lifespan of the sensor. It is recommended to use a value under 425°C"

#endif // __cplusplus
#endif // BME688DEFS
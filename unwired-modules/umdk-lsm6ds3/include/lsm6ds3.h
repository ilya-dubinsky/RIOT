/*
 * Copyright (C) 2016 Unwired Devices [info@unwds.com]
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup
 * @ingroup
 * @brief
 * @{
 * @file		lsm6ds3.h
 * @brief       ST's LSM6DS3 6-axis motion sensor driver definitions
 * @author      EP <ep@unwds.com>
 */
#ifndef LSM6DS3_H_
#define LSM6DS3_H_

#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "../../umdk-lsm6ds3/include/lsm6ds3_regs.h"
#include "periph/i2c.h"

/**
 * @brief Structure holds LSM6DS3 driver parameters
 */
typedef struct {
    i2c_t i2c;
    uint8_t i2c_addr;   /**< Default is 0x6B */

    bool gyro_enabled;
    uint16_t gyro_range;
    uint16_t gyro_sample_rate;
    uint16_t gyro_bandwidth;

    bool gyro_fifo_enabled;
    bool gyro_fifo_decimation;

    bool accel_enabled;
    bool accel_odr_off;

    uint16_t accel_range;
    uint16_t accel_sample_rate;
    uint16_t accel_bandwidth;

    bool accel_fifo_enabled;
    bool accel_fifo_decimation;

    bool temp_enabled;

    bool comm_mode;

    uint16_t fifo_threshold;
    uint16_t fifo_sample_rate;
    uint8_t fifo_mode_word;
} lsm6ds3_param_t;

/**
 * @brief Structure holds LSM6DS3 device
 */
typedef struct {
    lsm6ds3_param_t params;
} lsm6ds3_t;

/**
 * @brief Structure holds raw LSM6DS3 acceleration and gyro data
 */
typedef struct {
    float_t acc_x;
    float_t acc_y;
    float_t acc_z;

    float_t gyr_x;
    float_t gyr_y;
    float_t gyr_z;
} lsm6ds3_data_t;

/**
 * @brief Initializes LSM6DS3 driver with given parameters
 * @note Corresponding I2C peripheral must be already initialized
 * @note The parameters passed will be copied into device descriptor
 *
 * @param[out] *dev    device descriptor pointer
 * @param[in]  *param  device parameters structure
 *
 * @return 0  on success
 * @return <0 on error
 */
int lsm6ds3_init(lsm6ds3_t *dev, lsm6ds3_param_t *param);

bool lsm6ds3_configure(lsm6ds3_t *dev, lsm6ds3_param_t *param);

/**
 * @brief Gets raw measurement of current acceleration and gyro
 *
 * @param[in]  *dev  LSM6DS3 device pointer
 * @param[out] *data raw measurement data
 *
 * @return true  on success
 * @return false on error
 */
bool lsm6ds3_get_raw(lsm6ds3_t *dev, lsm6ds3_data_t *data);

/**
 * @brief Gets data from temperature sensor in Celsius degrees
 *
 * @param[in]   *dev   LSM6DS3 device pointer
 *
 * @return Temperature in Celsius degrees
 */
int16_t lsm6ds3_read_temp_c(lsm6ds3_t *dev);

#endif /* LSM6DS3_H_ */

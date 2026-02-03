/*
 * imu.h
 *
 *  Created on: Feb 2, 2026
 *      Author: manhhai
 */

#ifndef INC_IMU_H_
#define INC_IMU_H_

#include <stdbool.h>

typedef struct imu imu_t;

typedef struct {
    int  (* init )(imu_t *imu);
    int  (* read )(imu_t *imu);
    bool (* parse)(imu_t *imu, float *data);
    int  (* read_blocking)(imu_t *imu, float *data);
} imu_ops_t;

struct imu {
    void *ctx;
    imu_ops_t *ops;
};

#endif /* INC_IMU_H_ */

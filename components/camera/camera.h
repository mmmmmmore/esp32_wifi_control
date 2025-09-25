#pragma once
#include <stdbool.h>

#ifndef CAMERA_H
#define CAMERA_H

// Structure for register-value pair
struct regval_list {
    unsigned char reg;
    unsigned char val;
};

extern const struct regval_list ov7670_qvga_rgb565[];


// OV7670 initialization function for QVGA + RGB565
void ov7670_init_qvga_rgb565();


// Initialize the OV7670 camera sensor
bool camera_init(void);


#endif // CAMERA_H

#ifndef OV7670_CFG_H
#define OV7670_CFG_H

#include <stdint.h>

typedef struct {
    uint8_t reg;
    uint8_t val;
} ov7670_reg_t;

extern const ov7670_reg_t ov7670_init_reg_tbl[];
extern const size_t ov7670_init_reg_tbl_size;

#endif // OV7670_CFG_H

#pragma once

#include <stdint.h>
#include <stdbool.h>

bool sccb_init(void);
bool sccb_write(uint8_t reg_addr, uint8_t data);
bool sccb_read(uint8_t reg_addr, uint8_t *data);


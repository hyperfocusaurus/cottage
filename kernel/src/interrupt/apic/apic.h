#pragma once

#include <stdint.h>

void lapic_enable(uint16_t spurious_vector);
uint32_t lapic_read(uint32_t reg);
void lapic_write (uint32_t reg, uint32_t val);
void lapic_timer_stop();
void lapic_timer_calibrate();


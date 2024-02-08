// PCA95481 i2c bridge
#pragma once

#include "nrf_twi_mngr.h"

static const uint8_t PCA9548_ADDRESS = 0x70;
// Function prototypes for the i2c bridge
// i2c - pointer to already initialized and enabled twim instance
void pca9548a_bridge_init(const nrf_twi_mngr_t* i2c);
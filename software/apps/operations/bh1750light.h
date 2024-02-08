// BH1750 light sensor
#pragma once

#include "nrf_twi_mngr.h"

// Chip addresses for light sensor
static const uint8_t BH1750_LIGHT_ADDRESS = 0x23;

// OPCODE definitions for the light sensor
typedef enum {
    BH1750_LIGHT_POWER_DOWN = 0X00,
    BH1750_LIGHT_POWER_UP = 0x01,
    BH1750_LIGHT_RESET = 0x07,
    BH1750_LIGHT_Continuously_H_Resolution_Mode = 0x10,
    BH1750_LIGHT_Continuously_H_Resolution_Mode2 = 0x11,
    BH1750_LIGHT_Continuously_L_Resolution_Mode = 0x13,
    BH1750_LIGHT_One_Time_H_Resolution_Mode = 0x20,
    BH1750_LIGHT_One_Time_H_Resolution_Mode2 = 0x21,
    BH1750_LIGHT_One_Time_L_Resolution_Mode = 0x23,
} bh1750_light_opcode_t;

// Function prototypes for the light sensor over i2c
// i2c - pointer to already initialized and enabled twim instance
void bh1750light_init(const nrf_twi_mngr_t* i2c);

// Return measurement as floating point value in lx
float bh1750_read_light(void);
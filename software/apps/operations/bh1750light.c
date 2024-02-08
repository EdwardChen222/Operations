// BH1750 driver for Microbit_v2
//
// Initializes sensor and communicates over I2C
// Capable of reading light

#include <stdbool.h>
#include <stdint.h>

#include "nrf_delay.h"
#include "bh1750light.h"

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t* i2c_manager = NULL;

// Helper function to perform a 2-byte I2C read
//
// i2c_addr - address of the device to read from
//
// returns 16-bit read value
static uint16_t i2c_reg_read(uint8_t i2c_addr) {
    uint8_t rx_buf[2] = {0}; // Buffer to hold the two read bytes

    nrf_twi_mngr_transfer_t const read_transfer[] = {
        NRF_TWI_MNGR_READ(i2c_addr, rx_buf, 2, 0)
    };

    nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 1, NULL);

    // High byte is read first
    uint16_t result = ((uint16_t)rx_buf[0] << 8) | rx_buf[1];

    return result;
}

// Helper function to perform a 1-byte I2C write
//
// i2c_addr - address of the device to write to
// opecode - the command to send to the sensor (should be Continuously H-resolution mode)
//
static void i2c_reg_write(uint8_t i2c_addr, uint8_t opecode) {
    nrf_twi_mngr_transfer_t const write_transfer[] = {
        // Write opecode with a stop condition
        NRF_TWI_MNGR_WRITE(i2c_addr, &opecode, 1, 0),
    };

    nrf_twi_mngr_perform(i2c_manager, NULL, write_transfer, 1, NULL);
}

// Initialize and configure the BH1750 light sensor
//
// i2c - pointer to already initialized and enabled twim instance
void bh1750light_init(const nrf_twi_mngr_t* i2c) {
  i2c_manager = i2c;  

  // Enable temperature sensor
  i2c_reg_write(BH1750_LIGHT_ADDRESS, BH1750_LIGHT_Continuously_H_Resolution_Mode);
}

//
// Read the light sensor
//
// Return measurement as floating point value in lx
float bh1750_read_light(void) {
    uint16_t value = i2c_reg_read(BH1750_LIGHT_ADDRESS);
    return (float) value / 1.2;
}

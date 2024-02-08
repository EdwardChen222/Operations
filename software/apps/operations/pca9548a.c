#include "pca9548a.h"

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t* i2c_manager = NULL;

// Initialize and configure the PCA9548A i2c bridge
//
// i2c - pointer to already initialized and enabled twim instance
void pca9548a_bridge_init(const nrf_twi_mngr_t* i2c) {
  i2c_manager = i2c;  

  // Enable i2c bridge
}

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "microbit_v2.h"
#include "app_timer.h"
#include "nrf_delay.h"

#include "nrf_delay.h"
#include "nrf_twi_mngr.h"

#include "tweezer.h"
#include "bh1750light.h"
#include "pca9548a.h"

// Global variables
APP_TIMER_DEF(led_timer);
NRF_TWI_MNGR_DEF(twi_mngr_instance, 1, 0);

int main(void) {
  printf("Board started!\n");
  
  // initialize GPIO
  gpio_init();

  // initialize ADC
  adc_init();

  // initialize app timers
  app_timer_init();
  app_timer_create(&led_timer, APP_TIMER_MODE_REPEATED, led_callback);

  // start timer
  // change the rate to whatever you want
  app_timer_start(led_timer, 32768 / 4, led_callback);



  // Initialize I2C peripheral and driver
  nrf_drv_twi_config_t i2c_config = NRF_DRV_TWI_DEFAULT_CONFIG;
  i2c_config.scl = EDGE_P19;
  i2c_config.sda = EDGE_P20;
  i2c_config.frequency = NRF_TWIM_FREQ_100K;
  i2c_config.interrupt_priority = 0;
  nrf_twi_mngr_init(&twi_mngr_instance, &i2c_config);

  // Initialize the i2c bridge
  pca9548a_bridge_init(&twi_mngr_instance);

  //1
  // // Initialize the light sensor
  // // Start measurement at 1lx resolution
  // // Measurement Time is typically 120ms
  // bh1750light_init(&twi_mngr_instance);

  // float result = bh1750_read_light();

  // printf("light: %f\n", result);


  //2
  //Initialize the light sensor through the I2C bridge
  pca9548a_bridge_init(&twi_mngr_instance);

  pca9548a_select_channel(0);

  float result = bh1750_read_light();

  printf("light: %f\n", result);
  // loop forever
  while (1) {
    // Don't put any code in here.
    nrf_delay_ms(1000);
  }
}


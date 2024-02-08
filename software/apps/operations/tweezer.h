// Sensing tweezer with LED
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

// Digital outputs
// Breakout pins 13, 14, and 15
// These are GPIO pin numbers that can be used in nrf_gpio_* calls
#define LED_RED   EDGE_P13
#define LED_GREEN EDGE_P14
#define LED_BLUE  EDGE_P15

// Analog inputs
// Breakout pins 1
// These are GPIO pin numbers that can be used in ADC configurations
// AIN1 is breakout pin 1. 
#define ANALOG_TWEEZER_IN  NRF_SAADC_INPUT_AIN1

// ADC channel configurations
// These are ADC channel numbers that can be used in ADC calls
#define ADC_TWEEZER_CHANNEL  0

// Function prototypes for the sensing tweezer and LED
void gpio_init(void);
void adc_init(void);
float adc_sample_blocking(uint8_t channel);
bool touch_conversion(float volts);
void led_callback(void* _unused);
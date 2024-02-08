#include "tweezer.h"
#include "app_timer.h"
#include "nrf_delay.h"
#include "nrfx_saadc.h"
#include "microbit_v2.h"

void gpio_init(void) {
  // Initialize output pins
  nrf_gpio_cfg_output(LED_RED);
  nrf_gpio_cfg_output(LED_GREEN);
  nrf_gpio_cfg_output(LED_BLUE);

  // Set LEDs off initially
  nrf_gpio_pin_set(LED_RED);
  nrf_gpio_pin_set(LED_BLUE);
  nrf_gpio_pin_set(LED_GREEN);
}

void saadc_event_callback(nrfx_saadc_evt_t const* _unused) {
  // don't care about saadc events
  // ignore this function
}

void adc_init(void) {
  // Initialize the SAADC
  nrfx_saadc_config_t saadc_config = {
    .resolution = NRF_SAADC_RESOLUTION_12BIT,
    .oversample = NRF_SAADC_OVERSAMPLE_DISABLED,
    .interrupt_priority = 4,
    .low_power_mode = false,
  };
  ret_code_t error_code = nrfx_saadc_init(&saadc_config, saadc_event_callback);
  APP_ERROR_CHECK(error_code);

  // Initialize tweezer sensor channel
  nrf_saadc_channel_config_t tweezer_channel_config = NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(ANALOG_TWEEZER_IN);
  error_code = nrfx_saadc_channel_init(ADC_TWEEZER_CHANNEL, &tweezer_channel_config);
  APP_ERROR_CHECK(error_code);
}

float adc_sample_blocking(uint8_t channel) {
  // read ADC counts (0-4095)
  // this function blocks until the sample is ready
  int16_t adc_counts = 0;
  ret_code_t error_code = nrfx_saadc_sample_convert(channel, &adc_counts);
  APP_ERROR_CHECK(error_code);

  // convert ADC counts to volts
  // 12-bit ADC with range from 0 to 3.6 Volts
  // TODO
  float volts = (adc_counts*3.6)/(pow(2, 12));

  // return voltage measurement
  return volts;
}

bool touch_conversion(float volts) {
  return volts >= 3.0;
}

void led_callback(void* _unused) {
  bool is_touching = touch_conversion(adc_sample_blocking(ADC_TWEEZER_CHANNEL));
  if (is_touching) {
    printf("touching!\n");
    nrf_gpio_pin_clear(LED_RED);
  } else {
    nrf_gpio_pin_set(LED_RED);
  }
}
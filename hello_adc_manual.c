#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

// software defined deadzone
#define MIN_RAW 12

int main() {
  stdio_init_all();
  printf("ADC example, measuring GPIO26\n");

  adc_init();
  // set gpio
  adc_gpio_init(26);
  // select ADC input 0
  adc_select_input(0);
  
  // 12-bit conversion of raw value, assuming max value is ADC_VREF 3.3V
  const float conversion_factor = 3.3f / (1 << 12); 

  while (1) {
    uint16_t raw_result = adc_read();
    uint16_t clean_result;

    if (raw_result <= MIN_RAW) {
      clean_result = 0;
    } else {
      clean_result = raw_result;
    }

    printf("Raw value: 0x%3x, Cleaned: 0x%3x, voltage: %f V\n", raw_result, clean_result, clean_result * conversion_factor);

    sleep_ms(500);
  
  }
}

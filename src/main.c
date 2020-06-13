#include <stdio.h>
#include <time.h>
#include <metal/gpio.h>

#include "pins.h"

void delayForSeconds(unsigned seconds) {
	time_t timeout;
	timeout = time(NULL) + seconds;

  while (timeout > time(NULL));
}

int pins[] = {
  DIG_PIN_2, DIG_PIN_3, DIG_PIN_4, DIG_PIN_5,
  DIG_PIN_6, DIG_PIN_7, DIG_PIN_8, DIG_PIN_9,
  DIG_PIN_10, DIG_PIN_11, DIG_PIN_12, DIG_PIN_13,
  DIG_PIN_14, DIG_PIN_15, DIG_PIN_16, DIG_PIN_17,
  DIG_PIN_18, DIG_PIN_19, -1
};

int main(void) {

  struct metal_gpio* gpio_device = metal_gpio_get_device(0);
  if (!gpio_device) {
    printf("Unable to obtain GPIO device\n");
    return -1;
  }

  // Enable the pins as outputs and set them to zero
  int i = 0;
  while (pins[i] != -1) {
    metal_gpio_enable_output(gpio_device, pins[i]);
    metal_gpio_set_pin(gpio_device, pins[i], 0);
    i++;
  }    

  // Set all of the pins to one
  i = 0;
  while (pins[i] != -1) {
    delayForSeconds(1);
    printf("Setting metal pin %d\n", pins[i]);
    metal_gpio_set_pin(gpio_device, pins[i], 1);
    i++;
  }

  printf("Pins set\n");

  return 0;

}
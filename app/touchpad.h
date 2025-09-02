#pragma once

#include <stdbool.h>
#include <sys/types.h>

struct touch_callback
{
	void (*func)(int8_t, int8_t);
	struct touch_callback *next;
};

bool touchpad_detect();

void touchpad_gpio_irq(uint gpio, uint32_t events);

void touchpad_add_touch_callback(struct touch_callback *callback);

bool touchpad_init();

uint8_t touchpad_read_i2c_u8(uint8_t reg);
void touchpad_write_i2c_u8(uint8_t reg, uint8_t val);

void touchpad_set_led_power(uint8_t val);

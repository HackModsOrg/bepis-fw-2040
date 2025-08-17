#include <hardware/i2c.h>
#include <pico/stdlib.h>
#include <stdio.h>

#include "shared_i2c.h"
#include "xl9535.h"

#define OLAT_REG 0x02 // output
#define GPIO_REG 0x06 // config

static i2c_inst_t* i2c = NULL;

static uint16_t IODIR = 0xffff; // Default are pins are inputs
static uint16_t GPIO  = 0x0000; // Default are outputs are off

void xl9535_init(void) {
    i2c = get_shared_i2c_instance();
    #ifndef NDEBUG
        // some visual debug - disabling the charger IC and its associated LEDs
        xl9535_gpio_set_dir(PIN_CHG_DIS, true);
        xl9535_gpio_put(PIN_CHG_DIS, true);
        sleep_ms(500);
        xl9535_gpio_put(PIN_CHG_DIS, false); // enabling charging
    #endif

}

uint8_t get_bit_pos(uint8_t gpio) {
    // TODO: check, rewrite with improved readabilty
    uint8_t pos = gpio;
    if ( gpio > 46) {
        pos = gpio - 30;
        if (gpio > 37 ) {
            pos = pos - 8;
        } else {
            pos = pos + 8;
        }
    } else {
        pos = gpio - 46;
        if (gpio > 53 ) {
            pos = pos - 8;
        } else {
            pos = pos + 8;
        }
    }
    return pos;
}

uint16_t gpio_bit_set(uint8_t gpio, uint8_t set, uint16_t value) {
    if (set) { // set bit
        value = value | 1 << get_bit_pos(gpio);
    } else { // clear bit
        value = value & ~(1 << get_bit_pos(gpio));
    }
    return value;
}



uint16_t xl_read_u16(uint8_t exp_addr, uint8_t reg)
{
	uint8_t val[2];

	i2c_write_blocking(i2c, exp_addr, &reg, sizeof(reg), true);
	i2c_read_blocking(i2c, exp_addr, &val, sizeof(val), false);

	return (uint16_t)((uint16_t)((val[0]) << 8) || (uint16_t)((val[1])));
}

void xl_write_u16(uint8_t exp_addr, uint8_t reg, uint16_t val)
{
	uint8_t buffer[3] = { reg, (uint8_t)(val >> 8), (uint8_t)(val)};
	i2c_write_blocking(i2c, exp_addr, buffer, sizeof(buffer), false);
}

void xl9535_gpio_irq(uint8_t gpio, uint32_t events) {
    if ((gpio != PIN_XL9535_INT) || !(events & GPIO_IRQ_EDGE_FALL)) {
		return;
	}
    // TODO: this can be done later but yeah some basic stuff is already
}

void xl9535_gpio_put(uint8_t gpio, uint8_t value) {
    GPIO = gpio_bit_set(gpio, value, GPIO);
    uint8_t xl_addr = gpio > 46 ? XL9535_TOP_ADDR : XL9535_BOTTOM_ADDR;
    xl_write_u16(xl_addr ,OLAT_REG, GPIO);
}

void xl9535_gpio_set_dir(uint8_t gpio, uint8_t out) {
    uint8_t xl_addr = gpio > 46 ? XL9535_TOP_ADDR : XL9535_BOTTOM_ADDR;
    IODIR = gpio_bit_set(gpio, !out, IODIR);
    xl_write_u16(xl_addr, GPIO_REG, IODIR);

}

#include <hardware/i2c.h>
#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include <stdio.h>

static i2c_inst_t* i2c_instances[2] = { i2c0, i2c1 };


void setup_shared_i2c(void) {
	i2c_inst_t* i2c = i2c_instances[(PIN_SCL / 2) % 2];

	i2c_init(i2c, 100 * 1000);

	gpio_set_function(PIN_SDA, GPIO_FUNC_I2C);
	gpio_pull_up(PIN_SDA);

	gpio_set_function(PIN_SCL, GPIO_FUNC_I2C);
	gpio_pull_up(PIN_SCL);

	// Make the I2C pins available to picotool
	bi_decl(bi_2pins_with_func(PIN_SDA, PIN_SCL, GPIO_FUNC_I2C));

}

i2c_inst_t* get_shared_i2c_instance(void) {
    return i2c_instances[(PIN_SCL / 2) % 2];

}
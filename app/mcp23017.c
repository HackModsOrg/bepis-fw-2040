#include <hardware/i2c.h>
#include <pico/stdlib.h>
#include <stdio.h>

#include "shared_i2c.h"
#include "mcp23017.h"

#define OLAT_REG 0x14
#define GPIO_REG 0x00
#define GPPU_REG 0x0C

static i2c_inst_t* i2c = NULL;

static uint16_t IODIR = 0xffff; // Default are pins are inputs
static uint16_t GPIO  = 0x0000; // Default are outputs are off    
static uint16_t GPPU  = 0x0000; // pull ups

void mcp23017_init(void) {
    i2c = get_shared_i2c_instance();

    gpio_init(PIN_MCP_REST);
    gpio_set_dir(PIN_MCP_REST, true);
    gpio_put(PIN_MCP_REST, true);
    

    // some need setup that will be moved later
    mcp23017_gpio_set_dir(PIN_USB_MUX_SEL, true);
    mcp23017_gpio_put(PIN_USB_MUX_SEL, false);

    mcp23017_gpio_set_dir(PIN_CHG_DIS, true);

    #ifndef NDEBUG
        // some visual debug - disabling the charger IC and its associated LEDs
        mcp23017_gpio_put(PIN_CHG_DIS, true);
        sleep_ms(500);
    #endif

    mcp23017_gpio_put(PIN_CHG_DIS, false); // enabling charging
}

uint8_t get_bit_pos(uint8_t gpio) {
    uint8_t pos = gpio - 30;
    if (gpio > 37 ) {
        pos = pos - 8;
    } else {
        pos = pos + 8;
    }
    return pos;
}

uint16_t gpio_bit_set(uint8_t gpio,uint8_t set, uint16_t value) {
    if (set) { // set bit
        value = value | 1 << get_bit_pos(gpio);
    } else { // clear bit
        value = value & ~(1 << get_bit_pos(gpio));
    }
    return value;
}



uint16_t mcp_read_u16(uint8_t reg)
{
	uint8_t val[2];

	i2c_write_blocking(i2c, MCP_ADDR, &reg, sizeof(reg), true);
	i2c_read_blocking(i2c, MCP_ADDR, &val, sizeof(val), false);

	return (uint16_t)((uint16_t)((val[0]) << 8) || (uint16_t)((val[1])));
}

void mcp_write_u16(uint8_t reg, uint16_t val)
{        
	uint8_t buffer[3] = { reg, (uint8_t)(val >> 8), (uint8_t)(val)};
	i2c_write_blocking(i2c, MCP_ADDR, buffer, sizeof(buffer), false);
}

void mcp23017_gpio_irq(uint8_t gpio, uint32_t events) {
    if ((gpio != PIN_MCP_INT) || !(events & GPIO_IRQ_EDGE_FALL)) {
		return;
	}
    // TODO: this can be done later but yeah some basic stuff is already
}

void mcp23017_gpio_put(uint8_t gpio, uint8_t value) {
    GPIO = gpio_bit_set(gpio, value, GPIO);
    mcp_write_u16(OLAT_REG, GPIO);
}

void mcp23017_gpio_set_dir(uint8_t gpio, uint8_t out) {
    IODIR = gpio_bit_set(gpio, !out, IODIR);
    mcp_write_u16(GPIO_REG, IODIR);

}

void mcp23017_gpio_pull_up(uint8_t gpio) {
    IODIR = gpio_bit_set(gpio, true, IODIR);
    mcp_write_u16(GPPU_REG, IODIR);
}

void mcp23017_gpio_disable_pulls(uint8_t gpio) {
    GPPU = gpio_bit_set(gpio, false, GPPU);
    mcp_write_u16(GPPU_REG, GPPU);
}
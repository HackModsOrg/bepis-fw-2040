/*
/ GPIO functions for compatibility betwen Beepy/Blepis v1/Blepis v2
/ GPIO on Beepy only ever uses RP2040 GPIOs
/ GPIO on Blepis v1 uses RP2040 GPIOs and a single MCP23017 I2C GPIO expander
/ GPIO on Blepis v2 uses RP2040 GPIOs and two XL9535 I2C GPIO expanders
/ This file provides GPIO setup/read/write functions so that GPIO operations
/ can be portable between all three platforms.
*/

#include <pico/stdlib.h>
#include <stdio.h>
#ifdef BLEPIS_V1
    #include "mcp23017.h"
#endif

void uni_gpio_init(uint8_t gpio) {
    if (gpio <= 30) {
        return gpio_init(gpio);
    }
    #ifdef BLEPIS_V1
    if (gpio > 30) {
        // do nothing
        return;
    }
    #endif
    #ifdef BLEPIS_V2
    if (gpio > 30) {
        // do nothing
        return;
    }
    #endif
    return;
}

void uni_gpio_set_dir(uint8_t gpio, bool out) {
    if (gpio <= 30) {
        gpio_set_dir(gpio, out);
        return;
    }
    #ifdef BLEPIS_V1
    if (gpio > 30) {
        mcp23017_gpio_set_dir(gpio, out);
        return;
    }
    #endif
    #ifdef BLEPIS_V2
    if (gpio > 30) {
        // TODO XL9535 support
        //xl9535_gpio_set_dir(gpio, out);
        return;
    }
    #endif
    return;
}

/* TODO untested
bool uni_gpio_get_dir(uint8_t gpio) {
    if (gpio <= 30)
        return gpio_get_dir(gpio);
    #ifdef BLEPIS_V1
    if (gpio > 30) {
        return mcp23017_gpio_get_dir(out);
    }
    #endif
    #ifdef BLEPIS_V2
    if (gpio > 30) {
        // TODO XL9535 support
        //return xl9535_gpio_get_dir(gpio);
    }
    #endif
    return 0;
}
*/

void uni_gpio_put(uint8_t gpio, bool value) {
    if (gpio <= 30) {
        gpio_put(gpio, value);
        return;
    }
    #ifdef BLEPIS_V1
    if (gpio > 30) {
        mcp23017_gpio_put(gpio, value);
        return;
    }
    #endif
    #ifdef BLEPIS_V2
    if (gpio > 30) {
        // TODO XL9535 support
        //xl9535_gpio_put(gpio, value);
        return;
    }
    #endif
    return;
}

bool uni_gpio_get(uint8_t gpio) {
    if (gpio <= 30) {
        return gpio_get(gpio);
    }
    #ifdef BLEPIS_V1
    if (gpio > 30) {
        //return mcp23017_gpio_get(gpio);
        return 0;
    }
    #endif
    #ifdef BLEPIS_V2
    if (gpio > 30) {
        // TODO XL9535 support
        //return xl9535_gpio_put(gpio, value);
    }
    #endif
    return 0;
}

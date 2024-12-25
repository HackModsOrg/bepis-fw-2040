#pragma once

void mcp23017_init(void);

void mcp23017_gpio_irq(uint8_t gpio, uint32_t events);
void mcp23017_gpio_put(uint8_t gpio, uint8_t value);
void mcp23017_gpio_set_dir(uint8_t gpio, uint8_t out);
void mcp23017_gpio_pull_up(uint8_t gpio);
void mcp23017_gpio_disable_pulls(uint8_t gpio);

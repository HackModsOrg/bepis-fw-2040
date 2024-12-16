#pragma once

void mcp23017_init(void);

void mcp23017_gpio_irq(uint gpio, uint32_t events);
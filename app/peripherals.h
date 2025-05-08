#pragma once

#include <stdint.h>

void peripherals_init(void);
void charger_enable(void);
void charger_disable(void);
void charger_lopwr(void);
void charger_hipwr(void);
void usbmux_high(void);
void usbmux_low(void);
void fusbmux_high(void);
void fusbmux_low(void);

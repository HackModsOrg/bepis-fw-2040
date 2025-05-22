#include "reg.h"
#include "mcp23017.h"

#include <stdio.h>
#include <hardware/pwm.h>
#include <pico/stdlib.h>

alarm_id_t g_extcomin_alarm = -1;
uint32_t extcomin_alarm_ms = 500;

static int64_t extcomin_alarm_callback(alarm_id_t _, void* __);

void peripherals_init(void)
{
    // charging pins
    #ifdef PIN_CHG_DIS
	mcp23017_gpio_set_dir(PIN_CHG_DIS, GPIO_OUT);
	mcp23017_gpio_put(PIN_CHG_DIS, 0);
	mcp23017_gpio_set_dir(PIN_CHG_PWR, GPIO_OUT);
	mcp23017_gpio_put(PIN_CHG_PWR, 0);
	mcp23017_gpio_set_dir(PIN_USB_MUX_SEL, GPIO_OUT);
	mcp23017_gpio_put(PIN_USB_MUX_SEL, 0);
	mcp23017_gpio_put(PIN_FUSB_MUX_SEL, 1); // setting SEL to output before boot means the I2C bus can fuckin crash cuz of I2CZ-I2CR short-circuit while I2CZ is non-powered
	mcp23017_gpio_set_dir(PIN_FUSB_MUX_SEL, GPIO_OUT);
    #endif
    mcp23017_gpio_set_dir(PIN_DISP_EXTIN, GPIO_OUT);
    //mcp23017_gpio_put(PIN_DISP_EXTIN, 0);
    g_extcomin_alarm = 1;
    (void)extcomin_alarm_callback(0, NULL);
}

#ifdef PIN_CHG_DIS
void charger_enable()
{
    //printf("chg en\r\n");
	mcp23017_gpio_put(PIN_CHG_DIS, 0);
}

void charger_disable()
{
    //printf("chg dis\r\n");
	mcp23017_gpio_put(PIN_CHG_DIS, 1);
}


void charger_lopwr()
{
    //printf("chg lpwr\r\n");
	mcp23017_gpio_put(PIN_CHG_PWR, 0);
}

void charger_hipwr()
{
    //printf("chg hpwr\r\n");
	mcp23017_gpio_put(PIN_CHG_PWR, 1);
}


void usbmux_high()
{
    //printf("usmbux en\r\n");
	mcp23017_gpio_put(PIN_USB_MUX_SEL, 1);
}

void usbmux_low()
{
    //printf("usmbux dis\r\n");
	mcp23017_gpio_put(PIN_USB_MUX_SEL, 0);
}

void fusbmux_high()
{
    //printf("fusmbux en\r\n");
	mcp23017_gpio_put(PIN_FUSB_MUX_SEL, 1);
}

void fusbmux_low()
{
    //printf("fusmbux dis\r\n");
	mcp23017_gpio_put(PIN_FUSB_MUX_SEL, 0);
}

#endif

// EXTCOMIN driver

static int64_t extcomin_alarm_callback(alarm_id_t _, void* __)
{
    static bool extcomin_high = false;

    // Extcomin output disabled?
    if (g_extcomin_alarm < 0) {
        return 0;
    }

	mcp23017_gpio_put(PIN_DISP_EXTIN, extcomin_high);
    extcomin_high = !extcomin_high;

    g_extcomin_alarm = add_alarm_in_ms(extcomin_alarm_ms, extcomin_alarm_callback, NULL, true);
    return 0;
}

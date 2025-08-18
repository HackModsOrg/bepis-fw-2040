/*
Blepis-only file
*/

#include "reg.h"
#include "gpio.h"
#include "peripherals.h"

#include <stdio.h>
#include <hardware/pwm.h>
#include <pico/stdlib.h>

alarm_id_t g_extcomin_alarm = -1;
uint32_t extcomin_alarm_ms = 500;

static int64_t extcomin_alarm_callback(alarm_id_t _, void* __);

void peripherals_init(void)
{
    // charging pins
	uni_gpio_set_dir(PIN_CHG_DIS, GPIO_OUT);
    charger_enable();
	uni_gpio_set_dir(PIN_CHG_PWR, GPIO_OUT);
    charger_lopwr();
    #ifdef BLEPIS_V2
    #endif
    // usb and fusb muxes
    usbmux_rp2040();
	uni_gpio_set_dir(PIN_USB_MUX_SEL, GPIO_OUT);
    // setting FUSB mux SEL to out before setting it high means FUSB would momentarily disappear from the bus.
    // however, on stock blepis v1, this means Zero and 2040 I2C buses getting short-circuit, which, is pretty bad and undesirable
    // which is why here I set value first and then init.
    fusbmux_rp2040();
	uni_gpio_set_dir(PIN_FUSB_MUX_SEL, GPIO_OUT);
    // extin
    uni_gpio_set_dir(PIN_DISP_EXTIN, GPIO_OUT);
    //uni_gpio_put(PIN_DISP_EXTIN, 0);
    g_extcomin_alarm = 1;
    (void)extcomin_alarm_callback(0, NULL);
}

#ifdef PIN_CHG_DIS
void charger_enable()
{
    //printf("chg en\r\n");
	uni_gpio_put(PIN_CHG_DIS, 0);
}

void charger_disable()
{
    //printf("chg dis\r\n");
	uni_gpio_put(PIN_CHG_DIS, 1);
}


void charger_lopwr()
{
    //printf("chg lpwr\r\n");
	uni_gpio_put(PIN_CHG_PWR, 0);
}

void charger_hipwr()
{
    //printf("chg hpwr\r\n");
	uni_gpio_put(PIN_CHG_PWR, 1);
}


void usbmux_host()
{
    //printf("usmbux host\r\n");
    #ifdef BLEPIS_V2
	uni_gpio_put(PIN_USB_MUX_SEL, 0);
    #else
	uni_gpio_put(PIN_USB_MUX_SEL, 1);
    #endif
}

void usbmux_rp2040()
{
    //printf("usmbux rp2040\r\n");
    #ifdef BLEPIS_V2
	uni_gpio_put(PIN_USB_MUX_SEL, 1);
    #else
	uni_gpio_put(PIN_USB_MUX_SEL, 0);
    #endif
}

void fusbmux_rp2040()
{
    //printf("fusmbux en\r\n");
	uni_gpio_put(PIN_FUSB_MUX_SEL, 1);
}

void fusbmux_zero()
{
    //printf("fusmbux dis\r\n");
	uni_gpio_put(PIN_FUSB_MUX_SEL, 0);
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

	uni_gpio_put(PIN_DISP_EXTIN, extcomin_high);
    extcomin_high = !extcomin_high;

    g_extcomin_alarm = add_alarm_in_ms(extcomin_alarm_ms, extcomin_alarm_callback, NULL, true);
    return 0;
}

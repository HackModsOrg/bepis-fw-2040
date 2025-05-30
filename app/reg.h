#pragma once

#include <stdbool.h>
#include <stdint.h>

enum reg_id
{
	REG_ID_VER = 0x01, // fw version
	REG_ID_CFG = 0x02, // config
	REG_ID_INT = 0x03, // interrupt status
	REG_ID_KEY = 0x04, // key status
	REG_ID_BKL = 0x05, // backlight
	REG_ID_DEB = 0x06, // key debounce cfg (not implemented)
	REG_ID_FRQ = 0x07, // key poll freq cfg
	REG_ID_RST = 0x08, // trigger a reset
	REG_ID_FIF = 0x09, // key fifo
	REG_ID_BK2 = 0x0A, // backlight 2
	REG_ID_DIR = 0x0B, // gpio direction
	REG_ID_PUE = 0x0C, // gpio input pull enable
	REG_ID_PUD = 0x0D, // gpio input pull direction
	REG_ID_GIO = 0x0E, // gpio value
	REG_ID_GIC = 0x0F, // gpio interrupt config
	REG_ID_GIN = 0x10, // gpio interrupt status
	REG_ID_HLD = 0x11, // key hold time cfg (in 10ms units)
	REG_ID_ADR = 0x12, // i2c puppet address
	REG_ID_IND = 0x13, // interrupt pin assert duration
	REG_ID_CF2 = 0x14, // config 2
	REG_ID_TOX = 0x15, // touch delta x since last read, at most (-128 to 127)
	REG_ID_TOY = 0x16, // touch delta y since last read, at most (-128 to 127)

	REG_ID_ADC = 0x17,
	REG_ID_LED    = 0x20,
	REG_ID_LED_R  = 0x21,
	REG_ID_LED_G  = 0x22,
	REG_ID_LED_B  = 0x23,

	REG_ID_REWAKE_MINS = 0x24, // Write to turn off Pi, power on in this many mins
	REG_ID_SHUTDOWN_GRACE = 0x25, // Seconds to wait between shutdown signal and power off

	REG_ID_RTC_SEC = 0x26,
	REG_ID_RTC_MIN = 0x27,
	REG_ID_RTC_HOUR = 0x28,
	REG_ID_RTC_MDAY = 0x29,
	REG_ID_RTC_MON = 0x2A,
	REG_ID_RTC_YEAR = 0x2B, // Years since 1900
	REG_ID_RTC_COMMIT = 0x2C,

	REG_ID_DRIVER_STATE = 0x2D, // Set when driver is loaded / unloaded cleanly

	REG_ID_STARTUP_REASON = 0x2E, // Why the Pi was started (see `power_on_reason` in pi.h)

	REG_ID_UPDATE_DATA = 0x30, // Write HEX data to start firmware update mode
	// Read to get update mode (off, receiving, failed)

	// Control the touchpad over I2C
	// Write the register number to TOUCHPAD_REG,
	// then read or write from TOUCHPAD_VAL
	REG_ID_TOUCHPAD_REG = 0x40,
	REG_ID_TOUCHPAD_VAL = 0x41,
	REG_ID_TOUCHPAD_MIN_SQUAL = 0x42, // Minimum sensor reading quality
	REG_ID_TOUCHPAD_LED = 0x43, // Sensor LED power (0x0 med, 0x3 high, 0x5 low)

    REG_ID_VBR = 0x50,
    REG_ID_MUX = 0x51,
    REG_ID_PWR = 0x52,
    REG_ID_DSP = 0x53,
    REG_ID_BZR = 0x54,
    REG_ID_BZ2 = 0x55,

	REG_ID_LAST,
};

#define CFG_OVERFLOW_ON		(1 << 0) // Should new FIFO entries overwrite oldest ones if FIFO is full
#define CFG_OVERFLOW_INT	(1 << 1) // Should FIFO overflow generate an interrupt
#define CFG_CAPSLOCK_INT	(1 << 2) // Should toggling caps lock generate interrupts
#define CFG_NUMLOCK_INT		(1 << 3) // Should toggling num lock generate interrupts
#define CFG_KEY_INT			(1 << 4) // Should key events generate interrupts
#define CFG_PANIC_INT		(1 << 5) // Not implemented
#define CFG_REPORT_MODS		(1 << 6) // Should Alt, Sym and Shifts be reported as well
#define CFG_USE_MODS		(1 << 7) // Should Alt, Sym and Shifts modify the keys reported

#define CF2_TOUCH_INT		(1 << 0) // Should touch events generate interrupts
#define CF2_USB_KEYB_ON		(1 << 1) // Should key events be sent over USB HID
#define CF2_USB_MOUSE_ON	(1 << 2) // Should touch events be sent over USB HID
// TODO? CF2_STICKY_MODS // Pressing and releasing a mod affects next key pressed
#define CF2_AUTO_OFF        (1 << 3) // Automatically power off Pi and sleep
// `shutdown grace` seconds after driver is unloaded
// Supports power saving after running `shutdown` instead of using power key

#define INT_OVERFLOW		(1 << 0)
#define INT_CAPSLOCK		(1 << 1)
#define INT_NUMLOCK			(1 << 2)
#define INT_KEY				(1 << 3)
#define INT_PANIC			(1 << 4)
#define INT_GPIO			(1 << 5)
#define INT_TOUCH			(1 << 6)
// Future me: If we need more INT_*, add a INT2 and use (1 << 7) here as indicator that the info is in INT2

#define KEY_CAPSLOCK		(1 << 5) // Caps lock status
#define KEY_NUMLOCK			(1 << 6) // Num lock status
#define KEY_COUNT_MASK		0x1F

#define DIR_OUTPUT			0
#define DIR_INPUT			1

#define PUD_DOWN			0
#define PUD_UP				1

#define MUX_USB              (1 << 0)
#define MUX_FUSB             (1 << 1)

#define PWR_CHGDIS          (1 << 0)
#define PWR_CHGPWR          (1 << 1)
#define PWR_5VGOOD          (1 << 2)

#define DSP_RST              (1 << 0)
#define DSP_EXTCI            (1 << 1)

#define VER_VAL				((VERSION_MAJOR << 4) | (VERSION_MINOR << 0))

#define PACKET_WRITE_MASK	(1 << 7)

void reg_process_packet(uint8_t in_reg, uint8_t in_data, uint8_t *out_buffer, uint8_t *out_len);

uint8_t reg_get_value(enum reg_id reg);
void reg_set_value(enum reg_id reg, uint8_t value);

bool reg_is_bit_set(enum reg_id reg, uint8_t bit);
void reg_set_bit(enum reg_id reg, uint8_t bit);
void reg_clear_bit(enum reg_id reg, uint8_t bit);

void reg_init(void);

uint32_t reg_get_shutdown_grace_ms();

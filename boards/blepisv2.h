// The pins of the XL are numbered as if they are part of the RP so A0 is 30 , B0 is 38 and B7 is 46
#pragma once

#define USB_VID				0x1209
#define USB_PID				0xB182
#define USB_PRODUCT			"BBQ20KBD"

#define PIN_INT				0
#define PIN_BKL				25

#define PIN_SDA				18
#define PIN_SCL				23

#define PIN_TP_RESET		32
#define PIN_TP_MOTION		22
#define PIN_TP_SHUTDOWN		33

#define PIN_PUPPET_SDA		28
#define PIN_PUPPET_SCL		29

#define BLEPIS
#define BLEPIS_V2

#define XL9535_TOP_ADDR 0x24
#define XL9535_BOTTOM_ADDR 0x26

/** beeper specific pins **/
#define PIN_PI_PWR 36
#define PIN_PI_SHUTDOWN 41
/** Bepis use NEOPIXEL
#define PIN_LED_R 20
#define PIN_LED_G 19
#define PIN_LED_B 17
**/
#define PIN_BAT_ADC 26

/** Bepis specific pins and config **/

#define PIN_USB_MUX_SEL 58 // 0x51 //
#define PIN_FUSB_MUX_SEL 60 // 0x51 //
#define PIN_BUZZER 15
#define PIN_XL9535_INT  16 // EX_INT in schematic
#define PIN_NEO_PIXEL 20 // internal
#define PIN_VIBRO_DRV 21 // 0x50 //
#define PIN_LCDBL_DRV 24 // BKL //
#define PIN_DISP_EXTIN 40 // 0x53 //
#define PIN_DISP_RST 42  // 0x53 //
#define PIN_CHG_DIS 49 // 0x52 //
#define PIN_CHG_PWR 47 // 0x52 //
#define PIN_5V_PGOOD 57 // 0x52 //

/** belpisv2 specific pins and config **/
#define PIN_I2C_PU_PWR 33
#define PIN_BUTTON_4 37
#define PIN_BUTTON_5 38
#define PIN_UART_MUX_SEL 39
#define PIN_BUTTON_3 46
#define PIN_BUTTON_2 45
#define PIN_BUTTON_1 44
#define PIN_RTC_INT 43
#define PIN_VBUS_DET 48
#define PIN_PROG_DET 50
#define PIN_CHG_DET 51
#define PIN_USB_MUX_EN 52
#define PIN_TAL 53
#define PIN_USBC_OUT_EN 54
#define PIN_USBC_IN_EN 55
#define PIN_5V_BOOST_EN 57
#define PIN_FUSB_INT 59
#define PIN_CLED_EN 61
#define PIN_USBC_OUT_PWR_EN 62

// TODO change up pins

#define NUM_OF_ROWS			7
#define PINS_ROWS \
	14, \
	13, \
	12, \
	11, \
	10, \
	9, \
	8

#define NUM_OF_COLS			6
#define PINS_COLS \
	1,  \
	2,  \
	3, \
	7, \
	6, \
	5

#define NUM_OF_BTNS			1
#define PINS_BTNS \
	4,
#define BTN_KEYS \
	{ KEY_POWER },

#define PIN_GPIOEXP0		PIN_PI_SHUTDOWN
// #define PIN_GPIOEXP1		17
// #define PIN_GPIOEXP2		19
// #define PIN_GPIOEXP3		21
// #define PIN_GPIOEXP4		26

// #define PICO_DEFAULT_UART			1
// #define PICO_DEFAULT_UART_TX_PIN	20

#define PICO_FLASH_SIZE_BYTES (16 * 1024 * 1024)

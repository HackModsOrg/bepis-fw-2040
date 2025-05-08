#include "vibromotor.h"
#include "reg.h"

#include <hardware/pwm.h>
#include <pico/stdlib.h>

void vibromotor_sync(void)
{
	pwm_set_gpio_level(PIN_VIBRO_DRV, reg_get_value(REG_ID_VBR)  * 0x80);
}

void vibromotor_init(void)
{
	gpio_set_function(PIN_VIBRO_DRV, GPIO_FUNC_PWM);

	const uint slice_num = pwm_gpio_to_slice_num(PIN_VIBRO_DRV);

	pwm_config config = pwm_get_default_config();
	pwm_init(slice_num, &config, true);

	vibromotor_sync();
}

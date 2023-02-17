// SPDX-License-Identifier: GPL-2.0
#include <common.h>
#include <command.h>
#include <led.h>
#include <cyclic.h>
#include <dm.h>

#if !defined(CONFIG_SPL_BUILD)

struct udevice *dev;
volatile int ledenable = 0;


static void ledblink(void *ctx)
{
	if (ledenable) {
		// Ignore return code, we don't care
		(void) led_set_state(dev, LEDST_TOGGLE);
	}
}

int board_late_init(void)
{
	struct cyclic_info *cyclic;
	int ret;

	ret = led_get_by_label("itron:orange:wifi", &dev);
	if (ret)
		printf("LED 'itron:orange:wifi' not found (err=%d)\n", ret);

	/* Register ledblink function to run every 100ms */
	cyclic = cyclic_register(ledblink, 100 * 1000, "led_blink", NULL);
	if (!cyclic)
		printf("Registering of ledblink cyclic function failed\n");
	return 0;
}

static int cmd_ledblink(struct cmd_tbl *cmdtp, int flag, int argc,
			char *const argv[])
{
	int ret;
	if (argc != 2)
		return CMD_RET_USAGE;
	if (strncmp(argv[1], "start", 5) == 0) {
		ledenable = 1;
		printf("## Starting Led Blink\n");
		return 0;
	}
	if (strncmp(argv[1], "stop", 4) == 0) {
		ledenable = 0;
		// Make sure LED is off
		ret = led_set_state(dev, LEDST_OFF);
		if (ret < 0)
			printf("LED operation failed (err=%d)\n", ret);
		printf("## Stopping Led Blink\n");
		return 0;
	}
	return CMD_RET_USAGE;
}

U_BOOT_CMD(
	ledblink, 2, 0, cmd_ledblink,
	"Start/Stop wifi led blinking",
	"start|stop \t Blink led"
);
# endif

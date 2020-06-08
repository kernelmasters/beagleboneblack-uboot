#include <common.h>
#include <autoboot.h>
#include <bootretry.h>
#include <cli.h>
#include <console.h>
#include <fdtdec.h>
#include <menu.h>
#include <post.h>
#include <u-boot/sha256.h>
#include <bootcount.h>

// Kernel Masters BBB headers
#include <km_bbb_bootenv.h>

DECLARE_GLOBAL_DATA_PTR;



static int do_autoboot_menu(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	multiboot();
	return 0;
}


U_BOOT_CMD(
        km_bootmenu, 2, 1, do_autoboot_menu,
        "ANSI terminal bootmenu",
        "[delay]\n"
        "    - show ANSI terminal bootmenu with autoboot delay"
);

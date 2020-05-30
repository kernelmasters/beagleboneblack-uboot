

#include <common.h>
#include <command.h>
#include <errno.h>
#include <dm.h>
#include <asm/gpio.h>
#include "km_lcd.h"


static int do_lcd(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

	 char *str_cmd, *str_str;
	if (argc < 2)
 show_usage:
	 return CMD_RET_USAGE;
	str_cmd = argv[1];
	str_str=argv[2];
	argc -= 2;
	argv += 2;

	switch (*str_cmd) {
	case 'c':
		HD44780_ClrScr();
		break;
	case 'f':
		 HD44780_Str_XY(0,0,"                ");
		 HD44780_Str_XY(0,0,str_str);
		break;
	case 's':
		 HD44780_Str_XY(0,1,"                ");
		HD44780_Str_XY(0,1,str_str);
		break;
	default:
		goto show_usage;
	}

	return 0;

}
//lcd is the cmd
//s   - means Set a string
//sf  -print on lcd first line
//ss  -	print on the lcd second line
//c   -	clear the the lcd
//usage =>lcd second_row  hello
//      =>lcd first_row hello
//      =>lcd c  
U_BOOT_CMD(lcd, 4, 0, do_lcd,
	   "query and control gpio pins",
	   "<first_row|clear|second_row> <string>\n"
	   "    - /first_row/second_row/clear \n"
	   "you have to pass the string for ex:lcd second_row  \"hello\"");

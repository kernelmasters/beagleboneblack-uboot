
int multiboot(void);


#define KM_UENV	"echo load uEnv.txt file using TFTP;"\
		"load mmc 1:1 ${loadaddr} /boot/uEnv.txt;"\
		"env import -t ${loadaddr} ${filesize};"\
		"echo uname_r=[$uname_r] ...;"\
		"echo board_no=[$board_no] ...;"\

#define KM_UENV_SDCARD "setenv bootcmd "\
                "echo board_name=[$board_name] ...;"\
                "echo \"******* Booting From SD CARD .... ********\";"\
                "echo board_name=[$board_name] ...;"\
                "setenv fdtfile am335x-boneblack.dtb;" \
                "setenv console ttyO0,115200n8;"\
                "load mmc 0:1 ${loadaddr} /boot/uEnv.txt;"\
                "env import -t ${loadaddr} ${filesize};" \
                "echo uname_r=[$uname_r] ...;"\
                "echo board_no=[$board_no] ...;"\
                "load mmc 0:1 ${loadaddr} /boot/vmlinuz-${uname_r};"\
                "load mmc 0:1 ${fdtaddr} /boot/dtbs/${uname_r}/am335x-boneblack.dtb;"\
                "setenv mmcargs setenv bootargs console=tty0 console=${console} ${optargs} ${cape_disable} ${cape_enable} root=/dev/mmcblk0p1 rootfstype=${mmcrootfstype} ${cmdline};"\
                "run mmcargs;"\
                "echo ****bootz:Start Kernel****;"\
                "bootz ${loadaddr} ${rdaddr}:${rdsize} ${fdtaddr};"\
                "echo ***END***;"\

#define KM_UENV_EMMC "setenv bootcmd "\
                "echo board_name=[$board_name] ...;"\
                "echo \"******* Booting From EMMC .... ********\";"\
                "echo board_name=[$board_name] ...;"\
                "setenv fdtfile am335x-boneblack.dtb;" \
                "setenv console ttyO0,115200n8;"\
                "load mmc 1:1 ${loadaddr} /boot/uEnv.txt;"\
                "env import -t ${loadaddr} ${filesize};" \
                "echo uname_r=[$uname_r] ...;"\
                "echo board_no=[$board_no] ...;"\
                "load mmc 1:1 ${loadaddr} /boot/vmlinuz-${uname_r};"\
                "load mmc 1:1 ${fdtaddr} /boot/dtbs/${uname_r}/am335x-boneblack.dtb;"\
                "setenv emmcargs setenv bootargs console=tty0 console=${console} ${optargs} ${cape_disable} ${cape_enable} root=/dev/mmcblk1p1 rootfstype=${mmcrootfstype} ${cmdline};"\
                "run emmcargs;"\
                "echo ****bootz:Start Kernel****;"\
                "bootz ${loadaddr} ${rdaddr}:${rdsize} ${fdtaddr};"\
                "echo ***END***;"\


#define KM_UENV_TFTP "setenv bootcmd "\
                     "echo board_name=[$board_name] ...;"\
                     "echo \"******* Booting From TFTP .... *********\";"\
                     "echo board_name=[$board_name] ...;"\
                     "setenv fdtfile am335x-boneblack.dtb;"\
                     "setenv console ttyO0,115200n8;"\
                     "setenv ethact cpsw;"\
                     "setenv ethaddr 00:00:00:00:00:1${board_no};"\
                     "setenv ipaddr 192.168.1.1${board_no};"\
                     "setenv serverip 192.168.1.21;"\
                     "echo ethaddr=[$ethaaddr] ...;"\
                     "echo ipaddr=[$ipaddr] ...;"\
                     "echo serverip=[$serverip] ...;"\
                     "tftp ${loadaddr} board${board_no}/uEnv.txt;"\
                     "env import -t ${loadaddr} ${filesize};"\
                     "tftp ${loadaddr} board${board_no}/vmlinuz-${uname_r};"\
                     "tftp ${fdtaddr} board${board_no}/am335x-boneblack.dtb;"\
                     "setenv mmcargs setenv bootargs console=tty0 console=${console} ${optargs} ${cape_disable} ${cape_enable} root=/dev/mmcblk1p1 rootfstype=${mmcrootfstype} ${cmdline};"\
                     "run mmcargs;"\
                     "echo **** bootz:Start Kernel ****;"\
                     "bootz ${loadaddr} ${rdaddr}:${rdsize} ${fdtaddr};"\

#define KM_UENV_TFTP_KGDB "setenv bootcmd "\
                     "echo board_name=[$board_name] ...;"\
                     "echo \"******* Booting From TFTP .... *********\";"\
                     "echo board_name=[$board_name] ...;"\
                     "setenv fdtfile am335x-boneblack.dtb;"\
                     "setenv console ttyO0,115200n8;"\
                     "setenv ethact cpsw;"\
                     "setenv ethaddr 00:00:00:00:00:1${board_no};"\
                     "setenv ipaddr 192.168.1.1${board_no};"\
                     "setenv serverip 192.168.1.21;"\
                     "echo ethaddr=[$ethaaddr] ...;"\
                     "echo ipaddr=[$ipaddr] ...;"\
                     "echo serverip=[$serverip] ...;"\
                     "tftp ${loadaddr} board${board_no}/uEnv.txt;"\
                     "env import -t ${loadaddr} ${filesize};"\
                     "tftp ${loadaddr} board${board_no}/vmlinuz-${uname_r};"\
                     "tftp ${fdtaddr} board${board_no}/am335x-boneblack.dtb;"\
                     "setenv debugargs setenv bootargs ${optargs} ${cape_disable} ${cape_enable} root=${mmcroot} rootfstype=${mmcrootfstype} ${cmdline} mem=1G@0x80000000 root=/dev/mmcblk1p1 console=ttyO0,115200n8 kgdb=ttyO0,115200 kgdboc=ttyO0,115200n8 kgdbwait rootwait;"\
                     "run debugargs;"\
                     "echo **** bootz:Start Kernel ****;"\
                     "bootz ${loadaddr} ${rdaddr}:${rdsize} ${fdtaddr};"\

#define KM_ETHACT_CPSW  "echo setup cpsw;"\
			"setenv ethact cpsw;"\
			"setenv eth2addr 00:00:00:00:00:1${board_no};"\
			"setenv ipaddr 192.168.1.1${board_no};"\
			"setenv serverip 192.168.1.21;"\
			"echo ethact: ${ethact};"\

#define KM_ETHACT_ENC	"echo setup enc1;"\
			"setenv ethact enc1.0;"\
			"setenv eth2addr 00:00:00:00:00:1${board_no};"\
			"setenv ipaddr 192.168.1.1${board_no};"\
			"setenv serverip 192.168.1.21;"\
			"echo ethact: ${ethact};"\

#define KM_SPI_ENV	"echo setup spi2ethernet env;"\
			"setenv ethact enc1.0;"\
			"setenv eth2addr 00:00:00:00:00:1${board_no};"\
			"setenv ipaddr 192.168.1.1${board_no};"\
			"setenv serverip 192.168.1.21;"\
			"echo ethact: ${ethact};"\

#define KM_SPI_TEST	"ping 192.168.1.1;"\


#define KM_SERIAL_ZIMAGE_DTB	"echo press ctrl+a then s --> select xmodem --> arch/arm/boot/zImage;"\
				"loadx 0x82000000 ;" \
				"echo press ctrl+a then s --> select xmodem --> arch/arm/boot/dtbs/am335x-beagleboneblack.dtb;"\
				"loadx 0x88000000;"\
				"setenv emmcargs setenv bootargs console=tty0 console=${console} ${optargs} ${cape_disable} ${cape_enable} root=/dev/mmcblk1p1 rootfstype=${mmcrootfstype} ${cmdline};"\
				"run emmcargs;"\
				"echo **** bootz:Start Kernel ****;"\
				"bootz 0x82000000  -  0x88000000;"\

#define KM_SERIAL_DTB	"setenv bootcmd "\
			"echo board_name=[$board_name] ...;"\
			"echo \"******* Booting From EMMC .... ********\";"\
			"echo board_name=[$board_name] ...;"\
			"setenv fdtfile am335x-boneblack.dtb;" \
			"setenv console ttyO0,115200n8;"\
			"load mmc 1:1 ${loadaddr} /boot/uEnv.txt;"\
			"env import -t ${loadaddr} ${filesize};" \
			"echo uname_r=[$uname_r] ...;"\
			"echo board_no=[$board_no] ...;"\
			"load mmc 1:1 ${loadaddr} /boot/vmlinuz-${uname_r};"\
			"echo press ctrl+a s --> select xmodem --> arch/arm/boot/dtbs/am335x-beagleboneblack.dtb;"\
			"loadx 0x88000000;"\
			"setenv emmcargs setenv bootargs console=tty0 console=${console} ${optargs} ${cape_disable} ${cape_enable} root=/dev/mmcblk1p1 rootfstype=${mmcrootfstype} ${cmdline};"\
			"run emmcargs;"\
			"echo **** bootz:Start Kernel ****;"\
			"bootz  ${loadaddr}  -  0x88000000;"\



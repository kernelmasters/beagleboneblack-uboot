
int multiboot(void);

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
                "setenv emmcargs setenv bootargs console=tty0 console=${console} ${optargs} ${cape_disable} ${cape_enable} root=/dev/mmcblk0p1 rootfstype=${mmcrootfstype} ${cmdline};"\
                "run emmcargs;"\
                "echo ****bootz:Start Kernel****;"\
                "bootz ${loadaddr} ${rdaddr}:${rdsize} ${fdtaddr};"\
                "echo ***END***;"\


#define KM_UENV_TFTP "setenv bootcmd "\
                     "echo board_name=[$board_name] ...;"\
                     "echo \"******* Booting From TFTP .... *********\";"\
                     "echo board_name=[$board_name] ...;"\
                     "load mmc 0:1 ${loadaddr} /boot/uEnv.txt;"\
                     "env import -t ${loadaddr} ${filesize};"\
                     "echo uname_r=[$uname_r] ...;"\
                     "echo board_no=[$board_no] ...;"\
                     "setenv fdtfile am335x-boneblack.dtb;"\
                     "setenv console ttyO0,115200n8;"\
                     "setenv ethaddr 00:00:00:00:00:1${board_no};"\
                     "setenv ipaddr 192.168.1.1${board_no};"\
                     "setenv serverip 192.168.1.21;"\
                     "echo ethaddr=[$ethaaddr] ...;"\
                     "echo ipaddr=[$ipaddr] ...;"\
                     "echo serverip=[$serverip] ...;"\
                     "tftp ${loadaddr} board${board_no}/vmlinuz-${uname_r};"\
                     "tftp ${fdtaddr} board${board_no}/am335x-boneblack.dtb;"\
                     "setenv mmcargs setenv bootargs console=tty0 console=${console} ${optargs} ${cape_disable} ${cape_enable} root=/dev/mmcblk0p1 rootfstype=${mmcrootfstype} ${cmdline};"\
                     "run mmcargs;"\
                     "echo **** bootz:Start Kernel ****;"\
                     "bootz ${loadaddr} ${rdaddr}:${rdsize} ${fdtaddr};"\

#define KM_UENV_TFTP_KGDB "setenv bootcmd "\
                     "echo board_name=[$board_name] ...;"\
                     "echo \"******* Booting From TFTP .... *********\";"\
                     "echo board_name=[$board_name] ...;"\
                     "load mmc 0:1 ${loadaddr} /boot/uEnv.txt;"\
                     "env import -t ${loadaddr} ${filesize};"\
                     "echo uname_r=[$uname_r] ...;"\
                     "echo board_no=[$board_no] ...;"\
                     "setenv fdtfile am335x-boneblack.dtb;"\
                     "setenv console ttyO0,115200n8;"\
                     "setenv ethaddr 00:00:00:00:00:1${board_no};"\
                     "setenv ipaddr 192.168.1.1${board_no};"\
                     "setenv serverip 192.168.1.21;"\
                     "echo ethaddr=[$ethaaddr] ...;"\
                     "echo ipaddr=[$ipaddr] ...;"\
                     "echo serverip=[$serverip] ...;"\
                     "tftp ${loadaddr} board${board_no}/vmlinuz-${uname_r};"\
                     "tftp ${fdtaddr} board${board_no}/am335x-boneblack.dtb;"\
                     "setenv debugargs setenv bootargs ${optargs} ${cape_disable} ${cape_enable} root=${mmcroot} rootfstype=${mmcrootfstype} ${cmdline} mem=1G@0x80000000 root=/dev/mmcblk0p1 console=ttyO0,115200n8 kgdb=ttyO0,115200 kgdboc=ttyO0,115200n8 kgdbwait rootwait;"\
                     "run debugargs;"\
                     "echo **** bootz:Start Kernel ****;"\
                     "bootz ${loadaddr} ${rdaddr}:${rdsize} ${fdtaddr};"\


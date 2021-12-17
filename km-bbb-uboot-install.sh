#!/bin/sh
#New
# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White

# Bold
NC='\033[0m'              # No Color
BBlack='\033[1;30m'       # Black
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green
BYellow='\033[1;33m'      # Yellow
BBlue='\033[1;34m'        # Blue
BPurple='\033[1;35m'      # Purple
BCyan='\033[1;36m'        # Cyan
BWhite='\033[1;37m'       # White

BRedU='\033[4;31m'         # Red


check_mmc () {
        FDISK=$(LC_ALL=C fdisk -l 2>/dev/null | grep "Disk ${media}:" | awk '{print $2}')

        if [ "x${FDISK}" = "x${media}:" ] ; then
                echo ""
                echo "I see..."
                echo ""
                echo "lsblk:"
                lsblk | grep -v sr0
                echo ""
                unset response
                echo -n "${Green}Are you 100% sure, on selecting [${media}] (y/n)?${NC} "
                read response
                if [ "x${response}" != "xy" ] ; then
                        exit
                fi
                echo ""
        else
                echo ""
                echo "${Red}Are you sure? I Don't see [${media}], here is what I do see...${NC}"
                echo ""
                echo "lsblk:"
                lsblk | grep -v sr0
                echo ""
                echo "${Red}Permission Denied. Run with sudo"
                exit
        fi

}

if [ -z "$1" ]; then
        echo  "${Green}script usage: sudo $(basename $0) [--mmc /dev/sdX]  [--scp <user_name> <ip_addr>] ${NC}"
fi


# parse commandline options
while [ ! -z "$1" ] ; do
        case $1 in
        -h|--help)
	        echo "script usage: sudo $(basename $0) [--mmc /dev/sdX] [--scp <user_name <ipaddr>]"
                ;;
        --mmc)
		media=$2
		check_mmc
		echo "${Green}-----------------------------${NC}"
		echo "${Red}MLO: dd if=MLO of=$2 count=2 seek=1 bs=128k${NC}"
		dd if=MLO of=${media} count=2 seek=1 bs=128k
		echo "${Green}-----------------------------${NC}"
		echo ""
		echo ""
		echo "${Green}-----------------------------${NC}"
		echo "${Red}u-boot.img: dd if=u-boot.img of=$2 count=4 seek=1 bs=384k${NC}"
		dd if=u-boot.img of=${media} count=4 seek=1 bs=384k
		echo "${Green}-----------------------------${NC}"
                ;;
        --scp)
                if [ $# -le 2 ] ; then
                        echo "pls enter user-name of board"
                        read username
                        echo "pls enter ipaddress of board"
                        read ipaddress
                        echo -e "${Purple} scp MLO u-boot.img  username@$ipaddress:~/install ${NC}"
                        scp MLO u-boot.img ${username}@${ipaddress}:~/install
                else
                        echo -e "${Purple} scp MLO u-boot.img $2@$3:~/install ${NC}"
                        scp MLO u-boot.img $2@$3:~/install
                fi
		;;
	esac
        shift
done

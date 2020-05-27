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

echo "${BRed}${BRedU}Step1: Setup u-boot Environment${NC}"
echo " "
echo "${Green}-----------------------------"
echo "${Red}Check /home/$USER/out folder:"
echo "${Green}-----------------------------${NC}"
if [ -d /home/$USER/out ] ; then
	echo "out folder is found"
	else
		echo "out folder is not found and create a out folder".
		echo "mkdir -p /home/$USER/out/"
		mkdir -p /home/$USER/out/
fi

echo "${Green}-----------------------------"
echo "${Red}Check No. Of cpu's"
export cpus=`cat /proc/cpuinfo | grep processor | wc -l`
echo "${Red}No. of CPUS:$cpus"
echo "${Green}-----------------------------${NC}"
echo "";echo""


echo "${BRed}${BRedU}Step2: u-boot configuration${NC}"
echo " "
echo "${Green}-----------------------------"
echo "${Red}Check .config file"
echo "${Green}-----------------------------${NC}"
if [ -f .config ] ; then
	echo ".config file is found. skip configuration"
	else
	echo ".config file not found. To configure the board"
        echo "make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- am335x_evm_defconfig"
        make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- am335x_evm_defconfig
fi
echo "";echo""

echo "${BRed}${BRedU}Step3: u-boot compilation${NC}"
echo " "
echo "${Red}Build uboot source code. Check No. Of Cpu's"
export cpus=`cat /proc/cpuinfo | grep processor | wc -l`
echo "${Red}No. of CPUS:$cpus"
echo "${Green}-----------------------------${NC}"
echo "${Red}make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j${cpus}${NC}"
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j${cpus}
echo "";echo""

echo "${BRed}${BRedU}Step4: Install MLO and u-boot.img:${NC}"
echo " "
echo "${Green}-----------------------------"
echo "${Red} Copy MLO & U-boot.img in to ~/out folder"
echo "${Green}-----------------------------${NC}"
echo "cp ./MLO ./u-boot.img /home/$USER/out/"
cp ./MLO ./u-boot.img /home/$USER/out/
echo "";echo""

# parse commandline options
while [ ! -z "$1" ] ; do
        case $1 in
        -h|--help)
                echo "${Red}./km_build_uboot.sh [--board <value>]"
                ;;
        --board)
		echo "scp /home/$USER/out/MLO  /home/$USER/out/u-boot.img km@192.168.1.1$2:~/" 
		scp /home/$USER/out/MLO  /home/$USER/out/u-boot.img km@192.168.1.1$2:~/ 
                ;;
        esac
        shift
done

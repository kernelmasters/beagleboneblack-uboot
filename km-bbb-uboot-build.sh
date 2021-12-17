#!/bin/sh

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
echo "${Red}Check Cross Compiler Toolcahin:"
echo "${Green}-----------------------------${NC}"

if [ -d "/home/$USER/opt/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/bin" ] ; then
        echo "cross compile tool chain found."
else
        echo "cross compile tool chain not found. Install ..."
        mkdir ~/opt
        cd ~/opt
        wget http://142.93.218.33/elinux/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf.tar.xz
        tar -xvf gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf.tar.xz
        rm -r gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf.tar.xz
        export PATH=/home/$USER/opt/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/bin:$PATH
        sh -c "echo 'export PATH=/home/$USER/opt/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/bin:'$'PATH' >>  /home/$USER/.bashrc"
        temp=$USER
        sudo sh -c "echo 'export PATH=/home/$temp/opt/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/bin:'$'PATH' >>  /root/.bashrc"
	cd -
        echo "cross_compile tool chain install successfully"
fi

echo "${Green}-----------------------------"
echo "${Red}Check No. Of cpu's"
export cpus=`cat /proc/cpuinfo | grep processor | wc -l`
echo "${Red}No. of CPUS:$cpus"
echo "${Green}-----------------------------${NC}"
echo "";echo""

echo "${BRed}${BRedU}Check debian packages${NC}"
echo ""

dpkg -s bison > /dev/zero
if [ $? -eq 0 ]; then
    echo "bison Package  is installed!"
else
    echo "bison Package  is NOT installed!"
    sudo apt install bison
fi
dpkg -s flex > /dev/zero
if [ $? -eq 0 ]; then
    echo "flex Package  is installed!"
else
    echo "flex Package  is NOT installed!"
    sudo apt install flex
fi

echo "${BRed}${BRedU}Step2: U-boot source code configuration${NC}"
echo ""
echo "${Green}-----------------------------"
echo "${Red}Check .config file:"
echo "${Green}-----------------------------${NC}"
if [ -f .config ] ; then
        echo "${Red}~/.config file found.[U-boot Configuration has DONE]"
        echo "If you want to configure the u-boot again type \"yes\" otherwise \"no\" to skip u-boot configuration${NC}"
        read  temp
        if [ $temp = "yes" ];then
        echo "${Purple}make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig${NC}"
        make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig
        fi
else
        echo "${Green}~/.config file not found [U-boot Configuration has not done]."
        echo "u-boot confgiuration starts .....${NC}"
        x=5
        while [ "$x" -ne 0 ]; do
                echo -n "$x "
                x=$(($x-1))
                sleep 1
        done
        echo "${Purple}make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- am335x_evm_defconfig${NC}"
        make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- am335x_evm_defconfig
        if [ -f .config ] ; then
                echo "${Green}U-boot Configuration has done successfully"
        else
                echo "${Red}U-boot Configuration is not done. exit here"
                exit 0
        fi
fi
echo "";echo ""


echo "${BRed}${BRedU}Step3: u-boot compilation${NC}"
echo " "
echo "${Red}Build uboot source code"
echo "${Red}make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j${cpus}${NC}"
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j${cpus}
echo "";echo""

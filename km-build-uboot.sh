#!/bin/sh

echo "-----------------------------"
echo "Check ~/out folder:"
echo "-----------------------------"

if [ -d ~/out ] ; then
	echo "out folder is found"
		if [ -d ~/out/bbb-uboot ];then
			echo "bbb-uboot folder also found"
		else
			mkdir -p ~/out/bbb-uboot
		fi
	else
		echo "out folder is not found."
		mkdir -p ~/out/bbb-uboot
fi

echo "-----------------------------"
echo "Check .config file:"
echo "-----------------------------"

if [ -f .config ] ; then
	echo ".config file found. skip configuration"
	else
	echo ".config file not found. configure the board"
        make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- O=~/out/bbb-uboot am335x_evm_defconfig
fi


echo "-----------------------------"
echo "Build uboot source code. Check No. Of Cpu's"
export cpus=`cat /proc/cpuinfo | grep processor | wc -l`
echo "No. of CPUS:$cpus"
echo "-----------------------------"
echo "make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j${cpus}"
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- O=~/out/bbb-uboot -j${cpus}

